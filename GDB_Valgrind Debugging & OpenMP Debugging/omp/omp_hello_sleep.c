/******************************************************************************
* FILE: omp_hello.c
* DESCRIPTION:
*   OpenMP Example - Hello World - C/C++ Version
*   In this simple example, the master thread forks a parallel region.
*   All threads in the team obtain their unique thread number and print it.
*   The master thread only prints the total number of threads.  Two OpenMP
*   library routines are used to obtain the number of threads and each
*   thread's number.
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 04/06/05
*
* Modified 06-Mar-2021 Chuck Pateros, USD
* Randomizes the threads
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WAIT_TIME 10000000 //10 seconds in microseconds (10^-6 sec) 
#define NUM_THREADS 8 // this must match OMP_NUM_THREADS

int main (int argc, char *argv[]) 
{
int nthreads, tid;
int thread, initial_time;
int wait_time[NUM_THREADS];
int my_wait_time;

initial_time = time(NULL);

srand(initial_time);
for(thread=0;thread<NUM_THREADS;thread++){
	wait_time[thread]=random() % MAX_WAIT_TIME;
	printf("Thread %d, wait time %3.2f\n",thread,(float)wait_time[thread]/1000000.0);
	}

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();

  /* wait a random amount of time */

  my_wait_time = wait_time[tid];
  usleep(my_wait_time);


  printf("Hello World from thread = %d.  I waited %3.2f seconds\n", tid, (float)my_wait_time/1000000.0);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and disband */

}

