#include <stdio.h>
void sort_abc(int *l, int *m, int *n);

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    sort_abc(&a, &b, &c);
    printf("%d %d %d\n", a, b, c);
}
void sort_abc(int *l, int *m, int *n) {
	int tmp;

	if (*l < *m) {
		tmp = *l;
		*l = *m;
		*n = tmp;
	}
	if (*m < *n) {
		tmp = *m;
		*m = *n;
		*n = tmp;
	}
	if (*n < *l) {
		tmp = *n;
		*n = *l;
		*l = tmp;
	}
}