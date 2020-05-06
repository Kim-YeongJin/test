#include "digitalclock.h"

int main(){

    // Declare variables for subwindows and threads
    WINDOW *date_win, *time_win, *elapsed_win;
    pthread_t date_thread, time_thread, elapsed_thread;

    // Initiating window
    initscr();

    // set cursor
    curs_set(0);

    // Set subwindows' position
    date_win = subwin(stdscr, 5, 40, 0, 0);
    time_win = subwin(stdscr, 5, 30, 0, 40);
    elapsed_win = subwin(stdscr, 5, 30, 0, 70);

    // Set subwindows' borders
    box(date_win, ACS_VLINE, ACS_HLINE);
    box(time_win, ACS_VLINE, ACS_HLINE);
    box(elapsed_win, ACS_VLINE, ACS_HLINE);

    // Create Threads and Run
    date_thread = pthread_create(&date_thread, NULL, showdate, NULL);
    time_thread = pthread_create(&time_thread, NULL, showtime, NULL);
    elapsed_thread = pthread_create(&elapsed_thread, NULL, showelapsedtime, NULL);
    

    // Refresh each windows
    while(1){
	wrefresh(date_win);
        wrefresh(time_win);
        wrefresh(elapsed_win);
    }
    
    // After finishing all work, windows are deleted
    delwin(date_win);
    delwin(time_win);
    delwin(elapsed_win);
    endwin();


    return 0;
}
