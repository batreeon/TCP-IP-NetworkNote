#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_summation(void *arg);

int main(int argc, char **argv)
{
    pthread_t t1, t2;
    int range1[] = {1, 5};
    int range2[] = {6, 10};
    pthread_create(&t1, NULL, thread_summation, (void *)range1);
    pthread_create(&t2, NULL, thread_summation, (void *)range2);

    int *re1, *re2;
    pthread_join(t1, (void **)&re1);
    pthread_join(t2, (void **)&re2);

    int res = *(int*)re1 + *(int*)re2;
    printf("%d", res);
    free(re1);
    free(re2);
    return 0;
}

void *thread_summation(void *arg)
{
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];
    int *res;
    while(start <= end)
    {
        *res += start;
        ++start;
    }
    return (void*)res;
}