#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t forks[5];
sem_t room;
int numMeals[5];
int status[5];

void * philosopherFunc(void * philNo){
    int philosopherNum = *(int *)philNo;
    while(1){
        sleep(1);
        sem_wait(&room);
        printf("\nPhilosopher %d has entered room ", philosopherNum);
        sem_wait(&forks[(philosopherNum+1)%5]);
        sem_wait(&forks[philosopherNum]);

        numMeals[philosopherNum]++;
        printf("\nPhilosopher %d has EATEN %d meals", philosopherNum, numMeals[philosopherNum]);
        status[philosopherNum] = 0;

        sleep(1);
        sem_post(&forks[(philosopherNum+1)%5]);
        sem_post(&forks[philosopherNum]);
        sem_post(&room);
        printf("\nPhilosopher %d has EXITTED room and is thinking", philosopherNum);
    }
    
}

int main(){

    int philNo[5];
    printf("\nALL PHILOSOPHERS ARE THINKING\n");
    pthread_t thread_ids[5];
    sem_init(&room, 0, 4);

    for(int i = 0; i < 5; i++){
        sem_init(&forks[i], 0, 1);
        numMeals[i] = 0;
        status[i] = 1;
    }

    int i = 0;

    for(int i = 0; i < 5; i++){
        philNo[i] = i;
        pthread_create(&thread_ids[i], NULL, philosopherFunc, (void *)&philNo[i]);
    }

    for (int i = 0; i < 5; i++){
        pthread_join(thread_ids[i], NULL);
    }

}

