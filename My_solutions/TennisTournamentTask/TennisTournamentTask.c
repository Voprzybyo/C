int solution(int P, int C) {

	if (P % 2 != 0) {
		P--;
	}

	if (C > P / 2) {
		return P / 2;
	}
	else {
		return C;
	}
}