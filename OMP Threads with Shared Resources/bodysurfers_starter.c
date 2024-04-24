/* bodysurfers.c
 * A variant of the dining philosophers problem using bodysurfers.
 *
 *
 * Each bodysurfer brings one fin.  They each put their fin into
 * a shared locker.
 * If at least two fins are available, they surf.
 *
 * Project 2 - Week 2
 * 
 * CEO - Tyler
 * PM - Christine
 * DEV0 - Nadeen
 * DEV1- Alfie
 * TEST - BEN
 *
 * Chuck Pateros, University of San Diego
 * 14-Mar-2021
 *
 * derived from http://monismith.info/cs599/examples/ompPhilosophers.c
 */

#include <omp.h>        //Use OpenMP
#include <stdio.h>      //Provide I/O
#include <unistd.h>     //Use usleep (sleep for a number of microseconds)

#define NUM_SURFERS 5     //The number of bodysurfers
#define NUM_WAVES 50000 //The number of waves per bodysurfer

static omp_lock_t fin_locker_lock; //Lock to represent the fin locker lock
static int fin_locker_count=0; // the number of fins in the locker


void surfer()
{
  //Wait for all threads to start
  #pragma omp barrier

  //Set up variables for the thread id and fins.
  int surfer_id = omp_get_thread_num();
  int my_fin_count = 0;

  // We will count our waves to determine when we're too tired 
  int wave_count;
  for(wave_count = 0; wave_count < NUM_WAVES; wave_count++)
  {
    my_fin_count = 0;
    while(my_fin_count < 2)
    {
      //usleep(50); // have a refreshing beverage
      omp_set_lock(&fin_locker_lock); //Wait for access to the fin locker

      if(fin_locker_count >= 2)
      {
        fin_locker_count -= 2; // remove two fins
        my_fin_count = 2;
      }
      
      omp_unset_lock(&fin_locker_lock); // make locker available again
    } //end while waiting for 2 fins

// Cowabunga

      if((wave_count%1000)==0) // comment this line out for short runs
	printf("phil %d is surfing wave %20d\r", surfer_id,wave_count);
    //usleep(100); // use this line to simulate surfing time

    omp_set_lock(&fin_locker_lock); //Wait for access to the fin locker
 
    fin_locker_count += 2; // return fins
    my_fin_count = 0;
    
    omp_unset_lock(&fin_locker_lock);
    //usleep(50); // after surf rest is important
  } //end wave count
  printf("\n                      phil %d exhausted \n",surfer_id);
} // end surfer



int main(int argc, char ** argv)
{
  double elapsed_time;

  //Initialize fin locker lock

  omp_init_lock(&fin_locker_lock);

  // Initialize the fin locker
     fin_locker_count = 5;

  elapsed_time = omp_get_wtime(); // set up the sundial

  //Create and start bodysurfer threads.
  #pragma omp parallel num_threads(NUM_SURFERS)
  {
    surfer();
  }

  //Wait for bodysurfers to finish then destroy fin locker lock
  omp_destroy_lock(&fin_locker_lock);

  elapsed_time = omp_get_wtime() - elapsed_time;
  printf("Elapsed time: %f\n",elapsed_time);

  //End program and check out the bonfire
  return 0;
}

