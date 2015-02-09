#include "elevator_fsm.h"
#include "timer.h"
#include "requests.h"
#include "elev.h"

int lastFloor;
elev_motor_direction_t currentDirection;
