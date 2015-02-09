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

void fsm_evStopButtonPressed()
{
	if(currentState == ELEV_INIT)
	{
		return;
	}

	elev_set_motor_direction(DIRN_STOP);
	elev_set_stop_lamp(1);
	requests_clearAllRequests();
	requests_disableRequesting();

	if(currentState == ELEV_STOPPED_ON_FLOOR)
	{
		doorStatus = DOOR_OPEN;
    	elev_set_door_open_lamp(doorStatus);
		currentState = ELEV_EMERGENCY_STOP_ON_FLOOR;
	}
	else if(currentState == ELEV_MOVING)
	{
		currentState = ELEV_EMERGENCY_STOP_BETWEEN_FLOORS;
	}
}

void fsm_evStopButtonReleased()
{
	if(currentState == ELEV_INIT)
	{
		return;
	}

	elev_set_stop_lamp(0);
	requests_enableRequesting();

	if(currentState == ELEV_EMERGENCY_STOP_ON_FLOOR)
	{
		timer_start();
		currentState = ELEV_STOPPED_ON_FLOOR;
	}
	else if(currentState == ELEV_EMERGENCY_STOP_BETWEEN_FLOORS)
	{
		currentState = ELEV_STOPPED_BETWEEN_FLOORS;
	}
}

void fsm_evRequestButtonRegistered(int floor, elev_button_type_t buttonType)
{
	elev_set_button_lamp(buttonType, floor, 1);
	requests_requestFloor(floor, buttonType);
}

void fsm_evFloorReached(int floor)
{
    lastFloor = floor;
    elev_set_floor_indicator(floor);
    requests_closeRequest(floor);
    
    if(currentState == ELEV_INIT)
    {
        elev_set_motor_direction(DIRN_STOP);
        currentState = ELEV_STOPPED_ON_FLOOR;

        doorStatus = DOOR_OPEN;
        elev_set_door_open_lamp(doorStatus);
        
        timer_start();
        
        requests_enableRequesting();
    }
    
    if(currentState == ELEV_MOVING & requests_isFloorRequested(floor, currentDirection))
    {
    	elev_set_motor_direction(DIRN_STOP);
    	currentState = ELEV_STOPPED_ON_FLOOR;
    }
    
    if(currentState == ELEV_STOPPED_ON_FLOOR)
    {
    	
    }
}


void fsm_evTimeout()
{
    doorStatus = DOOR_CLOSED;
    elev_set_door_open_lamp(doorStatus);

    timer_stop();
}





