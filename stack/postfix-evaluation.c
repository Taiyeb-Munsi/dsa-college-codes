// Standard implementation of postfix expression evaluation

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Stack

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

void push(Stack *s, int key) { s->data[++s->top] = key; }

int pop(Stack *s) { return s->data[s->top--]; }

// Utility

int calculate(int a, int b, char op) {
  switch (op) {
  case '+': return a + b;
  case '-': return a - b;
  case '*': return a * b;
  case '/': return a / b;
  case '^': return pow(a, b);
  default:
    printf("Invalid operator expression\n");
    exit(1);
  }
}

// Evaluation

int eval(char *postfix) {
  int size;
  for (size = 0; postfix[size] != '\0'; ++size);

  Stack *s = create_stack(size);

  for (int i = 0; postfix[i] != '\0'; ++i) {
    if (isspace(postfix[i])) {
      continue;
    } else if (isdigit(postfix[i])) {
      int temp = 0;
      while (isdigit(postfix[i])) { temp = 10 * temp + (postfix[i++] - '0'); } // Fixing for multiple digit numbers

      push(s, temp);
    } else {
      int a = pop(s);
      int b = pop(s);

      int r = calculate(b, a, postfix[i]);
      push(s, r);
    }
  }

  int result = s->data[s->top];

  return result;
}

int main() {
  char postfix[256];

  printf("Enter postfix expression: ");

  scanf("%255[^\n]", postfix);

  int result = eval(postfix);

  printf("Result : %d\n", result);
  return 0; 
}
