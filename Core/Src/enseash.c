/*
File : enseash.c
Author : Capodagli Janus, Ouerfelli Karim
Description : Implementation of shell functions including argument parsing (Q6)
*/

#include "enseash.h"

void display_message(const char *str) {
    if (write(STDOUT_FILENO, str, strlen(str)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

int execute_command(char *command) {
    pid_t pid;
    int status;
    
    // Q6: Argument parsing variables
    char *argv[MAX_ARGS]; // Array to store arguments
    int argc = 0;
    
    // 1. Tokenize the command string by spaces
    // strtok modifies the input string by replacing separators with \0
    argv[argc] = strtok(command, " ");
    
    while (argv[argc] != NULL && argc < MAX_ARGS - 1) {
        argc++;
        argv[argc] = strtok(NULL, " "); // Continue scanning the same string
    }
    
    // The argument list must be terminated by NULL for execvp
    argv[argc] = NULL;

    // Safety check: if command was just spaces
    if (argv[0] == NULL) return 0;

    // 2. Forking process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // Q6: We use execvp instead of execlp
        // execvp takes the filename (argv[0]) and the array of arguments (argv)
        execvp(argv[0], argv);

        // If we reach here, execvp failed
        write(STDERR_FILENO, RED "Command not found\n" NC, 
                        sizeof(RED "Command not found\n" NC) - 1); 
                        
        exit(EXIT_FAILURE); 
    } else {
        // --- PARENT PROCESS ---
        wait(&status);
        return status;
    }
}