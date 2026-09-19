// Standard implementation of menu driven singly linked list

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

void delete_list(Node *head) {
  while (head != NULL) {
    Node *next = head->next;
    free(head);
    head = next;
  }
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

void insertP(Node **head, int key, int pos) {
  if (*head == NULL || pos <= 0) { // For negative psoition insert at front
    insertF(head, key);
    return;
  }

  Node *temp = create_node(key);
  Node *ptr = *head; // Iterator node
  int p = 0; // Iterator integer
  
  while (ptr->next != NULL && p != pos - 1) { 
    ptr = ptr->next;
    ++p;
  }
  
  temp->next = ptr->next;
  ptr->next = temp;
}

void deleteF(Node **head) {
  if (*head == NULL) {
    printf("List is empty\n"); 
    return;
  }

  Node *temp = *head;
  *head = (*head)->next;
  printf("Deleted element : %d\n", temp->data);
  free(temp);
}

void deleteE(Node **head) {
  if (*head == NULL) {
    printf("List is empty\n");
    return;
  }

  if ((*head)->next == NULL) {
    printf("Deleted element : %d\n", (*head)->data);
    free(*head);
    *head = NULL;
    return;
  }

  Node *ptr = *head;

  while ((ptr->next)->next != NULL) { ptr = ptr->next; }

  Node *temp = ptr->next;
  ptr->next = NULL;
  printf("Deleted element : %d\n", temp->data);
  free(temp);
}

void deleteP(Node **head, int pos) {
  if (*head == NULL) {
    printf("List is empty\n");
    return;
  }

  if (pos < 0) {
    printf("Invalid position\n");
    return;
  }

  if (pos == 0) {
    deleteF(head);
    return;
  }

  Node *ptr = *head; // Iterator node
  int p = 0; // Iterator integer
  
  while (ptr->next != NULL && p != pos - 1) { 
    ptr = ptr->next;
    ++p;
  }

  Node *temp = ptr->next;
  if (temp == NULL) {
    printf("Invalid position\n");
    return;
  }

  ptr->next = temp->next;
  printf("Deleted element : %d\n", temp->data);
  free(temp);
}

void display(Node *head) {
  for (Node *ptr = head; ptr != NULL; ptr = ptr->next) { printf("%d ", ptr->data); }
  printf("\n");
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
