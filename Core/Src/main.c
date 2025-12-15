/*
File : main.c
Author : Capodagli Janus, Ouerfelli Karim 
*/

#include "enseash.h"

int main(void) {
    char buffer[BUF_SIZE];
    char prompt_msg[BUF_SIZE]; // Buffer for dynamic prompt
    ssize_t ret;
    int status = 0; // Stores the return status of the command
    int first_command = 1; // Flag to check if it's the first loop

    display_message(WELCOME_MSG);

    while (1) {
        // Q4: Display return code or signal in the prompt
        if (first_command) {
            display_message(PROMPT);
            first_command = 0;
        } else {
            // Check how the previous command ended
            if (WIFEXITED(status)) {
                // Exited normally (e.g., exit(0))
                sprintf(prompt_msg, "enseash [exit:%d] %% ", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                // Killed by a signal (e.g., Ctrl+C or kill)
                sprintf(prompt_msg, "enseash [sign:%d] %% ", WTERMSIG(status));
            } else {
                // Fallback (should typically not happen in this simple shell)
                sprintf(prompt_msg, "%s", PROMPT);
            }
            display_message(prompt_msg);
        }

        // --- Standard Read Loop ---
        ret = read(STDIN_FILENO, buffer, BUF_SIZE - 1);

        if (ret <= 0) {
            break; 
        }

        buffer[ret - 1] = '\0';

        if (strlen(buffer) == 0) {
            status=0;
            continue; 
        }
        
        if (strcmp(buffer, "exit") == 0) {
            display_message("Bye bye...\n");
            break;
        }


        // Update status with the return value of execute_command
        status = execute_command(buffer);
    }

    return EXIT_SUCCESS;
}