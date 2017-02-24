/*
 * File:   main.c
 * Author: amita
 *
 * Created on February 22, 2017, 12:46 AM
 */

#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "configBits.h"
#include "machineStates.h" //machine state names
#include "I2C.h"
#include "macros.h"
#include "controlSensors.h"
#include "controlMotors.h"

/*
 PIN ASSIGNMENTS:
 * PORT B = KEYPAD
 * PORT D = LCD (ONLY WHEN LCD OPERATIONS ARE EXECUTED, WHICH NEVER HAPPENS DURING SORTING)
     *  D0    = motor which controls upper disc rotation
     *  A1:A2 = motor which controls fan rotation (A2 = high for clockwise, A1 = high for counterclockwise)
     *  D3    = microservo which controls chamber entrance door
     *  D4    = microservo which controls chamber exit door
     *  C0:C1 = stepper motor which controls the rotating containers (C0 = DIRECTION SIGNAL(0 = clockwise, 1 = counterclockwise) , C1 = STEP SIGNAL)
 * 
 */


void main(void) {
  
    //configuring all ports
    TRISA = 0x00;   //All output mode
    TRISC = 0x00;   //All output mode
    TRISD = 0x00;   //All output mode
    TRISB = 0xFF;   //All input mode
    //Initialize ports to 0
    LATA = 0x00; 
    LATB = 0x00; 
    LATC = 0x00;
    ADCON1 = 0xFF;  //Set PORTB to be digital instead of analog default
    
    initLCD(); //initialize the LCD

    INT1IE = 1;     //INT1 external interrupt enable (located in INTCON3 register), INTCON3 register handles external interrupt priorities 
    ei();           //Enable all interrupts
       
    //initial conditions of the machine
    currentScreen = MAIN_MENU;
    machineState = STANDBY;
    dispMainMenu();
    
    //initialize sorting information to zero
    numBottles = 0;
    numEskaNoCap = 0;
    numEskaCap = 0;
    numYopNoCap = 0;
    numYopCap = 0;
    numSeconds = 0;
    
    
    //Main loop for the entire robot
    while(1){
        di();
        ei();
        if (machineState==SORTING){
            setChamberEntrance(OPEN); 
            setLaserEmitter(ON);
            setUpperDiscRotation(ON); //upper disk rotates indefinitely as long as the machine is sorting
            if (bottleComing()){ 
                setFanRotation(COUNTERCLOCKWISE); 
                numBottles++;
                __delay_ms(BOTTLE_FALL_IN_CHAMBER); //wait for bottle to fall in the chamber 
                setChamberEntrance(CLOSED); //close chamber entrance door if a bottle is inside
                detectBottle();
                transferToContainer();
            }
            else{
                setFanRotation(CLOCKWISE);
            }
        }
    }
    return;
}

//keypressed interrupt gets called whenever a keypad key is pressed
void interrupt keypressed(void) {
    //INT1IF is the interrupt flag -  gets set as 1 is a key was pressed
    if(INT1IF){ 
        int keypress = (PORTB & 0xF0) >> 4; //find out which key on the keypad was pressed 
        dispCorrectScreen(keypress); //display the correct screen, update currentScreen variable, and update machineState variable if "start" selected
        INT1IF = 0;     //Clear flag bit
    }
}



