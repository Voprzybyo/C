int solution(int N) {

	int counter = 0;

	for (int i = 1; i <= N; i++) {

		if (N % i == 0) {
			counter++;
		}
	}
	return counter;
}