int solution(int A[], int N) {

	int temp = 0;
	int swapped = 0;
	int res = 0;
	int counter = 0;

	while (1) {

		swapped = 0;

		for (int i = 0; i < N - 1; i++) {


			if (A[i] > A[i + 1]) {
				temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
				swapped = 1;
			}
		}

		if (swapped == 0) { break; }
	}

	for (int i = 0; i < N; i++) {

		if (A[i] == A[i + 1]) {
			counter++;
		}
		else {
			if (counter % 2 == 0) {
				res = A[i];
			}
			counter = 0;
		}

	}

	return res;
}


int main()
{
	int A[] = { 9, 3, 9, 3, 9, 7, 9 };

	int res = solution(A, 7);

	printf("\n\n%d", res);

	return 0;
}