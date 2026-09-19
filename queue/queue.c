#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;
  int front;
  int rear;
  int size;
} Queue;

Queue *create_queue(int size) {
  Queue *q = (Queue *)malloc(sizeof(Queue));

  if (q == NULL) {
    printf("Allocation failed\n");
    exit(1);
  }

  q->data = (int *)malloc(size * sizeof(int));

  if (q->data == NULL) {
    printf("Allocation failed\n");
    free(q);

    exit(1);
  }

  q->front = q->rear = -1;
  q->size = size;

  return q;
}

void enqueue(Queue *q, int key) {
  if (q->rear == q->size - 1) {
    printf("Queue overflow\n");
    return;
  }

  if (q->front == -1)
    q->front = q->rear = 0;
  else
    ++q->rear;

  q->data[q->rear] = key;
}

void dequeue(Queue *q) {
  if (q->front == -1) {
    printf("Queue underflow\n");
    return;
  }

  printf("Deleted element : %d\n", q->data[q->front]);

  if (q->front == q->rear)
    q->front = q->rear = -1;
  else
    ++q->front;
}

void display(Queue *q) {
  if (q->front == -1) {
    printf("No element to display\n");
    return;
  }

  for (int i = q->front; i <= q->rear; ++i) 
    printf("%d ", q->data[i]);

  printf("\n");
}

int main() {
  int size, ch, temp;

  printf("Enter the size of the queue : ");
  scanf("%d", &size);

  if (size <= 0) {
    printf("Invalid size\n");
    return 0;
  }

  Queue *q = create_queue(size);

  do {
    printf("Enter your choice --\n"
           "1. ENQUEUE\n"
           "2. DEQUEUE\n"
           "3. Display\n"
           "4. Exit\n"
           "Enter your choice : ");
    scanf("%d", &ch);

    switch (ch) {
      case 1:
        printf("Enter the key to enqueue : ");
        scanf("%d", &temp);
        enqueue(q, temp);
        break;

      case 2:
        dequeue(q);
        break;

      case 3:
        printf("Elements of the queue :\n");
        display(q);
        break;

      case 4:
        break;

      default:
        printf("Invalid option\n");
        break;
    }
  }while (ch != 4);

  free(q->data);
  free(q);

  return 0;
}
