#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "chatshm.h"

int main() {

    int shmID; // shmget return type is int
    CHAT_INFO *chatInfo = NULL;

    void *shmaddr = (void *) 0;

    shmID = shmget((key_t)3836, sizeof(CHAT_INFO), 0666|IPC_CREAT|IPC_EXCL);

    if(shmID < 0){
	
    }

    shmaddr = shmat(shmID, (void *)0, 0000);
    chatInfo = (CHAT_INFO *) shmaddr; // void * -> CHAT_INFO*

    printf("-------------- Chat Message -------------\n");
    while(1){
	printf("[%s]%ld : %s\n",
		chatInfo->userID,
		chatInfo->messageTime,
		chatInfo->message);
	
	if(!strcmp(chatInfo->message, "/exit\n")){
		printf("%s is out\n", chatInfo->userID);
		break;
	}

	sleep(3);
    }
    

    return 0;
}
