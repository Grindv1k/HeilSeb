#include <sys/time.h>
#include "timer.h"

double lastTimeStamp;

double get_wall_time(void)
{
    struct timeval time;
    gettimeofday(&time, 0);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

void timer_start()
{
    lastTimeStamp = get_wall_time();
}

void timer_stop()
{
    lastTimeStamp = 0.0;
}

int timer_isTimeout()
{
    double diff = get_wall_time() - lastTimeStamp;
    
    if(diff < 0)
    {
        lastTimeStamp = get_wall_time();
        return 0;
    }

    if(diff > 3.0)
    {
        return 1;
    }

    return 0;
}

