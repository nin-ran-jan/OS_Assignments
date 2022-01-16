/*
SOURCE - https://man7.org/linux/man-pages/man7/unix.7.html
* File server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/signal.h>
#include <unistd.h>

#define SOCKET_NAME "mySocket.socket"
#define BUFFER_SIZE 22

int main(int argc, char *argv[])
{
    struct sockaddr_un name;
    int down_flag = 0;
    int ret;
    int connection_socket;
    int data_socket;
    char buffer[BUFFER_SIZE];

    connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (connection_socket == -1) {
        perror("socket creation error from server");
        exit(EXIT_FAILURE);
    }

    memset(&name, 0, sizeof(name));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, SOCKET_NAME, sizeof(name.sun_path) - 1);

    ret = bind(connection_socket, (const struct sockaddr *) &name, sizeof(name));
    if (ret == -1) {
        perror("binding error from server");
        exit(EXIT_FAILURE);
    }

    ret = listen(connection_socket, 2);
    if (ret == -1) {
        perror("listening error from server");
        exit(EXIT_FAILURE);
    }

    data_socket = accept(connection_socket, NULL, NULL);
    if (data_socket == -1) {
        perror("accepting error from server");
        exit(EXIT_FAILURE);
    }

    int countOfStrings = 0;

    while(1) {
        while(1) {
            countOfStrings++;
            ret = read(data_socket, buffer, sizeof(buffer));
            if (ret == -1) {
                perror("reading error from server");
                exit(EXIT_FAILURE);
            }
            buffer[sizeof(buffer) - 1] = 0;
            if (!strncmp(buffer, "END", sizeof(buffer))) {
                countOfStrings--;
                if(countOfStrings >= 50){
                    down_flag = 1;
                }
                break;
            }
            if ((int) buffer[BUFFER_SIZE - 2] % 5 == 0){
                ret = write(data_socket, buffer, sizeof(buffer));
                if (ret == -1) {
                    perror("writing error from server, while sending back information to the client");
                    exit(EXIT_FAILURE);
                }
            }
            printf("Accepted string is: ");
            for (int i = 0; i <= BUFFER_SIZE-3; i++){
                printf("%c",buffer[i]);
            }
            printf(" with ID: %d\n", (int) buffer[BUFFER_SIZE-2]);
            if (countOfStrings % 5 == 0){
                printf("\n");
            }
        }

        if (down_flag) {
            printf("Server terminated\n");
            break;
        }

    }

    if (close(data_socket) == -1){
        perror("not closing properly from server");
        exit(EXIT_FAILURE);
    }
    if (close(connection_socket) == -1){
        printf("not closing properly from server");
        exit(EXIT_FAILURE);
    }
    if (unlink(SOCKET_NAME) == -1){
        printf("not unlinking the socket from server");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
