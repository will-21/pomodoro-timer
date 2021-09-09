/**
* Pomodoro timer in C
*
* dev - Will Pryor
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/*    CONSTANTS         */
#define WORK_TIME 25 // time (min) to work for 1 cycle
#define REST_TIME 5 // time (min) to rest after each cycle
#define NUM_CYCLES 4 // number of cycles before a longer break
#define BREAK_TIME 20 // time (min) to rest after NUM_CYCLES

/*    COLOR CONSTANTS   */
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

/*    FUNCTIONS         */

/**
* Converts seconds (time_t) to minutes (float)
*/
float secondsToMin(time_t seconds) {
  return (float)seconds / 60;
}

/**
* Converts seconds (float) to min (time_t)
*/
time_t minToSeconds(float min) {
  return (time_t) (min * 60);
}

/**
* Returns the time in seconds since Jan 1 1970
*/
time_t getTime() {
  time_t t;
  t = time(NULL);
  return t;
}
/**
* Displays time on the screen
*     -not sure how yet - options for CLI printout vs gui??
*     -start with CLI
*     -display a star per min to indicate progress out of 25
*/
void displayTime(int num_stars) { // TODO: make enum status
  fflush(stdout); // TODO : necessary??
  system("clear");
  if (num_stars == WORK_TIME) { // TODO : add audio or something
    printf("%sDone working! Take a break for %d minutes!%s\n", KGRN, REST_TIME, KWHT);
  }
  else {
    char * stars = malloc(sizeof(char) * WORK_TIME);
    int i = 0;
    for (; i < num_stars; i++) { // TODO : more efficient way??
      stars[i] = '*';
    }
    for (; i < WORK_TIME; i++) {
      stars[i] = '-';
    }
    printf("Progress: %s%d min %sout of %s%d min%s\n\n", KGRN, num_stars, KWHT, KRED, WORK_TIME, KWHT);
    printf("[ %s%.*s%s%.*s %s]\n", KGRN, num_stars, "*************************", KRED,
    (WORK_TIME - num_stars), "-------------------------", KWHT);
    free(stars);
  }
}


int main(int argc, char *argv[]) {
  time_t startTime= getTime(); // starting time
  time_t currTime = startTime;
  time_t timePassed = 0;
  system("clear");
  //printf("%stest%st2\n", KRED, KGRN);
  displayTime(0);
  // program loop:
  while(1) {
    sleep(10); // TODO : how to not busy wait?? see systems code
    currTime = time(NULL);
    timePassed = currTime - startTime;
    if (timePassed % 60 == 0) {
      displayTime(secondsToMin(timePassed));
    }
  }

  return 0;
}
