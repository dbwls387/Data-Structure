#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_POLYS 300
#define BUFFER_LENGTH 80

struct term {
	int coef;
	int exp_x, exp_y;
	struct term *next;
};
typedef struct term Term;

typedef struct polynomial {
	char name;
	Term *first;
	int size;
} Polynomial;
Polynomial *polys[MAX_POLYS];
int n = 0;


void def(char *expression);											//함수를 정의하는함수
void add(char str1,char str2,char str3);					//두다항식을 더해 새로운 다항식을 정의하는함수
void add_term(int c, int e_x,int e_y,Polynomial *poly);		//항을 추가하는함수
void o_calc(char str,int a,int b);							//계산하는 함수(먼저호출) 다항식과 매개변수값을 넘겨줌 
int calc(Term *term, int x, int y);							//다항식의 값을 계산하는함수
void list();												//저장되어있는 다항식을 출력하는함수
void print(char str);										//다항식을 프린트하는함수(제일먼저호출)
void print_term(Term *);									//다항식안에 term(항을 출력하는함수)
void print_poly(Polynomial *p);								//다항식 자체(f or t)을 출력하는함수
void erase_blanks(char *expression);						//공백을 지워주는함수
void insert_polynomial(Polynomial *);						//다항식을 넣어주는함수
void destroy_polynomial(Polynomial *);						//다항식을 삭제하는함수

Polynomial *create_by_add_two_polynomials(char name, char f, char g); //두다항식을 더해 새로운 다항식을 만드는함수

Polynomial *poly_search(char str);									// 다항식을 찾아주는함수
Polynomial *create_by_parse_polynomial(char name, char *body);		//다항식을 만드는함수(def에서 사용)
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly); //다항식을 만드는함수(def에서 사용
																		//계수,차수를 add_term 함수에 넘겨줌)
Term *create_term_instance();										//다항식의 항을 만드는함수
Polynomial *create_polynomial_instance(char );						//다항식을 만드는함수


int main(void) {

	char buffer[BUFFER_LENGTH];
	char copy_buffer[BUFFER_LENGTH];
	char *command;
	char *arg1, *arg2, *arg3;

	while (1) {
		printf("$ ");
		fgets(buffer, sizeof(buffer), stdin);			//명령어를 입력받는다
		buffer[strlen(buffer) - 1] = '\0';				//명령의 마지막칸에 개행문자대신 널문자삽입
		strcpy(copy_buffer, buffer);					//명령어 전체를 copy_buffer에 복사
		command = strtok(buffer, " ");					//strtok을사용하여 명령어 인식

		if (strcmp(command, "def") == 0) {				// command 가 "def" 인경우
			def(copy_buffer);
		}
		if (strcmp(command, "calc") == 0) {				//command 가 "calc" 인경우
			arg1 = strtok(NULL, " ");
			arg2 = strtok(NULL, " ");
			arg3 = strtok(NULL, " ");
			o_calc(arg1[0], atoi(arg2), atoi(arg3));	//명령어로 다항식이름 매개변수를 넘겨줌
		}
		if (strcmp(command, "add") == 0) {				//command가 "add"인경우
			arg1 = strtok(NULL, "=");
			arg2 = strtok(NULL, " ");
			strtok(NULL, " ");
			arg3 = strtok(NULL, " ");
			add(arg1[0], arg2[0],arg3[0]);				//h = f + g 로넘겨줌
		}
		if (strcmp(command, "list") == 0) {				//command가 "list" 인경우
			list();
		}
		if (strcmp(command, "print") == 0) {			//command가 "print" 인경우
			arg1 = strtok(NULL, " ");
			print(arg1[0]);
		}
		if (strcmp(command, "exit") == 0)				//command가 "exit" 인경우
			break;
	}
	return 0;
}

