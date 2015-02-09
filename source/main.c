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
        int floor = elev_get_floor_sensor_signal();
        if(floor >= 0)
        {
            fsm_floorReached(floor);   
        }
    }

    return 0;
}
