

// Elevator movement
void hw_elevMoveDownwards();
void hw_elevMoveUpwards();
void hw_elevStop();

// Current floor status
int hw_getCurrentFloor(); 				// Returns a value 0-3 indicating which floor the elevator currently is on.
							// If the elevator is between floors, returns -1

// Checks button statii
int hw_getCallUpButtonStatus(int floor);		// Returns 1 if the call up button is pressed, else 0
int hw_getCallDownButtonStatus(int floor);		// Returns 1 if the call down button is pressed, else 0
int hw_getStopButtonStatus();				// Returns 1 if the stop button is pressed, else 0
int hw_getInsideButtonStatus(int floor);		// Returns 1 if the inside button is pressed, else 0

// LAMPS
void hw_setInsideButtonLampOn(int); 			// Int from 0-3, turns on lamp for corresponding button int
void hw_setInsideButtonLampOff(int); 			// Int from 0-3, turns off lamp for corresponding button int

void hw_setCallUpLampOn(int floor);			// Int 0-3, dir, turns on lamp for an up arrow button
void hw_setCallUpLampOff(int floor);			// Int 0-3, dir, turns off lamp for an up arrow button
void hw_setCallDownLampOn(int floor);			// Int 0-3, dir
void hw_setCallDownLampOff(int floor);			// Int 0-3, dir
void hw_setCallUpDownButtonLampsOff();			// Turns off lamps for all arrow buttons

void hw_setFloorButtonLampsOff();			// Turns off all floor button lamps (not floor indicator)
void hw_setFloorButtonLampOn(int floor);		// Turns on a floor button lamp
void hw_setFloorButtonLampOff(int floor);		// 

void hw_setLastFloorLamp(int floor);			// Holds last floor's lamp lit (indicator)

void hw_setStopLampOn();
void hw_setStopLampOff();

// Doors
void hw_closeDoors();					// Elevator door lamp on 
void hw_openDoors();					// off
