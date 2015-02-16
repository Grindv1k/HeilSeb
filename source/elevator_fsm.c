#include <stdio.h>
#include "elev.h"
#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"

int lastPassedFloor;
int isCurrentlyOnFloor;

elev_motor_direction_t 	currentDirection;
elev_door_status_t 		doorStatus;
elev_state_t 			currentState;

void fsm_evInit()
{
    currentState = ELEV_INIT;
    elev_init();

	isCurrentlyOnFloor = 0;
    
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

	if(isCurrentlyOnFloor)
	{
		doorStatus = DOOR_OPEN;
    	elev_set_door_open_lamp(doorStatus);

		currentState = ELEV_EMERGENCY_STOP_ON_FLOOR;

        timer_stop();
	}
	else
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
		currentState = ELEV_IDLE;
	}
	else if(currentState == ELEV_EMERGENCY_STOP_BETWEEN_FLOORS)
	{
		currentState = ELEV_STOPPED_BETWEEN_FLOORS;
	}
}


void fsm_evRequestButtonPressed(int requestedFloor, elev_button_type_t buttonType)
{
    if(currentState == ELEV_INIT || 
        currentState == ELEV_EMERGENCY_STOP_ON_FLOOR || 
		currentState == ELEV_EMERGENCY_STOP_BETWEEN_FLOORS)
    {
        return;
    }

	if(isCurrentlyOnFloor && requestedFloor == lastPassedFloor)
	{
		if(requests_isRequestsEmpty())
		{
			doorStatus = DOOR_OPEN;
			elev_set_door_open_lamp(doorStatus);

			timer_start();
		}
		return;
	}

	elev_set_button_lamp(buttonType, requestedFloor, 1);
	requests_requestFloor(requestedFloor, buttonType);
    
    if(doorStatus != DOOR_OPEN &&
		(currentState == ELEV_STOPPED_BETWEEN_FLOORS || currentState == ELEV_IDLE))
    {
		// The sign of the difference between the requested floor and last floor
		int floorDiffSign = (requestedFloor - lastPassedFloor > 0) - 
							(requestedFloor - lastPassedFloor < 0); 

		if(floorDiffSign)
		{
			if(currentState == ELEV_STOPPED_BETWEEN_FLOORS && currentDirection + floorDiffSign == 0)
			{
				lastPassedFloor += currentDirection;
			}

		    currentDirection = floorDiffSign;
		}
		else
		{
			if(currentState == ELEV_STOPPED_BETWEEN_FLOORS)
			{
		    	currentDirection *= -1;	
				lastPassedFloor -= currentDirection;
			}
			/*else if(currentState == ELEV_IDLE)
			{
				// If the elevator is idle (no requests) and 
				// the requested floor is the same as last floor, just open doors.

				doorStatus = DOOR_OPEN;
				elev_set_door_open_lamp(doorStatus);

				timer_start();
				
				return;
			}*/
		}

		elev_set_motor_direction(currentDirection);
		currentState = ELEV_MOVING;
	}
}

void fsm_evArriveFloorSignal(int floor)
{
	isCurrentlyOnFloor = 1;
    lastPassedFloor = floor;
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
	else if(requests_isFloorRequested(floor, currentDirection))    
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

void fsm_evLeaveFloorSignal()
{
	isCurrentlyOnFloor = 0;
}


void fsm_evTimeout()
{
    doorStatus = DOOR_CLOSED;
    elev_set_door_open_lamp(doorStatus);

    timer_stop();

    if(requests_existsRequestsInDirection(lastPassedFloor, currentDirection))
    {
        currentState = ELEV_MOVING;
        elev_set_motor_direction(currentDirection);   
    }
    else if(requests_existsRequestsInDirection(lastPassedFloor, -currentDirection))
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
