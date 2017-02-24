#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "configBits.h"
#include "machineStates.h"
#include "macros.h"


void rotateMicroServo(int *pin, int angle, int direction){
    if (direction == CLOCKWISE){
        
    }
    else if (direction == COUNTERCLOCKWISE){
        
    }
}

void setUpperDiscRotation(int on){
    LATDbits.LD0=on;
}


void setFanRotation(int direction){
    if (direction==CLOCKWISE){
        //turn the fan off for 0.1 seconds before switching directions (to prevent circuit from giving an unexpected reaction)
        if(LATAbits.LA1==1 && LATAbits.LA2==0){
            LATAbits.LA1=0;
            LATAbits.LA2=0;
            __delay_ms(100*0.1);
        }
        LATAbits.LA1=0;
        LATAbits.LA2=1;
    }
    else if (direction==COUNTERCLOCKWISE){
        //turn the fan off for 0.1 seconds before switching directions (to prevent circuit from giving an unexpected reaction)
        if(LATAbits.LA1==0 && LATAbits.LA2==1){
            LATAbits.LA1=0;
            LATAbits.LA2=0;
            __delay_ms(100*0.1);
        }
        LATAbits.LA1=1;
        LATAbits.LA2=0;
    }
    else if (direction==OFF){
        LATAbits.LA1=0;
        LATAbits.LA2=0;
    }
}

//code to control microservo motor, pin D3
void setChamberEntrance(int open){
    if (open==OPEN){
        //move motor clockwise
        int i;
        for (i=0;i<500;i++){
            LATDbits.LD3=1;
            __delay_ms(0.1*0.7);
            LATDbits.LD3=0;
            __delay_ms(0.1*(20-0.7));
        }
    }
    else if (open==CLOSED){
        //move motor counterclockwise
        int i;
        for (i=0;i<500;i++){
            LATDbits.LD3=1;
            __delay_ms(0.1*1.7);
            LATDbits.LD3=0;
            __delay_ms(0.1*(20-1.7)); 
        }
    }
}

//code to control microservo motor, pin D4 
void setChamberExit(int open){
     if (open==OPEN){
        //move motor counterclockwise 
        
    }
    else if (open==CLOSED){
        //move motor clockwise
        
    }
}

//code to control stepper motor
void transferToContainer(){
    //how to set the step size
    //how to set the speed
    LATCbits.LC0=0;                                                                                             ;
    int i;
    for (i=0;i<4096;i++){
        LATCbits.LC1=1;
        __delay_ms(100*0.001); 
        LATCbits.LC1=0;
        __delay_ms(100*0.001);
    }
}
