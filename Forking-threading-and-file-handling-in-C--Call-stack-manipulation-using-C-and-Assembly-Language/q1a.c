#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

void getAvgerage(char *fileName, char *AB){

    int fileDescriptor;
    char buffer;
    int cumulativeAssignmentMarks [] = {0,0,0,0,0,0}; //can take the marks of 6 assignments

    fileDescriptor = open(fileName, O_RDONLY);
    if (fileDescriptor < 0){
        printf("ERROR! File could not be opened.\n\n");
        exit(1);
    }


    int columnIndex;
    int rowIndex;
    char * line = (char *) calloc(201, sizeof(char));   //each row has no more than 200 characters.

    int temp = 0;

    while(1){
        
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

                else if (count == 1 && strcmp(token, AB) == 0){
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

    if (close(fileDescriptor) == -1){
        printf("ERROR! The close() system call could not close the file.\n\n");
        exit(1);
    }
    
    printf("The average marks of Section %s are:\n", AB);
    
    for(int i = 0; i < 6; i++){
        double averageForEachAssignment = (double) (cumulativeAssignmentMarks[i]);
        averageForEachAssignment /= (double) rowIndex;
        printf("Average marks of Assignment %d is %lf\n", i+1, averageForEachAssignment);
    }
    
    free(line);
    

    return;

}


int main(int argc, char * argv []) {
    
    pid_t pid = fork();
    
    if (pid <= -1){
        printf("ERROR! The fork() function could not create a fork.\n\n");
        exit(1);
    }

    else if (pid == 0){
        printf("Child Process executed first with ID = %d\n",getpid());
        getAvgerage(argv[1], "A");
        printf("\n");
        exit(0);
    }

    else{

        pid = waitpid(pid, NULL, 0);

        if (pid == -1){
            printf("ERROR! The waitpid() system call could not execute.\n\n");
            exit(1);
        }

        else{
            printf("Parent Process executed later with ID = %d\n", getpid());
            getAvgerage(argv[1], "B");
            printf("\n");
            exit(0);
        }
    }

    return 0;
}