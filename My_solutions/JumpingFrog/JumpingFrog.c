int solution(int X, int Y, int D) {

	int distance = Y - X;
	int jumps;

	while (distance > 0) {
		distance -= D;
		jumps++;
	}

	return jumps;

}