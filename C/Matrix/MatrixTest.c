//-----------------------------------------------------------------------------
//  MatrixTest.c 
//  A test client for the Matrix ADT
//  by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

#define ARR_SIZE 5

// Matrix Test Functions-------------------------------------------------------
// <function name>_test()
// Functions test edge cases of each function with different sized Matrix
// objects
void Matrix_test(FILE*);
bool size_test();
bool NNZ_test();
bool equals_test();
bool makeZero_test();
bool changeEntry_test();
bool copy_test();
bool transpose_test();
bool scalarMult_test();
bool sum_test();
bool diff_test();
bool product_test();

int main(int argc, char* argv[]){
  FILE *out;

  out = fopen("output.txt", "w");
  if (out == NULL){
    fprintf(stderr, "MatrixTest Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }
 
  fprintf(stdout, "**********Matrix ADT Test**********\n");
  fprintf(stdout, "Test results will be redirected to: \"output.txt\"\n");

  Matrix_test(out);
  
  fclose(out);
 
}

void Matrix_test(FILE* out){
  int n_arr[ARR_SIZE] = {0, 1, 10, 100, 1000};
  int n;
  
  fprintf(out, "**********Matrix ADT Test**********\n");

  fprintf(out, "**********size_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(size_test(n)){
      fprintf(out, "size_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "size_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  fprintf(out, "**********NNZ_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(NNZ_test(n)){
      fprintf(out, "NNZ_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "NNZ_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  fprintf(out, "**********equals_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(equals_test(n)){
      fprintf(out, "equals_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "equals_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  
  fprintf(out, "**********makeZero_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(makeZero_test(n)){
      fprintf(out, "makeZero_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "makeZero_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  
  fprintf(out, "**********changeEntry_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(changeEntry_test(n)){
      fprintf(out, "changeEntry_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "changeEntry_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  fprintf(out, "**********copy_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(copy_test(n)){
      fprintf(out, "copy_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "copy_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");
  
  fprintf(out, "**********transpose_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(transpose_test(n)){
      fprintf(out, "transpose_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "transpose_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");
    
  fprintf(out, "**********scalarMult_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(scalarMult_test(n)){
      fprintf(out, "scalarMult_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "scalarMult_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");
  
  fprintf(out, "**********sum_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(sum_test(n)){
      fprintf(out, "sum_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "sum_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");

  fprintf(out, "**********diff_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(diff_test(n)){
      fprintf(out, "diff_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "diff_test() with n = %d: FAILED\n", n);
    }
  }
  fprintf(out, "\n");
  
  fprintf(out, "**********product_test()**********\n");
  for(int i = 0; i < ARR_SIZE; i++){
    n = n_arr[i];
    if(product_test(n)){
      fprintf(out, "product_test() with n = %d: PASSED\n", n);
    } else {
      fprintf(out, "product_test() with n = %d: FAILED\n", n);
    }
  }
}

bool size_test(int n){
  Matrix Mn = newMatrix(n);
  
  if(size(Mn) != n) {
    freeMatrix(&Mn);
    return false;
  }
  
  makeZero(Mn);
  if(size(Mn) != n) {
    freeMatrix(&Mn);
    return false;
  }
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) i);
    if(size(Mn) != n) {
      freeMatrix(&Mn);
      return false;
    }
  }

  freeMatrix(&Mn);
  return true;
}

bool NNZ_test(int n){
  Matrix Mn = newMatrix(n);
  
  if(n != 0){
    for(int i = 1; i <= n; i++){
      changeEntry(Mn, i, i, (double) i);
      if(NNZ(Mn) != i) {
	freeMatrix(&Mn);
	return false;
      }
    }    
    if(NNZ(Mn) != n) {
      freeMatrix(&Mn);
      return false;
    }
    Matrix Mn_ = scalarMult(1.0, Mn);
    if(NNZ(Mn_) != n) {
      freeMatrix(&Mn_);
      freeMatrix(&Mn);
      return false;
    }
    freeMatrix(&Mn_);
  }
  
  Matrix Mn__ = scalarMult(0, Mn);
  if(NNZ(Mn__) != 0) {
    freeMatrix(&Mn);
    freeMatrix(&Mn__);
    return false;
  }
  
  /* makeZero(Mn); */
  /* if(NNZ(Mn) != 0) return false; */

  freeMatrix(&Mn__);
  freeMatrix(&Mn);
  return true;
}

bool equals_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);

  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) i);
    changeEntry(Mn_, i, i, (double) i);
    if(!equals(Mn, Mn_)) {
      freeMatrix(&Mn);
      freeMatrix(&Mn_);
      return false;
    }
  }

  makeZero(Mn);
  makeZero(Mn_);
  if(!equals(Mn, Mn_)) {
    freeMatrix(&Mn);
    freeMatrix(&Mn_);
    return false;
  }
  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
}

bool makeZero_test(int n){
  Matrix Mn = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) i); 
  }
  
  makeZero(Mn);
  if(NNZ(Mn) != 0) {
    freeMatrix(&Mn);
    return false;
  }
  freeMatrix(&Mn);
  return true;
}

bool changeEntry_test(int n){
  Matrix Mn = newMatrix(n);
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }
  if(NNZ(Mn) != 0){
    freeMatrix(&Mn);
    return false;
  }

  if(n !=  0) {
    for(int i = 1; i < n; i++){
      changeEntry(Mn, i, i, (double) i); 
    }
    if(NNZ(Mn) != n-1){
      freeMatrix(&Mn);
      return false;
    }
  }
  freeMatrix(&Mn);
  return true;
}

bool copy_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
}

bool transpose_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
 
}

bool scalarMult_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
 
}

bool sum_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
 
}

bool diff_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
 
}

bool product_test(int n){
  Matrix Mn = newMatrix(n);
  Matrix Mn_ = newMatrix(n);
  
  for(int i = 1; i < n; i++){
    changeEntry(Mn, i, i, (double) 0); 
  }

  freeMatrix(&Mn);
  freeMatrix(&Mn_);
  return true;
}
