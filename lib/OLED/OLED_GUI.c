/*****************************************************************************
* | File      	:	OLED_GUI.c
* | Author      :   Waveshare team
* | Function    :	Drawing
* | Info        :	
*----------------
* |	This version:   V1.0
* | Date        :   2018-04-17
* | Info        :   Basic version
******************************************************************************/
#include "OLED_GUI.h"
#include "DEV_Config.h"
#include <stdio.h>
#include "string.h"

Paint paint;
UBYTE Buffer[OLED_WIDTH * OLED_HEIGHT / 8];

void GUI_Init(UWORD width, UWORD height)
{
	paint.rotate = ROTATE_0;
    paint.width = width;
    paint.height = height;
}

void GUI_Clear(void) 
{
	memset(Buffer, 0x00, sizeof(Buffer));
}

void GUI_Display(void)
{
	OLED_SendBuf(Buffer);
}
    
static void GUI_SetBuf(UWORD Xpoint, UWORD Ypoint, UWORD Color)
{
	if(Color == WHITE){
		Buffer[Xpoint + Ypoint / 8 * OLED_Column] |= (0x01 << (Ypoint % 8));
	}else{
		Buffer[Xpoint + Ypoint / 8 * OLED_Column] |= (0x00 << (Ypoint % 8));
	}
}

/********************************************************************************
function:	Coordinate conversion
********************************************************************************/
static void GUI_Swop(UWORD Point1, UWORD Point2)
{
    UWORD Temp;
    Temp = Point1;
    Point1 = Point2;
    Point2 = Temp;
}

/********************************************************************************
function:	Draw_Point(Xpoint, Ypoint) Fill the color
parameter:
	Xpoint		:   The x coordinate of the point
	Ypoint		:   The y coordinate of the point
	Color		:   Set color
	Dot_Pixel	:	point size
********************************************************************************/
void GUI_DrawPoint(UWORD Xpoint, UWORD Ypoint, UWORD Color,
                   DOT_PIXEL Dot_Pixel, DOT_STYLE DOT_STYLE)
{
    if(Xpoint > paint.width || Ypoint > paint.height) {
		printf("GUI_DrawPoint Input exceeds the normal display range\r\n");
        return;
    }
    uint16_t XDir_Num ,YDir_Num;
    if(DOT_STYLE == DOT_STYLE_DFT) {
        for(XDir_Num = 0; XDir_Num < 2 * Dot_Pixel - 1; XDir_Num++) {
            for(YDir_Num = 0; YDir_Num < 2 * Dot_Pixel - 1; YDir_Num++) {
				GUI_SetBuf(Xpoint + XDir_Num - Dot_Pixel + 1, Ypoint + YDir_Num - Dot_Pixel + 1, Color);
            }
        }
    } else {
        for(XDir_Num = 0; XDir_Num <  Dot_Pixel; XDir_Num++) {
            for(YDir_Num = 0; YDir_Num <  Dot_Pixel; YDir_Num++) {
                GUI_SetBuf(Xpoint + XDir_Num + 1, Ypoint + YDir_Num + 1, Color);
            }
        }
    }
}

