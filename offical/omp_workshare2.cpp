#include <stdio.h>
#include <omp.h>
using namespace std;

const int MAXN = 50;

int main() {
	int nthreads, tid;
	double a[MAXN], b[MAXN], c[MAXN], d[MAXN];
	for (int i = 0; i < MAXN; i++) {
		a[i] = i * 1.5;
		b[i] = i + 22.35;
		c[i] = d[i] = 0.0;
	}
	#pragma omp parallel shared(a, b, c, d, nthreads) private(tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		
		printf("Thread %d starting ... \n", tid);
		
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				printf("Thread %d doing section 1\n", tid);
				for (int i = 0; i < MAXN; i++) {
					c[i] = a[i] + b[i];
					printf("Thread %d: c[%d] = %lf\n", tid, i, c[i]);
				}			
			}
			
			#pragma omp section
			{
				printf("Thread %d doing section 2\n", tid);
				for (int i = 0; i < MAXN; i++) {
					d[i] = a[i] * b[i];
					printf("Thread %d: d[%d] = %lf\n", tid, i, d[i]);
				}
			}
			
		}
		printf("Thread %d done.\n", tid);
	}
	return 0;
}

