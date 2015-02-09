#ifndef __ELEV_FSM_H__
#define __ELEV_FSM_H__

#define FLOOR_COUNT 4

// State machine 
void fsm_evInit(); // runs once at startup			

void fsm_evStopButtonPressed(); 
void fsm_evStopButtonReleased();

void fsm_evRequestButtonRegistered(int floor, elev_button_type_t buttonType); // a button from inside the elevator, or from some floor in a direction.

void fsm_evFloorReached(int);

void fsm_evTimeout();

void fsm_evBetweenFloors();

typedef enum tag_elev_door_status
{
    DOOR_CLOSED = 0,
    DOOR_OPEN = 1
} elev_door_status_t;

typedef enum tag_elev_state
{
    ELEV_INIT,
    ELEV_MOVING,
    ELEV_STOPPED_ON_FLOOR,
	ELEV_STOPPED_BETWEEN_FLOORS,
    ELEV_EMERGENCY_STOP_ON_FLOOR,
    ELEV_EMERGENCY_STOP_BETWEEN_FLOORS
} elev_state_t;

#endif
