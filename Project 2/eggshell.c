// Fragile implementation of a Unix shell
// Created by Stephan Ofosuhene on 9/27/18.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 511
#define ARG_SIZE 255


void strip_newline(char *str){
    int n = 0;
    while (true){
        if (str[n] == '\0'){
            break;
        } else if (str[n] == '\n'){
            str[n] = '\0';
            break;
        }
        n++;
    }
}


void get_arguments(char *argstring, int *arglen, char **buffer){
    int n = 0;

    // get all arguments with strtok and return them in an array
    strip_newline(argstring);
    char *argument = strtok(argstring, " ");
    while (argument != NULL) {
        buffer[n] = argument;
        argument = strtok(NULL, " ");;
        n++;
    }
    *arglen = n;
}


int run_builtins(char **args, int arglen, char **path){
    if (strcmp(args[0], "exit") == 0 && arglen == 1){
        exit(0);
    } else if (strcmp(args[0], "exit") == 0 && arglen > 1){
        // generate an error if arguments are provided
        printf("exit does not take arguments\n");
        return -1;
    }

    else if ((strcmp(args[0], "cd") == 0 && arglen < 2) || (strcmp(args[0], "cd") == 0 && arglen > 2)){
        printf("cd requires a single argument\n");
        return -1;

    } else if (strcmp(args[0], "cd") == 0 && arglen == 2){
        if (chdir(args[1]) == -1){
            printf("failed to change directory\n");
            return -1;
        }
        return 0;
    }

    else if (strcmp(args[0], "path") == 0){
        for (int i = 1; i < arglen; i ++){
            printf("adding to path: %s, i: %d\n", args[i], i);
            path[i-1] = args[i];
        }
    }

    return 1;
}


void run_system_commands(int argc, char **argv, char **path){
    char *current_path;
    char *command = argv[0];
    int n = 0;

    current_path = path[n];
    while (current_path != NULL){
        current_path = path[n];

        for (int i = 1; i < argc; i++) {
            int rc = fork();
            if (rc < 0) {
                printf("failed to create child process\n");
            } else if (rc == 0) {
                char src[100];
                char dest[100];
                strcpy(dest, current_path);
                strcpy(src, command);
                if (execv(strcat(dest, src), argv) == -1) {
                    printf("failed to run command\n");
                }
                exit(0);
            } else {
                wait(NULL);
            }
            wait(NULL);
        }
        n++;
        current_path = path[n];
    }
}


int main(int argc, char *argv[]){
    char inputBuffer[BUFFER_SIZE];
    char *arguments;
    char *allArgs[100];
    int arglen;
    char *path[100];
    int isbuiltin;
    path[0] = "/bin/";
    if (argc ==  1) {
        while (true) {
            printf("eggshell> ");
            fgets(inputBuffer, BUFFER_SIZE, stdin);

            arguments = inputBuffer;

            // collect all arguments using strtok into argv
            get_arguments(arguments, &arglen, allArgs);

            isbuiltin = run_builtins(allArgs, arglen, path);
            if (isbuiltin == 1) {
                run_system_commands(arglen, allArgs, path);
            }
        }
    } else {
        if (argc > 2){
            printf("too many arguments\n");
            return 0;
        }

        printf("*********************** batch mode ***********************\n");
        char buffer[BUFFER_SIZE];
        FILE* fp;
        fp = fopen(argv[1], "r");

        while (fgets(buffer, BUFFER_SIZE, fp) != NULL){
            strip_newline(buffer);
            arguments = buffer;
            get_arguments(arguments, &arglen, allArgs);
            isbuiltin = run_builtins(allArgs, arglen, path);
            if (isbuiltin == 1) {
                run_system_commands(arglen, allArgs, path);
            }
        }
        fclose(fp);
    }
}
