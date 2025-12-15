

#ifndef ENSEASH_H
#define ENSEASH_H

// dependencies

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 1024
#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "

// Declarations
void display_prompt();
void read_command(char *buf);

#endif