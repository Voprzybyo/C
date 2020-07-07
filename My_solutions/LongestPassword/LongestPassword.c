#include <stdio.h>
#include <string.h>

#define A_ASCII 65
#define Z_ASCII 90
#define a_ASCII 97
#define z_ASCII 122
#define Zero_ASCII 48
#define Nine_ASCII 57

int solution(char* S) {

	int howManyWords = 1;
	int point = 0;
	int howManyChars = 0;
	char LongestPassword[200];  LongestPassword[0] = '\0';
	int numberOfLetters = 0;
	int numberOfDigits = 0;
	int nonAlphanum = 0;

	for (int i = 0; i <= strlen(S); i++) {

		howManyChars++;
		if (
			(S[i] >= A_ASCII && S[i] <= Z_ASCII) ||
			(S[i] >= a_ASCII && S[i] <= z_ASCII)
			) {
			numberOfLetters++;
		}
		else if (S[i] >= Zero_ASCII && S[i] <= Nine_ASCII) {
			numberOfDigits++;
		}
		else if (S[i] != ' ' && S[i] != '\0') {
			nonAlphanum = 1;
		}

		if (S[i] == ' ' || S[i] == '\0') {

			if (numberOfLetters % 2 == 0 &&
				numberOfDigits % 2 == 1 &&
				nonAlphanum == 0)
			{
				if (howManyChars > strlen(LongestPassword)) {
					strncpy(LongestPassword, S + point, howManyChars);
					LongestPassword[howManyChars - 1] = '\0';
				}
			}
			howManyChars = 0;
			numberOfLetters = 0;
			numberOfDigits = 0;
			nonAlphanum = 0;
			point = i + 1;
		}
	}
	printf("\n\nLongest Password in accordance with the defined Password Policy = '%s'\n", LongestPassword);
	if (strlen(LongestPassword) > 0) {
		return strlen(LongestPassword);
	}
	else {
		return -1;
	}
}