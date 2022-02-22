摘抄自：https://www.cnblogs.com/wuyepeng/p/9737583.html

服务端：
　　服务器端先初始化socket，然后与端口绑定，对端口进行监听，调用accept阻塞，等待客户端连接。
　　socket() -> bind() -> listen() -> accept()
客户端：
　　客户端先初始化socket，然后与服务端连接，服务端监听成功则连接建立完成
　　socket() -> connect()

socket的大概过程是这样的：
	服务端先创建一个套接字，端口绑定，对端口进行监听，调用accpet阻塞，等待客户端连接。客户端创建一个套接字，然后通过三次握手完成tcp连接后服务端accpet返回重新建立一个套接字代表返回客户端的tcp连接，
(在accpet成功返回前有一个要注意的是server会有两个队列，一个存放完成三次握手的一个是未完成三次握手的，每次accpet会从完成三次握手的队列中取出一个并一直建立TCP连接，此时才能算是真正的连接成功)，
完成上面的步骤后即可以开始数据的传输了，数据传输结束后再调用close关闭连接

此外再说一下select函数在server和client双向通信中的重要作用：
	网络编程的过程中，经常会遇到许多阻塞的函数，网络编程时使用的recv, recvfrom、connect函数都是阻塞的函数，当函数不能成功执行的时候，程序就会一直阻塞在这里，无法执行下面的代码。
selcet函数是一个轮循函数，即当循环询问文件节点，可设置超时时间，超时时间到了就跳过代码继续往下执行，就像我们下面的第一个程序一样，如果不注释掉server的send那么如果server不想client发送消
息则进程就会停顿在此处等待server发送无法执行下面的代码，无法接受client发送过来的消息，第二个程序就对此进行的改进，在程序中引入了select当超时后就会跳过当前代码，执行下一步不会一直阻塞。（poll和epoll是对select的改进）


TCP编程的服务器端一般步骤是：                                                        	UDP编程的服务器端一般步骤是：
1、创建一个socket，用函数socket()； 　　                                            1、创建一个socket，用函数socket()； 　
2、设置socket属性，用函数setsockopt();  * 可选 *                                    2、设置socket属性，用函数setsockopt(); * 可选 *
3、绑定IP地址、端口等信息到socket上，用函数bind(); 　                               3、绑定IP地址、端口等信息到socket上，用函数bind();
4、开启监听，用函数listen()； 　　                                                  4、循环接收数据，用函数recvfrom(); 
5、接收客户端上来的连接，用函数accept()；                                           5、关闭网络连接；
6、收发数据，用函数send()和recv()，或者read()和write(); 　　
7、关闭网络连接； 　　
8、关闭监听；



TCP编程的客户端一般步骤是：	                                                         　 UDP编程的客户端一般步骤是：
1、创建一个socket，用函数socket()；                                                 1、创建一个socket，用函数socket()； 
2、设置socket属性，用函数setsockopt();  * 可选 *　　                                2、设置socket属性，用函数setsockopt();  * 可选 *
3、绑定IP地址、端口等信息到socket上，用函数bind();  * 可选 *　                      3、绑定IP地址、端口等信息到socket上，用函数bind();  * 可选 *
4、设置要连接的对方的IP地址和端口等属性； 　　                                      4、设置对方的IP地址和端口等属性; 
5、连接服务器，用函数connect()；                                                    5、发送数据，用函数sendto();
6、收发数据，用函数send()和recv()，或者read()和write(); 　　                        6、关闭网络连接；
7、关闭网络连接；




基本的局域网聊天
局域网TCP服务端：
实现的功能是client到server的半双工通信，server只能接受接收client发送过来的消息，但是不能向client发送消息。

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>
#define PORT 7000
#define QUEUE 20//连接请求队列
int conn;
void thread_task()
{
}
 
