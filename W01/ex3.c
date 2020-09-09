#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main() {
	int N, tmp;
	int data[MAX];

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &data[i]);

	int max = *data;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (*(data + i) < *(data + j)) {
				tmp = *(data + i);
				*(data + i) = *(data + j);
				*(data + j) = tmp;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		printf("%d\n", *(data + i));
	}
    
  return 0;
}