#include <stdio.h>
#include<time.h>
#include<stdlib.h>

void swap (int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}


void randomize ( int* arr, int n ) 
{ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
  
    // Start from the last element and swap one by one. We don't 
    // need to run for the first element that's why i > 0 
    for (int i = n-1; i > 0; i--) 
    { 
        // Pick a random index from 0 to i 
        int j = rand() % (i+1); 
  
        // Swap arr[i] with the element at random index 
        swap(&arr[i], &arr[j]); 
    } 
}

// Ordena uma dada sequência bitônica
void BitonicSortCut(int *vector, int n, int cresc){
    if (n > 1) {
        int m = n/2;
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
 
    int n = 1024;
    int vector[n];
    for(int i = 0; i<n; i++) vector[i] = i;
    randomize(vector,1024);
 
 
    BitonicSort(vector, n, 1);
 
    for(int i = 0; i < n; i++)
        printf("%d ", vector[i]);
}