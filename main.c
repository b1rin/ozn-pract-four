#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    int index;
    int sleep_time;
} Data;


void* routine(void*);

int main(int argc, char* argv[]) {
    char choice;
    do {
        
        pthread_t thread[5];
        int i;
        int arr[5];
        for (int j = 0; j < 5; j++) {
            printf("Choose sleep time for %d thread: ", j+1);
            scanf("%d", arr+j);
        }
        
        for (i = 0; i < 5; i++) {
            Data* data = malloc(sizeof(Data));
            data->index = i;
            data->sleep_time = arr[i];
            if (pthread_create(&thread[i], NULL, &routine, data)) return EXIT_FAILURE;
            printf("%d started working\n", data->index+1);
        }
        for (int j = 0; j < 20; j++) printf("=");
        printf("\n");
        
        for (i = 0; i < 5; i++) {
            if (pthread_join(thread[i], NULL)) return EXIT_FAILURE;
        }
        printf("Success!\n\n");
        
        printf("Press 'x' to quit or 'r' to restart: ");
        scanf(" %c", &choice);
    } while (choice != 'x');
    return EXIT_SUCCESS;
}


void* routine(void* arg) {
    Data* data = (Data*)arg;
    sleep(data->sleep_time);
    printf("Thread %d has stopped in %d seconds\n", data->index+1, data->sleep_time);
    free(arg);
    return NULL;
}
