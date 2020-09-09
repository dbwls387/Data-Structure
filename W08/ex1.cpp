#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"stackADT.h"

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 30
#define CAPACITY 50

struct node {
	Item *data;
	struct node *next;
};
struct stack_type {
	struct node *top;
	char *name;
};
stack_type *Stacks[CAPACITY];
int n = 0;

Stack search(char *name);
void list(Stack s);

int main(void) {
	char buffer[BUFFER_LENGTH];
	char *command;
	char *arg1, *arg2;

	while (1) {
		printf("$ ");
		fgets(buffer, BUFFER_LENGTH, stdin);
		buffer[strlen(buffer) - 1] = '\0';
		command = strtok(buffer, " ");

		if (strcmp(command, "create") == 0) {
			arg1 = strtok(NULL, " ");
			create(arg1);
		}
		else if (strcmp(command, "list") == 0) {
			arg1 = strtok(NULL, " ");
			list(search(arg1));
		}
		else if (strcmp(command, "push") == 0) {
			arg1 = strtok(NULL, " ");
			arg2 = strtok(NULL, " ");
			push(search(arg1), arg2);
		}
		else if (strcmp(command, "pop") == 0) {
			arg1 = strtok(NULL, " ");
			printf("%s", pop(search(arg1)));
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
	return 0;
}
Stack create(char *s_name) {
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	s->top = NULL;
	s->name = strdup(s_name);
	Stacks[n++] = s;
	return s;
}
Stack search(char *name) {
	int i = 0;
	for (i = 0; i < n; i++) {
		if (strcmp(name, Stacks[i]->name) == 0)
			return Stacks[i];
	}
	return 0;
}
void destroy(Stack s) {
	make_empty(s);
	free(s);
}
void make_empty(Stack s) {

	while (!is_empty(s))
		pop(s);
}
void push(Stack s, Item *i) {
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	if (new_node == NULL) {
		return;
	}
	new_node->data = strdup(i);
	new_node->next = s->top;
	s->top = new_node;
}
int is_empty(Stack s) {
	if (s->top == NULL)
		return 0;
	else
		return 1;
}
Item* pop(Stack s) {
	struct node *old_top;
	Item *i;

	old_top = s->top;
	i = old_top->data;
	s->top = old_top->next;
	free(old_top);
	return i;
}
Item *peek(Stack s) {
	return s->top->data;
}
void list(Stack s) {

	Stack p = search(s->name);
	struct node *q = s->top;
	if (q == NULL) {
		return;
	}
	while (q != NULL) {
		printf("%s\n", q->data);
		q = q->next;
	}
}