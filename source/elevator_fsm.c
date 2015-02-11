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
        timer_stop();
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
    
    if(doorStatus == DOOR_OPEN)
    {
        return;
    }

    if(currentState == ELEV_IDLE)
    {
        if(floor == lastFloor)
        {
            doorStatus = DOOR_OPEN;
            elev_set_door_open_lamp(doorStatus);

            timer_start();
            
            return;
        }
    }

    if(currentState == ELEV_STOPPED_BETWEEN_FLOORS || currentState == ELEV_IDLE)
    {
        int floorDiff = floor - lastFloor;

        if(floorDiff == 0)
        {
            currentDirection *= -1; 
        }
        else
        {
            currentDirection = floorDiff;
        }
    
        elev_set_motor_direction(currentDirection);
        currentState = ELEV_MOVING;
    }
}

void fsm_evFloorReached(int floor)
{
    lastFloor = floor;
    elev_set_floor_indicator(floor);
    
    if(currentState == ELEV_INIT)
    {
        elev_set_motor_direction(DIRN_STOP);
        currentState = ELEV_STOPPED_ON_FLOOR;

        doorStatus = DOOR_OPEN;
        elev_set_door_open_lamp(doorStatus);
        
        timer_start();
        
        requests_enableRequesting();
    }
    
    if((currentState == ELEV_MOVING || currentState == ELEV_IDLE || currentState == ELEV_STOPPED)
         && requests_isFloorRequested(floor, currentDirection))
    {
        requests_closeRequest(floor);
        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
        
        if(floor < FLOOR_COUNT - 1)
        {
            elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);        
        }
        if(floor > 0)
        {
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);        
        }

    	elev_set_motor_direction(DIRN_STOP);
    	currentState = ELEV_STOPPED_ON_FLOOR;
        doorStatus = DOOR_OPEN;
        elev_set_door_open_lamp(doorStatus);
        timer_start();
    }
}


void fsm_evTimeout()
{
    doorStatus = DOOR_CLOSED;
    elev_set_door_open_lamp(doorStatus);

    timer_stop();

    if(requests_existsRequestsInDirection(lastFloor, currentDirection))
    {
        currentState = ELEV_MOVING;
        elev_set_motor_direction(currentDirection);   
    }
    else if(requests_existsRequestsInDirection(lastFloor, -currentDirection))
    {
        currentState = ELEV_MOVING;
        currentDirection *= -1;
        elev_set_motor_direction(currentDirection);
    }
    else
    {
        currentState = ELEV_IDLE;
    }
}





