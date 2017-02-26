#include <xc.h>
#include <stdio.h>
#include "LCD.h"
#include "configBits.h"
#include "machineStates.h"
#include "macros.h"


//ULTRASONIC_SENSOR will either be ULTRASONIC_SENSOR_1, ULTRASONIC_SENSOR_2, or ULTRASONIC_SENSOR_3
int getDistance (int ULTRASONIC_SENSOR){    
    if (ULTRASONIC_SENSOR == ULTRASONIC_SENSOR_1){
        LATCbits.LC2 = 0; //set trig pin to low
        __delay_ms(0.0001*2); //delay 2 microseconds
        LATCbits.LC2 = 1; //set trig pin to high
        __delay_ms(0.0001*10); //delay 10 microseconds
        LATCbits.LC2=0;
        while (LATCbits.LC3==0){
            //wait for echo pin to go high
        }
        while (LATCbits.LC3==1){
            //start timing 
        }
        return 0;
    }
    if (ULTRASONIC_SENSOR == ULTRASONIC_SENSOR_2){
        LATCbits.LC4 = 0; //set trig pin to low
        __delay_ms(0.0001*2); //delay 2 microseconds
        LATCbits.LC4 = 1; //set trig pin to high
        __delay_ms(0.0001*10); //delay 10 microseconds
        LATCbits.LC4=0;
        while (LATCbits.LC5==0){
            //wait for echo pin to go high
        }
        int counter;
        while (LATCbits.LC5==1){
            counter++; 
        }
        return counter;
    }
    if (ULTRASONIC_SENSOR == ULTRASONIC_SENSOR_3){
        LATCbits.LC6 = 0; //set trig pin to low
        __delay_ms(0.0001*2); //delay 2 microseconds
        LATCbits.LC6 = 1; //set trig pin to high
        __delay_ms(0.0001*10); //delay 10 microseconds
        LATCbits.LC6=0;
        while (LATCbits.LC7==0){
            //wait for echo pin to go high
        }
        while (LATCbits.LC7==1){
            //start timing 
        }
        return 0;
    }
}

//emit is either ON or OFF
void setLaserEmitter(int emit){
    if (emit == ON){
        LATCbits.LC0 = 1;
    }
    else if (emit == OFF){
        LATCbits.LC0 = 0;
    }
}

int laserDetected(){
    return LATCbits.LC1;
}



//gets data from ultrasonic distance sensor #1 to determine
//C2 = TRIG, C3 = ECHO
int bottleComing(){
    if (getDistance(ULTRASONIC_SENSOR_2) > BOTTLE_ENTERING_CHAMBER_DISTANCE){
        return 1;
    }
    else{
        return 0;
    }
    
}

//sets the value of the detectedBottle variable in machineStates.h depending on the value of the sensors
//uses ultrasonic distance sensor #2, ultrasonic distance sensor #3, laser emitter, and laser detector
void detectBottle(){
    int noCap = 0; //boolean to represent whether the bottle has no cap
    int transparent = laserDetected(); //if the emitted laser is detected on the other side of the bottle, the bottle is transparent (ESKA brand)
    if (getDistance(ULTRASONIC_SENSOR_2) > TEST_CAP_DISTANCE || getDistance(ULTRASONIC_SENSOR_3) > TEST_CAP_DISTANCE){
        noCap = 1; //if either of the distances measured by the ultrasonic sensors exceeds TEST_CAP_DISTANCE, a cap is not present on the bottle
    }
    if (transparent && noCap){
        detectedBottle = ESKANOCAP;
        numEskaNoCap++;
    }
    else if (transparent && !noCap){
        detectedBottle = ESKACAP;
        numEskaCap++;
    }
    else if (!transparent && noCap){
        detectedBottle = YOPNOCAP;
        numYopNoCap++;
    }
    else if (!transparent && !noCap){
        detectedBottle = YOPCAP;
        numYopCap++;
    }
    
    
}

