#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#define BUFFER_SIZE (256*1024*1024)
#define SHARED_LIB_FUNC __cyg_profile_func_enter

#define VTRACE_OFF __attribute__((__no_instrument_function__))
#define STR(x) #x
#define EVAL(x,y) x(y)

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
	char *buffer;
	tf = fopen("test.vtrc", "w");	

	buffer = malloc(BUFFER_SIZE);

	if(!buffer)
		printf("[VTRACE] Could not allocate buffer.\n");

	setbuf(tf, buffer); 

	fprintf(tf, "VTRACE\n");
	fprintf(tf,"date:now :o)\n");

#ifdef SHARED_LIB_FUNC
	fprintf(tf,"mapping: %s %p\n", EVAL(STR,SHARED_LIB_FUNC), SHARED_LIB_FUNC);
#endif

	fprintf(tf,"data:\n");

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
