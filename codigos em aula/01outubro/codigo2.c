#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){
    int tam = atoi(argv[1]);
    int a[tam];
    int b[tam];
    int c[tam], d[tam];
    int i;

    #pragma omp parallel shared(tam,a,b) private(i)
    {
        #pragma omp sections
        {
            #pragma omp section
                for(i = 0; i < tam-1; i++) a[i] = 1;
            
            #pragma omp section
                for(i = 0; i < tam-1; i++) b[i] = 2;
        }
    }



    #pragma omp parallel shared(tam,a,b,c,d) private(i) num_threads(4)
    {
        #pragma omp sections
        {
            #pragma omp section
                for(i = 0; i < tam-1; i++) b[i] = (a[i]+a[i+1])/2;
            
            #pragma omp section
                for(i = 0; i < tam-1; i++) d[i] = 1.0/c[i];
        }
    }

    
}