int main()
{
   //printf("%d\n",AF_INET);//IPv4协议
    printf("%d\n",SOCK_STREAM);//字节流套接字
    int ss = socket(AF_INET, SOCK_STREAM, 0);//若成功则返回一个sockfd（套接字描述符）
    //printf("%d\n",ss);
    struct sockaddr_in server_sockaddr;//一般是储存地址和端口的。用于信息的显示及存储使用
    /*设置 sockaddr_in 结构体中相关参数*/
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);//将一个无符号短整型数值转换为网络字节序，即大端模式(big-endian)　
    //printf("%d\n",INADDR_ANY);
    //INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。
    //一般来说，在各个系统中均定义成为0值。
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);//将主机的无符号长整形数转换成网络字节顺序。　
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
 
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    ///成功返回非负描述字，出错返回-1
    conn = accept(ss, (struct sockaddr*)&client_addr, &length);
    //如果accpet成功，那么其返回值是由内核自动生成的一个全新描述符，代表与所返回客户的TCP连接。
    //accpet之后就会用新的套接字conn
    if( conn < 0 )
    {
        perror("connect");
        exit(1);
    }
 
    char buffer[1024];
    //创建另外一个线程
    //std::thread t(thread_task);
    //t.join();
    //char buf[1024];
    //主线程
    while(1)
    {
    //这里把send注释掉了，所以这个程序中server只能是接收client端的数据并能给client发送数据，即使不注释掉也没用，因为没有对是否有数据传入和传入
　　　　　//进行判断所以按照下面的代码这样写，每次都要先让server输入后才能输出client传过来的数据，若是server不输入则程序无法向下走就没有client发送过来的输出，
　　　　　//而且每次显示也只能是一行，这样显示就全是错的了，所以就需要select和FD_ISSET的判断了
        // memset(buf, 0 ,sizeof(buf));
        // if(fgets(buf, sizeof(buf),stdin) != NULL) {
        //     send(conn, buf, sizeof(buf), 0);   
        // }
 
        memset(buffer, 0 ,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);//从TCP连接的另一端接收数据。
        /*该函数的第一个参数指定接收端套接字描述符；
        第二个参数指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
        第三个参数指明buf的长度；
        第四个参数一般置0*/
        if(strcmp(buffer, "exit\n") == 0)//如果没有收到TCP另一端发来的数据则跳出循环不输出
        {
            break;
        }
        printf("%s", buffer);//如果有收到数据则输出数据
        //必须要有返回数据， 这样才算一个完整的请求
        send(conn, buffer, len , 0);//向TCP连接的另一端发送数据。
    }
    close(conn);//因为accpet函数连接成功后还会生成一个新的套接字描述符，结束后也需要关闭
    close(ss);//关闭socket套接字描述符
    return 0;
}




局域网TCP客户端：

/*局域网TCP客户端*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#define MYPORT  7000
#define BUFFER_SIZE 1024
 
int main()
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);
 
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    //127.0.0.1是本地预留地址
    //连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
 
    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
 
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {/*每次读取一行，读取的数据保存在buf指向的字符数组中，成功，则返回第一个参数buf；*/
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        if(strcmp(sendbuf,"exit\n")==0)
            break;
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
        fputs(recvbuf, stdout);
 
        memset(sendbuf, 0, sizeof(sendbuf));//接受或者发送完毕后把数组中的数据全部清空（置0）
        memset(recvbuf, 0, sizeof(recvbuf));
    }
    close(sock_cli);
    return 0;
}
/*在TCP三次握手完成后会进入等待连接队列，等待服务端调用accpet与之建立连接，这时候是server端调用accept跟客户端建立
通信，客户端并不需要调用accpet，因为有很多个客户端要跟服务端建立连接，这时候服务端就会有一个队列，对已经经过三次握
手的才可以建立连接（类似缓存信息），这个是由服务端来确认的，客户端并不知道什么时候服务端才能跟它建立连接，在服务端
没有调用accept与之连接或者还未排队到它，只能是一直等待，直到服务端准备好了才能跟客户端建立连接，所以主动权在服务端*/




