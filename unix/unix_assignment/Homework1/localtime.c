#include "digitalclock.h"

void *showtime(void *ptr){

    //Declare variable for storing current time data
    char time_now[50];

    while(1){
	time(&now);
	t = *localtime(&now);

	//Calculate time and convert to form that we want
	strftime(time_now, sizeof(time_now), "%H-%M-%S", &t);
	
	//Print on Window
	mvprintw(1, 41, "Local Time");
	mvprintw(3, 41, time_now);

	sleep(1);
    }

}


