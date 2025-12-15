/*
File : enseash.c
Author : Capodagli Janus, Ouerfelli Karim
Description : Implementation of shell functions
*/

#include "enseash.h"

// Implementation of display_message using write (system call)
void display_message(const char *str) {
    // STDOUT_FILENO is usually 1. 
    // We use strlen because we are forbidden to use printf but allowed string.h
    if (write(STDOUT_FILENO, str, strlen(str)) == -1) {
        // Handle write error
        perror("write");
        exit(EXIT_FAILURE);
    }
}

int execute_command(char *command) {
    pid_t pid;
    int status;

    // 1. Create child process
    pid = fork();

    if (pid == -1) {
        // Critical fork error
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // --- CHILD PROCESS ---
        // Execute the command. 
        // execlp searches for the command in the PATH environment variable.
        // Arguments: (filename, arg0, ..., NULL)
        execlp(command, command, (char *)NULL);

        // If we reach here, execlp failed (e.g., command not found)
        // We print a clean error message without printf
        write(STDERR_FILENO, "Command not found\n", 18);
        exit(EXIT_FAILURE); // Child must exit here
    } else {
        // --- PARENT ---
        // Wait allows us to retrieve the child's exit status
        wait(&status);
        return status; // Return the status to main for analysis
    }
}