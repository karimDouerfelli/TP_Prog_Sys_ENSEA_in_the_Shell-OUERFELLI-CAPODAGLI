/*
File : main.c
Author : Capodagli Janus, Ouerfelli Karim 
Description : Main loop of the shell with execution time measurement (Q5)
*/

#include "enseash.h"
#include <time.h> // Required for clock_gettime

int main(void) {
    char buffer[BUF_SIZE];
    char prompt_msg[BUF_SIZE]; // Buffer for dynamic prompt
    ssize_t ret;
    int status = 0; // Stores the return status of the command
    
    // Q5: Timing variables
    struct timespec start, end;
    long elapsed_ms = 0;

    // Flag to check if it's the first loop iteration
    int first_command = 1; 

    display_message(GRN WELCOME_MSG NC); //display the message in green

    while (1) {
        // --- 1. PROMPT DISPLAY (Logic concentrated here) ---
        // We display the result of the PREVIOUS command here
        if (first_command) {
            display_message(PROMPT);
            first_command = 0;
        } else {
            // Check how the previous command ended and format prompt
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                
                if (exit_code == 0) {
                    // SUCCESS : Display in green
                    snprintf(prompt_msg, BUF_SIZE, 
                             "enseash [exit:%d|" GRN "%ldms" NC "] %% ", 
                             exit_code, elapsed_ms);
                } else {
                    // FAILURE : Diplay in red
                    snprintf(prompt_msg, BUF_SIZE, 
                             "enseash [" RED "exit:%d" NC "|%ldms] %% ", 
                             exit_code, elapsed_ms);
                }
            } else if (WIFSIGNALED(status)) {
                // SIGNAL :Display in red
                snprintf(prompt_msg, BUF_SIZE, 
                         "enseash [" RED "sign:%d" NC "|%ldms] %% ", 
                         WTERMSIG(status), elapsed_ms);
            } else {
                strncpy(prompt_msg, PROMPT, BUF_SIZE);
            }
            display_message(prompt_msg);
        }

        // --- 2. READ INPUT ---
        ret = read(STDIN_FILENO, buffer, BUF_SIZE - 1);

        // Handle Ctrl+D (EOF) or Error
        if (ret <= 0) {
            break; 
        }

        buffer[ret - 1] = '\0'; // Remove \n

        // Handle empty input (User just pressed Enter)
        if (strlen(buffer) == 0) {
            status = 0;      // Reset status
            elapsed_ms = 0;  // Reset elapsed time
            continue; 
        }
        
        // Q3: Exit command
        if (strcmp(buffer, "exit") == 0) {
            display_message( RED " Bye bye...\n" NC); //display the message in red
            break;
        }

        // --- 3. EXECUTION & TIMING (Q5) ---
        
        // Start Timer
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Execute
        status = execute_command(buffer);

        // Stop Timer
        clock_gettime(CLOCK_MONOTONIC, &end);

        // Calculate duration in milliseconds
        // (sec difference * 1000) + (nanosec difference / 1000000)
        elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 + 
                     (end.tv_nsec - start.tv_nsec) / 1000000;
                     
        // Loop loops back to step 1 to display the result
    }

    return EXIT_SUCCESS;
}