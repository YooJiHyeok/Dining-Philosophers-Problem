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

    // 작은 번호 포크 먼저 요청 → 순서 고정
    int first = left < right ? left : right;
    int second = left < right ? right : left;

    for (int i = 0; i < 3; i++) {
        sem_wait(&forks[first]);
        sem_wait(&forks[second]);

        printf("Philosopher %d is eating with forks %d and %d\n", id, first, second);

        sem_post(&forks[second]);
        sem_post(&forks[first]);
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