客户端服务端双向异步聊天源码
以上的局域网聊天应用有一个很重要的缺点， 服务器只能显示客户端发送的消息， 却无法给客户端发送消息， 这个很尴尬；

通过使用C中的select()函数， 实现一个异步聊天工具：

异步聊天服务端代码：

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#define PORT 7000
#define QUEUE 20
 
int main()
{
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    //printf("%d\n",INADDR_ANY);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
 
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    ///成功返回非负描述字，出错返回-1
    int conn = accept(ss, (struct sockaddr*)&client_addr, &length);
    /*没有用来存储accpet返回的套接字的数组，所以只能实现server和单个client双向通信*/
    if( conn < 0 )
    {
        perror("connect");
        exit(1);
    }
    while(1)
    {
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(conn, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < conn)
            maxfd = conn;
        /*设置超时时间*/
        tv.tv_sec = 5;//设置倒计时
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            printf("select出错，客户端程序退出\n");
            break;
        }
        else if(retval == 0)
        {
            printf("服务端没有任何输入信息，并且客户端也没有信息到来，waiting...\n");
            continue;
        }
        else
        {
            /*客户端发来了消息*/
            if(FD_ISSET(conn,&rfds))
            {
                char buffer[1024];   
                memset(buffer, 0 ,sizeof(buffer));
                int len = recv(conn, buffer, sizeof(buffer), 0);
                if(strcmp(buffer, "exit\n") == 0) break;
                printf("%s", buffer);
                //send(conn, buffer, len , 0);把数据回发给客户端
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds))
            {
                char buf[1024];
                fgets(buf, sizeof(buf), stdin);
                //printf("you are send %s", buf);
                send(conn, buf, sizeof(buf), 0);   
            }
        }
    }
    close(conn);
    close(ss);
    return 0;
}




异步聊天客户端代码：

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#define MYPORT  7000
#define BUFFER_SIZE 1024
int main()
{
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
 
    ///定义sockfd
    sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip
 
    //连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
 
    while(1){
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(sock_cli, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < sock_cli)
            maxfd = sock_cli;
        /*设置超时时间*/
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            printf("select出错，客户端程序退出\n");
            break;
        }
        else if(retval == 0)
        {
            printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
            continue;
        }
        else
        {
            /*服务器发来了消息*/
            if(FD_ISSET(sock_cli,&rfds))
            {
                char recvbuf[BUFFER_SIZE];
                int len;
                len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
                printf("%s", recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds))
            {
                char sendbuf[BUFFER_SIZE];
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }
 
    close(sock_cli);
    return 0;
}




局域网内服务端和有限个客户端聊天源码
以上的局域网聊天只能支持一个用户， 我们还要改改， 必须是支持多用户的聊天室：

局域网TCP2人聊天服务端代码

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <thread>
#define PORT 7000
#define QUEUE 20
int ss;
struct sockaddr_in client_addr;
socklen_t length = sizeof(client_addr);
int conns[2] = {};//定义了一个容量为2的数组来存放套接字，所以server最多只能跟2个client通信
int z = 0;
void thread_fn()
{
    //成功返回非负描述字，出错返回-1
    int conn = accept(ss, (struct sockaddr*)&client_addr, &length);
    if( conn < 0 )
    {
        perror("connect");
        exit(1);
    }
    //把连接保存到临时数组中;
    conns[z] = conn;
    z++;
 
    fd_set rfds;
    struct timeval tv;//linux编程中，如果用到计时，可以用struct timeval获取系统时间
    int retval, maxfd;
    while(1)
    {
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(conn, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < conn)
        {
            maxfd = conn;
        }
        /*设置超时时间*/
        tv.tv_sec = 5;//5秒
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            printf("select出错，客户端程序退出\n");
            break;
        }
        else if(retval == 0)
        {
            printf("服务端没有任何输入信息，并且客户端也没有信息到来，waiting...\n");
            continue;
        }
        else
        {
            /*客户端发来了消息*/
            if(FD_ISSET(conn,&rfds))//判断conn是否在rfds中如果在返回非零，不再返回0
            {
                char buffer[1024];   
                memset(buffer, 0 ,sizeof(buffer));//把buffer中的所有值赋值为0，即清空buffer
                int len = recv(conn, buffer, sizeof(buffer), 0);//把接收到的数据存放于buffer中
                if(strcmp(buffer, "exit\n") == 0)//如果接受到的是空的，即没有收到任何信息
                    break;
                printf("%s", buffer);
                //send(conn, buffer, len , 0);把数据回发给客户端
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds))
            {
                char buf[1024];
                fgets(buf, sizeof(buf), stdin);//每次读取一行数据存放在buf中
                //printf("you are send %s", buf);
                for(int i=0; i<z; i++)
                {
                    send(conns[i], buf, sizeof(buf), 0);
                }   
            }
        }
    }
    close(conn);
}
void thread_select(int conn)
{
     
}
int main()
{
    ss = socket(AF_INET, SOCK_STREAM, 0);//SOCK_STREAM即tcp协议，AF_INET是IPv4套接字
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    //printf("%d\n",INADDR_ANY);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(ss, QUEUE) == -1)
    {
        perror("listen");
        exit(1);
    }
    std::thread t(thread_fn);//因为创建了两个线程所以只能连接两个client
    std::thread t1(thread_fn);//这里把收发数据都存放在thread_fn中，所以创建一个这样的线程就能使得server能多连接一个server
    t.join();
    t1.join();
    close(ss);
    return 0;
}




