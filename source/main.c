#include "elev.h"
#include <stdio.h>
#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"


int main() 
{
    fsm_evInit();
	
    while(1)
    {
		if(elev_get_stop_signal())
		{
			fsm_evStopButtonPressed()
		}

        int currentFloor = elev_get_floor_sensor_signal();
        if(currentFloor >= 0) // Floor reached
        {
            fsm_evFloorReached(currentFloor);   
        }
        
        if(timer_isTimeout())
        {
            fsm_evTimeOut();
        }

		for(int i = 0; i < 4; i++)
		{ 
			if(elev_get_button_signal(BUTTON_COMMAND, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_COMMAND)
			}

			if(elev_get_button_signal(BUTTON_CALL_UP, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_CALL_UP)
			}

			if(elev_get_button_signal(BUTTON_CALL_DOWN, i))
			{
				fsm_evRequestButtonRegistered(i, BUTTON_CALL_DOWN)
			}
		} 
		
		
		
    }

    return 0;
}
