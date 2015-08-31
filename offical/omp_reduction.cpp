#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100;
int main() {
	double a[MAXN], b[MAXN];
	for (int i = 0; i < MAXN; i++)
		a[i] = b[i] = i * 1.0;
	double sum = 0;
	
	int i;
	#pragma omp parallel for reduction(+:sum)
	for (i = 0; i < MAXN; i++)
		sum = sum + (a[i] * b[i]);
	printf("sum = %lf\n", sum);
	return 0;
}

