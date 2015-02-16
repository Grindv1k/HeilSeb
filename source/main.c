#include "elev.h"
#include <stdio.h>
#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"


int main() 
{
    fsm_evInit();

	int lastFrameStopButtonState = 0;
    int currentFrameStopButtonState = 0;

	int lastFrameFloorSensorState = -1;
    int currentFrameFloorSensorState = -1;

	while(1)
    {
        currentFrameStopButtonState = elev_get_stop_signal();

		if(currentFrameStopButtonState && !lastFrameStopButtonState)
		{
			fsm_evStopButtonPressed();
		}
		else if(!currentFrameStopButtonState && lastFrameStopButtonState)
		{
			fsm_evStopButtonReleased();
		}

		lastFrameStopButtonState = currentFrameStopButtonState;


        currentFrameFloorSensorState = elev_get_floor_sensor_signal();

		if(currentFrameFloorSensorState >= 0 && lastFrameFloorSensorState < 0)
		{
            fsm_evArriveFloorSignal(currentFrameFloorSensorState);  
		}
		else if(currentFrameFloorSensorState < 0 && lastFrameFloorSensorState >= 0)
		{
			fsm_evLeaveFloorSignal();
		}
		lastFrameFloorSensorState = currentFrameFloorSensorState;
        

		if(timer_isTimeout())
        {
            fsm_evTimeout();
        }

        
		for(int i = 0; i < FLOOR_COUNT; i++)
		{ 
			if(elev_get_button_signal(BUTTON_COMMAND, i))
			{
				fsm_evRequestButtonPressed(i, BUTTON_COMMAND);
			}

			if(i < FLOOR_COUNT - 1 && elev_get_button_signal(BUTTON_CALL_UP, i))
			{
				fsm_evRequestButtonPressed(i, BUTTON_CALL_UP);
			}

			if(i > 0 && elev_get_button_signal(BUTTON_CALL_DOWN, i))
			{
				fsm_evRequestButtonPressed(i, BUTTON_CALL_DOWN);
			}
		}
    }

    return 0;
}
