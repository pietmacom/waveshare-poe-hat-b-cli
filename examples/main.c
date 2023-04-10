#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include "OLED_Driver.h"
#include "OLED_GUI.h"
#include <time.h>
#include "CPU.h"
void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    
    FAN_OFF;
    
    DEV_ModuleExit();
    exit(0);
}
int cpu_num;                
char Eth0_IP[20],Wlan0_IP[20];
char temp[20];
char t[10];
uint32_t temp_m;


int main(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    DEV_ModuleInit();
    
    OLED_Init();
    GUI_Init(OLED_WIDTH, OLED_HEIGHT);
    GUI_Clear();
    
    FAN_ON;
    DEV_Delay_ms(20);
    FAN_OFF;
    
    while(1){
    temp_m = Get_CPU_Temperature(temp);//Get temperature
    
    Get_IP(Eth0_IP,Wlan0_IP);//Get IP
    
    POE_HAT_Display(0,Eth0_IP,temp_m, 38);
    
    DEV_Delay_ms(10000);
    }
	//System Exit
	DEV_ModuleExit();
	return 0;
	
}

