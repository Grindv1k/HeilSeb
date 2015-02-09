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
        int currentFloor = elev_get_floor_sensor_signal();
        if(currentFloor >= 0) // Floor reached
        {
            fsm_evFloorReached(currentFloor);   
        }
    }

    return 0;
}
