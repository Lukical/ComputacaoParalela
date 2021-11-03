/* Rodrigo Skurczynski - 41905113 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int thread_count = 4;
long double sum = 0;
void *Taylor(void* arg);
int main() //main
{
    long int l = 1;
    long thread;
    pthread_t* thread_handles; //cria threads
    thread_handles = malloc(thread_count*sizeof(pthread_t));//alocação
    time_t start = time(NULL); 
    while(1)
    {
        for(thread = 0;thread < thread_count;thread++)
        {
            pthread_create(&thread_handles[thread],NULL,Taylor,&l);
            pthread_join(thread_handles[thread],NULL);
            l++;
        }
        printf("\n %.20Lf %ld",sum,time(NULL) - start);
    }
    free(thread_handles);
}
void* Taylor(void* arg)
{
    int* num = (int*)arg;
    sum += (1.0 / *num);
    return NULL;
}
