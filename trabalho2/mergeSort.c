#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<string.h>
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

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}

void printArray (int arr[], int n) 
{ 
    for (int i = 0; i < n; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
}

int main(int argc, char* argv[]){
    int my_rank;
	int p; // número de processos
	int n=1024; // número de trapezóides
	MPI_Status status;

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

    if(my_rank == 0){
        int vet[1024];
        for(int i = 0; i<1024; i++) vet[i] = i;
        // randomize(vet,1024);
        for(int i = 1; i<4;i++){
            int *pos = vet+(256*i);
            MPI_Send(vet+(256*i),256,MPI_INT,i,0,MPI_COMM_WORLD);
        }

        // free(vet);
        mergeSort(vet,0,255);
        int aux[256];
        int resp[1024];
        int i;
        memcpy(resp,vet,256*sizeof(int));
        for(i = 1; i < 4; i++){
            MPI_Recv(aux,256,MPI_INT,i,0,MPI_COMM_WORLD,&status);
            memcpy(resp+(256*i),aux,256*(sizeof(int)));
            merge(resp,0,256*i,256);
        }
        printArray(resp,i*256);

    }
    
    if(my_rank == 1){
        int vet[256];
        MPI_Recv(vet,256,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        mergeSort(vet,0,255);
        MPI_Send(vet,256,MPI_INT,0,0,MPI_COMM_WORLD);       
    }
    if(my_rank == 2){
        int vet[256];
        MPI_Recv(vet,256,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        mergeSort(vet,0,255);
        MPI_Send(vet,256,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    if(my_rank == 3){
        int vet[256];
        MPI_Recv(vet,256,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        mergeSort(vet,0,255);
        MPI_Send(vet,256,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    

    MPI_Finalize();
}