#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *data;
	int size;
	int front;
	int rear;
} Queue;

int **createMatrix(int rowN, int colN) {
    int **res = (int **)malloc(rowN * sizeof(int *));
    
    for (int i = 0; i < rowN; ++i) res[i] = (int *)malloc(colN * sizeof(int));

    return res;
}

Queue *createQueue(int size) {
    Queue *temp = (Queue *)malloc(sizeof(Queue));
    
    temp->data = (int *)malloc(size * sizeof(int));
    temp->size = size;
    temp->front = -1;
    temp->rear = -1;
    
    return temp;
}

void enqueue(Queue *q, int key) {
	if (q->rear != q->size - 1) {
		if (q->front == -1) q->front = 0;
		q->data[++(q->rear)] = key;
	}
}

int dequeue(Queue *q) {
	if (q->front != -1 && q->front <= q->rear) return q->data[(q->front)++];
}

int front(Queue *q) {
	if (q->front != -1 && q->front <= q->rear) return q->data[q->front];
}

int search(int *arr, int key, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) return 1;
    }
    
    return 0;
}

void bfs(int **g) {
    int vN = g[0][0], eN = g[0][1];
    Queue *q = createQueue(vN + 1);
    int *visited = (int *)calloc(vN + 1, sizeof(int));

    enqueue(q, g[1][0]);
    visited[g[1][0]] = 1;
    while (q->front != -1 && q->front <= q->rear) {
        int v = dequeue(q);
        printf("%d ", v);

        for (int i = 1; i <= eN; ++i) {
            if (g[i][0] == v && !visited[g[i][1]]) {
                visited[g[i][1]] = 1;
                enqueue(q, g[i][1]);
            } else if (g[i][1] == v && !visited[g[i][0]]) {
                visited[g[i][0]] = 1;
                enqueue(q, g[i][0]);
            }
        }
    }
    
    free(visited);
    free(q->data);
    free(q);
}

int main() {
    int eN, vN;
    
    printf("Enter the number of vertices and edges : ");
    scanf("%d %d", &vN, &eN);
    
    int **edgeList = createMatrix(eN + 1, 2);
    
    edgeList[0][0] = vN;
    edgeList[0][1] = eN;
    
    printf("Enter the edges : \n");
	for (int i = 1; i <= eN; ++i) {
        scanf("%d %d", &edgeList[i][0], &edgeList[i][1]);
        
        while (edgeList[i][0] < 0 || edgeList[i][0] > vN || edgeList[i][1] < 0 || edgeList[i][1] > vN) {
            printf("Vertices must be between 0 and %d, re-enter the edge : \n", vN);
            scanf("%d %d", &edgeList[i][0], &edgeList[i][1]);
        }
    }
    
    printf("BFS Traversal : ");
    bfs(edgeList);
    
    printf("\n");
    return 0;
}
