#include "elev.h"
#include "requests.h"
#include "elevator_fsm.h"

int canTakeRequests = 0;
floor_request_status_t floorRequests[FLOOR_COUNT];

void requests_enableRequesting()
{
    canTakeRequests = 1;
}

void requests_disableRequesting()
{
    canTakeRequests = 0;
}

int requests_isRequestsEmpty()
{
    for(int i = 0; i < FLOOR_COUNT; i++)
    {
        if(floorRequests[i] != FLOOR_STOP_NONE)
		{
			return 0;
		}
    }

	return 1;
}

int requests_isOnlyRequest(int floor, elev_motor_direction_t dir)
{
    for(int i = floor; i < FLOOR_COUNT && i >= 0; i += dir)
    {
        if(i != floor && floorRequests[i] != FLOOR_STOP_NONE)
		{
			return 0;
		}
    }

	return floorRequests[floor] != FLOOR_STOP_NONE;
}

void requests_requestFloor(int floor, elev_button_type_t buttonType)
{
    if(!canTakeRequests)
    {
        return;
    }

	if(floor == 0 || floor == FLOOR_COUNT - 1)
	{
		floorRequests[floor] |= FLOOR_STOP_ALL;
	}
	else
	{
		if(buttonType == BUTTON_CALL_UP)
		{
		    floorRequests[floor] |= FLOOR_STOP_UP; 
		}
		else if(buttonType == BUTTON_CALL_DOWN)
		{
		    floorRequests[floor] |= FLOOR_STOP_DOWN;
		}
		else if(buttonType == BUTTON_COMMAND)
		{
		    floorRequests[floor] |= FLOOR_STOP_ALL;
		}
	}
}

int requests_isFloorRequested(int floor, elev_motor_direction_t dir)
{
    if(!canTakeRequests)
    {
        return 0;
    }

    if(requests_isOnlyRequest(floor, dir))
    {
		return 1;
    }

    if(dir == DIRN_UP)
    {
        return floorRequests[floor] & FLOOR_STOP_UP;
    }

    if(dir == DIRN_DOWN)
    {
        return floorRequests[floor] & FLOOR_STOP_DOWN;
    }

    return 0;
}

void requests_closeRequest(int floor)
{
    floorRequests[floor] = FLOOR_STOP_NONE;
}

void requests_clearAllRequests()
{
    for(int i = 0; i < FLOOR_COUNT; i++)
    {
        floorRequests[i] = FLOOR_STOP_NONE;
		elev_set_button_lamp(BUTTON_COMMAND, i, 0);
		if(i > 0)
			{
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 0);
			}
		if(i < FLOOR_COUNT - 1)
			{
				elev_set_button_lamp(BUTTON_CALL_UP, i, 0);	
			}
    }
}

int requests_existsRequestsInDirection(int floor, elev_motor_direction_t dir)
{
    for(int i = floor; i < FLOOR_COUNT && i >= 0; i += dir)
    {
        if(requests_isFloorRequested(i, dir))
        {
            return 1;
        }       
    }

    return 0;
}
