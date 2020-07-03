int solution(int A[], int N) {

	int counter = 0;

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < N; j++) {

			if (A[i] == A[j]) {
				counter++;
			}
		}
		if (counter > N / 2) {
			return i;
		}
		else {
			counter = 0;
		}
	}
	return -1;
}