int solution(int N, int M) {

	if (M == 1) return N;
	if (M == N) return 1;

	int a = N;
	int b = M;
	int temp;
	while (b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}

	return N / a;
}