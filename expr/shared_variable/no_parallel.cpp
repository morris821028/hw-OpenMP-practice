#include <omp.h>
#include <stdio.h>
using namespace std;

int main() {
	double sum = 0;
	for (int i = 0; i < 10000; i++)
		for (int j = 0; j < 50000; j++)
			sum += 1;
	printf("%lf\n", sum);
	return 0;
}

