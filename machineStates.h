
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
int numSeconds; //number of seconds since operation started

#endif	/* MACHINESTATES_H */
