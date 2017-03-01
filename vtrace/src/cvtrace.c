#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>


#define VTRACE_OFF __attribute__((__no_instrument_function__))


static FILE *tf = NULL;


static long VTRACE_OFF get_ns()
{
	long ns;
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	ns = ts.tv_nsec + (ts.tv_sec * 1000000000l);

	return ns;
}


static void VTRACE_OFF vtrace_exit()
{
	fclose(tf);
}


static void VTRACE_OFF vtrace_init()
{
	tf = fopen("test.vtrc", "a");

	fprintf(tf, "VTRACE\n");
	fprintf(tf,"date:now :o)\n");

	atexit(vtrace_exit);
}


void VTRACE_OFF __cyg_profile_func_enter(void *this_fn, void *call_site)
{
	static int init = 0;
	pthread_t t = pthread_self();

	if(!init)
	{
		init = 1;
		vtrace_init();
	}

	fprintf(tf, "%ld>%p\n", get_ns(), this_fn);
}


void  VTRACE_OFF __cyg_profile_func_exit(void *this_fn, void *call_site)
{
	pthread_t t = pthread_self();

	fprintf(tf, "%ld<%p\n", get_ns(), this_fn);
}
