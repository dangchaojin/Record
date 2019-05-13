#include <iostream>
#include <stdio.h>
#include <string.h>

#include <openssl/md5.h>

int main()
{
    char tmpbuf[64] = {0};
    char myip[48] = "0:0:0:0:0";
    char* renewCh = NULL;
    FILE *fpRead;

    char* command1 = (char*)"ifconfig eth0 | grep 'inet'";
    char* command2 = (char*)"ifconfig eth0 | grep 'ether'";
    fpRead = popen(command2, "r");
    fgets(tmpbuf, 64, fpRead);
    if(fpRead != NULL)
        pclose(fpRead);
    renewCh = strstr(tmpbuf, "ether");
    if(renewCh)
    {
        strncpy(myip, renewCh + sizeof("ether")-1, 48);
        myip[48] = '\0';
    }
    std::cout << "------eth0 ether = " << myip << std::endl; 

    return 0;
}
