int solution(int A[], int N) {

	int min = A[0] + A[1];
	min = min > 0 ? min : -min;
	int temp = 0;

	for (int i = 0; i < N; i++) {

		for (int j = 0; j < N; j++) {

			temp = A[i] + A[j];
			temp = temp > 0 ? temp : -temp;

			if (temp < min) {
				min = temp;
			}
		}
	}
	return min;
}
