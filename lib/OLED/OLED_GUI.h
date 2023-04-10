/*****************************************************************************
* | File      	:	OLED_GUI.h
* | Author      :   Waveshare team
* | Function    :	Drawing
* | Info        :	
*----------------
* |	This version:   V1.0
* | Date        :   2018-04-17
* | Info        :   Basic version
******************************************************************************/
#ifndef __OLED_GUI_H
#define __OLED_GUI_H		

#include "OLED_Driver.h"
#include "../Fonts/fonts.h"

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

typedef struct Paint_t {
    int width;
    int height;
    int rotate;
} Paint;

//dot pixel
typedef enum{
	DOT_PIXEL_1X1  = 1,		// dot pixel 1 x 1
	DOT_PIXEL_2X2  , 		// dot pixel 2 X 2 
	DOT_PIXEL_3X3  ,		// dot pixel 3 X 3
	DOT_PIXEL_4X4  ,		// dot pixel 4 X 4
	DOT_PIXEL_5X5  , 		// dot pixel 5 X 5
	DOT_PIXEL_6X6  , 		// dot pixel 6 X 6
	DOT_PIXEL_7X7  , 		// dot pixel 7 X 7
	DOT_PIXEL_8X8  , 		// dot pixel 8 X 8
}DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

//dot Fill style
typedef enum{
	DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
	DOT_FILL_RIGHTUP  , 		// dot pixel 2 X 2 
}DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

//olid line and dotted line
typedef enum{
	LINE_SOLID = 0,
	LINE_DOTTED,
}LINE_STYLE;

//DRAW Internal fill
typedef enum{
	DRAW_EMPTY = 0,
	DRAW_FULL,
}DRAW_FILL;

//time
typedef struct{
	uint16_t Year;  //0000
	uint8_t  Month; //1 - 12
	uint8_t  Day;   //1 - 30
	uint8_t  Hour;  //0 - 23
	uint8_t  Min;   //0 - 59 	
	uint8_t  Sec;   //0 - 59
}DEV_TIME;
extern DEV_TIME sDev_time;

//Defines commonly used colors for the display
#define WHITE     1
#define BLACK     0
#define OLED_BACKGROUND		BLACK
#define FONT_BACKGROUND		BLACK
#define FONT_FOREGROUND	    WHITE

/**
 *Macro definition variable name
 *
**/

//Drawing
void GUI_Init(UWORD width, UWORD height);
void GUI_Clear(void);
void GUI_Display(void);

void GUI_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void GUI_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel);
void GUI_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel );
void GUI_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius, UWORD Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel );


//Display string
void GUI_DisChar(UWORD Xstart, UWORD Ystart, const char Acsii_Char, sFONT* Font, UWORD Color_Background, UWORD Color_Foreground);
void GUI_DisString_EN(UWORD Xstart, UWORD Ystart, const char * pString, sFONT* Font, UWORD Color_Background, UWORD Color_Foreground );

//pic
void GUI_Disbitmap(UBYTE *pMap);

void POE_HAT_Display(UBYTE *WIFI_IP,UBYTE *Eth0_IP,UDOUBLE TEMP, UBYTE FAN_TEMP);
#endif  
	 
	 



