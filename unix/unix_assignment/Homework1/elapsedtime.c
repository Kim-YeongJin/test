#include "digitalclock.h"

void *showelapsedtime(void *ptr){
    //Declare variables for storing hour, minute, second for each
    int hour, minute, second;
    // counting for each second
    int elapsed = 0;

    while(1){
	//Convert elapsed count to each time unit
	second = elapsed % 60;
	minute = (elapsed / 60) % 60;
	hour = elapsed / 3600;

	//Print on Window
	mvprintw(1, 71, "Elapsed Time");
        mvprintw(3, 71, "%02d:%02d:%02d", hour, minute, second); 

	sleep(1);
	//Increasing elapsed count
	elapsed++;
    }
}
