#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100

typedef struct { /* 하나의 단어와 그 단어의 빈도수를 저장하기 위한 구조체 */
	char *word;
	int freq;
} Item;

struct node { /* 연결리스트의 노드의 구조를 정의하는 구조체 */
	Item *data;
	struct node *next;
};
typedef struct node Node;

Node *insert(Node *, char buf[]);

int main() {
	char buf[MAXLEN];
	Node *head = NULL; /* head는 지역변수이다. */
	while (1) {
		scanf("%s", buf);
		if (strcmp(buf, "EOF") == 0) break; /* 문자열 “EOF”를 입력하면 종료 */
		head = insert(head, buf); /* 입력된 문자열을 연결리스트에 반영 */
	}

	Node *p = head;
	while (p != NULL) {
		printf("%s:%d\n", p->data->word, p->data->freq);
		p = p->next;
	}
	return 0;
}

Node *insert(Node *head, char buf[]) {
	/* 입력된 문자열을 연결리스트에 반영하고 head노드의 주소를 반환한다. 이미 존재하는.  */
	/* 문자열이면 카운트만 증가 하고, 아니라면 정렬된 순서로 연결리스트에 추가한다.  */

	Node *p = head;
	if (p == NULL) {	//노드에 처음 넣는 경우
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->data = (Item*)malloc(sizeof(Item) * 10);
		temp->data->word = strdup(buf);
		temp->data->freq = 1;
		temp->next = NULL;
		p = temp;
		return p;
	}

	while (p != NULL) {
		if (strcmp(p->data->word, buf) == 0) {	  //맨앞 노드의 빈도수 증가
			p->data->freq++;
			return head;
		}	
		p = p->next;
	}
	p = head;
	if (strcmp(p->data->word, buf) > 0) { //맨앞 노드 앞에 들어가야 할 경우
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->data = (Item*)malloc(sizeof(Item) * 10);
		temp->data->word = strdup(buf);
		temp->data->freq = 1;
		temp->next = p;
		p = temp;
		return p;
	}

	int ch = 0;
	p = head;
	Node *q = p->next;
	while (q != NULL) {
		if (strcmp(q->data->word, buf) > 0) {
			Node *temp = (Node*)malloc(sizeof(Node));
			temp->data = (Item*)malloc(sizeof(Item) * 10);
			temp->data->word = strdup(buf);
			temp->data->freq = 1;			
			temp->next = q;			
			p->next = temp;
			ch = 1;
			return head;
		}		
		if (strcmp(q->data->word, buf) == 0) {
			p->data->freq++;
			return head;
		}		
		p = p->next;
		q = q->next;
	}
	if (p != NULL && ch == 0) {
		Node *temp = (Node*)malloc(sizeof(Node));
		temp->data = (Item*)malloc(sizeof(Item) * 10);
		temp->data->word = strdup(buf);
		temp->data->freq = 1;
		temp->next = NULL;
		p->next = temp;
		return head;
	}
	return head;
}