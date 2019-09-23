#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<omp.h>

//mudar size para 100 para testar tempo
#define SIZE 3

//descomentar para testar com 100x100
// int A [SIZE][SIZE] = {{1}};
// int B[SIZE][SIZE] = {{2}};

//exemplo para testar a logica do programa
int A [SIZE][SIZE] =   {{1,17,44},
                        {22,53,1},
                        {0,3,100}};
int B [SIZE][SIZE] = {{13,0,0},
                        {32,3,0},
                        {44,53,2}};
int C [SIZE][SIZE];

using namespace std;

void ler_matrizes(){
    FILE *fp;
    fp = fopen("matrizes.txt","r");
    for(int i = 0; i<2; i++){
        for(int j = 0; j<SIZE; j++){
            for(int k = 0; k<SIZE; k++){
                if(i == 0){
                    fscanf(fp,"%d ",&A[j][k]);                    
                }
                else{
                    fscanf(fp,"%d ",&B[j][k]);
                }
            }
        }
    }
    fclose(fp);
    return;
}

void imprimir(int (*matriz)[SIZE]){
    int i = 0, j = 0;
    while(i<SIZE){
        while(j<SIZE){
            printf("%d ",matriz[i][j]);
            j++;
        } 
        j = 0;
        i++;
        printf("\n");
    }
}

int main(){
    
    // ler_matrizes();

    // printf("oie\n");

    int i,j,k;
    #pragma omp parallel shared(A,B,C) private(i,j,k) num_threads(4)
    {
        #pragma omp for
        for(i = 0; i< SIZE; i++){
            for( j = 0; j< SIZE; j++){
                C[i][j] = 0;
                for(k = 0; k < SIZE; k++){
                    C[i][j] += A[i][k]*B[k][j];
                }
            }
        }

    }
    imprimir(C);

    



}