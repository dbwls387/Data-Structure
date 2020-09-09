#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

bool is_palindrome(char data[], int begin, int end, int n, int ch);

int main(void) {
	char data[MAX];
	int n = 0, i = 0;
	scanf("%s", data);

	while (data[i] != '\0') {
		n++; i++;
	}
	
	if (is_palindrome(data, 0, n - 1, n / 2, 0) == 0) {
		printf("No");
	}
	else {
		printf("Yes");
	}

	return 0;
}
bool is_palindrome(char data[], int begin, int end, int n, int ch) {
	if (data[begin] != data[end]) {
		return false;
	}
	else if (ch == n) {
		return true;
	}
	else {
		ch++;
		is_palindrome(data, begin + 1, end - 1, n, ch);
		return is_palindrome(data, begin + 1, end - 1, n, ch);
	}
}