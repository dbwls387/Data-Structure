#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int coef;
	int expo;
} Term;
Term *recognize(char* expr);

int main() {
	char expr[30];
	scanf("%s", expr);
	Term *t = recognize(expr);
	printf("%d %d\n", t->coef, t->expo);

	return 0;
}

Term *recognize(char *expr) {
	Term *t = (Term *)malloc(sizeof(Term));
	int i = 0;
	int sign_coef = 1;
	t->coef = 0;
	if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (expr[i] >= '0'&&expr[i] <= '9') {
		t->coef = t->coef * 10 + (int)(expr[i] - '0');
		i++;
	}
	if (t->coef == 0)
		t->coef = sign_coef;
	else
		t->coef *= sign_coef;

	if (expr[i] != 'x') {
		t->expo = 0;
		return t;
	}
	i++;
	if (i == '\0') 
		return t;
	if (expr[i] != '^') {
		t->expo = 1;
		return t;
	}
	i++;
	t->expo = 0;
	while (expr[i] >= '0'&&expr[i] <= '9') {
		t->expo = t->expo * 10 + (int)(expr[i] - '0');
		i++;
	}
	return t;
}