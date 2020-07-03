int solution(int N) {

	int min_perimeter = 2 * (1 + N);
	int perim = 0;
	int i = 1;

	for (i = 1; i < N / 2; i++) {
		int j = N / i;

		if (i * j != N) { continue; }

		perim = 2 * (i + j);

		if (perim < min_perimeter) {
			min_perimeter = perim;
		}
	}
	return min_perimeter;
}