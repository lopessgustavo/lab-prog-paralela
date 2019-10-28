#include <stdio.h>
#include <stdlib.h>

float calcula(float local_a, float local_b,
	int local_n, float h) {
	float integral;
	float x, i;
	float f(float x); // função a integrar
	integral = ( f(local_a) + f(local_b) ) /2.0;
	x = local_a;
    #pragma omp parallel private(i)
    {
        #pragma omp for
        for( i=1; i<=local_n; i++) {
            x += h;
            integral += f(x);
        }

    }
	
	integral *= h;
	return integral;
}

float f(float x) {

	float fx; // valor de retorno

	// esta é a função a integrar
	// exemplo: função quadrática
	fx = x * x;

	return fx;
}


int main(int argc, char** argv) {
    int p = 4;
    
	float a=0.0, b=1.0; // intervalo a calcular
	int n=1024; // número de trapezóides
	float h; // base do trapezóide
	float local_a, local_b; // intervalo local
	int local_n; // número de trapezóides local
	float integral; // integral no meu intervalo
	float total; // integral total


	float calcula(float local_a, float local_b,
		int local_n, float h);

	h = (b-a) / n;
	local_n = n / p;
	local_a = a + my_rank * local_n * h;
	local_b = local_a + local_n * h;

	integral = calcula(local_a, local_b, local_n, h);
    
	return 0;
}


