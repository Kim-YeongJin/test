#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "chatshm.h"

int main() {

    int shmID; // shmget return type is int

    shmID = shmget((key_t)3836, sizeof(CHAT_INFO), 0666);

    if(shmID < 0){
	perror ("shmget failed : ");
	exit(-1);
    }

    if(shmctl(shmID, IPC_RMID, 0) < 0) {
	printf("Failed to delete shared memory\n");
	exit(-1);
    }
    else {
	printf("Successfully delete shared memory\n");
    }

    return 0;
}
