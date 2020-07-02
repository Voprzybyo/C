
#include <stdio.h>

struct Results {
	int* A;
	int N;
};

struct Results solution(int A[], int N, int K) {

	struct Results struct_res;

	int temp = 0;

	for (int i = 0; i < K; i++) {
		temp = A[N - 1];

		for (int j = 1; j < N; j++) {

			A[N - j] = A[N - j - 1];

		}
		A[0] = temp;
	}

	struct_res.A = A;
	struct_res.N = N;

	return struct_res;
}




int main()
{
	printf("Hello World\n");

	struct Results res;
	struct Results* ptr;
	ptr = &res;

	res.N = 3;

	res.A[0] = 0;
	res.A[1] = 1;
	res.A[2] = 2;
	for (int i = 0; i < res.N; i++) {
		printf("%d", res.A[i]);
	}
	printf("\n");
	res = solution(res.A, res.N, 2);
	for (int i = 0; i < res.N; i++) {
		printf("%d", res.A[i]);
	}
	return 0;
}

#include <stdio.h>

struct Results {
	int* A;
	int N;
};

struct Results solution(int A[], int N, int K) {

	struct Results struct_res;

	int temp = 0;

	for (int i = 0; i < K; i++) {
		temp = A[N - 1];

		for (int j = 1; j < N; j++) {

			A[N - j] = A[N - j - 1];

		}
		A[0] = temp;
	}

	struct_res.A = A;
	struct_res.N = N;

	return struct_res;
}




int main()
{
	printf("Hello World\n");

	struct Results res;
	struct Results* ptr;
	ptr = &res;

	res.N = 3;

	res.A[0] = 0;
	res.A[1] = 1;
	res.A[2] = 2;
	for (int i = 0; i < res.N; i++) {
		printf("%d", res.A[i]);
	}
	printf("\n");
	res = solution(res.A, res.N, 2);
	for (int i = 0; i < res.N; i++) {
		printf("%d", res.A[i]);
	}
	return 0;
}
