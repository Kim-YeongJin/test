#include "chatshm.h"

int main() {

    // Define for saving shared memory Id
    int shmID;

    // Get shared memory ID which has key 20200406
    shmID = shmget((key_t)20200406, sizeof(CHAT_INFO), 0666);

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
