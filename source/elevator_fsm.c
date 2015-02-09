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
    elev_set_door_open_lamp(0);

    currentDirection = DIRN_DOWN;
    elev_set_motor_direction(currentDirection);
}

void fsm_evFloorReached(int floor)
{
    currentFloor = floor;
    elev_set_floor_indicator(floor);
    elev_set_motor_direction(DIRN_STOP);

    currentState = ELEV_STOPPED;
}

