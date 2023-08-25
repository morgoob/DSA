//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include "Matrix.h"
#include "List.h"
// structs---------------------------------------------------------------------

// Private Entry type
// Encapsulates the column and value info corresponding to a matrix entry
typedef struct EntryObj* Entry;

typedef struct EntryObj{
  int column;
  double value;
} EntryObj;

typedef struct MatrixObj {
  int size;
  int nonZeros;
  List *arr;
} MatrixObj;


// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Returns reference to a new Entry object. Initializes column and value 
Entry newEntry(int column, double value){
  Entry E = malloc(sizeof(EntryObj));
  E->column = column;
  E->value = value;
  return E;
}

// freeEntry()
// Frees HEAP memory associated with *pE, sets *pE to NULL
void freeEntry(Entry* pE){
  free(*pE);
  *pE = NULL;
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
  Matrix M;
  M = malloc(sizeof(MatrixObj));
  M->size = n;
  M->nonZeros = 0;

  M->arr = malloc((M->size + 1)*sizeof(List));
  for (int i = 1; i <= M->size; i++){
    M->arr[i] = newList();
  }

  return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i <= (*pM)->size; i++){
      freeList(&((*pM)->arr[i]));
    }

    free((*pM)->arr);
    free(*pM);
    *pM = NULL;
  }
}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
  if(M == NULL){
    fprintf(stderr, "Matrix Error: Calling size() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
  if(M == NULL){
    fprintf(stderr, "Matrix Error: Calling NNZ() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->nonZeros;
}

// entryEquals()
// helper function for equals, checks if two EntryObjs are the same
bool entryEquals(Entry A, Entry B){
  return A->column == B->column && A->value == B->value;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
  if(A == NULL || B == NULL){
    fprintf(stderr, "Matrix Error: Calling equals() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
   }
  if(A->size != B->size) return 0;
  if(A->nonZeros != B->nonZeros) return 0;
  if(A->size == 0 && B->size == 0) return 1;
  
  for(int i = 1; i <= A->size; i++){
    if(length(A->arr[i]) > 0 && length(B->arr[i]) > 0){
      moveFront(A->arr[i]);
      moveFront(B->arr[i]);
      if(length(A->arr[i]) != length(B->arr[i])) return 0;
      while(index(A->arr[i]) >= 0){
	if(!entryEquals((Entry) get(A->arr[i]), (Entry) get(B->arr[i]))) return 0;
	moveNext(A->arr[i]);
	moveNext(B->arr[i]);
      }
    }
  }
  
  return 1;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
  if(M == NULL){
    fprintf(stderr, "Matrix Error: Calling makeZero() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if(M->nonZeros == 0) return;

  List arr_i;
  Entry entry;
  // walk thru each list, free each entry, then clear List
  for(int i = 1; i <= M->size; i++){
    arr_i = M->arr[i];
    if(length(arr_i) > 0){
      moveFront(arr_i);
      while(index(arr_i) >= 0){
	entry = (Entry) get(arr_i);
	freeEntry(&entry);
	moveNext(arr_i);
      }
    }
    clear(arr_i);
  }
  
  M->nonZeros = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// FOUR CASES:
// 1. ij entry == 0, x == 0 -> do NOTHING
// 2. ij entry == 0, x != 0, insert new node in sorted order
// 3. ij entry != 0, x == 0, delete ij node and entry
// 4. ij entry != 0, x != 0, overwrite ij node 
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
  if(M == NULL){
    fprintf(stderr, "Matrix Error: Calling changeEntry() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if(i < 1 || i > M->size){
    fprintf(stderr, "Matrix Error: Calling changeEntry() on row out of range\n");
    exit(EXIT_FAILURE);
  }
  if(j < 1 || j > M->size){
    fprintf(stderr, "Matrix Error: Calling changeEntry() on column out of range\n");
    exit(EXIT_FAILURE);
  }

  int column;
  Entry entry, newE;
  List arr_i = M->arr[i];
  
  if(length(arr_i) == 0 && x != 0){
    newE = newEntry(j, x);
    append(arr_i, newE);
    M->nonZeros++;
    return;
  }
  
  moveFront(arr_i);
  for(moveFront(arr_i); index(arr_i) >= 0; moveNext(arr_i)){
    entry = (Entry) get(arr_i);
    column = entry->column;
    if(j == column){
      // non-zero entry 
      if(x == 0) {
	// case 3
	freeEntry(&entry);
	delete(arr_i);
	M->nonZeros--;
	return;
      } else {
	// case 4
	newE = newEntry(j, x);
	set(arr_i, newE);
	freeEntry(&entry);
	return;
      }
    } else if (j < column){
      // zero entry
      // case 1
      if(x == 0) return;
      // case 2
      newE = newEntry(j, x);
      insertBefore(arr_i, newE);
      M->nonZeros++;
      return;
    }
  }
  if (x != 0){
    newE = newEntry(j, x);
    append(arr_i, newE);
    M->nonZeros++;
  }
}

// Matrix Arithmetic operations -----------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
  if(A == NULL){
    fprintf(stderr, "Matrix Error: Calling copy() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }

  Entry newE, entry;
  Matrix M = newMatrix(A->size);
  for(int i = 1; i <= A->size; i++){
    if(length(A->arr[i]) > 0) {
      moveFront(A->arr[i]);
      while(index(A->arr[i]) >= 0){
	entry = (Entry) get(A->arr[i]);
	newE = newEntry(entry->column, entry->value);
	append(M->arr[i], newE);
	M->nonZeros++;
	moveNext(A->arr[i]); 
      }
    }
  }
  return M;
}

// vectorDot()
// Computes vector dot product of the 2 matrix rows represented by Lists P & Q
// Private helper function for transpose() and product()
double vectorDot(List P, List Q){
  double sum = 0;
  Entry entryP, entryQ;
  
  moveFront(Q);
  moveFront(P);
  while(index(P) >= 0 && index(Q) >= 0){
    entryP = (Entry) get(P);
    entryQ = (Entry) get(Q);
    if(entryP->column < entryQ->column){
      moveNext(P);
    } else if(entryQ->column < entryP->column){
      moveNext(Q);
    } else {
      sum += entryP->value*entryQ->value;
      moveNext(P);
      moveNext(Q);
    }
  }
  return sum;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
  if(A == NULL){
    fprintf(stderr, "Matrix Error: Calling transpose() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  
  Matrix A_t = newMatrix(A->size);
  Entry entry;
  int col;
  double val;
  List arr_i;
  for(int i = 1; i <= A->size; i++){
    arr_i = A->arr[i];
    if(length(arr_i) > 0){
      moveFront(arr_i);
      while(index(arr_i) >= 0){
	entry = (Entry) get(arr_i);
	col = entry->column;
	val = entry->value;
	changeEntry(A_t, col, i, val);
	moveNext(arr_i);
      }
    }
  }
  return A_t;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
  if(A == NULL){
    fprintf(stderr, "Matrix Error: Calling scalarMult() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }

  List arr_i;
  Matrix xA = newMatrix(A->size);
  if(x == 0) return xA;
  Entry entry, newE;
  for(int i = 1; i <= A->size; i++){
    arr_i = A->arr[i];
    if(length(arr_i) > 0) {
      moveFront(arr_i);
      while(index(arr_i) >= 0){
	entry = (Entry) get(arr_i);
	newE = newEntry(entry->column, x*entry->value);
	append(xA->arr[i], newE);
	xA->nonZeros++;
	moveNext(arr_i);
      }
    }
  }
  return xA;
}

// addList()
// Helper function for sum and diff
void addList(List S, List P, List Q, bool add){
  Entry entryP, entryQ, newE;
  int sign = 1;
  double value;
  if(!add) sign = -1;

  moveFront(P);
  moveFront(Q);
  while(index(P) >= 0 && index(Q) >= 0){
    entryP = (Entry) get(P);
    entryQ = (Entry) get(Q);
    if(entryP->column < entryQ->column){
      newE = newEntry(entryP->column, entryP->value);
      append(S, newE);
      moveNext(P);
    } else if (entryQ->column < entryP->column){
      newE = newEntry(entryQ->column, (double) sign*entryQ->value);
      append(S, newE);
      moveNext(Q);
    } else {
      value = entryP->value + (double) sign*entryQ->value;
      if(value != 0){
	newE = newEntry(entryP->column, value);
	append(S, newE);
      }
      moveNext(P);
      moveNext(Q);
    }
  }
  while(index(P) >= 0){
    entryP = (Entry) get(P);
    newE = newEntry(entryP->column, entryP->value);
    append(S, newE);
    moveNext(P);
  }
  while(index(Q) >= 0){
    entryQ = (Entry) get(Q);
    newE = newEntry(entryQ->column, (double) sign*entryQ->value);
    append(S, newE);
    moveNext(Q);
  }
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
  if(A == NULL || B == NULL){
    fprintf(stderr, "Matrix Error: Calling sum() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size){
    fprintf(stderr, "Matrix Error: Calling sum() on two matrices that are not the same size\n");
    exit(EXIT_FAILURE);
  }

  if(equals(A, B)) {
    return scalarMult(2, A);
  }
  
  Matrix sum = newMatrix(A->size);
  for(int i = 1; i <= A->size; i++){
    addList(sum->arr[i], A->arr[i], B->arr[i], true);
    sum->nonZeros += length(sum->arr[i]);
  }

  return sum;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
  if(A == NULL || B == NULL){
    fprintf(stderr, "Matrix Error: Calling diff() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size){
    fprintf(stderr, "Matrix Error: Calling diff() on two matrices that are not the same size\n");
    exit(EXIT_FAILURE);
  }

  if(equals(A, B)) return scalarMult(0, A);
  Matrix diff = newMatrix(A->size);
  for(int i = 1; i <= A->size; i++){
    addList(diff->arr[i], A->arr[i], B->arr[i], false);
    diff->nonZeros += length(diff->arr[i]);
  }

  return diff;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
  if(A == NULL || B == NULL){
    fprintf(stderr, "Matrix Error: Calling product() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size){
    fprintf(stderr, "Matrix Error: Calling product() on two matrices that are not the same size\n");
    exit(EXIT_FAILURE);
  }

  Matrix prod = newMatrix(A->size);
  Matrix B_t = transpose(B);
  
  for(int i = 1; i <= A->size; i++){
    for(int j = 1; j <= A->size; j++){
      changeEntry(prod, i, j, vectorDot(A->arr[i], B_t->arr[j]));
    } 
  }
  
  freeMatrix(&B_t);
  return prod;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
  if(M == NULL){
    fprintf(stderr, "Matrix Error: Calling printMatrix() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if(M->size == 0) return;

  Entry entry;
  List arr_i;
  for (int i = 1; i <= M->size; i++){
    arr_i = M->arr[i];
    if(length(arr_i) > 0){
      fprintf(out, "%d:", i);
      moveFront(arr_i);
      while(index(arr_i) >= 0){
	entry = (Entry) get(arr_i);
	fprintf(out, " (%d, %0.1f)", entry->column, entry->value);
	moveNext(arr_i);
      }
      fprintf(out, "\n");
    }
  }
}

