#include <stdio.h>

int solution(int A[], int N) {

	int counter = 0;
	int res = 0;

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < N; j++) {

			if (A[i] == A[j]) {
				counter++;
			}

			if (j == N - 1) {

				if ((counter % 2) == 0) {
					counter = 0;
				}
				else {
					res = A[i];
					return res;
				}
			}
		}
	}
}





int main()
{

	int A[] = { 9, 3, 9, 3, 9, 7, 9 };

	int res = solution(A, 7);

	printf("%d", res);

	return 0;
}
