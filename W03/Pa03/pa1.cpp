#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char ch_anagram(char*, char*);

int main(void) {
	char text[20], tmp[MAX];
	int n = 0, l = 0, q = 0, numnum[MAX];
	char *anag[MAX][MAX];
	char *real[MAX][MAX];
	char *arr[MAX] = { NULL };

	while(1) {
		scanf("%s", text);
		if (strcmp(text, "EOF") == 0)
			break;
		l = strlen(text);
		if (l > 0) {
			char* newstr = (char*)malloc(sizeof(char)*(l + 1));
			strcpy(newstr, text);
			arr[n] = newstr;
			n++;
		}
		else break;
	}
	for (int i = 0; i < n; i++) {
		q = 0;
		anag[i][q++] = arr[i];
		for (int j = i + 1; j < n; j++) {
			if (ch_anagram(arr[i], arr[j]) == 1) {
				//새로운 배열에 넣고 인덱스 날리기
				anag[i][q++] = arr[j];
				for (int i = j; i < n - 1; i++) {
					arr[i] = arr[i + 1];
				}
				n--; j--;
			}
		}
		numnum[i] = q;
	}

	for (int k = 0; k < n; k++) {		// 한 행 안의 단어 정렬
		for (int i = 0; i < numnum[k] - 1; i++) {
			for (int j = 0; j < numnum[k] - 1 - i; j++) {
				if (strcmp(anag[k][j], anag[k][j + 1]) > 0) {
					strcpy(tmp, anag[k][j]);
					strcpy(anag[k][j], anag[k][j + 1]);
					strcpy(anag[k][j + 1], tmp);
				}
			}
		}
	}
	int index[MAX];
	for (int i = 0; i < n; i++) {
		index[i] = i;
	}
	int ttmp = 0;

	for (int i = n - 1; i >= 0; i--) {		//사전식 배열
		for (int j = 0; j < i; j++) {
			if (strcmp(anag[index[j]][0], anag[index[j + 1]][0]) > 0) {
				ttmp = index[j];
				index[j] = index[j + 1];
				index[j + 1] = ttmp;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < numnum[index[i]]; j++) {
			printf("%s ", anag[index[i]][j]);
		}
		printf("\n");
	}

	return 0;
}

char ch_anagram(char a[], char b[]) {
	int fir[26] = { 0 }, sec[26] = { 0 }, n = 0;

	while (a[n] != '\0') {
		fir[a[n] - 'a']++;
		n++;
	}
	n = 0;
	while (b[n] != '\0') {
		sec[b[n] - 'a']++;
		n++;
	}
	for (int i = 0; i < 26; i++) {
		if (fir[i] != sec[i])
			return 0;		//아나그램 아님
	}
	return 1;				//아나그램
}