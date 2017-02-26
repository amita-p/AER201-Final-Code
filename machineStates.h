
/* machineStates.h  */
#ifndef MACHINESTATES_H
#define MACHINESTATES_H

//variables which store the current state
int machineState;
int currentScreen;

//variables which store sorting log information for current sorting process (null values if machineState!=SORTING)
int numBottles; //total number of bottles so far in operation
int numEskaNoCap; 
int numEskaCap; 
int numYopNoCap;
int numYopCap;
volatile double numSeconds; //number of seconds since operation started

//tracks the current angular position of the containers (clockwise from the chamber exit)
int eskaNoCapPos;
int eskaCapPos;
int yopNoCapPos;
int yopCapPos;

//detected bottle
int detectedBottle;

//stores the last value of numSeconds when a bottle was coming into the chamber
double lastTimeBottleCame;

#endif	/* MACHINESTATES_H */

