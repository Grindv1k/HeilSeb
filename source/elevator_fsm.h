#ifndef __ELEV_FSM_H__
#define __ELEV_FSM_H__

#define FLOOR_COUNT 4

// State machine 
void fsm_evInit(); // runs once at startup			

void fsm_evStopButtonPressed(); 
void fsm_evStopButtonReleased();

// a button from inside the elevator, or from some floor in a direction.
void fsm_evRequestButtonPressed(int requestedFloor, elev_button_type_t buttonType); 

void fsm_evArriveFloorSignal(int floor);
void fsm_evLeaveFloorSignal();

void fsm_evTimeout();

typedef enum tag_elev_door_status
{
    DOOR_CLOSED = 0,
    DOOR_OPEN = 1
} elev_door_status_t;

typedef enum tag_elev_state
{
    ELEV_INIT,
    ELEV_IDLE,
    ELEV_MOVING,
    ELEV_STOPPED_ON_FLOOR,
	ELEV_STOPPED_BETWEEN_FLOORS,
    ELEV_EMERGENCY_STOP_ON_FLOOR,
    ELEV_EMERGENCY_STOP_BETWEEN_FLOORS
} elev_state_t;

#endif
