
// Standard implementation of sparse to non-sparse triplet conversion

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int **data;
  int row;
  int col;
} Matrix;

Matrix *create_matrix(int row, int col) {
  Matrix *temp = (Matrix *)malloc(sizeof(Matrix));

  temp->data = (int **)malloc(row * sizeof(int *));

  for (int i = 0; i < row; ++i) { temp->data[i] = (int *)malloc(col * sizeof(int)); }

  temp->row = row;
  temp->col = col;

  return temp;
}

void free_matrix(Matrix *m) {
  for (int i = 0; i < m->row; ++i) { free(m->data[i]); }
  free(m->data);
  free(m);
}

void print_matrix(Matrix *m) {
  for (int i = 0; i < m->row; ++i) {
    for (int j = 0; j < m->col; ++j) { printf("%4d ", m->data[i][j]); }
    printf("\n");
  }
}

Matrix *non_sparse(Matrix *sparse) {
  int non_zero = 0;
  
  for (int i = 0; i < sparse->row; ++i) {
    for (int j = 0; j < sparse->col; ++j) {
      if (sparse->data[i][j] != 0) { ++non_zero; }
    }
  }

  Matrix *res = create_matrix(non_zero + 1, 3);

  res->data[0][0] = sparse->row;
  res->data[0][1] = sparse->col;
  res->data[0][2] = non_zero;

  int k = 1; // Result row iterator

  for (int i = 0; i < sparse->row; ++i) {
    for (int j = 0; j < sparse->col; ++j) {
      if (sparse->data[i][j] != 0) {
        res->data[k][0] = i;
        res->data[k][1] = j;
        res->data[k][2] = sparse->data[i][j];
        ++k;
      }
    }
  }

  return res;
}

int main() {
  int row, col;
  printf("Enter the row and column of the matrix : ");
  scanf("%d %d",  &row, &col);

  if (row <= 0 || col <= 0) {
    printf("Invalid dimensions\n");
    return 1;
  }

  Matrix *sparse = create_matrix(row, col);

  printf("Enter the elements of the matrix (%d x %d):\n", row, col);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) { scanf("%d", &sparse->data[i][j]); }
  }

  Matrix *res = non_sparse(sparse);

  printf("\nTriplet representation (row, col, value):\n");
  print_matrix(res);

  free_matrix(sparse);
  free_matrix(res);
  return 0;
}
