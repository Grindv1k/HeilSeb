// State machine 
void fsm_evInit(); // runs once at startup			

void fsm_evStopButtonPressed(); 
void fsm_evStopButtonReleased();

void fsm_evInsideButtonRegistered(int floor); // a button for some floor (int) is registered from inside the elevator
void fsm_evRequestButtonRegistered(int floor, elev_button_type_t); // a button from some floor (int) is registered, in a direction (dir)

void fsm_evFloorReached(int);

void fsm_evMoveElevDownwards();
void fsm_evMoveElevUpwards();

void fsm_evInitialFloorReached(); // only part of the initialization

void fsm_evTimeout();





