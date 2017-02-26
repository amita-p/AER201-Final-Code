 	
/* LCD.h  */
#ifndef LCD_H
#define LCD_H


// Command set for Hitachi 44780U LCD display controller
#define LCD_CLEAR           0b01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0b1100
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE2    0b11000000

//LCD Control Registers
#define RS          LATDbits.LATD2          
#define E           LATDbits.LATD3
#define	LCD_PORT    LATD   //On LATD[4,7] to be specific
#define LCD_DELAY   250

//functions from LCD.c
void initLCD(void);
void lcdInst(char data);
void lcdNibble(char data);
void lcdWrite(char *string1, char *string2);
void clearLCD();
void dispMainMenu();
void dispSortingScreen();
void dispLogsMenu();
void dispLogsDisplayMenuScreen();
void dispDownloadToPCScreen();
void dispCorrectScreen(int key);

#endif	/* LCD_H */