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
    }}
int execute_command(char *command){ // Q2 pdf page 56
    int pid , status ; 
    // Q6
    // we need pointeurs table to stock "ls","-l"...
    char *argv[MAX_ARGS];
    int i = 0;
    //cleaning the memory 
    memset(argv,0,sizeof(argv));
    // 
    argv[i] = strtok(command," \t\n");
    while(argv[i] != NULL && i < MAX_ARGS -1){
        i++;
        argv[i] = strtok(NULL," \t\n"); //NULL ==> continue on the same chaine 
    }
    // execvp need the end of the  tableur with NULL 
    argv[i]= NULL;

    //if the user put space and enter , argv[0] is NULL
    if(argv[0]==NULL) return 0;

    pid= fork();
    if(pid == - 1){
        //fork error
    return -1;
    }
    else if(pid != 0 ){ // father code 
        wait(&status);
        return status; // we send the info ot the main 
    }
    else{ // child code 
        execlp(argv[0], argv); //arguments :(filename, arg0, ...) we dont need the path 
        //char *errormsg= "Command not found\n";
        //write(STDERR_FILENO,errormsg,strlen(errormsg));
        perror("Command not found ");
        exit(EXIT_FAILURE);
    }
}
void write_integer(int n){
    char buffer[20];
    int i =0;
    if(n==0){
        write(STDOUT_FILENO,"0",1);
        return;
    }
    //we() extract one by one 
    while(n > 0){
        buffer[i] = (n % 10) + '0'; // char ASCII
        n/=10;
        i++;
    }
    //buffer normal
    while(i > 0){
        i--;
        write(STDOUT_FILENO, &buffer[i], 1);
    }
}