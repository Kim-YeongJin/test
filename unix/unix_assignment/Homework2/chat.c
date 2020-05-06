#include "chatshm.h"

int main(int argc, char* argv[]) {

    int shmID; // Define for saving shared memory ID
    char userID[20]; // Define for saving user ID
    
    // Declare instance of CHAT_INFO struct and allocate memory 10 times of checkInfo struct
    CHAT_INFO *chatInfo = (CHAT_INFO *)malloc(sizeof(struct checkInfo) * 10);

    // Declare shared memory address for 0 and type casting int to void*
    void *shmaddr = (void *) 0;

    // If user doesn't type userID, messenger print error message
    if(argc < 2){
	fprintf(stderr, "[Usage]: ./chat UserID \n");
    	exit(-1);
    }

    // Save user ID in userID variable
    strcpy(userID, argv[1]);

    // Create 1 shared memory, its key is 20200406
    shmID = shmget((key_t)20200406, sizeof(CHAT_INFO), 0666|IPC_CREAT|IPC_EXCL);

    // If there already exists shared memory which has key 20200406, then Dont' create sharedmemory
    // and just reference shared memory ID
    if(shmID < 0){
	shmID = shmget((key_t)20200406, sizeof(CHAT_INFO), 0666);
    }

    // attach shared memory into process
    shmaddr = shmat(shmID, (void *)0, 0000);
    // type casting from void* to CHAT_INFO*
    chatInfo = (CHAT_INFO *) shmaddr;

    printf("-------------- Chat Message -------------\n");
    while(1){
	// Define variables for saving message and current time
	char inputstr[40];
	char time_now[50];

	// get input message from user and save in inputstr
	printf("Enter your message : ");
	fgets(inputstr, 40, stdin);
	
	// get current time
	time(&now);
	t = *localtime(&now);

	// Change form to what we want
	strftime(time_now, sizeof(time_now), "%H:%M:%S", &t);	

	// if user type "..", print all message except user's own message
	if(strcmp(inputstr, "..\n")==0){
	    int i = 0;
	    for(i=0; i<chatInfo->messageID; i++){
		if(strcmp(chatInfo[i].userID, userID) != 0){
		    printchat(chatInfo, i);
		}
	    }
	}
	// if user type /bye, break loop
	else if(strcmp(inputstr, "/bye\n")==0){
	    break;
	}
	// If user type any message, save each message in chatInfo shared memory
	else{
	    strcpy(chatInfo[chatInfo->messageID].userID, userID);
	    strcpy(chatInfo[chatInfo->messageID].messageTime, time_now);
	    strcpy(chatInfo[chatInfo->messageID].message, inputstr);
	
	    // Print user's own message echoed
	    printchat(chatInfo, chatInfo->messageID);
	    // Increase messageID for distinguish each message
            chatInfo->messageID++;
	}
    }

    return 0;
}
