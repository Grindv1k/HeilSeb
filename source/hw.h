#ifndef __INCLUDE_DRIVER_H__
#define __INCLUDE_DRIVER_H__

#define N_FLOORS 4 // Number of floors

int elev_init(void); //Initialize elevator. @return Non-zero on success, 0 on failure.

typedef enum tag_elev_motor_direction 
{ 
    DIRN_DOWN = -1,
    DIRN_STOP = 0,
    DIRN_UP = 1
} 
elev_motor_direction_t; // for function elev_set_motor_direction()

void elev_set_motor_direction(elev_motor_direction_t dirn);
 
void elev_set_door_open_lamp(int value); 	//  Turn door-open lamp on or off. 
						// @param value Non-zero value turns 
						// lamp on, 0 turns lamp off.


int elev_get_obstruction_signal(void);		// unused 

int elev_get_stop_signal(void);			// 1 when detected, else 0

void elev_set_stop_lamp(int value);		// 1 to set, 0 to off 

int elev_get_floor_sensor_signal(void);		// -1 when not on floor, 0 ground floor up to
						// 3 for top floor.

void elev_set_floor_indicator(int floor);	// 0 ground, 3 top. 

typedef enum tag_elev_lamp_type { 
    BUTTON_CALL_UP = 0,		// "uparrow" type button
    BUTTON_CALL_DOWN = 1,	// "downarrow" type button
    BUTTON_COMMAND = 2		// button from inside the elevator
} elev_button_type_t;

int elev_get_button_signal(elev_button_type_t button, int floor); //use enum above, plus a floor number

void elev_set_button_lamp(elev_button_type_t button, int floor, int value); //use enum above, int floor, and int value should be 0 for off and non-zero for on.

#endif // #ifndef __INCLUDE_DRIVER_H__
