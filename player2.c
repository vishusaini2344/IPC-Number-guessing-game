#include "common.h"

int main() {
    int shmid;
    SharedData *sharedData;

    // Attach to shared memory
    shmid = shmget(SHM_KEY, sizeof(SharedData), 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    sharedData = (SharedData *)shmat(shmid, NULL, 0);
    if (sharedData == (SharedData *)-1) {
        perror("shmat");
        exit(1);
    }

    // Wait for Player 1 to set the number
    while (!sharedData->ready1);

    printf("Player 2: Start guessing the number!\n");

    while (1) {
        printf("Enter your guess: ");
        scanf("%d", &sharedData->guess);
        sharedData->ready2 = 1;  // Indicate that a guess is made

        // Wait for feedback
        while (sharedData->ready2);

        printf("Player 2: Feedback: %s\n", sharedData->message);
        if (strcmp(sharedData->message, "Correct!") == 0) {
            break;
        }
    }

    // Detach shared memory
    shmdt(sharedData);

    return 0;
}
