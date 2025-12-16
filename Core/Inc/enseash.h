#ifndef ENSEASH_H
#define ENSEASH_H

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>  //indisponsible pour les macros WEXITSTATUS
#include <stdio.h>



#define BUF_SIZE 1024  //standard for a command input buffer.
#define MAX_ARGS 128 // argument limit 
#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "

// Declarations
// We use one functions to generate the code 
void display_message(const char *str); //Q1
int execute_command(char *command); //Q2
void write_integer(int n); // Q4

#endif