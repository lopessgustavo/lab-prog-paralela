#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<omp.h>
#include <mpi.h>


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

int main(int argc, char *argv[]){
    
    // ler_matrizes();
    // rank = id, np = num de processos
    int rank,np,origem,destino,tag = 0;

    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&np);
    
    int tamanho = SIZE/np;
    int resto = SIZE % np;
    int vet[SIZE] = {0};

    if(rank != 0){
        int i,j,k,soma;
     
        for(i = (rank-1)*tamanho; i<((rank-1)*tamanho)+tamanho; i+=1){
     
            for( j = 0; j < SIZE; j++){
                int soma = 0;
                
                for(k = 0; k < SIZE; k++){
                    soma+= A[i][k]*B[k][j];
                }
                vet[j] = soma;
            }

            // enviando linha i 
            MPI_Send(&vet,SIZE,MPI_INT,0,i,MPI_COMM_WORLD);
            
        }
        if(rank == np-1){
            do{
     
                for( j = 0; j < SIZE; j++){
                    int soma = 0;
                
                    for(k = 0; k < SIZE; k++){
                        soma+= A[i][k]*B[k][j];
                    }
                    vet[j] = soma;
            }

            // enviando linha i 
            MPI_Send(&vet,SIZE,MPI_INT,0,i,MPI_COMM_WORLD);
            
            i++;
            }while(i<SIZE);
        }
        
        

        // todas linhas enviadas
        MPI_Barrier(MPI_COMM_WORLD);
     
    }
    else{
        int buffer[SIZE];
        for(int i = 0; i< SIZE; i++){
            MPI_Recv(buffer,SIZE,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            memcpy(C[status.MPI_TAG],buffer,sizeof(int)*SIZE);

        }
        // todas linhas recebidas
        MPI_Barrier(MPI_COMM_WORLD);
        imprimir(C);
        printf("\n");
    }
    MPI_Finalize();

}
