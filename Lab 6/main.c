/* Rodrigo Skurczynski - 41905113 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int m = 3;
int n = 3;
int x[3] = {1, 2, 3};
int y[3];

int A[3][3] = {
  {1, 2, 4},
  {8, 16, 32},
  {64, 128, 256}
};

void *Pth_math_vect(void* rank);
int main(int argc, char* argv[]) //main
{
    long thread;
    pthread_t* thread_handles; //cria threads
    thread_count = strtol(argv[1],NULL,10);//conversão
    thread_handles = malloc(thread_count*sizeof(pthread_t));//alocação

    for(thread = 0;thread < thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,Pth_math_vect,(void*)thread);
        pthread_join(thread_handles[thread],NULL);
    }
    free(thread_handles);
    for(int i = 0; i < 3; i++)
    {
        printf("%d ", y[i]);
    }
    return 0;
}

void *Pth_math_vect(void* rank) //função multiplica array
{
    long my_rank = (long) rank;
    int i,j;
    int local_m = m / thread_count;
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    for(i = my_first_row;i <= my_last_row;i++)
    {
        y[i] = 0;
        for(j = 0;j < n;j++)
        {
            y[i] += A[i][j] * x[j];
        }
    }
    return NULL;
}
