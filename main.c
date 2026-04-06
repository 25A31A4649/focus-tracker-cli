#include <stdio.h>
#include <time.h>
#include <stdlib.h>

time_t start, end;
int isRunning = 0;

void startSession() {
    if (isRunning) {
        printf("[WARNING] Session already running.\n");
        return;
    }
    start = time(NULL);
    isRunning = 1;
    printf("[START] Session started.\n");
}

void endSession() {
    if (!isRunning) {
        printf("[WARNING] No active session.\n");
        return;
    }

    end = time(NULL);
    int duration = (int)difftime(end, start);

    int h = duration / 3600;
    int m = (duration % 3600) / 60;
    int s = duration % 60;

    printf("[DONE] Session ended.\n");
    printf("[TIME] %d hr %d min %d sec\n", h, m, s);

    FILE *file = fopen("log.txt", "a");
    if (file == NULL) {
        printf("[ERROR] File issue.\n");
        return;
    }

    fprintf(file, "%d %d %d\n", h, m, s);
    fclose(file);

    isRunning = 0;
}

void viewStats() {
    FILE *file = fopen("log.txt", "r");
    if (file == NULL) {
        printf("[INFO] No data.\n");
        return;
    }

    int h, m, s, total = 0, count = 0;

    while (fscanf(file, "%d %d %d", &h, &m, &s) != EOF) {
        total += h*3600 + m*60 + s;
        count++;
    }

    fclose(file);

    printf("[STATS] Total sessions: %d\n", count);
    printf("[STATS] Total time: %d sec\n", total);
}

int main() {
    int choice;

    while (1) {
        printf("\n1.Start\n2.End\n3.Stats\n4.Exit\n> ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: startSession(); break;
            case 2: endSession(); break;
            case 3: viewStats(); break;
            case 4: exit(0);
            default: printf("Invalid\n");
        }
    }
}
