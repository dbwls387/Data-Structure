#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 70000

int check_alpha(char);

int main(void) {
	char *arr[MAX];
	char word[30];
	int wcnt = 0;
	int q = 0, len;
	int same[MAX];

	FILE *fp = fopen("pride_and_prejudice.txt", "r");

	while (fscanf(fp, "%s", word) != EOF) {
		//fscanf(fp, "%s", word);

		len = (strlen(word));				//입력받은 단어길이
		if (len < 7)						//길이가 7이하면 다시 처음으로
			continue;

		int checnt = 0;
		for (int i = 0; i < len; i++) {		//기호 확인
			if (check_alpha(word[i]) == 0)
				checnt++;
		}
		if (checnt == len)
			continue;						//다 기호라 while 처음으로 돌아가기

		for (int i = 0; i < len; i++) {		//대문자 -> 소문자
			if ('A' <= word[i] && word[i] <= 'Z') {
				word[i] -= 'A' - 'a';
			}
		}

		while (1) {							//단어 맨 뒤의 기호 제거
			if (check_alpha(word[len - 1]) == 0) {
				word[len - 1] = '\0';
				len--;
			}
			else
				break;
		}
		int index = 0;
		//단어 맨 앞의 기호 제거
		for (int j = 0; j < len; j++) {
			if (word[j] >= 'a'&&word[j] <= 'z') {
				index = j;
				break;
			}
		}
		len -= index;
		for (int i = 0; i < len; i++) {
			word[i] = word[index];
			index++;
		}
		word[len] = '\0';

		if (len < 7)		//길이가 7이하면 다시 처음으로
			continue;

		arr[q] = strdup(word);
		q++;
		wcnt++;
	}
	fclose(fp);

	char tmp[MAX];
	for (int i = wcnt - 1; i >= 0; i--) {		//사전식 배열
		for (int j = 0; j < i; j++) {
			if (strcmp(arr[j], arr[j + 1]) > 0) {
				strcpy(tmp, arr[j]);
				strcpy(arr[j], arr[j + 1]);
				strcpy(arr[j + 1], tmp);
			}
		}
	}

	for (int i = 0; i < wcnt; i++)				//빈도수 배열 1로 초기화
		same[i] = 1;

	for (int i = 0; i < wcnt; i++) {			//같은 단어 빈도수 올리기
		for (int j = i + 1; j < wcnt; j++) {
			if (strcmp(arr[i], arr[j]) == 0) {
				same[i] += 1;
				same[j] += 1;
			}
		}
	}
	for (int i = 0; i < wcnt - 1; i++) {			//같은 단어가 사전식 배열로 있으니까 배열을 다 한칸씩 땡겨주기 
		if (strcmp(arr[i], arr[i + 1]) == 0) {
			for (int j = i; j < wcnt; j++) {
				arr[j] = arr[j + 1];
				same[j] = same[j + 1];
			}
			i--;		
			wcnt--;
		}
	}

	for (int i = 0; i < wcnt; i += 10) {
		printf("%s %d\n", arr[i], same[i]);
	}

	return 0;
}
int check_alpha(char word) {
	if ((word >= 'a'&&word <= 'z') ||( word >= 'A'&&word <= 'Z'))
		return 1;		//알파벳임
	else
		return 0;		//기호임
}
char *strdup(char *s) {
	char *p;
	p = (char *)malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}