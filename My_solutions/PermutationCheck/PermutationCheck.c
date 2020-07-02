int solution(int A[], int N) {
	int counter = 0;
	for (int i = 1; i < N + 1; i++) {
		counter = 0;
		for (int j = 0; j < N; j++) {
			if (A[j] == i) {
				counter++;
			}
		}
		if (counter != 1) {
			return 0;
		}
	}
	return 1;
}