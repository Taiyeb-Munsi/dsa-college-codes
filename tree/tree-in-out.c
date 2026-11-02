// Standard implementation of input and output binary tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left;
	struct Node *right;
} Node;

Node *createNode(int data) {
	Node *temp = (Node *)malloc(sizeof(Node));
	
	temp->data = data;
	temp->left = temp->right = NULL;
	
	return temp;
}

Node *inputTree() {
	char ch;
	int temp;
	
	printf("Enter the value : ");
	scanf("%d", &temp);
	
	Node *root = createNode(temp);
	
	printf("Insert left : ");
	scanf(" %c", &ch);
	
	if (ch == 'y' || ch == 'Y') root->left = inputTree();
	
	printf("Insert right : ");
	scanf(" %c", &ch);
	
	if (ch == 'y' || ch == 'Y') root->right = inputTree();
	
	return root;
}

void display(Node *root, int space) {
	if (root == NULL) return;
	
	space += 5;
	
	display(root->right, space);
	printf("\n");
	for (int i = 5; i <= space; ++i) printf(" ");
	printf("%d\n", root->data);
	display(root->left, space);
}

void printTree(Node *root) {
	display(root, 0);
}

void inorder(Node *root) {
    if (root == NULL) return;
    
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL) return;
    
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root) {
    if (root == NULL) return;
    
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
	Node *root;
	
	root = inputTree();

	printf("\nTree Structure:\n");	
	printTree(root);

	printf("\nPreorder : ");
    preorder(root);
    
    printf("\nInorder : ");
    inorder(root);
    
    printf("\nPostorder : ");
    postorder(root);
    
    printf("\n");
	
	return 0;
}
