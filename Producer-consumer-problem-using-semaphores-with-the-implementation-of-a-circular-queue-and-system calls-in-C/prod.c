#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<wait.h>
#include<sys/time.h>
#include<time.h>
#include<signal.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>
#include <fcntl.h>

int main(){
    int fd = open("/dev/urandom", O_RDONLY);
    while(1){
        unsigned char array[8];
        int element = read(fd, &array, 8); //reading 8 bytes from the urandom file
        unsigned long long number = 0; //initializing number to 0
        for (int i = 0; i < 8; i++){
            number = number << 8; //left shifting the number by 8 bits. 
            number |= array[i]; //storing the character (1 byte = 8 bits), into this number. 
            //Repeating the process 8 times to get a 64 bit number
        }
        if (syscall(450, number) == 0){
            printf("Producer -> %llu \n", number);
            sleep(1);
        }
    }
}