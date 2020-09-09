#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int main(void) {
	char arr[MAX];
	int len = 0, q = 0;
	int num[MAX];
	int ten = 0, n_r = 0, sum = 0;

	scanf("%s", arr);

	len = strlen(arr);

	for (int i = 0; i < len; i++) {
		if (47 < arr[i] && arr[i]< 58) {
			num[q++] = arr[i] - 48;
			if (47 > arr[i + 1] || arr[i + 1] > 58) {
				for (int j = 0; j < q; j++) {
					ten = num[j];
					for (int k = 0; k < q - j - 1; k++) {
						ten *= 10;
					}
					sum += ten;
				}
				q = 0;
			}
		}
	}

	printf("%d\n", sum);

	return 0;
}