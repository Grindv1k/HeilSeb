#ifndef __REQUESTS_H__
#define __REQUESTS_H__

void requests_enableRequesting();			// 
void requests_clearAllRequests();			// 
void requests_disableRequesting();			//
void requests_requestFloor(int floor, elev_button_type_t buttonType);		//
int requests_isFloorRequested(int floor, elev_motor_direction_t dir);		// 
void requests_closeRequest(int floor);			//

typedef enum tag_floor_request_status
{
    FLOOR_STOP_NONE = 0,
    FLOOR_STOP_UP = 1,
    FLOOR_STOP_DOWN = 2,
    FLOOR_STOP_ALL = 3
} floor_request_status_t;

#endif
