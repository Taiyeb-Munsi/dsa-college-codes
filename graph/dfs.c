#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *data;
	int size;
	int top;
} Stack;

int **createMatrix(int rowN, int colN) {
    int **res = (int **)malloc(rowN * sizeof(int *));
    
    for (int i = 0; i < rowN; ++i) res[i] = (int *)malloc(colN * sizeof(int));

    return res;
}

Stack *createStack(int size) {
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    
    temp->data = (int *)malloc(size * sizeof(int));
    temp->size = size;
    temp->top = -1;
    
    return temp;
}

void push(Stack *s, int key) {
	if (s->top != s->size - 1) s->data[++(s->top)] = key;
}

int pop(Stack *s) {
	if (s->top != -1) return s->data[(s->top)--];
}

int peek(Stack *s) {
	if (s->top != -1) return s->data[s->top];
}

int search(int *arr, int key, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) return 1;
    }
    
    return 0;
}

void dfs(int **g) {
    int vN = g[0][0], eN = g[0][1];
    Stack *s = createStack(eN + 1);
    int *visited = (int *)malloc(vN + 1 * sizeof(int));

    push(s, g[1][0]);
    while (s->top != -1) {
        int v = pop(s);
        if (visited[v]) continue;
        visited[v] = 1;
        printf("%d ", v);

        for (int i = eN; i >= 1; --i)
            if (g[i][0] == v && !visited[g[i][1]])
                push(s, g[i][1]);
    }
    
    free(visited);
    free(s->data);
    free(s);
}

int main() {
    int eN, vN;
    
    printf("Enter the number of vertices and edges : ");
    scanf("%d %d", &vN, &eN);
    
    int **edgeList = createMatrix(eN + 1, 2);
    
    edgeList[0][0] = vN;
    edgeList[0][1] = eN;
    
    printf("Enter the edges : \n");
	for (int i = 1; i <= eN; ++i) scanf("%d %d", &edgeList[i][0], &edgeList[i][1]);
    
    printf("DFS Traversal : ");
    dfs(edgeList);
    
    printf("\n");
    return 0;
}