void add_term(int c, int e_x,int e_y,Polynomial *poly) {	//항을 만드는함수
	if (c == 0)
		return;
	Term *p = poly->first, *q = NULL;

	while (p != NULL && p->exp_x > e_x) {			// x에대한 내리차순으로 하기위한 while문
		q = p;
		p = p->next;
	}
	if (p != NULL && e_x == 0) {					//만약 x의차수가 0인경우
		while (p != NULL && p->exp_y > e_y&&p->exp_x==e_x) {	// y의차수를 비교하기위해 while문 한번더실행
			q = p;									//이떄 p와 q의 이동과정에서 x의차수가 바뀔경우 탈출
			p = p->next;
		}
		if (p !=NULL&&p->exp_y == e_y&&p->exp_x==e_x) {	//while문 실행후 x의차수와 y의차수가 같아진경우
			p->coef += c;					
			if (p->coef == 0) {				//y의차수가 같을때 더해서 계수가 0인경우
				if (q == NULL)				//첫항인경우
					poly->first = p->next;
				else 
					q->next = p->next;		//첫항이 아닌경우
				poly->size--;
				free(p);
			}
			return;							//실행후 리턴
		}
		if(p!=NULL&&p->exp_y!=e_y){			//while 문 실행후 y의차수가 다른경우
			Term *term = create_term_instance();	//새로운 항 추가후 리턴
			term->coef = c;
			term->exp_x = e_x;
			term->exp_y = e_y;
			term->next = p;
			q->next = term;
			poly->size++;
			return;
		}
	}
	if (p != NULL && p->exp_x == e_x) {					//입력 x의차수와 p의차수가 같은경우
		if (p->exp_y==e_y) {							//이떄 x의차수와 y의차수도 같은경우
			p->coef += c;								
			if (p->coef == 0) {							//더해서 계수가 0이된경우
				if (q == NULL)							//첫항인경우
					poly->first = p->next;
				else
					q->next = p->next;					//첫항이 아닌경우					
				poly->size--;
				free(p);
			}
			return;
		}
		while (p != NULL && p->exp_y > e_y && p->exp_x==e_x) {	//x의차수만 같고 y의차수는 다른경우
			q = p;										//이때 p와 q의이동과정에서 e_x가 달라지면 탈출
			p = p->next;
		}
		if (p!=NULL && p->exp_x==e_x && p->exp_y == e_y) {	//이동후 x와 y의차수가 같아진경우
			if (p->coef += c) {
				if (p->coef == 0) {
					if (q == NULL)
						poly->first = p->next;
					else {
						q->next = p->next;
					}
					poly->size--;
					free(p);
				}
			}
			return;
		}
		Term *term = create_term_instance();	
		term->coef = c;							//이조건은 처음에 입력 x와 p의 x가 같은경우임 
		term->exp_x = e_x;						//모든 while문 조건을 다통과한후 겹치치않을경우 
		term->exp_y = e_y;						//새로운항을 정의
		term->next = p;
		q->next = term;
		poly->size++;
		return;
	}
	Term *term = create_term_instance(); //모든조건을 만족후 p의앞에 q의 뒤에 삽입
	term->coef = c;
	term->exp_x = e_x;
	term->exp_y = e_y;
	
	if (q == NULL) {						//항이 1개도없을경우 와 맨처음노드에 삽입할때 사용
		term->next = poly->first;
		poly->first = term;
	}
	else {
		term->next = p;						//중간 노드에 삽입
		q->next = term;
	}
	poly->size++;							//항의 개수 ++
}

void o_calc(char str,int a,int b) {			//항을 계산하는함수

	int result = 0;
	Polynomial *poly=poly_search(str);		//계산하고자하는 함수를 입력받아 서치함수를 통해받음
	Term *t = poly->first;
	while (t != NULL) {
		result += calc(t, a, b);			//매개변수와 다항식안에 항을 넘겨줌 그결과값들을 더함
		t = t->next;
	}
	printf("%d\n", result);					//각항의 결과값을 다더한 값을 출력

}
int calc(Term *term, int x,int y) {
	int result = term->coef;

	for (int i = 0;i < term->exp_x;i++) {		//항의 계수, x,y의차수를 고려하여 항의값 계산
		result *= x;
	}
	for (int i = 0;i < term->exp_y;i++) {
		result *= y;
	}
	return result;
}

void list() {							//다항식안에 있는 함수들을 차례대로 출력
	for (int i = 0;i < n;i++) {
		print(polys[i]->name);
	}
}

