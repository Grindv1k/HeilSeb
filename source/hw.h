
void hw_closeDoors();
void hw_openDoors();

void hw_elevMoveDownwards();
void hw_elevMoveUpwards();
void hw_elevStop();

// Returns a value 1-4 indicating which floor the elevator currently is on.
// If the elevator is between floors, returns 0
int hw_getCurrentFloor();

// Returns 1-4 depending on floor wanted
int hw_elevGetFloorButton();
