//-----------------------------------------------------------------------------
//  ListTest.c 
//  A test client for the List ADT
//  by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
  int num;
  char* name;
} EntryObj;

void List_test(FILE*);
Entry newEntry(int, char*);
void freeEntry(Entry*);
bool length_test(List, int);
bool index_test(List);
bool clear_test(List);

int main(int argc, char* argv[]){
  FILE *out;

  out = fopen("list_output.txt", "w");
  if (out == NULL){
    fprintf(stderr, "ListTest Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }
 
  fprintf(stdout, "**********List ADT Test**********\n");
  fprintf(stdout, "Test results will be redirected to: \"list_output.txt\"\n");

  List_test(out);
  
  fclose(out);
}

void List_test(FILE* out){
  List L = newList();
  
  fprintf(out, "**********List ADT Test**********\n");
  fprintf(out, "\n");
  
  fprintf(out, "**********Length Test**********\n");
  if(length_test(L, 0)){
    fprintf(out, "Length test: PASSED\n");
  } else {
    fprintf(out, "Length test: FAILED\n");
  }
  fprintf(out, "\n");
  
  fprintf(out, "**********Index Test**********\n");
  if(index_test(L)){
    fprintf(out, "Length test: PASSED\n");
  } else {
    fprintf(out, "Length test: FAILED\n");
  }
  fprintf(out, "\n");
  
  fprintf(out, "**********Clear Test**********\n");
  if(clear_test(L)){
    fprintf(out, "Length test: PASSED\n");
  } else {
    fprintf(out, "Length test: FAILED\n");
  }
  fprintf(out, "\n");
}

// newEntry()
// Returns reference to a new Entry object. Initializes column and value 
Entry newEntry(int num, char* name){
  Entry E = malloc(sizeof(EntryObj));
  E->num = num;
  E->name = name;
  return E;
}

// freeEntry()
// Frees HEAP memory associated with *pE, sets *pE to NULL
void freeEntry(Entry* pE){
  free(*pE);
  *pE = NULL;
}

bool length_test(List L , int expected){
  if(length(L) != expected) return false;
  return true;
}

bool index_test(List L){
  moveBack(L);
  moveNext(L);
  if(index(L) != -1) return false;

  moveFront(L);
  movePrev(L);
  if(index(L) != -1) return false;

  return true;
}

bool clear_test(List L){
  clear(L);
  if(length(L) != 0) return false;

  return true;
}