局域网TCP2人聊天客户端代码：

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#define MYPORT  7000
#define BUFFER_SIZE 1024
int main()
{
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
 
    ///定义sockfd
    sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip
 
    //连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
 
    while(1){
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(sock_cli, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < sock_cli)
            maxfd = sock_cli;
        /*设置超时时间*/
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1)
        {
            printf("select出错，客户端程序退出\n");
            break;
        }else if(retval == 0)
        {
            printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
            continue;
        }
        else
        {
            /*服务器发来了消息*/
            if(FD_ISSET(sock_cli,&rfds))
            {
                char recvbuf[BUFFER_SIZE];
                int len;
                len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
                printf("%s", recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds))
            {
                char sendbuf[BUFFER_SIZE];
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }
 
    close(sock_cli);
    return 0;
}



完美异步聊天服务端和客户端源码
以上的多客户聊天不是很好， 因为只允许两个客户端连接， 体验非常差， 如果支持无限个客户端聊天的话那该多好啊， 哈哈， 这个也是可以的， 我们只要使用c＋＋的list即可， 它是可以自增的数组(其实算是链表)， 引用 头文件<list>即可：

无限个客户聊天的 服务端代码：

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include <thread>
#include <list>
 
#define PORT 7000
#define IP "127.0.0.1"
 
int s;
struct sockaddr_in servaddr;
socklen_t len;
std::list<int> li;//用list来存放套接字，没有限制套接字的容量就可以实现一个server跟若干个client通信
 
void getConn()
{
    while(1)
    {
        int conn = accept(s, (struct sockaddr*)&servaddr, &len);
        li.push_back(conn);
        printf("%d\n", conn);
    }
}
 
void getData()
{
    struct timeval tv;
    tv.tv_sec = 10;//设置倒计时时间
    tv.tv_usec = 0;
    while(1)
    {
        std::list<int>::iterator it;
        for(it=li.begin(); it!=li.end(); ++it)
        {           
            fd_set rfds;   
            FD_ZERO(&rfds);
            int maxfd = 0;
            int retval = 0;
            FD_SET(*it, &rfds);
            if(maxfd < *it)
            {
                maxfd = *it;
            }
            retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
            if(retval == -1)
            {
                printf("select error\n");
            }
            else if(retval == 0)
            {
                //printf("not message\n");
            }
            else
            {
                char buf[1024];
                memset(buf, 0 ,sizeof(buf));
                int len = recv(*it, buf, sizeof(buf), 0);
                printf("%s", buf);
            }
        }
        sleep(1);
 
    }
}
 
void sendMess()
{
    while(1)
    {
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);
        //printf("you are send %s", buf);
        std::list<int>::iterator it;
        for(it=li.begin(); it!=li.end(); ++it)
        {
            send(*it, buf, sizeof(buf), 0);
        }
    }
}
 
