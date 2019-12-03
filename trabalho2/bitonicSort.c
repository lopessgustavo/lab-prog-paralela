#include <stdio.h>
#include <omp.h>
// Ordena uma dada sequência bitônica
void BitonicSortCut(int *vector, int n, int cresc){
    if (n > 1) {
        int m = n/2;
        int k, i, t;

        #pragma omp parallel private(i,k) num_threads(4)

        t = omp_get_thread_num();
                
        printf("Thread %d \n", t);

        #pragma omp for
        for(int i = 0; i < m; i++)
            if ((cresc == 1 && vector[i] > vector[i+m]) || 
                (cresc == 0 && vector[i] < vector[i+m])){
                int aux = vector[i];
                vector[i] = vector[i+m];
                vector[i+m] = aux; 
            }
        BitonicSortCut(vector, m, cresc);
        BitonicSortCut(vector + m, m, cresc);
    }
}
// Transforma a sequência em sequência bitônica
// e a ordena
void BitonicSort(int *vector, int n, int cresc){
    if (n > 1) {
        int m = n/2;
        BitonicSort(vector, m, 1); 
        BitonicSort(vector + m, m, 0);
        BitonicSortCut(vector, n, cresc);
    }
}
 
int main (){
 
    int vector[ ] = {5, 1, 6, 9, 8, 7, 0, 3};
    int n = 8;
 
    BitonicSort(vector, n, 1);
 
    for(int i = 0; i < n; i++)
        printf("%d ", vector[i]);
}