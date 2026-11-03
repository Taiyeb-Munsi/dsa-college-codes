#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node **data;
    int top;
    int size;
} Stack;

Stack *createStack(int size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));

    if (s == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }

    s->data = (Node **)malloc(size * sizeof(Node *));

    if (s->data == NULL) {
        printf("Allocation failed\n");
        free(s);
        exit(1);
    }

    s->top = -1;
    s->size = size;

    return s;
}

void push(Stack *s, Node *key) { s->data[++s->top] = key; }

Node *pop(Stack *s) { return s->data[s->top--]; }

Node *peek(Stack *s) { return s->data[s->top]; }

Node *createNode(char data) {
    Node *temp = (Node *)malloc(sizeof(Node));
    
    temp->data = data;
    temp->left = temp->right = NULL;
    
    return temp;
}

void display(Node *root, int space) {
    if (root == NULL) return;
    
    space += 5;
    
    display(root->right, space);
    printf("\n");
    for (int i = 5; i <= space; ++i) printf(" ");
    printf("%c\n", root->data);
    display(root->left, space);
}

void printTree(Node *root) {
    display(root, 0);
}

void expTree(char *e) {
    Stack *s = createStack(100);
    
    for (int i = 0; e[i] != '\0'; ++i) {
        char c = e[i];
        
        if (isspace(c)) continue;
        
        if (isalnum(c)) {
            push(s, createNode(c));
        } else {
            Node *a = pop(s);
            Node *b = pop(s);
            
            Node *root = createNode(c);
            
            root->right = a;
            root->left = b;
            
            push(s, root);
        }
    }
    
    Node *res = peek(s);
    printTree(res);
}

void deleteTree(Node *root) {
    if (root == NULL) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    free(root);
}

int main() {
    char expression[100];

    printf("Enter the postfix expression : ");
    scanf("%99s", expression);
    
    printf("Expression tree : \n");
    expTree(expression);

	deleteTree(root);
    return 0;
}