int main()
{
    //new socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr(IP);
    if(bind(s, (struct sockaddr* ) &servaddr, sizeof(servaddr))==-1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(s, 20) == -1)
    {
        perror("listen");
        exit(1);
    }
    len = sizeof(servaddr);
 
    //thread : while ==>> accpet
    std::thread t(getConn);
    t.detach();//detach的话后面的线程不同等前面的进程完成后才能进行，如果这里改为join则前面的线程无法判断结束，就会
    //一直等待，导致后面的线程无法进行就无法实现操作
    //printf("done\n");
    //thread : input ==>> send
    std::thread t1(sendMess);
    t1.detach();
    //thread : recv ==>> show
    std::thread t2(getData);
    t2.detach();
    while(1)//做一个死循环使得主线程不会提前退出
    {
 
    }
    return 0;
}
/*这个跟前面的不一样的地方是，把获得连接套接字getConn和发送信息sendMess和接收信息getData放在三个函数中，创建
的三个线程分别对应处理三个函数，就可以使得server能跟若干个client通信*/

问：为什么要创建三个线程去处理三个函数，单个线程并不可以吗，多线程和单线程处理起来有什么不同？

答：首先，这里用到多线程的目的是为了提高处理能力，减少等待时间，多线程可以并发执行，即可以同时对三个函数进行处理，处理起来会快很多。这里也是可以用单线程来处理的，但是单线程每次只能做一件事情，不能同时去获得连接套接字、发送消息、接收消息，这样在做其中一件事情的时候其他的两件事情就要等待，这样处理时间会比多线程慢很多。多线程可以及时的响应，单线程不能及时响应。



无限个客户端连接的客户端代码：

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#define MYPORT  7000
#define BUFFER_SIZE 1024
int main()
{
    int sock_cli;
    fd_set rfds;
    struct timeval tv;
    int retval, maxfd;
 
    ///定义sockfd
    sock_cli = socket(AF_INET,SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip
 
    //连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
 
    while(1){
        /*把可读文件描述符的集合清空*/
        FD_ZERO(&rfds);
        /*把标准输入的文件描述符加入到集合中*/
        FD_SET(0, &rfds);
        maxfd = 0;
        /*把当前连接的文件描述符加入到集合中*/
        FD_SET(sock_cli, &rfds);
        /*找出文件描述符集合中最大的文件描述符*/   
        if(maxfd < sock_cli)
            maxfd = sock_cli;
        /*设置超时时间*/
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        /*等待聊天*/
        retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
        if(retval == -1){
            printf("select出错，客户端程序退出\n");
            break;
        }else if(retval == 0){
            printf("客户端没有任何输入信息，并且服务器也没有信息到来，waiting...\n");
            continue;
        }else{
            /*服务器发来了消息*/
            if(FD_ISSET(sock_cli,&rfds)){
                char recvbuf[BUFFER_SIZE];
                int len;
                len = recv(sock_cli, recvbuf, sizeof(recvbuf),0);
                printf("%s", recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }
            /*用户输入信息了,开始处理信息并发送*/
            if(FD_ISSET(0, &rfds)){
                char sendbuf[BUFFER_SIZE];
                fgets(sendbuf, sizeof(sendbuf), stdin);
                send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }
 
    close(sock_cli);
    return 0;
}


