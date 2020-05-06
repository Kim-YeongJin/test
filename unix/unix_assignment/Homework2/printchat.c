#include "chatshm.h"

// Print userID, messageTime, message
void printchat(CHAT_INFO *chatInfo, int i){
    printf("[%s] %s : %s\n", chatInfo[i].userID, chatInfo[i].messageTime, chatInfo[i].message);
}
