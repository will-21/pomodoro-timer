/**
* Pomodoro timer in C
*
* Try to figure out if sleep() wastes a lot of cpu time - if so, alternatives?
*
* dev - Will Pryor
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h> // TODO : use this
//#include <conio.h> // sound plalying stuff
//#include "inc/fmod.h" // sound playing stuff
//#include "SDL/SDL.h"
//#include "SDL/SDL_mixer.h"

/*    CONSTANTS         */
#define WORK_TIME 2//25 // time (min) to work for 1 cycle
#define REST_TIME 5 // time (min) to rest after each cycle
#define NUM_CYCLES 4 // number of cycles before a longer break
#define BREAK_TIME 20 // time (min) to rest after NUM_CYCLES
#define MAX_NUM_POMS 8 // maximum # pomodoros before the program ends
#define SECONDS_IN_MINUTE 5 // 60 changeable for debugging / demos

typedef enum {
  WORK,
  REST,
  BREAK,
} State;

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
* Displays the rest timer for short rests between pomodoros
*
*
*/
int displayRest() {
  for (int i = 0; i < REST_TIME; i++) {
    system("clear");
    printf("%sDone working! Take a rest for %d minutes!%s\n", KGRN, REST_TIME, KWHT);
    printf("[ %.*s%.*s ]\n", i, "*****", REST_TIME - i, "-----");
    sleep(SECONDS_IN_MINUTE);
  }
  system("clear");
  printf("%sShort rest finished. Back to work!%s\n", KGRN, KWHT);
  printf("[ %.*s ]\n", REST_TIME, "*****");
  sleep(5);
}

/**
* Displays the break timer for longer breaks
*
*/
void displayBreak() {
  for (int i = 0; i < BREAK_TIME; i++) {
    system("clear");
    printf("%sGreat job! Take a longer break for %d minutes.%s\n", KGRN, BREAK_TIME, KWHT);
    printf("[ %.*s%.*s ]\n", i, "**********************", BREAK_TIME - i, "--------------------");
    sleep(SECONDS_IN_MINUTE);
  }
  system("clear");
  printf("%sBreak finished. Back to work!%s\n", KGRN, KWHT);
  printf("[ %.*s ]\n", BREAK_TIME, "********************");
  sleep(5);
}

/**
* Displays time on the screen
*     -not sure how yet - options for CLI printout vs gui??
*     -start with CLI
*     -display a star per min to indicate progress out of 25
*/
void displayTime(int num_stars, int pomCounter) { // TODO: make enum status
  //if (st == WORK) {
    //fflush(stdout); // TODO : necessary??
    system("clear");
    if (num_stars >= WORK_TIME) { // TODO : add audio or something
      //printf("%sDone working! Take a break for %d minutes!%s\n", KGRN, REST_TIME, KWHT);
      displayRest();
    }
    else {
      printf("Pomodoro %d\n", pomCounter);
      printf("Progress: %s%d min %sout of %s%d min%s\n\n", KGRN, num_stars, KWHT, KRED, WORK_TIME, KWHT);
      printf("[ %s%.*s%s%.*s %s]\n", KGRN, num_stars, "*************************", KRED,
      (WORK_TIME - num_stars), "-------------------------", KWHT);
    }
    sleep(5);
}

int main(int argc, char *argv[]) {
  time_t startTime= getTime(); // starting time
  time_t currTime = startTime;
  time_t timePassed = 0;
  time_t minPassed = 1;
  int pomCounter = 1; // counter for which Pomodoro this is
  State st = WORK;

  system("clear");
  displayTime(0, pomCounter);
  sleep(SECONDS_IN_MINUTE); // TODO : how to not busy wait?? see systems code
  // program loop:
  while(pomCounter < MAX_NUM_POMS + 1) {
    displayTime(minPassed, pomCounter);
    minPassed++;
    if (minPassed > WORK_TIME) { // short rest time
      minPassed = 0;
      pomCounter++;
      displayTime(minPassed, pomCounter);
    }
    else if (pomCounter == NUM_CYCLES) { // longer break time
      displayBreak();
    }
    sleep(SECONDS_IN_MINUTE); // TODO : how to not busy wait?? see systems code
  }
  printf("Done! Great job focusing!\n");
  return 0;
}
