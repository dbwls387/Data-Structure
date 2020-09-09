#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
	int num;
	struct node* next;
};

typedef struct node Node;
Node* head = NULL;
int cnum;

void add(int num1, int num2);
void find(int num1);
void count(int num1);
void delete_value(int num1);
void list(void);

int main(void) {
	char buffer[10];
	char* token1, *token2, *token3;
	while (1) {
		printf("$ ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strlen(buffer) - 1] = '\0';
		token1 = strtok(buffer, " ");
		token2 = strtok(NULL, " ");
		token3 = strtok(NULL, "\0");
		if (!strcmp(token1, "add"))
			add(atoi(token2), atoi(token3));
		else if (!strcmp(token1, "find"))
			find(atoi(token2));
		else if (!strcmp(token1, "list"))
			list();
		else if (!strcmp(token1, "count"))
			count(atoi(token2));
		else if (!strcmp(token1, "delete"))
			delete_value(atoi(token2));
		else if (!strcmp(token1, "exit"))
			break;
	}
}

void add(int num1, int num2) {  //num1이 index,num2가 value
	Node* p, *q;
	int i = 0;
	if (num1 > cnum) {
		printf("invalid index\n");
		return;
	}
	if (cnum == 0) {
		head = (Node*)malloc(sizeof(Node));
		if (head == NULL)return;
		head->num = num2;
		head->next = NULL;
		cnum++;
	}
	else {
		if (num1 == 0) {
			q = (Node*)malloc(sizeof(Node));
			if (q == NULL)return;
			q->num = num2;
			q->next = head;
			head = q;
			cnum++;
		}
		else if (cnum > num1) {
			p = head;
			for (i = 0; i < num1 - 1; i++)
				p = p->next;
			q = (Node*)malloc(sizeof(Node));
			if (q == NULL)return;
			q->num = num2;
			q->next = p->next;
			p->next = q;
			cnum++;
		}
		else if (cnum == num1) {
			p = head;
			q = (Node*)malloc(sizeof(Node));
			if (q == NULL)return;
			while (p->next != NULL)
				p = p->next;
			q->num = num2;
			q->next = NULL;
			p->next = q;
			cnum++;
		}
	}
}

void find(int num1) {
	Node* p = head;
	int i = 0;
	int n = 0;
	int id = -1;
	while (p != NULL) {
		if (p->num == num1)
		{
			n++;
			break;
		}
		p = p->next;
		i++;
	}
	if (n != 0)
		printf("%d\n", i);
	else
		printf("%d\n", id);
}

void count(int num1) {
	Node* p = head;
	int i = 0;
	while (p != NULL)
	{
		if (p->num == num1)
			i++;
		p = p->next;
	}
	printf("%d\n", i);
}

void delete_value(int num1) {
	Node* p = head;
	Node* q = NULL;
	int n = 0;
	while (p != NULL){
		if (p->num == num1){
			if (q == NULL){
				head = p->next;
				free(p);
				n++;
				break;
			}
			else{
				q->next = p->next;
				free(p);
				n++;
				break;
			}
		}
		q = p;
		p = p->next;
	}
	if (n == 0)
		printf("not exist\n");
}

void list(void){
	Node* p;
	p = head;
	while (p != NULL){
		printf("%d ", p->num);
		p = p->next;
	}
	printf("\n");
}