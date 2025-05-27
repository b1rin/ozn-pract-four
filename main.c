#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int index;          // thread index
    int sleep_time;     // thread sleep time
} Data;

// thread function prototype
void* routine(void*);

int main(int argc, char* argv[]) {
    char choice;
    do {
        // thread declaration
        pthread_t thread[5];
        int i;
        int arr[5];
        for (int j = 0; j < 5; j++) {
            printf("Choose sleep time for %d thread: ", j+1);
            scanf("%d", arr+j);
        }
        // creating threads
        for (i = 0; i < 5; i++) {
            Data* data = malloc(sizeof(Data));
            data->index = i;
            data->sleep_time = arr[i];
            if (pthread_create(&thread[i], NULL, &routine, data)) return EXIT_FAILURE;
            printf("%d started working\n", data->index+1);
        }
        for (int j = 0; j < 50; j++) printf("=");
        printf("\n");
        // joining threads
        for (i = 0; i < 5; i++) {
            if (pthread_join(thread[i], NULL)) return EXIT_FAILURE;
        }
        printf("Success!\n\n");
        // loop condition
        printf("Press 'x' to quit or 'r' to restart: ");
        scanf(" %c", &choice);
    } while (choice != 'x');
    return EXIT_SUCCESS;
}

// thread function implementation
void* routine(void* arg) {
    Data* data = (Data*)arg;
    sleep(data->sleep_time);
    printf("Thread %d has stopped in %d seconds\n", data->index+1, data->sleep_time);
    free(arg);
    return NULL;
}
