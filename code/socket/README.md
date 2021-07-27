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