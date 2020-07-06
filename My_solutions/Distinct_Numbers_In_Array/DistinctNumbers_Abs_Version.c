int solution(int A[], int N) {

	int counter = 0;
	for (int i = 0; i < N; i++) {
		A[i] = A[i] >= 0 ? A[i] : -A[i];

		for (int j = i - 1; j >= 0; j--) {

			if (A[j] == A[i]) {
				counter--;
				break;
			}
		}
		counter++;
	}
	return counter;
}