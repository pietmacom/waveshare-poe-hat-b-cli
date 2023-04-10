#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include "OLED_Driver.h"
#include "OLED_GUI.h"

void  Handler(int signo) {
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();
    exit(0);
}

int main(int argc, char *argv[]) {
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    if(argc == 1) {
	printf("Allowed option are:\n\n");
	printf("\t%s fan on\n", argv[0]);
	printf("\t%s fan off\n", argv[0]);
	printf("\n");
	printf("\t%s oled \"row1\"\n", argv[0]);
	printf("\t%s oled \"row1\" \"row2\"\n", argv[0]);
	printf("\t%s oled \"row1\" \"row2\" \"row3\"\n", argv[0]);
	printf("\t%s oled \"row1\" \"row2\" \"row3\" \"row4\"\n", argv[0]);
	printf("\n");
	printf("Display width: %i\n", OLED_WIDTH);
	printf("Display height: %i\n", OLED_HEIGHT);
	printf("Fan: On/Off\n");
	printf("\n");
	return 0;
    }

    DEV_ModuleInit();
    if (strcmp(argv[1], "fan") == 0) {
        if (strcmp(argv[2], "on") == 0) {
            FAN_ON;
            printf("Fan turned on!\n");
        } else if (strcmp(argv[2], "off") == 0) {
            FAN_OFF;
            printf("Fan turned off!\n");
        }

    } else if (strcmp(argv[1], "oled") == 0) {
        DEV_ModuleInit();
        OLED_Init();
        GUI_Init(OLED_WIDTH, OLED_HEIGHT);
        GUI_Clear();
        if(argc == 2) {
	    printf("= cleared =\n");

        } else if(argc == 3) {
	    GUI_DisString_EN(0 , 0, argv[2], &Font20, FONT_BACKGROUND, WHITE);
	    printf("row 1: %s\n", argv[2]);

	} else if(argc == 4) {
	    GUI_DisString_EN(0 , 0, argv[2], &Font16, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 16, argv[3], &Font16, FONT_BACKGROUND, WHITE);
	    printf("row 1: %s\n", argv[2]);
	    printf("row 2: %s\n", argv[3]);

	} else if(argc == 5) {
	    GUI_DisString_EN(0 , 0, argv[2], &Font12, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 10, argv[3], &Font12, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 20, argv[4], &Font12, FONT_BACKGROUND, WHITE);
	    printf("row 1: %s\n", argv[2]);
	    printf("row 2: %s\n", argv[3]);
	    printf("row 3: %s\n", argv[4]);
	    
        } else if(argc == 6) {
	    GUI_DisString_EN(0 , 0, argv[2], &Font8, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 8, argv[3], &Font8, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 16, argv[4], &Font8, FONT_BACKGROUND, WHITE);
	    GUI_DisString_EN(0 , 24, argv[5], &Font8, FONT_BACKGROUND, WHITE);
	    printf("row 1: %s\n", argv[2]);
	    printf("row 2: %s\n", argv[3]);
	    printf("row 3: %s\n", argv[4]);
	    printf("row 4: %s\n", argv[5]);
        } else {
	    printf("To many rows!\n");
        }
        GUI_Display();
    }
    DEV_ModuleExit();
}
