#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ncurses.h>
#include <time.h>
#include <sys/shm.h>

// define buffer size fo saving message
#define BUFFSIZE 1024

// Declare Windows
WINDOW *base_scr, *input_scr, *output_scr, *account_scr, *time_scr;

// Define struct for saving input or output data
struct message_buffer {
	char name[20];
	char msg[BUFFSIZE];
	int id;
};

// Define struct for saving user information
typedef struct checkInfo {
	char userID[20];
	char message[40];
	char messageTime[20];
	int messageID;
	// Check the number of user in chat room
	int user_count;
	// Variable for saving user name
	char log[10][20];
} CHAT_INFO;

// Declare two instances of message_buffer struct for saving in & out message
struct message_buffer buff_in;
struct message_buffer buff_out;

// Declare for getting time
time_t now;
struct tm t;

// Declare Flag variable that indicates state now
int is_running;
// Declare chat information in global variable
CHAT_INFO *chatInfo;
// Declare global variable for saving time now
char time_now[50];

// Define functions
void print_chat();
void *get_input();
void chat();
void cleanup();
void die(char *msg);
void *show_time();
void *show_account();

int main(int argc, char* argv[]) {

	// Declare for saving shared memory id
	int shmID;
	// Declare for saving user name
	char userID[20];

	// Allocate memory 10 times of checkInfo struct to chatInfo 
	chatInfo = (CHAT_INFO *)malloc(sizeof(struct checkInfo) * 10);

	// Type casting from int to void*
	void *shmaddr = (void *) 0;

	// if user doesn't type name, the error message appears
	if(argc < 2){
		fprintf(stderr, "[Usage] : ./chat UserID \n");
		exit(-1);
	}

	// Saving user name in userID variable
	strcpy(userID, argv[1]);

	// Create shared memory id which key is 20200421 exclusively
	shmID = shmget((key_t)20200421, sizeof(CHAT_INFO), 0666|IPC_CREAT|IPC_EXCL);

	// If there's already shared memory exists, don't create and just get shared memory id
	if(shmID < 0){
		shmID = shmget((key_t)20200421, sizeof(CHAT_INFO), 0666);
	}

	// Set shared memory address
	shmaddr = shmat(shmID, (void *)0, 0000);

	// Set shared memory address in chatInfo
	chatInfo = (CHAT_INFO *) shmaddr;

	// saving user name in account list, buffer in name
	strcpy(chatInfo->log[chatInfo->user_count], userID);
	strcpy(buff_in.name, userID);
	// Increase user count that indicates the number of memebers in chat room
	chatInfo->user_count++;

	// Initiating screen
	initscr();

	// Call chat function
	chat();

	return 0;
}

void chat(){
	// Set windows' size
	base_scr = newwin(24, 80, 0, 0);
	output_scr = subwin(base_scr, 20, 60, 0, 0);
	input_scr = subwin(base_scr, 4, 60, 20,0);
	account_scr = subwin(base_scr, 20, 20, 0, 60);
	time_scr = subwin(base_scr, 4, 20, 20, 60);

	// Set box line in subwindows
	box(output_scr, ACS_VLINE, ACS_HLINE);
	box(input_scr, ACS_VLINE, ACS_HLINE);
	box(account_scr, ACS_VLINE, ACS_HLINE);
	box(time_scr, ACS_VLINE, ACS_HLINE);

	// Refresh subwindows
	wrefresh(output_scr);
	wrefresh(input_scr);
	wrefresh(account_scr);
	wrefresh(time_scr);

	// Set scroll ok
	scrollok(output_scr, TRUE);

	// Print message on output screen and draw box line, refresh
	mvwprintw(output_scr, 0, 1, "\n ***** Type /bye to quit!! ***** \n\n");
	box(output_scr, ACS_VLINE, ACS_HLINE);
	wrefresh(output_scr);

	// Initialize buffer ids and flag
	buff_in.id = 0;
	buff_out.id = 0;
	is_running = 1;

	// Declare thread for controlling chat program
	pthread_t thread[3];

	// Create 3 threads
	pthread_create(&thread[0], NULL, get_input, NULL);
	pthread_create(&thread[1], NULL, show_time, NULL);
	pthread_create(&thread[2], NULL, show_account, NULL);

	// Wait until all thread is finished
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	// Delete all windows
	delwin(base_scr);
	delwin(input_scr);
	delwin(output_scr);
	delwin(account_scr);
	delwin(time_scr);
}

