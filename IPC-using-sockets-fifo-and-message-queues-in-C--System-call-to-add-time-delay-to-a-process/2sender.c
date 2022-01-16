/*
SOURCE - https://www.geeksforgeeks.org/named-pipe-fifo-example-c-program/
* File client.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
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
    char characterArray [50][22] = {{0}};
    char fifoName [] = "myFifo";
    char _fifoName [] = "_myFifo";
    int count = 0;

    for (int x = 0; x < 50; x++){
        for (int i = 0; i < 20; i++){
            characterArray[x][i] = 'a' + rand() % 26;
        }
        characterArray[x][20] = x+1;
    }

    mkfifo(fifoName, 0666);
    mkfifo(_fifoName, 0666);

    while (1)
    {
        fd = open(fifoName, O_WRONLY);
        if(fd == -1){
            perror("cannot open file for writing in client");
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < 5; i++){
            
            ret = write(fd, characterArray[count*5 + i], strlen(characterArray[count])+1);
            if(ret == -1){
                perror("writing data in client");
                exit(EXIT_FAILURE);
            }

            sleep(1);
            
        }

        ret = close(fd);
        if (ret == -1){
            perror("closing file for writing in client");
            exit(EXIT_FAILURE);
        }
        
        _fd = open(_fifoName, O_RDONLY);
        if(_fd == -1){
            perror("cannot open file for reading in client");
            exit(EXIT_FAILURE);
        }

        ret = read(_fd, buffer, sizeof(buffer));
        if(ret == -1){
            perror("reading data in client");
            exit(EXIT_FAILURE);
        }

        printf("Highest ID received is %d\n", (int) buffer[BUFFER_SIZE-2]);

        close(_fd);
        if (ret == -1){
            perror("closing file for reading in client");
            exit(EXIT_FAILURE);
        }
        count++;
        if (count >= 10){
            printf("Fifo terminated\n");
            break;
        }
    }

    unlink(fifoName);
    unlink(_fifoName);
    return 0;
}