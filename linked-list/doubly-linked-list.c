// Standard implementation of menu driven linear doubly linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
	struct Node *prev;
} Node;

Node *createNode(int key) {
	Node *temp = (Node *)malloc(sizeof(Node));
	
	if (temp == NULL) {
	    printf("Allocation failed\n");
	    exit(1);
	}
	
	temp->data = key;
	temp->next = temp->prev = NULL;
	
	return temp;
}

void insertF(Node **head, int data) {
	Node *newNode = createNode(data);
	
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	
	(*head)->prev = newNode;
	newNode->next = *head;
	
	*head = newNode;
}

void insertE(Node **head, int data) {
	Node *newNode = createNode(data);
	
	if (*head == NULL) {
		*head = newNode;
		return;
	}
	
	Node *temp = *head;
	
	while (temp->next != NULL) temp = temp->next;
	
	temp->next = newNode;
	newNode->prev = temp;
}

void insertP(Node **head, int data, int pos) {
	if (*head == NULL || pos <= 0) {
		insertF(head, data);
		return;
	}

	Node *newNode =  createNode(data);
	
	
	Node *ptr = *head;
	int i = 0;
	
	while (ptr->next != NULL && i < pos - 1) {
		ptr = ptr->next;
		++i;
	}
	
	newNode->next = ptr->next;
	newNode->prev = ptr;
	
	if (newNode->next != NULL) (newNode->next)->prev = newNode;
	ptr->next = newNode;
}

void deleteF(Node **head) {
	if (*head == NULL) {
		printf("List empty\n");
		return;
	}
	
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		return;
	}
	
	Node *temp = *head;
	
	*head = (*head)->next;
	(*head)->prev = NULL;
	
	free(temp);
}

void deleteE(Node **head) {
	if (*head == NULL) {
		printf("List empty\n");
		return;
	}
	
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
		return;
	}
	
	Node *ptr = *head;
	
	while (ptr->next->next != NULL) ptr = ptr->next;
	
	free(ptr->next);
	ptr->next = NULL;
}

void deleteP(Node **head, int pos) {
	if (*head == NULL) {
		printf("List empty\n");
		return;
	}
	
	if (pos < 0) {
		printf("Invalid position\n");
		return;
	} else if (pos == 0) {
		deleteF(head);
		return;
	}
	
	Node *ptr = *head;
	int i = 0;
	
	while (ptr != NULL && i < pos) { //Going to the node to be deleted insteadd of previous one, idea given by Upasana
		ptr = ptr->next;
		++i;
	}
	
	if (ptr == NULL) {
		printf("Invalid position\n");
		return;
	}
	
	ptr->prev->next = ptr->next;
	if (ptr->next != NULL) ptr->next->prev = ptr->prev;
	free(ptr);
}

void display(Node *head) {
    if (head == NULL) {
    	printf("List empty\n"); 
    	return;
    }
    
    for (Node *t = head; t != NULL; t = t->next) printf("%d ", t->data);
    printf("\n");
}

void delete_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main() {
  int ch, key, pos;
  Node *head = NULL;

  do {
    printf("Enter your choice --\n"
           "1. Insert beginning\n"
           "2. Insert end\n"
           "3. Insert position\n"
           "4. Delete Begining\n"
           "5. Delete end\n"
           "6. Delete pos\n"
           "7. Display\n"
           "8. Exit\n"
           "Enter your choice : ");
    scanf("%d", &ch);

    switch (ch) {
      case 1:
        printf("Enter the key to insert front : ");
        scanf("%d", &key);
        insertF(&head, key);
        break;

      case 2:
        printf("Enter the key to insert end : ");
        scanf("%d", &key);
        insertE(&head, key);
        break;

      case 3:
        printf("Enter the key & position to insert at position : ");
        scanf("%d %d", &key, &pos);
        insertP(&head, key, pos);
        break;

      case 4:
        deleteF(&head);
        break;
      
      case 5:
        deleteE(&head);
        break;

      case 6:
        printf("Enter the position to delete at : ");
        scanf("%d", &pos);
        deleteP(&head, pos);
        break;

      case 7:
        display(head);
        break;

      case 8:
        break;

      default:
        printf("Invalid option\n");
        break;
    }
  }while (ch != 8);

  delete_list(head);

  return 0;
}
