#include "digitalclock.h"

void *showdate(void *ptr){
    // Declare variable for storing date data
    char date[50];

    while(1){
	time(&now);
	t = *localtime(&now);

        //Calculate current time and convert to form that we want
	strftime(date, sizeof(date), "%Y-%m-%d", &t);
	
	//Print On Window
	mvprintw(1, 2, "Local Date");
	mvprintw(3, 2, date);
        sleep(1);
    }

}


