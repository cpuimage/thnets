
#ifdef _MSC_VER
#include "win_gettime.h"
#include <windows.h>
#include <time.h> 
    
	 int clock_gettime(int clk_id, struct timespec *tp)
{
	unsigned long msec;
	msec = GetTickCount();
	tp->tv_sec = msec / 1000;
	tp->tv_nsec = (msec % 1000) * 1000000L;
	return 0;
} 
#endif