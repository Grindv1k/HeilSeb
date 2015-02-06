// State machine 

void fsm_evCloseDoors();
void fsm_evOpenDoors();

void fsm_evMoveElevDownwards();
void fsm_evMoveElevUpwards();

void fsm_evInitialFloorReached(); // Necessary? Could add floor 1 to queue during startup and let the elev stop there.
void fsm_evFloorReached();

void fsm_evTimeout();

void fsm_evStopButtonPressed();
void fsm_evStopButtonReleased();

void fsm_evInsideButtonRegistered(int);
void fsm_evFloorReached(int);

