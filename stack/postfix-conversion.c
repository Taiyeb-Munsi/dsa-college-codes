// Standard implementation of conversion of infix expression to postfix

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Stack

typedef struct {
  char *data;
  int top;
  int size;
} Stack;

Stack *create_stack(int size) {
  Stack *s = (Stack *)malloc(sizeof(Stack));

  if (s == NULL) {
    printf("Allocation failed\n");
    exit(1);
  }

  s->data = (char *)malloc(size * sizeof(char));

  if (s->data == NULL) {
    printf("Allocation failed\n");
    free(s);
    exit(1);
  }

  s->top = -1;
  s->size = size;

  return s;
}

void push(Stack *s, char key) { s->data[++s->top] = key; }

int pop(Stack *s) { return s->data[s->top--]; }

int peek(Stack *s) { return s->data[s->top]; }

// Utility

int precedence(char c) {
  if (c == '^') {
    return 3;
  } else if (c == '*' || c == '/') {
    return 2;
  } else if (c == '+' || c == '-') {
    return 1;
  } else {
    return 0;
  }
}

// Transformation

char *postfix(char *infix) {
  int size = 0;

  while (infix[size] != '\0') {
    ++size;
  }

  if (size <= 2) {
    return NULL;
  }

  char *result = (char *)malloc(
      (size + 1) *
      sizeof(char)); // +1 for the '\0' terminator, which is not counted in size
  Stack *s = create_stack(size);

  int k = 0;

  for (int i = 0; infix[i] != '\0'; ++i) {
    char c = infix[i];

    if (isspace(c)) {
      continue;
    } else if (isalnum(c)) {
      result[k++] = c;
    } else if (c == '(') {
      push(s, c);
    } else if (c == ')') {
      while (peek(s) != '(') {
        result[k++] = pop(s);
      }

      pop(s); // pop the '('
    } else {
      while (s->top != -1 &&
             (precedence(peek(s)) > precedence(c) ||
              (precedence(c) == precedence(peek(s)) && c != '^'))) {
        result[k++] = pop(s);
      }

      push(s, c);
    }
  }

  while (s->top != -1) {
    result[k++] = pop(s);
  } // add the rest of the operators in stack

  free(s->data);
  free(s);

  result[k] = '\0';

  return result;
}

int main() {
  char infix[256];

  printf("Enter infix expression: ");
  scanf("%255[^\n]", infix);

  char *result = postfix(infix);

  if (result == NULL) {
    printf("Invalid input\n");
    return 1;
  }

  printf("Result : %s\n", result);
  free(result);

  return 0;
}
