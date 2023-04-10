/*****************************************************************************
* | File      	:	OLED_Driver.h
* | Author      :   Waveshare team
* | Function    :	0.9inch OLED using SSD1306 control
* | Info        :	
*----------------
* |	This version:   V1.0
* | Date        :   2018-04-17
* | Info        :   Basic version
******************************************************************************/
#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H		

#include "DEV_Config.h"

//Type macro definition
#define	UBYTE		uint8_t
#define	UWORD		uint16_t
#define	UDOUBLE		uint32_t

//I2C
#define IIC_CMD        0X00
#define IIC_RAM        0X40
#define OLED_WriteReg(Reg) I2C_SET_Addr(0x3C);\
                           I2C_Write_Byte(IIC_CMD, Reg)
#define OLED_WriteData(Data)    I2C_SET_Addr(0x3C);\
                                I2C_Write_Byte(IIC_RAM, Data)

//Define the full screen height length of the display
#define OLED_WIDTH      128
#define OLED_HEIGHT     32
#define OLED_Column		OLED_WIDTH
#define OLED_Page		OLED_HEIGHT / 8

/*
end
******************************************************************************/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SendBuf(UBYTE *Buf);

#endif  
	 
	 



