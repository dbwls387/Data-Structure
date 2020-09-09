#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	char *name[100], *singer[100], arr[100][200], *number[100], name2[100][100], singer2[100][100];
	int number2[100];
	int N;

	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++)
		fgets(arr[i], sizeof(arr[i]), stdin);
	for (int i = 0; i < N; i++)	{
		name[i] = strtok(arr[i], "-");
		singer[i] = strtok(NULL, "-");
		number[i] = strtok(NULL, " #.");
	}
	for (int i = 0; i < N; i++)	{
		strcpy(name2[i], name[i]);
		name2[i][strlen(name2[i]) - 1] = '\0';
		strcpy(singer2[i], singer[i]);
		number2[i] = atoi(number[i]);
	}
	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < strlen(singer2[i]) - 1; j++)
			singer2[i][j] = singer2[i][j + 1];
		singer[i][strlen(singer2[i]) - 1] = '\0';
	}

	int j = N, temp = 0;
	char tmp[100];
	while (j > 0) {
		for (int i = 0; i < j - 1; i++)	{
			if (number2[i] > number2[i + 1]) {
				strcpy(tmp, name2[i]);
				strcpy(name2[i], name2[i + 1]);
				strcpy(name2[i + 1], tmp);

				strcpy(tmp, singer2[i]);
				strcpy(singer2[i], singer2[i + 1]);
				strcpy(singer2[i + 1], tmp);

				temp = number2[i];
				number2[i] = number2[i + 1];
				number2[i + 1] = temp;
			}
		}
		j--;
	}
	for (int i = 0; i < N; i++) {
		printf("%02d-%s-%s.mp3\n", i + 1, name2[i], singer2[i]);
	}

	return 0;
}