#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define SYS_kernel_2d_memcpy 448

int main(int argc, char **argv)
{
    float m1[4][3] = {{1.0,2.0,3.0},{3.0,4.0,5.0},{5.0,6.0,7.0},{7.0,8.0,9.0}};
    float m2[4][3] = {{0.343,5.0,352.6},{34.0,453.0,7364.123},{45.70,1.0,92838.2424},{35,32,6567.1}};

    printf("This is the starting matrix:\n");

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf\t", m2[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int res = syscall(SYS_kernel_2d_memcpy, m2, m1, 4, 3);

    if(res < 0){
        perror("ERROR! Syscall not performing operation");
        exit(1);
    }

    printf("This is the final matrix:\n");

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 3; j++){
            printf("%lf\t", m2[i][j]);
        }
        printf("\n");
    }

    return 0;
}