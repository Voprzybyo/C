int solution(int A[], int N) {

	int max_number_of_flags = 1;
	int howManyPeaks = 0;
	int j = 0;

	for (int i = 1; i < N - 1; i++) {
		printf("i = %d\n", i);
		if ((A[i - 1] < A[i]) && (A[i + 1] < A[i])) {
			howManyPeaks++;
		}
	}

	int peak_points[howManyPeaks];

	for (int i = 1; i < N - 1; i++) {
		printf("i = %d\n", i);

		if ((A[i - 1] < A[i]) && (A[i + 1] < A[i])) {
			peak_points[j] = i;
			j++;
		}
	}

	for (int i = 0; i < howManyPeaks; i++) {
		printf("Peak point: %d\n", peak_points[i]);

	}

	int rel[howManyPeaks - 1];

	for (int i = 1; i < howManyPeaks; i++) {
		rel[i] = peak_points[i] - peak_points[i - 1];
		printf("rel[i] = %d\n", rel[i]);
	}

	max_number_of_flags = 1;

	if (howManyPeaks == 1) {
		return 1;
	}
	int max = howManyPeaks;
	for (int liczba_flag = howManyPeaks; liczba_flag > 2; liczba_flag--) {
		for (int numer_relacji = 0; numer_relacji < howManyPeaks - 1; numer_relacji++) {

			printf("Liczba flag = %d max = %d\n", liczba_flag, max);

			if (liczba_flag < rel[numer_relacji]) {
				max--;
				rel[numer_relacji] = rel[numer_relacji] + rel[numer_relacji + 1];
				numer_relacji--;
			}
		}
		if (max > max_number_of_flags) {
			max_number_of_flags = max;
			printf("Aktualizacja max_number_of_flags na: %d\n", max_number_of_flags);
		}
		max = howManyPeaks;
	}
	return max_number_of_flags;
}