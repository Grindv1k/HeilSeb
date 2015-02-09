#include "requests.h"

#define FLOOR_COUNT 4

int canTakeRequests = 0;
floor_request_status_t floorRequests[FLOOR_COUNT];

void requests_enableRequesting()
{
    canTakeRequests = 1;
}

void requests_clearAllRequests()
{
    for(int i = 0; i < FLOOR_COUNT; i++)
    {
        floorRequests[i] = FLOOR_STOP_NONE;
    }
}
