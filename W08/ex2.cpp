#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_LENGTH 100

typedef struct node {
	int number;
	struct node *next;
}Node;

typedef struct stack {
	struct node *top = NULL;
	int tail_number;
}*Stack;

void is_operator(Stack s, char ch);
void push(Stack s);
void pop(Stack s);
Stack create();

int main(void) {
	int i = 0;
	char buffer[BUFFER_LENGTH];

	fgets(buffer, BUFFER_LENGTH, stdin);
	buffer[strlen(buffer) - 1] = '\0';
	Stack p = create();

	while (buffer[i] != '\0') {
		is_operator(p, buffer[i]);
		i++;
	}
	return 0;
}
void is_operator(Stack s, char ch) {
	if (ch == '(')
		push(s);
	else if (ch == ')')
		pop(s);
	else
		return;
}
void push(Stack s) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->next = s->top;
	s->top = new_node;

	s->tail_number++;
	new_node->number = s->tail_number;

	printf("%d ", s->tail_number);
}
void pop(Stack s) {
	Node *old_top;
	printf("%d ", s->top->number);

	old_top = s->top;
	s->top = s->top->next;

	free(old_top);

}
Stack create() {
	Stack s = (Stack)malloc(sizeof(struct stack));
	s->tail_number = 0;
	s->top = NULL;
	return s;
}