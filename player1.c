#include "common.h"

int main() {
    int shmid;
    SharedData *sharedData;

    // Create shared memory
    shmid = shmget(SHM_KEY, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach shared memory
    sharedData = (SharedData *)shmat(shmid, NULL, 0);
    if (sharedData == (SharedData *)-1) {
        perror("shmat");
        exit(1);
    }

    printf("Player 1: Enter the number for Player 2 to guess: ");
    scanf("%d", &sharedData->number);
    sharedData->ready1 = 1;  // Indicate that the number is set
    sharedData->ready2 = 0;  // Reset Player 2's ready flag

    // Wait for Player 2 to guess
    while (1) {
        if (sharedData->ready2) {
            if (sharedData->guess < sharedData->number) {
                strcpy(sharedData->message, "Too low!");
                printf("Player 1: Player 2 guessed %d. Feedback: Too low!\n", sharedData->guess);
            } else if (sharedData->guess > sharedData->number) {
                strcpy(sharedData->message, "Too high!");
                printf("Player 1: Player 2 guessed %d. Feedback: Too high!\n", sharedData->guess);
            } else {
                strcpy(sharedData->message, "Correct!");
                printf("Player 1: Player 2 guessed %d. Feedback: Correct!\n", sharedData->guess);
                break;
            }
            sharedData->ready2 = 0;  // Reset Player 2's ready flag
        }
    }

    // Detach shared memory
    shmdt(sharedData);

    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
