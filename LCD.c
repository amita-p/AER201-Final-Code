#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "configBits.h"
#include "machineStates.h"
#include "macros.h"



void initLCD(void) {
    __delay_ms(150);
    lcdInst(0b00110011);
    lcdInst(0b00110010);
    lcdInst(0b00101000);
    lcdInst(0b00001111);
    lcdInst(0b00000110);
    lcdInst(0b00000001);
    __delay_ms(150);
}

void lcdInst(char data) {
    RS = 0;
    lcdNibble(data);
}

void putch(char data){
    RS = 1;
    lcdNibble(data);
}

void lcdNibble(char data){
    // Send of 4 most sig bits, then the 4 least sig bits (MSD,LSD)
    char temp = data & 0xF0;
    LATD = LATD & 0x0F;
    LATD = temp | LATD;

    E = 0;
    __delay_us(LCD_DELAY);
    E = 1;    
    __delay_us(LCD_DELAY);
    
    data = data << 4;
    
    temp = data & 0xF0;
    LATD = LATD & 0x0F;
    LATD = temp | LATD;

    E = 0;
    __delay_us(LCD_DELAY);
    E = 1;
    __delay_us(LCD_DELAY);
}

void lcdWrite(char *string1, char *string2){
    clearLCD();
    printf(string1);
    lcdInst(LCD_CURSOR_LINE2);
    printf(string2);
    lcdInst(LCD_CURSOR_OFF);
}


void clearLCD(){
    lcdInst(LCD_CLEAR);
    lcdInst(LCD_CURSOR_BACK);
}

void dispMainMenu(){
    clearLCD();
    lcdWrite("1:START 11:31:45", "2:LOGS  22/02/17");
}

void dispSortingScreen(){
    clearLCD();
    lcdWrite("SORTING...","0:47");
}


void dispLogsMenu(){
    clearLCD();
    lcdWrite("1:DOWNLOAD 3:ESC","2:DISP LOGS");   
}

void dispLogsDisplayMenuScreen(){
    clearLCD();
    lcdWrite("1:SCROLLDN 3:ESC","2:SCROLLUP");   
}

void dispDownloadToPCScreen(){
    clearLCD();
    lcdWrite("TRANSFERRING...","");
}

void dispTerminationScreen(){
    clearLCD();
    lcdWrite("TERMINATED","3: ESC");
}

//this function gets called whenever a key is pressed and is given the key which was pressed 
//it displays the correct screen on the LCD in response to the key which was pressed
//it updates the currentScreen variable
//if "start" is selected, it updates the machineState variable to to SORTING and starts the timer
void dispCorrectScreen(int key){
    //at any time, if 3 is pressed on the keypad, you go back to the main menu unless sorting is taking place
    if (key == 2 && machineState != SORTING){
        dispMainMenu();
        currentScreen = MAIN_MENU;
    }
    else if (currentScreen == MAIN_MENU){
        if (key == 0){
            machineState = SORTING;
            dispSortingScreen();
            currentScreen = SORTING_SCREEN;
            T0CONbits.TMR0ON = 1; //turn on the timer
        }
        else if (key == 1){
            dispLogsMenu();
            currentScreen = LOGS_MENU;
        }
       
    }
    else if (currentScreen == LOGS_MENU){
        if (key == 0){
            dispDownloadToPCScreen();
            currentScreen = DOWNLOAD_TO_PC_SCREEN;
        }
        else if (key == 1){
            dispLogsDisplayMenuScreen();
            currentScreen = LOGS_DISPLAY_MENU_SCREEN;
        }
    }
       
}


