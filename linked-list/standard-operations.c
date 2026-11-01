// Standard implementation of standard operations on linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node;

Node *create_node(int key) {
	Node *n = (Node *)malloc(sizeof(Node));
  	if (n == NULL) {
    	printf("Allocation failed\n");
    	exit(1);
  	}

  	n->data = key;
  	n->next = NULL;

  	return n;
}

void insertF(Node **head, int key) {
  	Node *temp = create_node(key);
  
 	temp->next = *head;
  	*head = temp;
}

void insertE(Node **head, int key) {
  	if (*head == NULL) {
    	insertF(head, key);
    	return;
  	}

  	Node *temp = create_node(key);
  	Node *ptr = *head; // Iterator node
  
  	while (ptr->next != NULL) { ptr = ptr->next; }

  	ptr->next = temp;
}

void display(Node *head) {
    if (head == NULL) {
    	printf("List empty\n"); 
    	return;
    }
    
    for (Node *t = head; t != NULL; t = t->next) printf("%d ", t->data);
    printf("\n");
}

void deleteList(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

void sort(Node **head) {
	for (Node *i = *head; i != NULL; i = i->next) {
		Node *min = i;
		
		for (Node *j = i; j != NULL; j = j->next) {
			if (j->data < min->data) min = j;
		}
		
		if (i != min) {
			int temp = i->data;
			i->data = min->data;
			min->data = temp;
		}
	}
}

void reverse(Node **head) {
	Node *res = NULL;
	
	for (Node *i = *head; i != NULL; i = i->next) insertF(&res, i->data);
	
	deleteList(*head);
	*head = res;
}

int main() {
	int choice;
	int temp;
	
	Node *head = NULL;
	
	printf("Enter the elements (enter d to exit) :\n");
	while(scanf("%d", &temp) == 1) insertE(&head, temp);
	while(getchar() != '\n');
	
	printf("Select operations :\n"
		   "1. Sort\n"
		   "2. Reverse\n"
		   "3. Exit\n");
	scanf("%d", &choice);
		   
	switch(choice) {
		case 1:
			sort(&head);
			break;
		
		case 2:
			reverse(&head);
			break;
		
		case 3:
			break;
			
		default:
			printf("Invalid input\n");
			break;
	}
	
	printf("Resulting list :\n");
	display(head);
	deleteList(head);
	
	return 0;
}

