#ifndef __CHAT_SHM_H__ 
#define __CHAT_SHM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>

// Declare struct for saving chat information
typedef struct checkInfo {

    char userID[20];
    char messageTime[10];
    char message[40];
    int messageID; // I add messageID variable to distinguish each message

} CHAT_INFO;

// Define for checking current time
time_t now;
struct tm t;

// Define function that print chat message
void printchat(CHAT_INFO *chatInfo, int i);

#endif // __CHAT_SHM_H__
