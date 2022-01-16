/*
SOURCE - https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
* File server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 22

int main(int argc, char *argv[])
{
    int fd = 0;
    int _fd = 0;
    int ret = 0;
    char buffer[BUFFER_SIZE];
    char fifoName [] = "myFifo";
    char _fifoName [] = "_myFifo";
    int count = 1;

    mkfifo(fifoName, 0666);
    mkfifo(_fifoName, 0666);
    

    while (1)
    {
        fd = open(fifoName, O_RDONLY);
        if(fd == -1){
            perror("cannot open file for reading in client");
            exit(EXIT_FAILURE);
        }

        ret = read(fd, buffer, sizeof(buffer));
        if(ret == -1){
            perror("reading data in client");
            exit(EXIT_FAILURE);
        }


        printf("Accepted string is: ");
        for (int i = 0; i <= BUFFER_SIZE-3; i++){
            printf("%c",buffer[i]);
        }
        printf(" with ID: %d\n", (int) buffer[BUFFER_SIZE-2]);
        if (count % 5 == 0){
            printf("\n");
        }

        close(fd);
        if (ret == -1){
            perror("closing file for reading in client");
            exit(EXIT_FAILURE);
        }

        if (count % 5 == 0){
            _fd = open(_fifoName, O_WRONLY);
            if(_fd == -1){
                perror("cannot open file for writing in client");
                exit(EXIT_FAILURE);
            }

            ret = write(_fd, buffer, strlen(buffer)+1);
            if(ret == -1){
                perror("writing data in client");
                exit(EXIT_FAILURE);
            }

            ret = close(_fd);
            if (ret == -1){
                perror("closing file for writing in client");
                exit(EXIT_FAILURE);
            }
        }
        
        count++;
        if (count > 50){
            break;
        }
    }

    return 0;
}
