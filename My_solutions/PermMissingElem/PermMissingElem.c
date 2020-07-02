int solution(int A[], int N) {

	for (int i = 1; i < N + 1; i++) {

		for (int j = 0; j < N; j++) {
			if (A[j] == i) {
				break;
			}
			if (j == N - 1) {
				return i;
			}
		}

	}
}