void print(char str) {					// 다항식을 출력하는함수
	for (int i = 0;i < n;i++) {
		if (str == polys[i]->name) {	//입력받은 다항식의 이름과 같은 다항식을 찾아 출력함수 호출
			print_poly(polys[i]);
			return;
		}
	}
	printf("%c Polynomial No exist\n",str);	//만약 없을시 존재하지않는다고 출력
	return;
}
void print_poly(Polynomial *p) {		//다항식을 출력하는함수 print_term함수를 호출시켜줌
	
	int count = 0;
	printf("%c=", p->name);
	Term *t = p->first;
	while (t != NULL) {					//다항식을 차례로 출력하면서 전진
		print_term(t);
		t = t->next;
		count++;
		if (count != p->size) {			//만약 마지막 항은 +기호를 출력하면 안되기 위한 조건문
			if (t->coef > 0)
				printf("+");
		}
	}
	printf("\n");
}
void print_term(Term *t) {

	if (t->coef != 1 && t->coef != -1) {				//계수가 1또는 -1인이 아닌경우
		if (t->exp_x == 0 && t->exp_y == 0) {			//상수항일떄 계수만출력
			printf("%d", t->coef);
			return;
		}
		else if (t->exp_x == 1 && t->exp_y == 0) {		//x항만있고 그차수가 1인경우
			printf("%dx", t->coef);
			return;
		}

		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 0) {		//x의항만 있고 그차수가 1이아닌경우
			printf("%dx^%d", t->coef, t->exp_x);
			return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 1) {		//x의항이 1이아니고 y의항이 1인경우
			printf("%dx^%dy", t->coef, t->exp_x);
			return;
		}

		else if (t->exp_x == 1 && t->exp_y == 1) {		//x의항의차수가 1이고 y의항의 차수가 1인경우
			printf("%dxy", t->coef);
			return;
		}
		else if (t->exp_x == 1 && t->exp_y != 1 && t->exp_y!=0) {		//x의항의 차수가 1이고 y의항의 차수가 1이아닌경우
			printf("%dxy^%d", t->coef, t->exp_y);
			return;
		}

		else if (t->exp_x == 0 && t->exp_y == 1) {		//x항이없고 y의항의 차수가 1인경우
			printf("%dy", t->coef);
			return;
		}
		else if (t->exp_x == 0 && t->exp_y != 1 && t->exp_y!=0) {		//x항이없고 y의항의 차수가 1이아닌경우
			printf("%dy^%d", t->coef, t->exp_y);
			return;
		}
		else if (t->exp_x != 1 &&t->exp_x!=0 && t->exp_y != 1 && t->exp_y!=0) {		//x의항이 차수가 1이아니고 y의항의 차수가 1이아닌경우		
			printf("%dx^%dy^%d", t->coef, t->exp_x, t->exp_y);
			return;
		}
		return;
	}

	if (t->coef == 1) {						//계수가 1인경우
		if (t->exp_x == 0 && t->exp_y == 0) {		//계수가 1일떄 x,y의차수가 0인경우
			printf("%d", t->coef);
			return;
		}
		if (t->exp_x == 1 && t->exp_y == 0) {		//x항만있고 그차수가 1인경우
		printf("x");
		return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 0) {		//x의항만 있고 그차수가 1이아닌경우
			printf("x^%d",t->exp_x);
			return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 1) {		//x의항이 1이아니고 y의항이 1인경우
			printf("x^%dy",t->exp_x);
			return;
		}

		else if (t->exp_x == 1 && t->exp_y == 1) {		//x의항의차수가 1이고 y의항의 차수가 1인경우
			printf("xy");
			return;
		}
		else if (t->exp_x == 1 && t->exp_y != 1 && t->exp_y!=0) {		//x의항의 차수가 1이고 y의항의 차수가 1이아닌경우
			printf("xy^%d",t->exp_y);
			return;
		}

		else if (t->exp_x == 0 && t->exp_y == 1) {		//x항이없고 y의항의 차수가 1인경우
			printf("y");
			return;
		}

		else if (t->exp_x == 0 && t->exp_y != 1 && t->exp_y!=0) {		//x항이없고 y의항의 차수가 1이아닌경우
			printf("y^%d",t->exp_y);
			return;
		}
		else if (t->exp_x != 1 && t->exp_y != 1 && t->exp_y!=0) {		//x의항이 차수가 1이아니고 y의항의 차수가 1이아닌경우		
			printf("x^%dy^%d",t->exp_x, t->exp_y);
			return;
		}
		return;
	}
	if (t->coef == -1) {			//계수가 -1인경우
		if (t->exp_x == 0 && t->exp_y == 0) {		//계수가 -1이고 x,y의 차수가 0인경우
			printf("%d", t->coef);
			return;
		}
		if (t->exp_x == 1 && t->exp_y == 0) {		//x항만있고 그차수가 1인경우
			printf("-x");
			return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 0) {		//x의항만 있고 그차수가 1이아닌경우
			printf("-x^%d", t->exp_x);
			return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y == 1) {		//x의항이 1이아니고 y의항이 1인경우
			printf("-x^%dy",t->exp_x);
			return;
		}

		else if (t->exp_x == 1 && t->exp_y == 1) {		//x의항의차수가 1이고 y의항의 차수가 1인경우
			printf("-xy");
			return;
		}
		else if (t->exp_x == 1 && t->exp_y != 1) {		//x의항의 차수가 1이고 y의항의 차수가 1이아닌경우
			printf("-xy^%d",t->exp_y);
			return;
		}

		else if (t->exp_x == 0 && t->exp_y == 1) {		//x항이없고 y의항의 차수가 1인경우
			printf("-y");
			return;
		}

		else if (t->exp_x == 0 && t->exp_y != 1) {		//x항이없고 y의항의 차수가 1이아닌경우
			printf("-y^%d", t->exp_y);
			return;
		}
		else if (t->exp_x != 1 && t->exp_x!=0 && t->exp_y != 1 && t->exp_y!=0) {		//x의항이 차수가 1이아니고 y의항의 차수가 1이아닌경우		
			printf("-x^%dy^%d", t->exp_x, t->exp_y);
			return;
		}
	}
	return;
}

