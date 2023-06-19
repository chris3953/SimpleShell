#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BLOCK_SIZE 116

int main(int argc, char *argz[])
{

    char Buffer[BLOCK_SIZE];
    char *StoresCommands[strlen(Buffer)];
    char delim[] = " ";


    while (1)
    {
        printf("prompt$ ");
        // grabs user input
        scanf("%[^\n]%*c", Buffer);
        // created an array to store each user command

        // creates a token value of each user command ignoring white space
        char *Tokenize = strtok(Buffer, delim);
        int count = 0;
        StoresCommands[count] = Tokenize;

        // strtok returns null when there is no more data left
        //  loads users commands
        while (Tokenize != NULL)
        {
            // printf("%s\n", StoresCommands[count]);
            Tokenize = strtok(NULL, delim);
            count = count + 1;
            StoresCommands[count] = Tokenize;
        }

        pid_t childProcessID;
        int pid = fork();
        int status;


        if (pid == 0) // Checks to ensure pid is 0 and runs execvp where the child process is. If it fails with a status code of -1 it exits();
        {
            status = execvp(StoresCommands[0], StoresCommands);
            if (status < 0)
            {
                exit(0);
            }
        }
        else
        {
            childProcessID = wait(&status); // Waits for the child to finish its buisness and prints out the PID and status.
            printf("Child %d, exited with %d\n", childProcessID, status);
        }
    }

    free(Buffer); // Frees up the memory allocated
    free(StoresCommands);

    return 0;
}