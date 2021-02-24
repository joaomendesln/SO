#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define PI 3.1415926

int status = 0;

double *areas_trapezios;

int qtd_threads;
int qtd_trapezios;

// f_1
// double f(double x){
// 	return 2 * x;
// }
// double a = 0, b = 10, h, local_b_temp;

// f_2
double f(double x){
	return sin(2 * x) + cos(2 * x);
}
double a = 0, b = 2 * PI, h, local_b_temp;

void* integral(void *tid){

	int cont = (int)(size_t)tid;

	// cálculo do local_n
	double local_n = qtd_trapezios / qtd_threads;

	if (qtd_trapezios % qtd_threads != 0 && cont == qtd_threads - 1){
		local_n += qtd_trapezios % qtd_threads;
	} 

	// cálculo de local_a e local_b 
	double local_a = local_b_temp;
	double local_b = local_a + local_n * h;
	local_b_temp = local_b;

	// método 2 
	double area_thread = (f(local_a) + f(local_b)) / 2;

	for (int i = 1; i < local_n; ++i)
	{
		double x_i = local_a + i * h;
		area_thread += f(x_i);
	}
	area_thread = h * area_thread;
	

	// armazenamento da área obtida na thread no vetor areas_trapezios
	areas_trapezios[cont] = area_thread;

	pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	local_b_temp = a;
	qtd_threads = atoi(argv[1]);
	qtd_trapezios = atoi(argv[2]);

	h = (b - a)/qtd_trapezios;
	
	pthread_t threads[qtd_threads];

	void *thread_return;

	areas_trapezios = malloc (qtd_threads * sizeof (double));

	for (int i = 0; i < qtd_threads; ++i)
	{
		status = pthread_create(&threads[i], NULL, integral, (void *)(size_t) i);

		if (status != 0) 
		{
			printf("Erro na criação da thread. Código de erro: %d\n", status);
			return 1;
		}
	}

	for (int i = 0; i < qtd_threads; i++)
		pthread_join(threads[i], &thread_return);

	double total = 0;

	for (int i = 0; i < qtd_threads; i++)
		total += areas_trapezios[i];

	printf("%lf\n", total);
	printf("%.2e\n", total);

	return 0;
}