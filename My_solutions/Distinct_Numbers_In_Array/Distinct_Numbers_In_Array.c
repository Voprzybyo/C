int solution(int A[], int N) {

	int counter = 0;

	for (int i = 0; i < N; i++) {

		for (int j = i - 1; j >= 0; j--) {

			if (A[i] == A[j]) {
				counter--;
				break;
			}
		}
		counter++;
	}
	return counter;
}