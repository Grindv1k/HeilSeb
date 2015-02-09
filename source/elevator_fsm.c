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
    elev_init();
    elev_set_door_open_lamp();

    currentDirection = DIRN_DOWN;
    elev_set_motor_direction(currentDirection);
}

