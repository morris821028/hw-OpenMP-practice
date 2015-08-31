#include <stdio.h>
#include <omp.h>
using namespace std;
const int MAXN = 100;
double a[MAXN], b[MAXN], sum;
double dotprod() {
	int tid;
	tid = omp_get_thread_num();
	#pragma omp for reduction(+:sum)
	for (int i = 0; i < MAXN; i++) {
		sum = sum + (a[i] * b[i]);
		printf("tid %d i %d\n", tid, i);
	}
}
int main() {
	for (int i = 0; i < MAXN; i++)
		a[i] = b[i] = 1.0 * i;
	sum = 0;
	#pragma omp parallel
		dotprod();
	printf("sum %lf\n", sum);
	return 0;
}

