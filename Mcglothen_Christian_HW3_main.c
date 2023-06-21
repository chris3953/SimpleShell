/**************************************************************
* Class:  CSC-415-02 Summer 2023
* Name:Christian McGlothen
* Student ID:918406078
* GitHub ID:chris3953
* Project: Assignment 3 – Simple Shell
*
* File: <Mcglothen_Christian_HW3_main.c>
*
* Description: The purpose of this assignment is to practice forking and understanding processes.
  The assignment covers prompting user input while parsing and using commands such
  as execvp() and strtok() which allows for use of linux command line executions and tokenizing 
  C strings. 
*
**************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define BLOCK_SIZE 116

char Buffer[BLOCK_SIZE]; 
char *StoresCommands[BLOCK_SIZE];
char UserInput[BLOCK_SIZE];
char delim[] = " ";
int ResultOFexecvp; 

int main(int argc, char *argz[])
{
    // while creates an inifite loop until broken by EOF or exit command
    while (1)
    {
        // the following do while loop is used for prompting users for input until they have entered
        // anything other than a blank line 
        do
        {   printf("Prompt> "); 
            fgets(Buffer, BLOCK_SIZE, stdin);
            Buffer[strcspn(Buffer, "\n")] = '\0';// remove trailing newline character

            // check for EOF to prevent infinite loop
            if(feof(stdin))
            { 
              exit(0); 

            }
            // If the input is a blank line, continue scanning
        } while (strlen(Buffer) == 0);

        // creates a token value of each user command ignoring white space
        // must declare one before using in while in order to use NULL key word in (strtok)
        char *Tokenize = strtok(Buffer, delim);
        int count = 0;

        StoresCommands[count] = Tokenize; // Stores users commands

        if (strcmp(StoresCommands[0], "exit") == 0) // check id user typed exit, if so exit
        {
            exit(0);
        }

        // strtok returns null when there is no more data left
        //  loads users commands
        while (Tokenize != NULL)
        {
            Tokenize = strtok(NULL, delim); // getting next token in the userInput string
            count = count + 1;
            StoresCommands[count] = Tokenize; // store them in an array of commands 
        }

        // creating variables needed to fork()
        pid_t childPID;
        int pid = fork();
    
        if (pid == 0) // Checks to ensure pid is 0. ;
        {
            //check if execvp executed
            ResultOFexecvp= execvp(StoresCommands[0], StoresCommands);
            if (ResultOFexecvp < 0)
            {
                exit(0);
            }
        }
        else
        {
            childPID = wait(&ResultOFexecvp); // Waits for the child to finish 
            printf("Child %d, exited with %d\n", childPID, ResultOFexecvp);
        }
    }

    free(Buffer); // Frees up the memory allocated
    free(StoresCommands);

    return 0;
}

