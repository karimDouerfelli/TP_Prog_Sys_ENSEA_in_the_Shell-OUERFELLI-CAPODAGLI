#ifndef ENSEASH_H
#define ENSEASH_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h> 

#define BUF_SIZE 1024
// Updated to English as requested
#define WELCOME_MSG "Welcome to ENSEA Shell.\nType 'exit' to quit.\n"
#define PROMPT "enseash % "

// Prototypes
void display_message(const char *str);
int execute_command(char *command);

#endif