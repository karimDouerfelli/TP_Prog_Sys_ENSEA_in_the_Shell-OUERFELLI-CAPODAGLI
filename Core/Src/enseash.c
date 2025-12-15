/*
File : enseash.c
Author : Capodagli Janus, Ouerfelli Karim
Description : Implementation of shell functions
*/

#include "enseash.h"

// Implementation of display_message using write
void display_message(const char *str) {
    // STDOUT_FILENO is usually 1. 
    // We use strlen because we are forbidden to use printf but allowed string.h
    if (write(STDOUT_FILENO, str, strlen(str)) == -1) // int write(int fileDescriptor, void *buffer, size_t bytesToWrite)
    { // when write = -1 it's mean a error 
        
        exit(EXIT_FAILURE);
    }
}