//Rodrigo Skurczynski - 41905113
//Wellerson Rodriguês Alves - 41994647
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>   
int thread_count = 100;  
void Taylor(int num,long double *S);   
void escreve(FILE* file,long int den,long double S,long int t);      
int main()                              
{                        
        long int den = 0;       
        long double S = 0;            
        int i = 0;   
        int count = 0;    
        long int t = 0;   
        FILE *file;      
        if((file = fopen("dados.txt","r")) == NULL)     
        {                            
                printf("Arquivo dados.txt não existe\n");    
                return 1;    
        }      
        else   
        {           
                char t1[100];   
                char t2[100];
                char t3[100]; 
                while(i < 3)  
                {        
                        if(i == 0) fgets(t1,100,file);  
                        else if(i == 1) fgets(t2,100,file);  
                        else if(i == 2) fgets(t3,100,file); 
                        i++; 
                }    
                den = atol(t1); 
                t = atol(t3);  
                char *temp;     
                S = strtod(t2,&temp);   
        }                            
        fclose(file);               
        time_t start = time(NULL);  
        while(1)                   
        {                           
                count ++;            
                printf("\n Distancia:%.10Lf Tempo:%ld",S,(time(NULL) - start) + t);      
                if(count > 120)     
                {                       
                        #pragma omp parallel num_threads(1) 
                        escreve(file,den,S,time(NULL) - start + t); 
                        count = 0;                        
                }                   
                #pragma omp parallel num_threads(thread_count)   
                Taylor(den++,&S);                
        }                              
}                                        
void Taylor(int num,long double *S)      
{                                        
        #pragma omp atomic               
        *S += (1.0/num);
        } 
void escreve(FILE* file,long int den,long double S,long int t) 
{     
        #pragma omp critical 
        {    
                file = fopen("dados.txt","w+");
                //perror("fopen()");
                char c1[100]; 
                char c2[100];   
                char c3[100]; 
                sprintf(c1,"%ld\n",den);   
                sprintf(c2,"%.10Lf\n",S); 
                sprintf(c3,"%ld\n",t);   
                fputs(c1,file);     
                fputs(c2,file);    
                fputs(c3,file);   
                fclose(file);  
        }                
}  
