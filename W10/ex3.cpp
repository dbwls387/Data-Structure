#include <stdio.h>

int is_sum(int data[], int start, int end);
int K, cnt = 0;

int main(void) {
	int data[100], N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
		scanf("%d", &data[i]);
	scanf("%d", &K);

	int start = 0, end = N - 1;
	printf("%d", is_sum(data, 0, N - 1));

	return 0;
}
int is_sum(int data[], int start, int end) {
	int sum;
	sum = data[start] + data[end];

	if (end <= start)
		return cnt;

	if (sum > K) {
		end--;
		return is_sum(data, start, end);
	}
	else if (sum < K) {
		start++;
		return is_sum(data, start, end);
	}
	else {
		end--;
		start++;
		cnt++;
		return is_sum(data, start, end);
	}
}