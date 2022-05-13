#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void *read(void *arg);
void *accu(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

// 使用两个信号量可以保证两个线程交替进行，如果只使用一个信号量可能会导致两个线程竞争，可能导致无法交替，即同一个线程连续两次抢到运行权
int main(int argc, char const *argv[])
{
    pthread_t id_t1, id_t2;
    sem_init(&sem_one, 0, 0);
    sem_init(&sem_two, 0, 1);

    pthread_create(&id_t1, NULL, read, NULL);
    pthread_create(&id_t2, NULL, accu, NULL);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void *read(void *arg)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        fputs("Input num: ", stdout);

        sem_wait(&sem_two);
        scanf("%d", &num);
        sem_post(&sem_two);
    }
    return NULL;
}
void *accu(void *arg)
{
    int sum = 0, i;
    for (i = 0; i < 5; i++)
    {
        sem_wait(&sem_two);
        sum += num;
        sem_post(&sem_two);
    }
    printf("Result: %d \n", sum);
    return NULL;
}