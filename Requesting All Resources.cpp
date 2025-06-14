#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t forks[N];
pthread_t philosophers[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    for (int i = 0; i < 3; i++) {
        // 두 개 포크를 모두 요청
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("Philosopher %d is eating with forks %d and %d\n", id, left, right);

        // 식사 완료 후 포크 반납
        sem_post(&forks[right]);
        sem_post(&forks[left]);
    }
    return NULL;
}

int main() {
    int ids[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&forks[i]);

    return 0;
}
