#ifndef __TIMER_H__
#define __TIMER_H__

void timer_start();
void timer_stop();

// Returns 1 if timer is timeout, 0 if not
int timer_isTimeout();




#endif
