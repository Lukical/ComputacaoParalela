/* Rodrigo Skurczynski - 41905113 - 5G */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int thread_count = 4;
void Taylor(int num,double* sum);
int main()
{	
	long int l = 1;
	long double sum = 0;
	time_t start = time(NULL); 
	while(1)
	{
		#pragma omp parallel num_threads(thread_count)
		Taylor(l++,&sum);
		printf("\n %.20Lf %ld",sum,time(NULL) - start);
	}
}
void Taylor(int num,long double* sum)
{
    #pragma omp critical
    *sum += (1.0 / num);
}
