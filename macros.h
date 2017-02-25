/* macros.h  */
#ifndef MACROS_H
#define MACROS_H

//Machine states
#define STANDBY 1
#define SORTING 2

//LCD Screens
#define MAIN_MENU 3
#define SORTING_SCREEN 4
#define LOGS_MENU 5
#define LOGS_DISPLAY_MENU_SCREEN 6
#define DOWNLOAD_TO_PC_SCREEN 7

//Fan Directions
#define CLOCKWISE 8
#define COUNTERCLOCKWISE 9

//Chamber Entrance/Exit States
#define CLOSED 10
#define OPEN 11

//ON and OFF
#define ON 12
#define OFF 13

//Bottles
#define ESKACAP 14
#define ESKANOCAP 15
#define YOPCAP 16
#define YOPNOCAP 17

//Ultrasonic distance sensors
#define ULTRASONIC_SENSOR_1 18
#define ULTRASONIC_SENSOR_2 19
#define ULTRASONIC_SENSOR_3 20

#define TEST_CAP_DISTANCE 0

#define BOTTLE_ENTERING_CHAMBER_DISTANCE 0

//angular speed, degrees/second
#define CONTAINER_ROTATION_SPEED 360


#define FULL_ROTATION_NUM_STEPS 4096

#define BOTTLE_FALL_IN_CHAMBER 0 //number of seconds for bottle to fall into chamber since door opens
#define BOTTLE_FALL_IN_CONTAINER 0 //number of seconds for bottle to fall out of chamber and into container 






#endif	/* MACROS_H */

