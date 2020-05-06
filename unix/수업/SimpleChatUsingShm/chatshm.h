#ifndef __CHAT_SHM_H__  // guarantee include once 
// ifndef = if not defined and then define __CHAT_SHM_H__
#define __CHAT_SHM_H__

typedef struct checkInfo {

    char userID[20];
    long messageTime;
    char message[40];

} CHAT_INFO;

#endif // __CHAT_SHM_H__ (guarantee include once)
