#include <stdio.h>
#include <omp.h>
using namespace std;

const int ROWA = 62;
const int COLA = 15;
const int COLB = 7;
int main() {
	int tid, nthreads, chunk;
	double a[ROWA][COLA], b[COLA][COLB], c[ROWA][COLB];
	chunk = 10;
	#pragma omp parallel shared(a, b, c, nthreads, chunk) private(tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Starting matrix multiple example with %d threads\n", nthreads);
			printf("Initializing matrices ...\n");
		}
		
		#pragma omp for schedule(static, chunk)
		for (int i = 0; i < ROWA; i++)
			for (int j = 0; j < COLA; j++)
				a[i][j] = i+j;
		#pragma omp for schedule(static, chunk)
		for (int i = 0; i < COLA; i++)
			for (int j = 0; j < COLB; j++)
				b[i][j] = i*j;
		#pragma omp for schedule(static, chunk)
		for (int i = 0; i < ROWA; i++)
			for (int j = 0; j < COLB; j++)
				c[i][j] = 0;
		printf("Thread %d starting matrix multiply ...\n", tid);
		#pragma omp for schedule(static, chunk)
		for (int i = 0; i < ROWA; i++) {
			printf("Thread %d did row %d\n", tid, i);
			for (int j = 0; j < COLB; j++) {
				for (int k = 0; k < COLA; k++)
					c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	printf("Result Matrix\n");
	for (int i = 0; i < ROWA; i++, puts(""))
		for (int j = 0; j < COLB; j++)
			printf("%6.2f   ", c[i][j]);			
	return 0;
}

