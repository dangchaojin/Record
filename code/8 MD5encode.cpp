/********************************************************************
思路：定义一个字符串，生成消息摘要，程序运行后要求输入字符串，
再生成一个消息摘要,将两个消息摘要作比较，相等则输入正确
（因为hash函数不可逆）
*********************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>   //molloc所在头文件  后可用new申请空间
#include "openssl/md5.h"
//包含md5函数的库为/usr/lib/libcrypto.a(.so)，编译时使用 -lcrypto
/*
int main()
{
    char *raw_pwd = "123456";
    unsigned char *raw_md_raw = (unsigned char *)malloc(10);
    unsigned char *raw_md;

    raw_md = MD5((const unsigned char *)raw_pwd, strlen(raw_pwd), raw_md_raw);
	//MD5((const unsigned char*)raw_pwd.c_str(), raw_pwd.size(), raw_md_raw);

    char *pwd = (char *)malloc(10);
    std::cout << "please enter password:" << std::endl;
    std::cin >> pwd;

    unsigned char *md;
    md = MD5((const unsigned char *)pwd, strlen(pwd), NULL);

    std::cout << std::endl;
    std::cout << "原始密码:" << raw_pwd << std::endl;
    std::cout << "原始密码的信息摘要:" << raw_md << std::endl;
    std::cout << "输入密码:" << pwd << std::endl;
    std::cout << "输入密码的信息摘要:" << md << std::endl;


    if(*raw_md == *md)
    {
        std::cout << "correct!" << std::endl;
    }
    else
    {
        std::cout << "wrong!" << std::endl;
    }

    return 0;
}
*/
/***********************************************************
int MD5_Init(MD5_CTX *c);
//初始化MD5上下文结构

int MD5_Update(MD5_CTX *c, const void *data, size_t len);
//刷新MD5，将文件连续数据分片放入进行MD5刷新。

int MD5_Final(unsigned char *md, MD5_CTX *c);
//产生最终的MD5数据

unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);
//直接产生字符串的MD5
//第三个参数可以不指定，置NULL,程序会自动分配地址空间,但是上述程序两次调用该函数
//后一次的结果会覆盖前一次（两次使用了同样的空间）所以第一次分配了新的字符串 raw_md_raw
*************************************************************/



//*************************文件MD5码****************************************

#define MAXDATABUFF 1024
#define MD5LENTH 16

int main(int arc, char *arv[])
{
    //string、ifstream、ios均是在std中
    std::string strFilePath = arv[1];
    std::ifstream ifile(strFilePath.c_str(),std::ios::in|std::ios::binary);    //打开文件
    unsigned char MD5result[MD5LENTH];
    do
    {
        if (ifile.fail())   //打开失败不做文件MD5
        {
            std::cout << "open file failure!so only display string MD5!" << std::endl;
            break;    
        }    
        MD5_CTX md5_ctx;    
        MD5_Init(&md5_ctx);
    
        char DataBuff[MAXDATABUFF];
        while(!ifile.eof())
        {
            ifile.read(DataBuff,MAXDATABUFF);   //读文件
            int length = ifile.gcount();
            if(length)
            {
                MD5_Update(&md5_ctx,DataBuff,length);   //将当前文件块加入并更新MD5
            }
        }
        MD5_Final(MD5result,&md5_ctx);  //获取MD5
        std::cout<<"file MD5:"<<std::endl;
        for(int i = 0; i < MD5LENTH; i++)  //将MD5以16进制输出
            std::cout << std::hex << (int)MD5result[i];          //hex是在标准库中
        std::cout << std::endl;
    }while(false); 
    
    MD5((const unsigned char*)strFilePath.c_str(),strFilePath.size(),MD5result);    //获取字符串MD5
    std::cout << "string MD5:" << std::endl;
    for(int i = 0; i < MD5LENTH; i++)
        std::cout << std::hex << (int)MD5result[i];
    std::cout << std::endl;
    return 0;
}

//                  ./a.out ./hello.txt
//                   两次运行结果对比
//****************************************/
