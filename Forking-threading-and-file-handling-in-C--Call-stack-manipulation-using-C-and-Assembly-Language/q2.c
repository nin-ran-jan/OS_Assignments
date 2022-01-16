#include <stdio.h>
#include <stdlib.h>
#include "C.c"

extern void B(long t);

void A(){

    long input;

    printf("Input a signed 64-bit integer: ");
    scanf("%ld", &input);

    B(input);
}

int main(){

    A();

    return 0;
}