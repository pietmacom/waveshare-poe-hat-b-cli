#include "CPU.h"


#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

float g_cpu_used;           


uint32_t Get_CPU_Temperature(char *ch_temp)
{
    uint32_t i,temp;
    int fd;
    char value_str[20];
    fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
    if (fd < 0) {
        return -1;
    }
    for(i=0;; i++) {
        if (read(fd, &value_str[i], 1) < 0) {
            return -1;
        }
        if(value_str[i] < '0' || value_str[i] > '9') {
            // printf("value_str = %d\r\n",value_str[i]);
            break;
        }
        // printf("%c",value_str[i]);
       
    }
    printf("\r\n\r\n");
    temp = 0;
    for (i = 0; value_str[i] >= '0' && value_str[i] <= '9'; ++i)  
    {  
        temp = 10 * temp + (value_str[i] - '0');
        ch_temp[i] = value_str[i];
    }  
    close(fd);
    // printf("temp = %d\r\n",temp);
    return temp;
}



void Get_IP(char *eth0,char *wlan0)
{
    struct ifaddrs * ifAddrStruct=NULL;
    struct ifaddrs * ifa=NULL;
    void * tmpAddrPtr=NULL;
    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) // check it is IP4
		{
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            //printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
            if(ifa->ifa_name[0] == 'e' && ifa->ifa_name[1] == 't')
                strcpy(eth0,addressBuffer);
            if(ifa->ifa_name[0] == 'w' && ifa->ifa_name[1] == 'l')
                strcpy(wlan0,addressBuffer);
        }
		else if (ifa->ifa_addr->sa_family == AF_INET6) // check it is IP6
		{
            // is a valid IP6 Address
            tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            // printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
    if (ifAddrStruct!=NULL)
	{
		freeifaddrs(ifAddrStruct);
	}


}

