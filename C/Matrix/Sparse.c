//-----------------------------------------------------------------------------
// Sparse.c
// Client module for Matrix ADT
// Usage: ./Sparse <input file> <output file>
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include"Matrix.h"

#define MAX_LEN 300
#define ARR_COLUMN 3

// matrix_ops()
// Reads input file, assembles new Matrix
// Input file Format:
// First Line: three integers n, a, b, separated by spaces
// n: Matrix size, a, b: # of non-zero entries in Matrix A, B, respectively
// Second lind: blank
// subsequent lines: e lines will contain a space separated list of three
// numbers: two integers and a double, giving the row, column, and value of the
// corresponding matrix entry. Matrices A and B are separated by blank line
// Performs matrix athrithmetic operations as specified in pa write up. PRints
// to output file.
// A, B, (1.5)A, A + B, A + A, B - A, A - A, A_t, AB, B*B
void matrix_ops(FILE*, FILE*);

int main(int argc, char* argv[]){
  FILE *in, *out;
  
  if (argc != 3){
    fprintf(stderr, "Sparse Error in main(): Incorrect number of command line arguments\nUsage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  in = fopen(argv[1], "r");
  if (in == NULL){
    fprintf(stderr, "Sparse Error in main(): Unable to open %s for reading\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  out = fopen(argv[2], "w");
  if (out == NULL){
    fprintf(stderr, "Sparse Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  matrix_ops(in, out);
  
  fclose(in);
  fclose(out);
}

// read_file()
// Reads input file, assembles new Matrix
// Input file Format:
// First Line: three integers n, a, b, separated by spaces
// n: Matrix size, a, b: # of non-zero entries in Matrix A, B, respectively
// Second lind: blank
// subsequent lines: e lines will contain a space separated list of three
// numbers: two integers and a double, giving the row, column, and value of the
// corresponding matrix entry. Matrices A and B are separated by blank line
void matrix_ops(FILE* in, FILE* out){
  int line_count, row_index, col_index, n, row, column;
  double toki, value;
  double **arr;
  char line[MAX_LEN];
  char *token, *garbage;
  bool zeros, breakPoint;

  line_count = 0;
   while(fgets(line, MAX_LEN, in) != NULL){
    line_count++;
  }
  
  arr = (double**)malloc(line_count*sizeof(double*));
  for(int i = 0; i < line_count; i++){
    arr[i] = (double*)malloc(ARR_COLUMN*sizeof(double));
  }
  
  rewind(in);
  row_index = col_index = 0;

  while(row_index < line_count && fgets(line, MAX_LEN, in) != NULL){
    token = strtok(line, " \n");
    if(row_index == 0){
      n = atoi(token);
    }
    
    if(token == NULL){
      arr[row_index][0] = 0;
      arr[row_index][1] = 0;
      arr[row_index][2] = 0; 
    }
    while(token != NULL && col_index < ARR_COLUMN){
      toki = strtod(token, &garbage);
      arr[row_index][col_index] = toki;
      token = strtok(NULL, " ");
      col_index++;
    }
    row_index++;
    col_index = 0;
  }

  if(n == 0) exit(EXIT_SUCCESS);
  
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  breakPoint = false;
  zeros = false;
  
  for(int i = 2; i < line_count; i++){
    row = (int) arr[i][0];
    column = (int) arr[i][1];
    value = arr[i][2];
    zeros = row == 0 && column == 0 && value == 0;
    
    if(zeros && !breakPoint){
      breakPoint = true;
    } 
    
    if(!breakPoint && !zeros){
      changeEntry(A, row, column, value);
    } else if (breakPoint && !zeros){
      changeEntry(B, row, column, value);
    }
  }

  // A
  fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(out, A);
  fprintf(out, "\n");
  
  // B
  fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(out, B);
  fprintf(out, "\n"); 
  
  // (1.5)A
  fprintf(out, "(1.5)*A =\n");
  Matrix xA = scalarMult(1.5, A);
  printMatrix(out, xA);
  fprintf(out, "\n");

  // A + B
  fprintf(out, "A+B =\n");
  Matrix AplusB = sum(A, B);
  printMatrix(out, AplusB);
  fprintf(out, "\n");

  // A + A
  fprintf(out, "A+A =\n");
  Matrix AplusA = sum(A, A);
  printMatrix(out, AplusA);
  fprintf(out, "\n");
  
  // B - A
  fprintf(out, "B-A =\n");
  Matrix BminusA = diff(B, A);
  printMatrix(out, BminusA);
  fprintf(out, "\n");

  // A - A
  fprintf(out, "A-A =\n");
  Matrix AminusA = diff(A, A);
  printMatrix(out, AminusA);
  fprintf(out, "\n");

  
  // A_t
  fprintf(out, "Transpose(A) =\n");
  Matrix A_t = transpose(A);
  printMatrix(out, A_t);
  fprintf(out, "\n");

  // AB
  fprintf(out, "A*B =\n");
  Matrix AB = product(A, B);
  printMatrix(out, AB);
  fprintf(out, "\n");

  // B*B
  fprintf(out, "B*B =\n");
  Matrix BB = product(B, B);
  printMatrix(out, BB);
  fprintf(out, "\n");
  
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&xA);
  freeMatrix(&AplusB);
  freeMatrix(&AplusA);
  freeMatrix(&BminusA);
  freeMatrix(&AminusA);
  freeMatrix(&A_t);
  freeMatrix(&AB);
  freeMatrix(&BB);

  for(int i = 0; i < line_count; i++){
    free(arr[i]);
  }
  free(arr);
}
