int binaryGap(int N) {

	int binaryNum[32];

	int i = 0;
	int length = 0;
	while (N > 0) {

		binaryNum[i] = N % 2;
		N = N / 2;
		i++; length++;
	}

	int max = 0;
	int res = 0;
	int start = 0;

	for (int i = 0; i < length; i++) {

		if (binaryNum[i] == 1 && binaryNum[i + 1] == 0) {
			start = 1;
			max = 0;
			continue;
		}

		if (start == 1 && binaryNum[i] == 0) {
			max++;

			if (res < max) {
				res = max;
			}

		}
		else {
			start = 0;
			max = 0;
		}

	}

	return res;
}