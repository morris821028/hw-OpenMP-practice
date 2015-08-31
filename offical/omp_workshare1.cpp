#include <stdio.h>
#include <omp.h>
using namespace std;
#define CHUNKSIZE 10
#define MAXN 100
int main() {
	int nthreads, tid, chunk, i;
	double A[MAXN], B[MAXN], C[MAXN];
	for (int i = 0; i < MAXN; i++)
		A[i] = B[i] = i;
	chunk = CHUNKSIZE;
#pragma omp parallel shared(A,B,C,nthreads,chunk) private(i,tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}
		printf("Thread %d starting ... \n", tid);
		
		#pragma omp for schedule(dynamic,chunk)
		for (i = 0; i < MAXN; i++) {
			C[i] = A[i] + B[i];
			printf("Thread %d: C[%d] = %lf\n", tid, i, C[i]);
		}
	}
	return 0;
}

