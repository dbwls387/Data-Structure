#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int compare(char *str1, char *str2);

int main(void) {
	int result = 0;
	char word1[30], word2[30];

	scanf("%s", word1);
	scanf("%s", word2);
	result=compare(word1, word2);

	if (result == -1) 
		printf("%s %s", word2, word1);
	else if (result == 0) 
		printf("%s %s",word1,word2);
	else
		printf("%s %s",word1,word2);

	return 0;
}
int compare(char *str1, char *str2) {
	if (*str1 == '\0' && *str2 == '\0') 
		return 0;
	else if (*str1 > *str2) 
		return -1;
	else if (*str1 < *str2) 
		return 1;
	else 
		return compare((str1 + 1), (str2 + 1));
}