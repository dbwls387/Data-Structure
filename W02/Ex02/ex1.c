#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

int main(void) {
	char arr[MAX];
	int len = 0;
	char tmp[MAX];

	scanf("%s", arr);

	len = strlen(arr);

	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr[i] > arr[j]) {
				tmp[0] = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp[0];
			}
		}
	}

	printf("%s", arr);

	return 0;
}