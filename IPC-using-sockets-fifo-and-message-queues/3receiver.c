/*
SOURCE - https://www.geeksforgeeks.org/ipc-using-message-queues/
* File server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define BUFFER_SIZE 22

struct mesg_buffer {
    long mesg_type;
    char mesg_text[22];
};

int main()
{
    key_t keyServerToClient;
    key_t keyClientToServer;
    int msgidClientToServer;
    int msgidServerToClient;
    int ret;
    int count;

    keyServerToClient = ftok("3receiver.c", 0);
    keyClientToServer = ftok("3sender.c", 1);

    struct mesg_buffer messageServerToClient;
    struct mesg_buffer messageClientToServer;

    messageClientToServer.mesg_type = 1;
    messageServerToClient.mesg_type = 1;

    count = 1;

    msgidClientToServer = msgget(keyClientToServer, 0666 | IPC_CREAT);
    if(msgidClientToServer == -1){
        perror("creating message queue from server");
        exit(EXIT_FAILURE);
    }

    msgidServerToClient = msgget(keyServerToClient, 0666 | IPC_CREAT);
    if(msgidServerToClient == -1){
        perror("creating message queue from client");
        exit(EXIT_FAILURE);
    }

    while(1){
    
        ret = msgrcv(msgidClientToServer, &messageClientToServer, sizeof(messageClientToServer), 1, 0);
        if(ret == -1){
            perror("receiving message from client to server");
            exit(EXIT_FAILURE);
        }

        printf("Data received is: ");

        for(int j = 0; j < BUFFER_SIZE-2; j++){
            printf("%c", messageClientToServer.mesg_text[j]);
        }

        printf(" with index: %d\n", messageClientToServer.mesg_text[BUFFER_SIZE-2]);

        if (((int) messageClientToServer.mesg_text[BUFFER_SIZE-2]) % 5 == 0){
            strcpy(messageServerToClient.mesg_text,messageClientToServer.mesg_text);
    
            ret = msgsnd(msgidServerToClient, &messageServerToClient, sizeof(messageServerToClient), 0);
            if (ret == -1){
                perror("sending message from client");
                exit(EXIT_FAILURE);
            }

            printf("\n");
        }

        count++;

        if(count > 50){
            break;
        }
    }
    
    return 0;
}