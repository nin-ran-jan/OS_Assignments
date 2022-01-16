#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

struct args{
    char *fileName;
    char *AB;
};

int totalCumulativeMarks [] = {0,0,0,0,0,0};
int totalRowIndex = 0;

void * getAvgerage(void * args1){

    struct args * arguments = args1;

    int fileDescriptor;
    char buffer;
    int cumulativeAssignmentMarks [] = {0,0,0,0,0,0}; //can take the marks of 6 assignments

    fileDescriptor = open(arguments->fileName, O_RDONLY);
    if (fileDescriptor < 0){
        printf("ERROR! File could not be opened.\n\n");
        exit(1);
    }


    int columnIndex = 0;
    int rowIndex = 0;
    char * line = (char *) calloc(201, sizeof(char));   //each row has no more than 200 characters.

    int temp = 0;

    while(1){    //will only proceed if the file has no errors and some value stored in the buffer

        temp = read(fileDescriptor, &buffer, 1);

        if (temp <= -1){
            printf("ERROR! The file was improperly read.\n\n");
            exit(1);
        }

        else if (temp == 0){
            break;
        }
        
        else if (buffer == '\n'){
            line[columnIndex] = '\0';
            columnIndex = 0;
            
            
            char* token = strtok(line, ",");
            int count = 0;
            while (token != NULL) {

                if (count == 0){
                    token = strtok(NULL, ",");
                    count++;
                }

                else if (count == 1 && strcmp(token, arguments->AB) == 0){
                    rowIndex++;
                    for (int i = 0; i < 6; i++){
                        token = strtok(NULL, ",");
                        cumulativeAssignmentMarks[i] += atoi(token);
                    }
                    break;
                }

                else{
                    break;
                }
            }

        }

        else{
            line[columnIndex] = buffer;
            columnIndex++;
        }
        
    }

    close(fileDescriptor);

    totalRowIndex += rowIndex;

    printf("The average marks of Section %s are:\n", arguments->AB);
    
    for(int i = 0; i < 6; i++){
        totalCumulativeMarks[i] += cumulativeAssignmentMarks[i];
        double averageForEachAssignment = (double) (cumulativeAssignmentMarks[i]);
        averageForEachAssignment /= (double) rowIndex;
        printf("Average marks of Assignment %d is %lf\n", i+1, averageForEachAssignment);
    }
    
    free(line);    
    pthread_exit(NULL);

}


int main(int argc, char * argv []) {

    struct args args1, args2;
    args1.fileName = argv[1];
    args2.fileName = argv[1];
    args1.AB = "B";
    args2.AB = "A";

    pthread_t thread_id1;
    pthread_t thread_id2;

    int tid =  pthread_create(&thread_id1, NULL, &getAvgerage, (void *) &args1);

    if (tid != 0){
        printf("ERROR! Couldn't create a thread.\n\n");
        exit(1);
    }

    tid =  pthread_create(&thread_id2, NULL, &getAvgerage, (void *) &args2);

    if (tid != 0){
        printf("ERROR! Couldn't create a thread.\n\n");
        exit(1);
    }

    tid = pthread_join(thread_id1, NULL);

    if (tid != 0){
        printf("ERROR! Couldn't join a thread.\n\n");
        exit(1);
    }

    tid = pthread_join(thread_id2, NULL);

    if (tid != 0){
        printf("ERROR! Couldn't join a thread.\n\n");
        exit(1);
    }

    printf("\nFinal Output - Students of the entire batch:\n");

    for(int i = 0; i < 6; i++){
        double averageForEachAssignment = (double) (totalCumulativeMarks[i]);
        averageForEachAssignment /= (double) totalRowIndex;
        printf("Total average marks of Assignment %d is %lf\n", i+1, averageForEachAssignment);
    }

    printf("\n");

    exit(0);
    
    return 0;
}