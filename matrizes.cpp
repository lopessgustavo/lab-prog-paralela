#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

using namespace std;

int main(){
    FILE *fp;
    fp = fopen("matrizes.txt","w");
    for(int i = 0; i<2; i++){
        for(int j = 0; j<SIZE; j++){
            for(int k = 0; k<SIZE; k++){
                fprintf(fp,"%d ", rand() % 100);
            }
        }
    }
    fclose(fp);

}