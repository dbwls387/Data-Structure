#include<stdio.h>
#include<string.h>

#define MAX 50

void floor(int data[], int K, int begin, int end);
void ceiling(int data[], int k, int begin, int end);

int large = -1000;
int small = 1000;

int main(void) {
	int N = 0, K = 0;
	int data[MAX];
	int begin = 0;

	scanf("%d", &N);

	for (int i = 0;i < N;i++) 
		scanf("%d", &data[i]);

	scanf("%d", &K);

	floor(data, K, begin, N - 1);

	if (large == -1000)
		printf("-1 ");	
	else
		printf("%d ", large);

	ceiling(data, K, begin, N - 1);

	if (small == 1000) 
		printf("-1");
	else
		printf("%d", small);

	return 0;
}
void floor(int data[], int k, int begin, int end) {
	if (begin > end)
		return;
	else if (data[begin] <=k) {
		if (large <= data[begin]) {
			large = data[begin];
			floor(data, k, ++begin, end);
		}
	}
	else {
		floor(data, k, ++begin, end);
	}
}
void ceiling(int data[], int k, int begin, int end) {
	if (begin > end)
		return;
	else if (data[begin] >= k) {
		if (small >= data[begin]) {
			small = data[begin];
			ceiling(data, k, ++begin, end);
		}
	}
	else {
		ceiling(data, k, ++begin, end);
	}
}