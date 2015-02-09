#include "elev.h"
#include <stdio.h>
#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"


int main() 
{
    fsm_evInit();

	int lastFrameStopButtonState = 0;

    while(1)
    {
		if(elev_get_stop_signal() && !lastFrameStopButtonState)
		{
			fsm_evStopButtonPressed();
		}
		else if(!elev_get_stop_signal() && lastFrameStopButtonState)
		{
			fsm_evStopButtonReleased();
		}

		lastFrameStopButtonState = elev_get_stop_signal();

        int currentFloor = elev_get_floor_sensor_signal();
        if(currentFloor >= 0) // Floor reached
        {
            fsm_evFloorReached(currentFloor);   
        }
        
		if(timer_isTimeout())
        {
            fsm_evTimeout();
        }

        
		for(int i = 0; i < FLOOR_COUNT; i++)
		{ 
			if(elev_get_button_signal(BUTTON_COMMAND, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_COMMAND);
			}

			if(i < FLOOR_COUNT - 1 && elev_get_button_signal(BUTTON_CALL_UP, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_CALL_UP);
			}

			if(i > 0 && elev_get_button_signal(BUTTON_CALL_DOWN, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_CALL_DOWN);
			}
		}
    }

    return 0;
}
