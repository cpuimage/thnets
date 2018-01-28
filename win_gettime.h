 
#ifdef _MSC_VER
#ifndef win_time_h
#define win_time_h

#include <windows.h>
#include <time.h> 

#define NAME_MAX 255
#define M_PI 3.14159265358979323846 
	 
#define CLOCK_MONOTONIC 0 

	int clock_gettime(int clk_id, struct timespec *tp);

#endif
#endif 