/*****************************************************************************
* | File      	:	OLED_Driver.c
* | Author      :   Waveshare team
* | Function    :	0.9inch OLED using SSD1306 control
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2018-04-17
* | Info        :   Basic version
******************************************************************************/
#include "OLED_Driver.h"
#include <stdio.h>
#include "string.h"

/*******************************************************************************
function:
		Common register initialization
*******************************************************************************/
static void OLED_InitReg()
{
	OLED_WriteReg(0xAE);

	OLED_WriteReg(0x40);//---set low column address
	OLED_WriteReg(0xB0);//---set high column address

	OLED_WriteReg(0xC8);//-not offset

	OLED_WriteReg(0x81);
	OLED_WriteReg(0xff);

	OLED_WriteReg(0xa1);

	OLED_WriteReg(0xa6);

	OLED_WriteReg(0xa8);
	OLED_WriteReg(0x1f);

	OLED_WriteReg(0xd3);
	OLED_WriteReg(0x00);

	OLED_WriteReg(0xd5);
	OLED_WriteReg(0xf0);

	OLED_WriteReg(0xd9);
	OLED_WriteReg(0x22);

	OLED_WriteReg(0xda);
	OLED_WriteReg(0x02);

	OLED_WriteReg(0xdb);
	OLED_WriteReg(0x49);

	OLED_WriteReg(0x8d);
	OLED_WriteReg(0x14);
	
	OLED_WriteReg(0xaf);
}

void OLED_Clear(void)
{
    char Column,Page;
    for(Page = 0; Page < OLED_Page; Page++) {
        OLED_WriteReg(0xb0 + Page);    //Set page address
        OLED_WriteReg(0x00);           //Set display position - column low address
        OLED_WriteReg(0x10);           //Set display position - column high address
        for(Column = 0; Column < OLED_Column; Column++)
            OLED_WriteData(0xff);
    }
}

void OLED_Init(void)
{
    OLED_InitReg();
	
	OLED_Clear();
}

void OLED_SendBuf(UBYTE *Buf)
{
    char Column,Page;
    UBYTE *ptr = Buf;
    for(Page = 0; Page < OLED_Page; Page++) {
        OLED_WriteReg(0xb0 + Page);
        OLED_WriteReg(0x00);
        OLED_WriteReg(0x10);
        for(Column = 0; Column < OLED_Column; Column++) {
            OLED_WriteData(*ptr);
            ptr++;
        }
    } 
}
