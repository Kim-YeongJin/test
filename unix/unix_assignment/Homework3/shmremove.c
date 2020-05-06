#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>

typedef struct checkInfo {
 
    char userID[20];
    char messageTime[10];
 	char message[40];
    int messageID; // I add messageID variable to distinguish each message

} CHAT_INFO;


int main() {

    // Define for saving shared memory Id
    int shmID;

    // Get shared memory ID which has key 20200406
    shmID = shmget((key_t)20200421, sizeof(CHAT_INFO), 0666);

    // If there's no shared memory ID which has key 20200406, then print error message
    if(shmID < 0){
	perror ("shmget failed : ");
	exit(-1);
    }

    // Delete shared memory
    // If there's no shared memory to delete, print error message
    if(shmctl(shmID, IPC_RMID, 0) < 0) {
	printf("Failed to delete shared memory\n");
	exit(-1);
    }
    // If deleting is finished successfully, print success message
    else {
	printf("Successfully delete shared memory\n");
    }

    return 0;
}
