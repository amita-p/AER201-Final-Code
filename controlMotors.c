#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "configBits.h"
#include "machineStates.h"
#include "macros.h"


//angular speed is in degrees per second
//direction is either CLOCKWISE OR COUNTERCLOCKWISE
void rotateStepperMotor(int degrees,int angularSpeed ,int direction){
    int numSteps= (degrees/360.0)*4096;
    double delay = 360.0/(4096*angularSpeed); //number of seconds per pulse 
    if (direction == CLOCKWISE){
        LATCbits.LC0 = 0; 
    }
    else if (direction == COUNTERCLOCKWISE){
        LATCbits.LC0 = 1; 
    }
    for (int i=0;i<numSteps;i++){
        LATCbits.LC1 = 1;
        //__delay_ms(100*0.5*delay); 
        LATCbits.LC1 = 0;
        //__delay_ms(100*0.5*delay);
    } 
}

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
        if(LATAbits.LA0==1 && LATAbits.LA1==0){
            LATAbits.LA0=0;
            LATAbits.LA1=0;
            __delay_ms(100*0.1);
        }
        LATAbits.LA0=0;
        LATAbits.LA1=1;
    }
    else if (direction==COUNTERCLOCKWISE){
        //turn the fan off for 0.1 seconds before switching directions (to prevent circuit from giving an unexpected reaction)
        if(LATAbits.LA0==0 && LATAbits.LA1==1){
            LATAbits.LA0=0;
            LATAbits.LA1=0;
            __delay_ms(100*0.1);
        }
        LATAbits.LA0=1;
        LATAbits.LA1=0;
    }
    else if (direction==OFF){
        LATAbits.LA0=0;
        LATAbits.LA1=0;
    }
}

//code to control microservo motor, pin A2
void setChamberEntrance(int open){
    if (open==OPEN){
        //move motor clockwise
        int i;
        for (i=0;i<500;i++){
            LATAbits.LA2=1;
            __delay_ms(0.1*0.7);
            LATAbits.LA2=0;
            __delay_ms(0.1*(20-0.7));
        }
    }
    else if (open==CLOSED){
        //move motor counterclockwise
        int i;
        for (i=0;i<500;i++){
            LATAbits.LA2=1;
            __delay_ms(0.1*1.7);
            LATAbits.LA2=0;
            __delay_ms(0.1*(20-1.7)); 
        }
    }
}

//code to control microservo motor, pin A3 
void setChamberExit(int open){
     if (open==OPEN){
        //move motor counterclockwise 
        
    }
    else if (open==CLOSED){
        //move motor clockwise
        
    }
}

//code to control stepper motor
void rotateContainers(){
    int containerPos;
    if (detectedBottle == ESKACAP){
        containerPos = eskaCapPos;
    }
    else if (detectedBottle == ESKANOCAP){
        containerPos = eskaNoCapPos;
    }
    else if (detectedBottle == YOPCAP){
        containerPos = yopCapPos;
    }
    else if (detectedBottle == YOPNOCAP){
        containerPos = yopNoCapPos;
    }
    
    if (containerPos==0){
        //do nothing
    }
    else if (containerPos == 90){
        rotateStepperMotor(90, CONTAINER_ROTATION_SPEED, COUNTERCLOCKWISE);
        eskaCapPos=(eskaCapPos+270)%360;
        eskaNoCapPos=(eskaNoCapPos+270)%360;
        yopCapPos=(yopCapPos+270)%360;
        yopNoCapPos=(yopNoCapPos+270)%360;
    }
    else if (containerPos == 180){
        rotateStepperMotor(180, CONTAINER_ROTATION_SPEED, COUNTERCLOCKWISE);
        eskaCapPos=(eskaCapPos+180)%360;
        eskaNoCapPos=(eskaNoCapPos+180)%360;
        yopCapPos=(yopCapPos+180)%360;
        yopNoCapPos=(yopNoCapPos+180)%360;
    }
    else if (containerPos == 270){
        rotateStepperMotor(90, CONTAINER_ROTATION_SPEED, CLOCKWISE);
        eskaCapPos=(eskaCapPos+90)%360;
        eskaNoCapPos=(eskaNoCapPos+90)%360;
        yopCapPos=(yopCapPos+90)%360;
        yopNoCapPos=(yopNoCapPos+90)%360;
    }
}