/********************************************************************************
function:	Draw a line of arbitrary slope
parameter:
	Xstart ：Starting x point coordinates
	Ystart ：Starting x point coordinates
	Xend   ：End point x coordinate
	Yend   ：End point y coordinate
	Color  ：The color of the line segment
********************************************************************************/
void GUI_DrawLine(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                  UWORD Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel)
{
    if(Xstart > paint.width || Ystart > paint.height ||
       Xend > paint.width || Yend > paint.height) {
		   printf("GUI_DrawLine Input exceeds the normal display range\r\n");
        return;
    }

    if(Xstart > Xend)
        GUI_Swop(Xstart,Xend);
    if(Ystart > Yend)
        GUI_Swop(Ystart,Yend);

    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;
    int32_t dx =(int32_t)Xend -(int32_t)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    int32_t dy =(int32_t)Yend -(int32_t)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

    // Increment direction, 1 is positive, -1 is counter;
    int32_t XAddway = Xstart < Xend ? 1 : -1;
    int32_t YAddway = Ystart < Yend ? 1 : -1;

    //Cumulative error
    int32_t Esp = dx + dy;
    int8_t Line_Style_Temp = 0;

    for(;;) {
        Line_Style_Temp++;
        //Painted dotted line, 2 point is really virtual
        if(Line_Style == LINE_DOTTED && Line_Style_Temp %3 == 0) {
            //printf("LINE_DOTTED\r\n");
            GUI_DrawPoint(Xpoint, Ypoint, OLED_BACKGROUND, Dot_Pixel, DOT_STYLE_DFT);
            Line_Style_Temp = 0;
        } else {
            GUI_DrawPoint(Xpoint, Ypoint, Color, Dot_Pixel, DOT_STYLE_DFT);
        }
        if(2 * Esp >= dy) {
            if(Xpoint == Xend) break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if(2 * Esp <= dx) {
            if(Ypoint == Yend) break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}

/********************************************************************************
function:	Draw a rectangle
parameter:
	Xstart ：Rectangular  Starting x point coordinates
	Ystart ：Rectangular  Starting x point coordinates
	Xend   ：Rectangular  End point x coordinate
	Yend   ：Rectangular  End point y coordinate
	Color  ：The color of the Rectangular segment
	Filled : Whether it is filled--- 1 solid 0：empty
********************************************************************************/
void GUI_DrawRectangle(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,
                       UWORD Color, DRAW_FILL Filled, DOT_PIXEL Dot_Pixel )
{
    if(Xstart > paint.width || Ystart > paint.height ||
       Xend > paint.width || Yend > paint.height) {
		   printf("Input exceeds the normal display range\r\n");
        return;
    }

    if(Xstart > Xend)
        GUI_Swop(Xstart,Xend);
    if(Ystart > Yend)
        GUI_Swop(Ystart,Yend);

    UWORD Ypoint;
    if(Filled ) {
        for(Ypoint = Ystart; Ypoint < Yend; Ypoint++) {
            GUI_DrawLine(Xstart, Ypoint, Xend, Ypoint, Color , LINE_SOLID, Dot_Pixel);
        }
    } else {
        GUI_DrawLine(Xstart, Ystart, Xend, Ystart, Color , LINE_SOLID, Dot_Pixel);
        GUI_DrawLine(Xstart, Ystart, Xstart, Yend, Color , LINE_SOLID, Dot_Pixel);
        GUI_DrawLine(Xend, Yend, Xend, Ystart, Color , LINE_SOLID, Dot_Pixel);
        GUI_DrawLine(Xend, Yend, Xstart, Yend, Color , LINE_SOLID, Dot_Pixel);
    }
}

/********************************************************************************
function:	Use the 8-point method to draw a circle of the
				specified size at the specified position.
parameter:
	X_Center  ：Center X coordinate
	Y_Center  ：Center Y coordinate
	Radius    ：circle Radius
	Color     ：The color of the ：circle segment
	Filled    : Whether it is filled: 1 filling 0：Do not
********************************************************************************/
void GUI_DrawCircle(UWORD X_Center, UWORD Y_Center, UWORD Radius,
                    UWORD Color, DRAW_FILL  Draw_Fill , DOT_PIXEL Dot_Pixel)
{
    if(X_Center > paint.width || Y_Center >= paint.height) {
		printf("GUI_DrawCircle Input exceeds the normal display range\r\n");
        return;
    }

    //Draw a circle from(0, R) as a starting point
    int16_t XCurrent, YCurrent;
    XCurrent = 0;
    YCurrent = Radius;

    //Cumulative error,judge the next point of the logo
    int16_t Esp = 3 -(Radius << 1 );

    int16_t sCountY;
    if(Draw_Fill == DRAW_FULL) {
        while(XCurrent <= YCurrent ) { //Realistic circles
            for(sCountY = XCurrent; sCountY <= YCurrent; sCountY ++ ) {
                GUI_DrawPoint(X_Center + XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //1
                GUI_DrawPoint(X_Center - XCurrent, Y_Center + sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //2
                GUI_DrawPoint(X_Center - sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //3
                GUI_DrawPoint(X_Center - sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //4
                GUI_DrawPoint(X_Center - XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //5
                GUI_DrawPoint(X_Center + XCurrent, Y_Center - sCountY, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //6
                GUI_DrawPoint(X_Center + sCountY, Y_Center - XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );             //7
                GUI_DrawPoint(X_Center + sCountY, Y_Center + XCurrent, Color, DOT_PIXEL_DFT, DOT_STYLE_DFT );
            }
            if(Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 *(XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    } else { //Draw a hollow circle
        while(XCurrent <= YCurrent ) {
            GUI_DrawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //1
            GUI_DrawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //2
            GUI_DrawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //3
            GUI_DrawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //4
            GUI_DrawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //5
            GUI_DrawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //6
            GUI_DrawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //7
            GUI_DrawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color, Dot_Pixel, DOT_STYLE_DFT );             //0

            if(Esp < 0 )
                Esp += 4 * XCurrent + 6;
            else {
                Esp += 10 + 4 *(XCurrent - YCurrent );
                YCurrent --;
            }
            XCurrent ++;
        }
    }
}

/********************************************************************************
function:	Show English characters
parameter:
	Xpoint           ：X coordinate
	Ypoint           ：Y coordinate
	Acsii_Char       ：To display the English characters
	Font             ：A structure pointer that displays a character size
	Color_Background : Select the background color of the English character
	Color_Foreground : Select the foreground color of the English character
********************************************************************************/
void GUI_DisChar(UWORD Xpoint, UWORD Ypoint, const char Acsii_Char,
                 sFONT* Font, UWORD Color_Background, UWORD Color_Foreground)
{
    UWORD Page, Column;

    if(Xpoint > paint.width || Ypoint > paint.height) {
		printf("GUI_DisChar Input exceeds the normal display range\r\n");
        return;
    }

    uint32_t Char_Offset =(Acsii_Char - ' ') * Font->Height *(Font->Width / 8 +(Font->Width % 8 ? 1 : 0));
    const unsigned char *ptr = &Font->table[Char_Offset];

    for(Page = 0; Page < Font->Height; Page ++ ) {
        for(Column = 0; Column < Font->Width; Column ++ ) {

            //To determine whether the font background color and screen background color is consistent
            if(FONT_BACKGROUND == Color_Background) { //this process is to speed up the scan
                if(*ptr &(0x80 >>(Column % 8)))
                    GUI_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
            } else {
                if(*ptr &(0x80 >>(Column % 8))) {
                    GUI_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Foreground, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                } else {
                    GUI_DrawPoint(Xpoint + Column, Ypoint + Page, Color_Background, DOT_PIXEL_DFT, DOT_STYLE_DFT);
                }
            }
            //One pixel is 8 bits
            if(Column % 8 == 7)
                ptr++;
        }/* Write a line */
        if(Font->Width % 8 != 0)
            ptr++;
    }/* Write all */
}

/********************************************************************************
function:	Display the string
parameter:
	Xstart           ：X coordinate
	Ystart           ：Y coordinate
	pString          ：The first address of the English string to be displayed
	Font             ：A structure pointer that displays a character size
	Color_Background : Select the background color of the English character
	Color_Foreground : Select the foreground color of the English character
********************************************************************************/
void GUI_DisString_EN(UWORD Xstart, UWORD Ystart, const char * pString,
                      sFONT* Font,UWORD Color_Background, UWORD Color_Foreground )
{
    UWORD Xpoint = Xstart;
    UWORD Ypoint = Ystart;

    if(Xstart > paint.width || Ystart > paint.height) {
		printf("GUI_DisString_EN Input exceeds the normal display range\r\n");
        return;
    }

    while(* pString != '\0') {
        //if X direction filled , reposition to(Xstart,Ypoint),Ypoint is Y direction plus the height of the character
        if((Xpoint + Font->Width ) > paint.width ) {
            Xpoint = Xstart;
            Ypoint += Font->Height;
        }

        // If the Y direction is full, reposition to(Xstart, Ystart)
        if((Ypoint  + Font->Height ) > paint.height ) {
            Xpoint = Xstart;
            Ypoint = Ystart;
        }
        GUI_DisChar(Xpoint, Ypoint, * pString, Font, Color_Background, Color_Foreground);

        //The next character of the address
        pString ++;

        //The next word of the abscissa increases the font of the broadband
        Xpoint += Font->Width;
    }
}

/********************************************************************************
function:	Display the bit map,1 byte = 8bit = 8 points
parameter:
	pMap   : Pointing to the picture
note:
	This function is suitable for bitmap, because a 16-bit data accounted for 16 points
********************************************************************************/
void GUI_Disbitmap(UBYTE *pMap)
{
   UWORD Column,Page;
   UBYTE *ptr = pMap;
    for(Page = 0; Page < OLED_Page; Page++) {
        for(Column = 0; Column < OLED_Column; Column++){
			Buffer[Column + Page * 128] = *ptr;
			ptr++;
		}           
    } 
}
UBYTE FAN_MODE  ;
void POE_HAT_Display(UBYTE *WIFI_IP,UBYTE *Eth0_IP,UDOUBLE TEMP, UBYTE FAN_TEMP)
{
    UBYTE t[10];
    GUI_Clear();
    if(Eth0_IP[0] != 0){
        GUI_DisString_EN(0 , 0, "eth :", &Font12, FONT_BACKGROUND, WHITE);
        GUI_DisString_EN(35 , 0, Eth0_IP, &Font12, FONT_BACKGROUND, WHITE);
    }else if(WIFI_IP != 0){
        GUI_DisString_EN(0 , 0, "wlan:", &Font12, FONT_BACKGROUND, WHITE);
        GUI_DisString_EN(35 , 0, WIFI_IP, &Font12, FONT_BACKGROUND, WHITE);
    }else{
        GUI_DisString_EN(0 , 0, "eth :", &Font12, FONT_BACKGROUND, WHITE);
        GUI_DisString_EN(35 , 0, Eth0_IP, &Font12, FONT_BACKGROUND, WHITE);
    }
    
    GUI_DisString_EN(0 , 20, "Temp:", &Font12, FONT_BACKGROUND, WHITE);
    printf("TEMP = %d\r\n",TEMP);
    if( TEMP/1000>=100){
        t[0] = (TEMP/1000/100)%10+'0';
        t[1] = (TEMP/1000/10)%10+'0';
        t[2] = (TEMP/1000/1)%10+'0';
        t[3] = '\0';
    }else if(TEMP/1000 >=10){
        t[0] = (TEMP/1000/10)%10+'0';
        t[1] = (TEMP/1000/1)%10+'0';
        t[2] = '.';
        t[3] = (TEMP/100/1)%10+'0';
        t[4] = '\0';
    }else if(TEMP/1000 >0){
        t[0] = TEMP/1000/1%10+'0';
        t[2] = '.';
        t[1] = TEMP/100/1%10+'0';
        t[3] = TEMP/10/1%10+'0';
        t[4] = '\0';
    }else {
        t[0] = TEMP/1000/1%10+'0';
        t[2] = '.';
        t[1] = TEMP/100/1%10+'0';
        t[3] = TEMP/10/1%10+'0';
        t[4] = '\0';
    }
    
    GUI_DisString_EN(35 , 20, t, &Font12, FONT_BACKGROUND, WHITE);
    GUI_DisString_EN(75 , 20, "FAN:", &Font12, FONT_BACKGROUND, WHITE);
    if(TEMP/1000 >= FAN_TEMP){
        FAN_ON;
        FAN_MODE = 1;
    }else if(TEMP/1000 < FAN_TEMP-2){
        FAN_OFF;
        FAN_MODE = 0;
    }
    
    if(FAN_MODE == 1){
        GUI_DisString_EN(105 , 20, "ON", &Font12, FONT_BACKGROUND, WHITE);
        
    }else{
        GUI_DisString_EN(105 , 20, "OFF", &Font12, FONT_BACKGROUND, WHITE);
    }
    GUI_Display();
}

