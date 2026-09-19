// Standard implementation of menu driven stack

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *data;
  int top;
  int size;
} Stack;

Stack *create_stack(int size) {
  Stack *s = (Stack *)malloc(sizeof(Stack));

  if (s == NULL) {
    printf("Allocation failed\n");
    exit(1);
  }

  s->data = (int *)malloc(size * sizeof(int));

  if (s->data == NULL) {
    printf("Allocation failed\n");
    free(s);
    exit(1);
  }

  s->top = -1;
  s->size = size;

  return s;
}

void push(Stack *s, int key) {
  if (s->top == s->size - 1) {
    printf("Stack overflow\n");
    return;
  }

  s->data[++s->top] = key;
}

void pop(Stack *s) {
  if (s->top == -1) {
    printf("Stack underflow\n");
    return;
  }

  printf("Deleted element : %d\n", s->data[s->top--]);
}

void display(Stack *s) {
  if (s->top == -1) {
    printf("No elements to display\n");
    return;
  }

  for (int i = 0; i <= s->top; ++i)
    printf("%d ", s->data[i]);

  printf("\n");
}

int main() {
  int size, ch, key;
  printf("Enter the size of the stack : ");
  scanf("%d", &size);

  if (size <= 0) {
    printf("Invalid size\n");
    return 1;
  }

  Stack *s = create_stack(size);

  do {
    printf("Enter your choice :\n"
           "1. PUSH\n"
           "2. POP\n"
           "3. Display\n"
           "4. Exit\n"
           "Enter your choice : ");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
      printf("Enter the element to push : ");
      scanf("%d", &key);
      push(s, key);
      break;

    case 2:
      pop(s);
      break;

    case 3:
      printf("Elements in the stack :\n");
      display(s);
      break;

    case 4:
      break;

    default:
      printf("Invalid input\n");
      break;
    }

  } while (ch != 4);

  free(s->data);
  free(s);

  return 0;
}
