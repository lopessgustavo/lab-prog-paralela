#include<string.h>
#include<stdlib.h>
#include<stdio.h>


int main(){
	long fac = 1;
	long number = 20;

	#pragma omp parallel
	{
		long omp_priv = 1;

		#pragma omp for nowait schedule(dynamic, 5)
		for(long n = 2; n <= number; n++){
			omp_priv *=n;
		}

		#pragma omp atomic
		fac *= omp_priv;
	}

	printf("result = %ld\n", fac);

	return 0;
}
	
