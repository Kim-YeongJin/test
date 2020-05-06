#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <ncurses.h>
#include <unistd.h>

time_t now;
struct tm t;

void *showdate(void *ptr);
void *showtime(void *ptr);
void *showelapsedtime(void *ptr);
