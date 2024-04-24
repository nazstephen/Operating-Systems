/******************************************************************************
* FILE: omp_hello_spin.c
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
* Waits using spin counters
*
* Project 2 - Week 1
*
* CEO - Tyler
* PM - Christine
* DEV0 - Nadeen
* DEV1 - Alfie
* Tester - Ben
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WAIT_COUNT 2000000000 // may need to change   
#define NUM_THREADS 8 // this should match OMP_NUM_THREADS

int main (int argc, char *argv[]) 
{
int nthreads, tid;
int thread, initial_time;
unsigned long long int wait_count[NUM_THREADS];
unsigned long long int count[NUM_THREADS];
int my_wait_count;

initial_time = time(NULL);

srand(initial_time);
for(thread=0;thread<NUM_THREADS;thread++){
	wait_count[thread]=random() % MAX_WAIT_COUNT;
	printf("Thread %d, wait count %10llu\n", 
			thread,wait_count[thread]);
	}

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid)
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();

  /* wait a random amount of time */

  //my_wait_count = wait_count[tid];
  // usleep(my_wait_count); // alternative to spinning

  //for(count[tid]=0;count[tid]<my_wait_count;count[tid]++);
  for(count[tid]=0;count[tid]<wait_count[tid];count[tid]++);
  


  printf("Hello World from thread = %d.  I waited %10llu counts\n", tid, count[tid]);

  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  } // end of #pragma

}  /* All threads join master thread and disband */