void *get_input(){
	// Declare buffer for saving input message
	char tmp[BUFFSIZE];
	
	// Running until flag is changed
	while(is_running){
		// Get string from input screen to buffer
		mvwgetstr(input_scr, 1, 1, tmp);
		// Saving buffer's message to buff_in.msg
		sprintf(buff_in.msg, "%s\n", tmp);
		// if user type /bye
		// Change account list and refresh account screen
		if(strcmp(buff_in.msg, "/bye\n") == 0) {
			int i = 0;
			int j = 0;
			for(i=0; i<chatInfo->user_count; i++){
				if(strcmp(chatInfo->log[i], buff_in.name) == 0){
					for(j=i+1; j<chatInfo->user_count; j++){
						strcpy(chatInfo->log[j-1], chatInfo->log[j]);
						strcpy(chatInfo->log[j], "");
					}
				}
			}
			
			// Decrease user count
			chatInfo->user_count = chatInfo->user_count - 1;
			
			werase(account_scr);
			wrefresh(account_scr);
			// Exit
			die("exit");
		}
		// If user type ..
		// Call print_chat function
		else if(strcmp(buff_in.msg, "..\n") == 0){
			print_chat();
		}
		// If user type any message except last two
		// Saving user information and time in chatInfo list
		// messageID is unique for each message
		else{
			strcpy(chatInfo[chatInfo->messageID].userID, buff_in.name);
			strcpy(chatInfo[chatInfo->messageID].messageTime, time_now);
			strcpy(chatInfo[chatInfo->messageID].message, buff_in.msg);
			
			// Increase messageID
			chatInfo->messageID++;

			// Print user message on output screen
		    wprintw(output_scr, " [Send : %s] > %s", buff_in.name, buff_in.msg);
			// Increase buffer id
			buff_in.id++;
		}

		// Refresh output screen and input screen
		box(output_scr, ACS_VLINE, ACS_HLINE);
		wrefresh(output_scr);
		werase(input_scr);
		box(input_scr, ACS_VLINE, ACS_HLINE);
		wrefresh(input_scr);
		usleep(100);
	}
	return 0;
}

void print_chat(){
	
	int i=0;
			
	// If user type ..
	// Print all of messages in shared memory except user's own messages
	for(i=0; i<chatInfo->messageID; i++){
		memset(&*buff_out.msg, 0, BUFFSIZE);
		sprintf(buff_out.msg, " [Recv : %s [%s]] %s", 
			chatInfo[i].userID, chatInfo[i].messageTime, chatInfo[i].message);

		if(strcmp(chatInfo[i].userID,  buff_in.name) != 0){
			wprintw(output_scr, buff_out.msg);
			box(output_scr, ACS_VLINE, ACS_HLINE);
			wrefresh(output_scr);
		}
	}

	usleep(30000);
}

// Delete all windows
void cleanup(){
	delwin(base_scr);
	delwin(input_scr);
	delwin(output_scr);
	delwin(account_scr);
	delwin(time_scr);
	endwin();
}

// Delete all windows and exit
void die(char *s){
	delwin(input_scr);
	delwin(output_scr);
	delwin(account_scr);
	delwin(time_scr);
	endwin();
	perror(s);
	exit(1);
}

// This function shows current time and elapsed time
void *show_time(){
	
	int hour, min, sec;
	int elapsed = 0;
	int count = 0;

	// Running until flag is changed
	while(is_running){
		// Get current time
		time(&now);
		t = *localtime(&now);

		// This function sleeps in 500ms so we have to set count 2
		// because 1s = 500ms
		if(count == 2){
			elapsed++;
			// Change elapsed time to time form
			sec = elapsed % 60;
			min = (elapsed / 60) % 60;
			hour = elapsed / 3600;
		
			// set count 0
			count = 0;
		}
		// Saving current time in form that we want
		strftime(time_now, sizeof(time_now), "%H:%M:%S", &t);

		// Print current time and elapsed time on time screen and refresh
		mvwprintw(time_scr, 1, 1, time_now);
		mvwprintw(time_scr, 2, 1, "%02d:%02d:%02d", hour, min, sec);
		box(time_scr, ACS_VLINE, ACS_HLINE);
		wrefresh(time_scr);
		usleep(500000);
		// Increase count in 500ms
		count = count + 1;
	}
	return 0;
}

void *show_account(){
	// Running until the flag is changed
	while(is_running){
		int i=0;
		// Erase account list for showing account list's any changes
		werase(account_scr);

		// Print account list on account screen using user count
		for(i=0; i<chatInfo->user_count; i++){
			mvwprintw(account_scr, i+1, 1, chatInfo->log[i]);
		}
		// Refresh account screen
		box(account_scr, ACS_VLINE, ACS_HLINE);
		wrefresh(account_scr);
		sleep(1);
	}
	return 0;
}








