int solution(int A[], int N) {
	int flag = 0;
	int i = 1;

	if (N == 1) {
		if (A[0] != 1) {
			return 1;
		}
		else {
			return 2;
		}
	}

	for (i = 1; i < N; i++) {
		flag = 0;
		for (int j = 0; j < N; j++) {

			if (A[j] == i) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			return i;
		}
	}
	return ++i;
}