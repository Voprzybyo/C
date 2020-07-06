int max(int num1, int num2)
{
	return (num1 > num2) ? num1 : num2;
}

int solution(int A[], int N) {

	int tempTab[N];
	tempTab[0] = A[0];

	for (int i = 1; i < N; i++) {
		tempTab[i] = tempTab[i - 1];
		for (int minus = 2; minus <= 6; minus++) {
			if (i >= minus) {
				tempTab[i] = max(tempTab[i], tempTab[i - minus]);
			}
			else {
				break;
			}
		}
		tempTab[i] += A[i];
	}
	return tempTab[N - 1];
}