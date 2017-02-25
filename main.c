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
 * D2:D7 = LCD (ONLY WHEN LCD OPERATIONS ARE EXECUTED, WHICH NEVER HAPPENS DURING SORTING)
 * C3:C4 = I2C/RTC
 * A6:A7 = external oscillator
 * D0    = motor which controls upper disc rotation
 * A0:A1 = motor which controls fan rotation (A2 = high for clockwise, A1 = high for counterclockwise)
 * A2    = microservo which controls chamber entrance door
 * A3    = microservo which controls chamber exit door
 * A4:A5 = stepper motor which controls the rotating containers (C0 = DIRECTION SIGNAL(0 = clockwise, 1 = counterclockwise) , C1 = STEP SIGNAL)
 * C0    = laser emitter
 * C1    = laser detector
 * C2+C5 = ultrasonic distance sensor #1 (detects if bottle is coming into chamber), 2 = trig, 5 = echo
 * E0:E1 = ultrasonic distance sensor #2 (on the entrance of the chamber), 0 = trig, 1 = echo
 * C6:C7 = ultrasonic distance sensor #3 (on the exit of the chamber), 6 = trig, 7 = echo
 */

/*
 * THINGS TO NOTE:
 * __delay_ms(0.1 * number of milliseconds)
 * __delay_ms(100 * number of seconds)  
 */


void main(void) {
    
    //configuring all ports
    TRISA = 0x00;   //All output mode
    TRISC = 0x00;   //All output mode
    TRISD = 0x00;   //All output mode
    TRISE = 0x00;   //All output mode
    TRISB = 0xFF;   //All input mode
    //Initialize ports to 0
    LATA = 0x00; 
    LATB = 0x00; 
    LATC = 0x00;
    LATE = 0b111;
    
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
    
    //initialize the angular position of the containers (clockwise from the chamber exit)
    eskaNoCapPos = 270;
    eskaCapPos = 0; //initially, container which holds Eska with cap is directly underneath the chamber exit 
    yopNoCapPos = 180;
    yopCapPos = 90;
    
    //initial conditions of the machine
    //NEED TO STILL SET THE CONTAINERS SUCH THAT THEY ARE IN THEIR INITIAL POSITION
    setChamberEntrance(OPEN); 
    setChamberExit(CLOSED);
    
    
    T0CONbits.T08BIT = 1; //use 8 bit timer/counter
    T0CONbits.T0CS = 0; //timer mode
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2=1; //extend increment time period
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS0=1;
    T0CONbits.TMR0ON = 1; //turn on the timer
      
    while(1){
        LATCbits.LC0=1;
        __delay_ms(1000);
         LATCbits.LC0=0;
        __delay_ms(1000);
    }
   
  
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
                detectBottle(); //set the detectedBottle variable
                rotateContainers();
                setChamberExit(OPEN);
                __delay_ms(BOTTLE_FALL_IN_CONTAINER);
                setChamberExit(CLOSED);
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
    //INT1IF is the interrupt flag -  gets set as 1 if a key was pressed
    if(INT1IF){ 
        int keypress = (PORTB & 0xF0) >> 4; //find out which key on the keypad was pressed 
        dispCorrectScreen(keypress); //display the correct screen, update currentScreen variable, and update machineState variable if "start" selected
        INT1IF = 0;     //Clear flag bit
    }
}



