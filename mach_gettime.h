#ifdef __MACH__ 
#include <sys/types.h>
#include <sys/_types/_timespec.h>
#include <mach/mach.h>
#include <mach/clock.h>

#ifndef mach_time_h
#define mach_time_h 
// XXX only supports a single timer
#define TIMER_ABSTIME -1 
int clock_gettime(int clk_id, struct timespec *tp);

#endif

#endif