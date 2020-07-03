int solution(char* S) {

	int MAXSIZE = 100000;

	int stack[MAXSIZE];
	int top = -1;

	int isempty() {

		if (top == -1)
			return 1;
		else
			return 0;
	}

	int isfull() {

		if (top == MAXSIZE)
			return 1;
		else
			return 0;
	}

	int peek() {
		return stack[top];
	}

	int pop() {
		int data;

		if (!isempty()) {
			data = stack[top];
			top = top - 1;
			return data;
		}
		else {
			printf("Could not retrieve data, Stack is empty.\n");
		}
	}

	int push(int data) {

		if (!isfull()) {
			top = top + 1;
			stack[top] = data;
		}
		else {
			printf("Could not insert data, Stack is full.\n");
		}
	}

	for (int i = 0; i < strlen(S); i++) {

		if (S[i] == '(') {
			push(')');
		}
		else if (S[i] == '[') {
			push(']');
		}
		else if (S[i] == '{') {
			push('}');
		}

		else if (S[i] == ')' || S[i] == ']' || S[i] == '}') {
			if (top == -1) {
				return 0;
			}
			else {
				char temp = pop();
				if (temp != S[i]) {
					return 0;
				}
			}
		}
	}

	if (top == -1) {
		return 1;
	}
	else {
		return 0;
	}

}