#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "chatshm.h"

int main(int argc, char* argv[]) {

    int shmID; // shmget return type is int
    char userID[20];
    CHAT_INFO *chatInfo = NULL;

    void *shmaddr = (void *) 0;

    if(argc < 2){
	fprintf(stderr, "[Usage]: ./shmwrite UserID \n");
    	exit(-1);
    }

    strcpy(userID, argv[1]);

    shmID = shmget((key_t)3836, sizeof(CHAT_INFO), 0666);

    if(shmID < 0){
	
    }

    shmaddr = shmat(shmID, (void *)0, 0000);
    chatInfo = (CHAT_INFO *) shmaddr; // void * -> CHAT_INFO*

    printf("-------------- Chat Message -------------\n");
    while(1){
	char inputstr[40];

	printf("Enter your message : ");
	fgets(inputstr, 40, stdin);
	strcpy(chatInfo->userID, userID);
	chatInfo->messageTime++;
	strcpy(chatInfo->message, inputstr);
    }
    

    return 0;
}
