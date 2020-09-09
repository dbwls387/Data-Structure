#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
int main(void) {
	char arr[MAX], data[MAX];
	int n = 0;

	fgets(arr, sizeof(arr), stdin);
	
	strcpy(data, arr);

	char *tok = strtok(data, ",");
	while (tok != NULL) {
		n++;
		tok = strtok(NULL, ",");
	}
	printf("%d\n", n);

	tok = strtok(arr, ",");
	while (tok != NULL) {
		printf("%s\n", tok);
		tok = strtok(NULL, ",");
	}
	
	return 0;
}