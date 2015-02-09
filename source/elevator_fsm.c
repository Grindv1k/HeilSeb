#include "elev.h"
#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"

int lastFloor;

elev_motor_direction_t currentDirection;

elev_door_status_t doorStatus;

elev_state_t currentState;

void fsm_evInit()
{
    currentState = ELEV_INIT;

    elev_init();
    
    requests_clearAllRequests();
    
    doorStatus = DOOR_CLOSED;
    elev_set_door_open_lamp(doorStatus);

    currentDirection = DIRN_DOWN;
    elev_set_motor_direction(currentDirection);
}

void fsm_evFloorReached(int floor)
{
    lastFloor = floor;
    elev_set_floor_indicator(floor);
    
    if(currentState == ELEV_INIT)
    {
        elev_set_motor_direction(DIRN_STOP);
        currentState = ELEV_STOPPED;

        doorStatus = DOOR_OPEN;
        elev_set_door_open_lamp(doorStatus);
        
        timer_start();
        
        requests_enableRequesting();
    }
}

void fsm_evTimeOut()
{
    doorStatus = DOOR_CLOSED;
    elev_set_door_open_lamp(doorStatus);

    timer_stop();
}

/*void fsm_evInsideButtonRegistered(int floor)
{
	elev_set_button_lamp(BUTTON_COMMAND, int floor)
	requests_requestFloor(int floor, BUTTON_COMMAND)
}
*/



