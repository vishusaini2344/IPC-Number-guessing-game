#ifndef COMMON_H
#define COMMON_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 1234   // Shared memory key
#define MAX_MSG_SIZE 256  // Maximum message size

typedef struct {
    int number;       // Number to guess
    char message[MAX_MSG_SIZE]; // Feedback message
    int guess;        // Player 2's guess
    int ready1;       // Player 1 ready flag
    int ready2;       // Player 2 ready flag
} SharedData;

#endif
