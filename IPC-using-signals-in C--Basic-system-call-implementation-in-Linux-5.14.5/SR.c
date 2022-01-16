#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>

#define _XOPEN_SOURCE 700

pid_t S1;

unsigned int randomNumberGenerator();

void signalAlarmHandler(int signalNumber){
    int random_number_generated = randomNumberGenerator();
    // printf("%u\n", random_number_generated);
    const union sigval signal_value = {random_number_generated};
    // signal_value.sival_int = random_number_generated;
    sigqueue(S1, SIGTERM, signal_value);
}

unsigned int randomNumberGenerator()
{
    int k = 0;
    unsigned int value;
    while (k < 20)
    {
        asm("rdrand %0\n\t"
        :"=a"(value)::);
        if (value == 0){
            break;
        }
        k++;
    }
    return value;
}


int main(int argc, char const *argv[])
{
    S1 = atoi(argv[0]);
    // printf("\n%d\n", S1);
    struct itimerval tm;
    tm.it_interval.tv_sec = 1;
    tm.it_interval.tv_usec = 100000;
    tm.it_value.tv_sec = 1;
    tm.it_value.tv_usec = 100000;
    struct sigaction signal_action1;
    memset(&signal_action1, 0, sizeof(signal_action1));
    signal_action1.sa_handler = &signalAlarmHandler;
    sigaction(SIGALRM, &signal_action1, NULL);
    setitimer(ITIMER_REAL, &tm, NULL);

    while(1);

    return 0;
}