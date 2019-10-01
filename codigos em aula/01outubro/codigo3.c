#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10


int main(int argc, char** argv){
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], D[SIZE][SIZE], E[SIZE][SIZE], F[SIZE][SIZE],
    G[SIZE][SIZE], H[SIZE][SIZE], R1[SIZE][SIZE], R2[SIZE][SIZE],R3[SIZE][SIZE],R4[SIZE][SIZE], R5[SIZE][SIZE], RF[SIZE][SIZE];
    int i , j, k;

    for(int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 1;
            D[i][j] = 1;
            E[i][j] = 1;
            F[i][j] = 1;
            G[i][j] = 1;
            H[i][j] = 1;
            R1[i][j] = 0;
            R2[i][j] = 0;
            R3[i][j] = 0;
            R4[i][j] = 0;
            R5[i][j] = 0;
            RF[i][j] = 0;
        }
    }


    #pragma omp parallel shared(A,B,C,D,E,F,G,H,R1,R2,R3,R4,RF) private(i,j,k) num_threads(2)
    {


        #pragma omp sections nowait
        {
            //Section de soma
            #pragma omp section
            {
                //Somar matriz
                for(i = 0; i < SIZE ; i++){
                    for(j = 0; j < SIZE ; j++){
                        R1[i][j] = A[i][j] + B[i][j];
                        R3[i][j] = E[i][j] + F[i][j];
                    }
                }

                //Somar resultados
                for(i = 0; i < SIZE ; i++){
                    for(j = 0; j < SIZE ; j++){
                        R5[i][j] = R1[i][j] + R3[i][j];
                    }
                }
            }

            //Section de Multiplicação
            #pragma omp section
            {
                for(i = 0; i < SIZE; i++){
                    for( j = 0; j < SIZE; j++){
                        R2[i][j] = 0;
                        R4[i][j] = 0;
                        for(k = 0; k < SIZE; k++){
                            R2[i][j] += C[i][k]*D[k][j];
                            R4[i][j] += G[i][k]*H[k][j];
                        }
                    }
                }

                for(i = 0; i < SIZE ; i++){
                    for(j = 0; j < SIZE ; j++){
                        R5[i][j] = R2[i][j] + R4[i][j];
                    }
                }
            }
           
        }

        #pragma omp critical
        {
            for(i = 0; i < SIZE ; i++){
                for(j = 0; j < SIZE ; j++){
                    RF[i][j] += R5[i][j];
                }
            }
        }
    }

    for(i = 0; i < SIZE ; i++){
        for(j = 0; j < SIZE ; j++){
            printf("%d ",RF[i][j]);
        }
        printf("\n");
    }
    
    
}