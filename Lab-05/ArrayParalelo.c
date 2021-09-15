/* Rodrigo Skurczynski - 41905113 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int j; //posição
void *arrayMult(void *arg) //função que multiplica
{
    int* num = (int*)arg;
    int t = j++;
	*num *= 4;
    return NULL;
}
int main() //main
{
	int i,p;
	int size = 10;
    int v[10] = {1,2,4,8,16,32,64,128,256,512};
    pthread_t tid[size];
    for(i = 0; i < size;i++) //inicia threads
    {
        pthread_create(&tid[i],NULL,arrayMult,&v[i]);
        pthread_join(tid[i], NULL);
    }
    for(i = 0; i < size;i++) //printa vetor
    {
        printf("v[%i] = %d \n",i,v[i]);
    }
    pthread_exit(NULL);
    return 0;
}
