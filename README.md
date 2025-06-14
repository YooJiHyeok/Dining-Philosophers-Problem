# Dining-Philosophers-Problem
# Requesting All Resources
## Code

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
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);

            printf("Philosopher %d is eating with forks %d and %d\n", id, left, right);

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


## Implementation Result
![Requesting All Resources](https://github.com/YooJiHyeok/Dining-Philosophers-Problem/blob/main/Requesting%20All%20Resources.png)
## Evaluation
철학자는 두 포크를 동시에 얻을 수 있을 때만 식사함.
데드락 회피: 양쪽 포크가 모두 확보될 때만 진행됨.
이 방식은 자원 부족으로 굶주릴 수 있는 철학자는 생길 수 있으나, 데드락은 발생하지 않음.
# Resource Ordering
## Code

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

## Implementation Result
![Resource Ordering](https://github.com/YooJiHyeok/Dining-Philosophers-Problem/blob/main/Resource%20Ordering.png)
## Evaluation
모든 철학자는 항상 낮은 번호의 포크를 먼저 집음.
이로 인해 순환 대기 조건이 원천적으로 깨짐 → 데드락 없음.
자원 요청 순서를 통일함으로써 공정성 향상.
## Conclusion
코드 구현이 어려워 코딩 ai(챗 gpt 및 Gemini)를 일부 참고하여 구현 하였는데, 앞선 Readers Writers 문제에 비해 조금은 쉬운 느낌을 받아 조금 더 편하게 구현 할 수 있었다.
