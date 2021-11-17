#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   
#include <omp.h>  
#include <string.h> 
int thread_count = 100; 
void Taylor(int num,long double *S); 
int main() 
{            
        long int den = 0;   
        long double S = 0;    
        int i = 0;              
        FILE *file;    
        if((file = fopen("dados.txt","r")) == NULL)   
        {                    
                printf("Arquivo dados.txt não existe\n");  
                return 1;     
        }    
        else
        {
                char t1[30];
                char t2[30];
                while(i < 2)
                {
                        if(i == 0) fgets(t1,30,file); 
                        else if(i == 1) fgets(t2,30,file);
                        i++;
                }
                den = atol(t1);
                char *temp;
                S = strtod(t2,&temp);
        }
        fclose(file);
        time_t start = time(NULL);
        while(1) 
        {
                printf("\n Distancia:%.10Lf Tempo:%ld",S,time(NULL) - start);
                //file = fopen("dados.txt","w+");
                //perror("fopen()");
                //char* c1 = den + "";
                //char c2[sizeof(S)];
                //memcpy(c2,&S,sizeof(S));
                //fputs(c1,file);
                //fputs(c2,file); 
                //fclose(file); 
                #pragma omp parallel num_threads(thread_count)
                Taylor(den++,&S);
        }
}
void Taylor(int num,long double *S)
{
        #pragma omp atomic
        *S += (1.0/num);
}
