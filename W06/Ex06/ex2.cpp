#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	int coef;
	int expo_x, expo_y;
} Term;

Term *recognize(char *expr);
int main()
{
	char expr[30];
	int coef, exp_x, exp_y;
	scanf("%s", expr);
	Term *t = recognize(expr);
	printf("%d %d %d\n", t->coef, t->expo_x, t->expo_y);
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
	while (expr[i] >= '0'&&expr[i] <= '9') {	//계수
		t->coef = t->coef * 10 + (int)(expr[i] - '0');
		i++;
	}
	if (t->coef == 0)
		t->coef = sign_coef;
	else
		t->coef *= sign_coef;

	if (expr[i] != 'x') {
		t->expo_x = 0;
		t->expo_y = 0;		
		if (expr[i] == 'y') {
			i++; i++;
			while (expr[i] >= '0'&&expr[i] <= '9') {
				t->expo_y = t->expo_y * 10 + (int)(expr[i] - '0');
				i++;
			}
		}
		return t;
	}
	i++;
	if (i == '\0') {
		t->expo_x = 0;
		t->expo_y = 0;
		return t;
	}
	if (expr[i] != '^')  {
		t->expo_x = 1;
		if (expr[i] != 'y')
			return t;
	}
	i++;
	int ch = 0;
	if (expr[i] >= '0'&&expr[i] <= '9')
		t->expo_x = 0;
	while (expr[i] >= '0'&&expr[i] <= '9') {	//x차수
		t->expo_x = t->expo_x * 10 + (int)(expr[i] - '0');
		i++;
		ch = 1;
	}
	//
	if (ch == 0)
		i--;
	if (expr[i] != 'y') {		//y차수
		t->expo_y = 0;
		return t;
	}
	i++;
	if (expr[i] != '^') {
		t->expo_y = 1;
		return t;
	}
	i++;
	t->expo_y = 0;

	while (expr[i] >= '0'&&expr[i] <= '9') {	
		t->expo_y = t->expo_y * 10 + (int)(expr[i] - '0');
		i++;
	}


	return t;
}