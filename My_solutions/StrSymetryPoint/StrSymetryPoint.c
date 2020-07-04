int solution(char* S) {

	int j = strlen(S) - 1;
	int counter = 0;

	if (strlen(S) == 1) { return 0; }
	if (strlen(S) == 0) { return -1; }
	if (strlen(S) % 2 == 0) { return -1; }

	for (int i = 0; i < strlen(S); i++) {

		if (S[i] == S[j]) {
			counter++;
		}
		else {
			return -1;
		}

		if (i == j) {
			return i;
		}
		j--;
	}
}