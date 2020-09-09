#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

int main(void) {
	int n, m, max[MAX];
	char word[50];
	char *arr[MAX][MAX];
	scanf("%d %d", &m, &n);

	for (int i = 0; i < m; i++) {			//입력받기
		for (int j = 0; j < n; j++) {
			scanf("%s", word);
			arr[i][j] = strdup(word);
		}
	}
	max[0] = strlen(arr[0][0]);				
	int q = 0;
	for (int i = 0; i < n; i++) {			//세로줄에서 제일 긴 길이 구하기 
		for (int j = 0; j < m; j++) {
			int len = strlen(arr[j][i]);
			if (max[q] < len)
				max[q] = len;
		}
		q++;
	}
	for (int i = 0; i < m; i++) {			//줄맞춤 공백 설정
		q = 0;
		for (int j = 0; j < n; j++) {
			printf("%s", arr[i][j]);
			if (j != (n - 1))
				printf(" ");
			if (j != (n - 1)) {
				for (int k = 0; k < max[q] - strlen(arr[i][j]); k++)
					printf(" ");
			}		
			q++;
		}
		printf("\n");
	}

	return 0;
}