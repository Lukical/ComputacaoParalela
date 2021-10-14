/* Rodrigo Skurczynski - 41905113 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count = 2;
double sum;
double pi;
int n = 1000000;

void *Thread_sum(void* rank);
int main() //main
{
    long thread;
    pthread_t* thread_handles; //cria threads
    thread_handles = malloc(thread_count*sizeof(pthread_t));//alocação

    for(thread = 0;thread < thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,Thread_sum,(void*)thread);
        pthread_join(thread_handles[thread],NULL);
    }
    free(thread_handles);
    printf("%f",pi);
}
void* Thread_sum(void* rank)
{
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;

    if(my_first_i % 2 == 0)
    {
        factor = 1;
    }
    else
    {
        factor = -1;
    }
    for(i = my_first_i;i < my_last_i; i++, factor = - factor)
    {
        sum += factor / (2* i+1);
    }
    pi = 4*sum;
    return NULL;
}
