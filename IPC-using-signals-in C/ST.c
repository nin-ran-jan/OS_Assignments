
#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>

#define _XOPEN_SOURCE 700

pid_t S1;
unsigned long cpuCycles;

void signalAlarmHandler(int signalNumber){
    unsigned long eax, edx;
    asm volatile("rdtsc\n\t":
    "=a" (eax), "=d" (edx));
    cpuCycles = ((unsigned long)eax | (unsigned long)edx << 32);
    // printf("%lu\n", cpuCycles);
    union sigval signal_value;
    signal_value.sival_int = cpuCycles;
    sigqueue(S1, SIGTERM, signal_value);
    kill(getpid(), SIGTERM);    
}

void signalTerminationHandler(int signal_number){
    unsigned long totalSeconds = cpuCycles/2.4e9;
    unsigned long hours = totalSeconds/3600;
    totalSeconds = totalSeconds - 3600*hours;
    unsigned int minutes = totalSeconds/60;
    totalSeconds = totalSeconds - 60*minutes;
    unsigned int seconds = totalSeconds;
    printf("Time: %lu hours, %u minutes and %u seconds\n", hours, minutes, seconds);
}


int main(int argc, char const *argv[])
{
    S1 = atoi(argv[0]);
    struct itimerval tm;
    tm.it_interval.tv_sec = 1;
    tm.it_interval.tv_usec = 100000; 
    tm.it_value.tv_sec = 1;
    tm.it_value.tv_usec = 100000;
    struct sigaction signal_action;
    memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_handler = &signalTerminationHandler;
    struct sigaction signal_action2;
    memset(&signal_action2, 0, sizeof(signal_action2));
    signal_action2.sa_handler = &signalAlarmHandler;
    sigaction(SIGALRM, &signal_action2, NULL);
    sigaction(SIGTERM, &signal_action, NULL);
    setitimer(ITIMER_REAL, &tm, NULL);

    while(1);

    return 0;
}