/*
SOURCE - https://man7.org/linux/man-pages/man7/unix.7.html
* File client.c
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <math.h>

#define SOCKET_NAME "mySocket.socket"
#define BUFFER_SIZE 22

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int ret;
    int data_socket;
    char buffer[BUFFER_SIZE];
    char characterArray [50][22] = {{0}};

    for (int x = 0; x < 50; x++){
        for (int i = 0; i < 20; i++){
            characterArray[x][i] = 'a' + rand() % 26;
        }
        characterArray[x][20] = x+1;
    }

    data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (data_socket == -1) {
        perror("socket creation error from client");
        exit(EXIT_FAILURE);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

    ret = connect(data_socket, (const struct sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        perror("server connection error from client");
        exit(EXIT_FAILURE);
    }

    int countOfStrings = 0;
    while (1){
        while(1){
            ret = write(data_socket, characterArray[countOfStrings], strlen(characterArray[countOfStrings]) + 1);
            if (ret == -1) {
                perror("writing data to socket from client");
                exit(EXIT_FAILURE);
            }
            countOfStrings++;
            if (countOfStrings%5 == 0){
                break;
            }
        }
        strcpy(buffer, "END");
        ret = write(data_socket, buffer, strlen(buffer) + 1);
        if (ret == -1) {
            perror("writing \"END\" to the socket from client");
            exit(EXIT_FAILURE);
        }
        memset(buffer,0,sizeof(buffer));
        ret = read(data_socket, buffer, sizeof(buffer));
        if (ret == -1) {
            perror("reading info back from the server to client");
            exit(EXIT_FAILURE);
        }
        printf("Highest ID received is %d\n", (int) buffer[BUFFER_SIZE-2]);
        memset(buffer,0,sizeof(buffer));
        if (countOfStrings >= 50){
            break;
        }
    }

    ret = close(data_socket);
    if(ret == -1){
        perror("closing data socket");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

}