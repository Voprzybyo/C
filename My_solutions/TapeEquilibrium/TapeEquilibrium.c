#include <assert.h>

int solution(int A[], int N) {

	int sum1 = 0;
	int sum2 = 0;
	int minimal = 1000;
	int difference = 0;

	assert(N > 1);

	for (int P = 1; P < N; P++) {
		for (int i = 0; i < N; i++) {
			if (i < P) {
				sum1 += A[i];
			}
			else {
				sum2 += A[i];
			}
		}
		difference = sum1 - sum2;
		difference = difference > 0 ? difference : -difference;

		sum1 = sum2 = 0;

		if (minimal > difference) {
			minimal = difference;
		}
	}
	return minimal;
}