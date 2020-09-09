#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

int main(void) {
	int diff[MAX], n = 0, cnt = 0;
	char *input = (char*)malloc(100);
	char *word[MAX];

	while (1) {
		scanf("%s", input);

		if (strcmp(input, "EOF") == 0)
			break;

		int len = strlen(input);
		for (int q = 0; q < len; q++) {
			if ('A' <= input[q] && input[q] <= 'Z') {
				input[q] -= 'A' - 'a';
			}
		}
		word[n] = strdup(input);
		n++;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (strcmp(word[i], word[j]) == 0) {
				for (int k = i; k < n; k++) {
					word[k] = word[k + 1];
				}
				j--;
				n--;
			}
		}
	}
	n--;


	printf("%d\n", n);

	return 0;
}