void add(char str1, char str2, char str3) {				//두다항식을 더한다
	Polynomial *p = create_by_add_two_polynomials(str1, str2, str3);	// h = f + g 형식으로 넘겨줌 
	insert_polynomial(p);								//새로 정의한 h를 포인터배열에 넣어줌
}
Polynomial *create_by_add_two_polynomials(char name, char f, char g) {	//두다항식을 더해 새로운다항식 정의
	//이함수의 원리는 새로운다항식을 정의할떄 한다항식 새로운 다항식에다가
	//다항식의 항들을 다넣어주면 add_term함수에서 정렬을 알아서 해주므로 넣주기만하면된다

	Polynomial *tmp=create_polynomial_instance(name);					//새로운다항식
	Polynomial *poly_f=poly_search(f);									//더하는 다항식중 하나
	Polynomial *poly_g = poly_search(g);								//더하는 다항식중 하나

	Term *term_f = poly_f->first;
	Term *term_g = poly_g->first;

	while (term_f != NULL) {											//f의다항식을넣어줌
		add_term(term_f->coef, term_f->exp_x, term_f->exp_y, tmp);
		term_f = term_f->next;
	}
	while (term_g != NULL) {											//g의다항식을넣어줌
		add_term(term_g->coef, term_g->exp_x, term_g->exp_y, tmp);
		term_g = term_g->next;
	}
	return tmp;		//새로만든 다항식을 리턴
}
void def(char *str) {
	int i = 0;			
	char *trash=strtok(str, " ");					//def명령어 제거
	char *f_name = strtok(NULL, "=");				//f_name은 다항식 이름
	erase_blanks(f_name);
	if (f_name == NULL || strlen(f_name) != 1) {
		printf("Invaild Segment.\n");
		return;
	}
	char *exp_body = strtok(NULL, "=");
	erase_blanks(exp_body);
	if (exp_body == NULL || strlen(exp_body) <= 0) {
		printf("Invail Segment.\n");
		return;
	}
	Polynomial *pol = create_by_parse_polynomial(f_name[0], exp_body);	//새로운 다항식의 이름과 몸체를 넘겨줌
	insert_polynomial(pol);
}
Polynomial *create_by_parse_polynomial(char name, char *body) {		//받은이름과 몸체를 정의하는함수
	
	Polynomial *ptr_poly = create_polynomial_instance(name);		//받은이름의 다항식을 정의하는함수
	int i = 0,begin_term=0;

	while (i < strlen(body)) {
		if (body[i] == '-' || body[i] == '+')
			i++;
		while (i<strlen(body)&&body[i] != '-' && body[i] != '+') {
			i++;
		}
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);

		if (result == 0) {
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly) {	//다항식에 각항을 만드는함수
	//계수,차수 다항식을 add_term함수에 넘겨줌
	int i = begin;
	int sign_coef = 1, coef = 0, expo_x = 1,expo_y=1;

	if (expr[i] == '+')
		i++;
	else if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}

	if (coef == 0)									//coef가 0인경우 상수항이아니라
		coef = sign_coef;							//계수가 -1또는 1인경우일수도 있다
	else
		coef *= sign_coef;

	if (i >= end) {									//상수항인 경우
		add_term(coef, 0,0, p_poly);
		return 1;
	}
	if (expr[i] == 'x') {							//첫항이 x인경우 y가있을수도 없을수도있음
		i++;
		if (i >= end) {								//계수다음에 x가나오고 y도없으면 x의차수는1 y의차수는0
			add_term(coef, 1, 0, p_poly);
			return 1;
		}
		if (expr[i] == 'y') {						//x의차수가 1인경우
			i++;
			if (i >= end) {
				add_term(coef, 1, 1, p_poly);		//x의차수가 1이고 y의차수가 1인경우
				return 1;
			}
			i++;
			expo_y = 0;
			while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {		//x의차수가 1이고 y의차수가 1이아닌경우
				expo_y = expo_y * 10 + (int)(expr[i] - '0');
				i++;
			}
			add_term(coef, 1, expo_y,p_poly);
			return 1;
		}

		i++;
		expo_x = 0;
		while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
			expo_x = expo_x * 10 + (int)(expr[i] - '0');
			i++;
		}
		if (i >= end) {									//x의차수가 1이아니고 y가없는경우
			add_term(coef, expo_x, 0,p_poly);
			return 1;
		}
	
		i++;
		if (i >= end) {									//x의차수가 1이아니고 y의차수가 1인경우
			add_term(coef, expo_x,1, p_poly);
		}
		i++;

		expo_y = 0;										//
		while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
			expo_y = expo_y * 10 + (int)(expr[i] - '0');
			i++;
		}
		add_term(coef, expo_x, expo_y, p_poly);				//x의차수가 1이아니고 y의차수가 1이아닌경우
		return 1;
	}

	if (expr[i] == 'y') {									//x항이없고 y항만 있는경우
		i++;
		if (i >= end) {
			add_term(coef, 0, 1, p_poly);					//x항이없고 y의항의 차수가 1인경우
			return 1;
		}
		i++;
	}
	expo_y = 0;												// y항의 계수를 계산
	while (i < end&&expr[i] >= '0'&&expr[i] <= '9') {
		expo_y = expo_y * 10 + (int)(expr[i] - '0');
		i++;
	}
	add_term(coef,0,expo_y, p_poly);						//x항이없고 y의항의 차수가 1이아닌경우
	return 1;
}
void erase_blanks(char *exp) {		//공백을 지워주는함수

	int j = 0;
	for (int i = 0;i < strlen(exp);i++) {	//for문을 돌면서 공백이 나올시 모든인덱스값을 한칸씩떙김
		if (exp[i] == ' ') {
			j = i;
			while (exp[j + 1] != '\0') {		//while문을 돌면서 한칸시떙김
				exp[j] = exp[j + 1];
				j++;
			}
			exp[j] = '\0';
		}
	}
}
Term *create_term_instance() {		//새로운 항을 정의
	Term *t_term = (Term *)malloc(sizeof(Term));
	t_term->coef = 0;
	t_term->exp_x = 0;
	t_term->exp_y = 0;
	t_term->next = NULL;
	return t_term;
}
Polynomial *create_polynomial_instance(char t_name) {	//새로운 다항식을 정의
	Polynomial *t_poly = (Polynomial *)malloc(sizeof(Polynomial));
	t_poly->first = NULL;
	t_poly->name = t_name;
	t_poly->size = 0;
	return t_poly;
}
Polynomial *poly_search(char str) {			//다항식을 찾아주는 함수
	for (int i = 0;i < n;i++)
		if (str == polys[i]->name)
			return polys[i];				//찾은다항식을 리턴
	return 0;
}
void insert_polynomial(Polynomial *p) {		//다항식을 다항식배열에 넣는함수

	for (int i = 0;i < n;i++) {
		if (polys[i]->name == p->name) {	//만약 넣고자하는 다항식이 이미 존재하는경우
			destroy_polynomial(polys[i]);	//기존 다항식을 free시키고 새로운 다항식을
			polys[i] = p;					//기존 다항식 위치에 삽입
			return;
		}
	}
	polys[n++] = p;							//만약 새로운 다항식일시 맨마지막칸에 삽입
}
void destroy_polynomial(Polynomial *p) {	//다항식을 지워주는 함수

	Term *t = p->first, *q;

	while (t != NULL) {				//그다항식의 각항들을 free시켜줌
		q = t;
		t = t->next;
		free(q);
	}
	free(p);
}