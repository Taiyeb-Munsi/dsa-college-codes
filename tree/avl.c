// Standard implementation of menu driven AVL Tree

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int height;
	struct Node *left;
	struct Node *right;
} Node;

Node *createNode(int data) {
	Node *temp = (Node *)malloc(sizeof(Node));
	
	temp->data = data;
	temp->left = temp->right = NULL;
	temp->height = 1;
	
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

int max(int a, int b) { return (a > b) ? a : b; }

int height(Node *root) {
	if (root == NULL) return 0;
	return root->height;
}

void deleteTree(Node *root) {
    if (root == NULL) return;
    
    deleteTree(root->left);
    deleteTree(root->right);
    
    free(root);
}

Node *rightRotate(Node *y) {
	Node *x = y->left;
	Node *z = x->right;
	
	x->right = y;
	y->left = z;
	
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	
	return x;
}

Node *leftRotate(Node *x) {
	Node *y = x->right;
	Node *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	
	return y;
}

int getBalance(Node *root) {
	if (root == NULL) return 0;
	return height(root->left) - height(root->right);
}

Node *insertNode(Node *root, int key) {
	if (root == NULL) return createNode(key);
	
	if (key < root->data)
		root->left = insertNode(root->left, key);
	else if (key > root->data)
		root->right = insertNode(root->right, key);
	else
		return root;
		
	root->height = max(height(root->left), height(root->right)) + 1;
		
	int balance = getBalance(root);
	
	if (balance > 1 && key < root->left->data) return rightRotate(root);
	
	if (balance < -1 && key > root->right->data) return leftRotate(root);
	
	if (balance > 1 && key > root->left->data) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	
	if (balance < -1 && key < root->right->data) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node *findMax(Node *node) {
    Node *current = node;
    while (current->right != NULL)
        current = current->right;
    return current;
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
    
    if (root == NULL) return root;
    
    root->height = max(height(root->left), height(root->right)) + 1;
    
    int balance = getBalance(root);
    
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root); 
       
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
        
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

int main() {
	int choice = 0, key;
	Node *root = NULL;
		
	while (choice != 4) {
		printf("Select operation :\n"
		   "1. Insert node\n"
		   "2. Delete node\n"
		   "3. Display tree\n"
		   "4. Exit\n");
		scanf("%d", &choice);   
		
		switch(choice) {
			case 1:
				printf("Enter the keys to insert : ");
				scanf("%d", &key);
				root = insertNode(root, key);
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
