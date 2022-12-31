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

int main(){
    while(1){
        unsigned long long element = 0;
        if(syscall(449, &element) != 1){
            printf("Consumer -> %llu \n", element);
        }
    }
}