// Standard implementation of polynomial operations using linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int coeff;
	int exp;
	struct Node *next;
} Node;

Node *create_node(int coeff, int exp) {
	Node *n = (Node *)malloc(sizeof(Node));
  	if (n == NULL) {
    	printf("Allocation failed\n");
    	exit(1);
  	}

  	n->coeff = coeff;
  	n->exp = exp;
  	n->next = NULL;

  	return n;
}

void insertE(Node **head, int coeff, int exp) {
	Node *temp = create_node(coeff, exp);

  	if (*head == NULL) {
    	temp->next = *head;
    	*head = temp;
    	return;
  	}

  	Node *ptr = *head; // Iterator node
  
  	while (ptr->next != NULL) { ptr = ptr->next; }

  	ptr->next = temp;
}


void deleteList(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

Node *inputPoly() {
	int degree, temp;
	Node *poly = NULL;
	
	printf("Enter the degree of the polynomial : ");
	scanf("%d", &degree);
	
	for (int i = degree; i >= 0; --i) {
		printf("Enter the coefficient of x^%d : ", i);
		scanf("%d", &temp);
		
		insertE(&poly, temp, i);
	}
	
	return poly;
}

void printPoly(Node *head) {
	int first = 1;
	
	for (Node *cur = head; cur != NULL; cur = cur->next) {
		int c = cur->coeff;
		
		if (c == 0) continue;
		
		if (first) {
			if (c < 0) printf("-");
		} else {
			printf(c < 0 ? "-" : "+");
		}
		
		if (c < 0) c = -c;
		
		if (c != 1 || cur->exp == 0) printf("%d", c);
		
		if (cur->exp == 1)
			printf("x");
		else if (cur->exp > 1)
			printf("x^%d", cur->exp);
			
		first = 0;
	}
	
	if (first) printf("0");

	printf("\n");
}

Node *addPoly(Node *p1, Node *p2) {
	Node *res = NULL;
	
	while (p1 != NULL && p2 != NULL) {
		if (p1->exp > p2->exp) {
			insertE(&res, p1->coeff, p1->exp);
			p1 = p1->next;
		} else if (p1->exp < p2->exp) {
			insertE(&res, p2->coeff, p2->exp);
			p2 = p2->next;
		} else {
			insertE(&res, (p1->coeff + p2->coeff), p1->exp);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	
	while (p1 != NULL) {
		insertE(&res, p1->coeff, p1->exp);
		p1 = p1->next;
	}
	
	while (p2 != NULL) {
		insertE(&res, p2->coeff, p2->exp);
		p2 = p2->next;
	}
	
	return res;
}

Node *multPoly(Node *p1, Node *p2) {
	Node *res = NULL;

    for (Node *a = p1; a != NULL; a = a->next) {
        for (Node *b = p2; b != NULL; b = b->next) {
            Node *temp = create_node(a->coeff * b->coeff, a->exp + b->exp);
            Node *merged = addPoly(res, temp);
            deleteList(res);
            deleteList(temp);
            res = merged;
		}
	}

    return res;
}

int main() {
	int choice;
	Node *p1 = inputPoly();
	Node *p2 = inputPoly();
	Node *res = NULL;

	printf("Select operation :\n"
		   "1. Add\n"
		   "2. Multiply\n"
		   "3. Exit\n");
	scanf("%d", &choice);
		   
	switch(choice) {
		case 1:
			res = addPoly(p1, p2);
			break;
		
		case 2:
			res = multPoly(p1, p2);
			break;
		
		case 3:
			break;
			
		default:
			printf("Invalid input\n");
			break;
	}
	
	printf("Resulting list :\n");
	printPoly(res);
	
	deleteList(p1);
	deleteList(p2);
	deleteList(res);
	return 0;
}

