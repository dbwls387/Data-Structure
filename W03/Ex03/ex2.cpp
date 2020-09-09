#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
int main(void) {
	char arr[MAX], data[MAX][MAX];
	int n = 0;

	fgets(arr, sizeof(arr), stdin);

	int len = strlen(arr);
	int q = 0, reme[MAX], a = 0, b = 0;
	int idx[MAX];

	for (int i = 0; i < len-1; i++) {
		if (arr[i] == '\"') {
			i++;
			while (1) {
				data[a][b++] = arr[i++];
				if (arr[i] == '\"') 
					break;
			}
			idx[a] = b;
			a++;
			b = 0;
		}
		else if ((arr[i] == ',') && (arr[i + 1] == ',')) {
			data[a][b++] = *" ";
			idx[a] = b;
			a++;
			b = 0;
		}
		else if (arr[i] == ',') {

		}
		else {
			while (1) {
				data[a][b++] = arr[i++];
				if (arr[i] == ',') {
					i--;
					break;
				}
				if (i == len)
					break;
			}
			idx[a] = b;
			a++;
			b = 0;
		}
	}

	printf("%d\n", a);
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < idx[i]; j++) {
			printf("%c", data[i][j]);
		}
		printf("\n");
	}

	return 0;
}