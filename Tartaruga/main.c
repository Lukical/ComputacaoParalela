/* Rodrigo Skurczynski - 41905113 - 5G */
/* Wellerson Rodriguês Alves - 41994647 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int thread_count = 100;
void Taylor(int num,long double* S);

int main()
{
        long int l = 1;
        long double S = 0;
        time_t start = time(NULL);
        while(1)
        {
                #pragma omp paralell num_threads(thread_count/2)
                Taylor(l++,&S);
                printf("\n %.10Lf %ld", S, time(NULL) - start);

                #pragma omp paralell  num_threads(thread_count/2)
                Taylor(l++, &S);
                printf("\n %.10Lf %ld", S, time(NULL) - start);
        }
}

void Taylor(int num, long double* S)
{
        #pragma omp critical
        *S += (1.0/num);
}
