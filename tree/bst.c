// Standard implementation of menu driven Binary Search Tree

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

void display(Node *root, int space) {
    if (root == NULL) return;
    
    space += 5;
    
    display(root->right, space);
    printf("\n");
    for (int i = 5; i <= space; ++i) printf(" ");
    printf("%d\n", root->data);
    display(root->left, space);
}

void printTree(Node *root) { display(root, 0); }

Node* insertNode(Node *root, int key) {
    if (root == NULL) return createNode(key);

    if (key < root->data)
    	root->left = insertNode(root->left, key);
    else if (key > root->data)
    	root->right = insertNode(root->right, key);
    
    return root;
}

Node *findMax(Node *root) {
	if (root == NULL) return NULL;
	
	while (root->right != NULL) root = root->right;
	
	return root;  
}

Node *delNode(Node *root, int key) {
	if (root == NULL) return NULL;
	
	if (key < root->data)
    	root->left = delNode(root->left, key);
    else if (key > root->data)
    	root->right = delNode(root->right, key);
    else {
    	if (root->left != NULL && root->right != NULL) {
    		Node *temp = findMax(root->left);
    		root->data = temp->data;
    		root->left = delNode(root->left, temp->data);
    	} else {
    		Node *temp = root;
    		
    		if (root->left == NULL)
    			root = root->right;
    		else if (root->right == NULL)
    			root = root->left;
    		
    		free(temp);
    	}
    }
    
    return root;
}

void deleteTree(Node *root) {
    if (root == NULL) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    free(root);
}

int main() {
	int choice = 0, key;
	Node *root = NULL;
		
	while (choice != 4) {
		printf("Select operation :\n"
		   "1. Insert nodes\n"
		   "2. Delete node\n"
		   "3. Display tree\n"
		   "4. Exit\n");
		scanf("%d", &choice);   
		
		switch(choice) {
			case 1:
				printf("Enter the keys to insert : ");
				while (scanf("%d", &key) == 1) root = insertNode(root, key);
				while(getchar() != '\n');
				break;
			
			case 2:
				printf("Enter the keys to delete : ");
				scanf("%d", &key);
				root = delNode(root, key);
				if (root == NULL) {
					printf("Tree is empty\n");
				}
				break;
			
			case 3:
				printf("Tree :");
				printTree(root);
				break;
			
			case 4:
				break;
				
			default:
				printf("Invalid input\n");
				break;
		}
	}
	
	printf("\n");

	deleteTree(root);	
	return 0;
}
