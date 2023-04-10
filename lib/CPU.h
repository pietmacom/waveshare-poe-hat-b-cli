#ifndef __CPU_H
#define __CPU_H

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>
#include <string.h>   
#define MAXBUFSIZE 1024
#define WAIT_SECOND 3   //暂停时间，单位为“秒”  
#include <unistd.h>
#include <fcntl.h>
#include "DEV_Config.h"
typedef  struct occupy        
{  
    char name[20];      
    unsigned int user;  
    unsigned int nice;  
    unsigned int system;
    unsigned int idle;  
} CPU_OCCUPY ;  

typedef struct PACKED         
{
    char name[20]; 
    long total; 
    char name2[20];
    long free;            
}MEM_OCCUPY;

void cal_occupy(CPU_OCCUPY *, CPU_OCCUPY *); 
void get_occupy(CPU_OCCUPY *); 
void get_mem_occupy(MEM_OCCUPY *) ;
float get_io_occupy();
void get_disk_occupy(char ** reused);
void getCurrentDownloadRates(long int * save_rate);


uint32_t Get_CPU_Temperature(char *ch_temp);
float get_g_cpu_used();
void Get_IP(char *eth0,char *wlan0);
uint32_t Get_CPU_Temperature(char *ch_temp);
#endif  
	 