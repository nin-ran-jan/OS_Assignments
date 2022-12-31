/*
SOURCE - https://www.geeksforgeeks.org/ipc-using-message-queues/
* File client.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define BUFFER_SIZE 22

struct mesg_buffer {
    long mesg_type;
    char mesg_text[BUFFER_SIZE];
};
  
int main()
{
    key_t keyServerToClient;
    key_t keyClientToServer;
    int msgidClientToServer;
    int msgidServerToClient;
    int ret;
    int count;
    char characterArray [50][22] = {{0}};

    for (int x = 0; x < 50; x++){
        for (int i = 0; i < 20; i++){
            characterArray[x][i] = 'a' + rand() % 26;
        }
        characterArray[x][20] = x+1;
    }

    keyServerToClient = ftok("3receiver.c", 0);
    keyClientToServer = ftok("3sender.c", 1);

    struct mesg_buffer messageServerToClient;
    struct mesg_buffer messageClientToServer;

    messageClientToServer.mesg_type = 1;
    messageServerToClient.mesg_type = 1;

    msgidClientToServer = msgget(keyClientToServer, 0666 | IPC_CREAT);
    if(msgidClientToServer == -1){
        perror("creating message queue from client");
        exit(EXIT_FAILURE);
    }

    msgidServerToClient = msgget(keyServerToClient, 0666 | IPC_CREAT);
    if(msgidServerToClient == -1){
        perror("creating message queue from client");
        exit(EXIT_FAILURE);
    }

    count = 1;

    while(1){

        for(int i = 0; i < 5; i++){

            strcpy(messageClientToServer.mesg_text,characterArray[count-1]);
            
            ret = msgsnd(msgidClientToServer, &messageClientToServer, sizeof(messageClientToServer), 0);
            if (ret == -1){
                perror("sending message from client");
                exit(EXIT_FAILURE);
            }

            count++;
            if (count > 50){
                break;
            }
        }

        ret = msgrcv(msgidServerToClient, &messageServerToClient, sizeof(messageServerToClient), 1, 0);
        if(ret == -1){
            perror("receiving message from client to server");
            exit(EXIT_FAILURE);
        }

        printf("Highest index received is: %d\n", messageServerToClient.mesg_text[BUFFER_SIZE-2]);

        if (count > 50){
            break;
        }
        
    }

    ret = msgctl(msgidClientToServer, IPC_RMID, NULL);
    if(ret == -1){
        perror("could not destroy message queue");
        exit(EXIT_FAILURE);
    }

    ret = msgctl(msgidServerToClient, IPC_RMID, NULL);
    if(ret == -1){
        perror("could not destroy message queue");
        exit(EXIT_FAILURE);
    }

    return 0;
}

