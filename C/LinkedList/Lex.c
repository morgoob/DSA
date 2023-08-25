//-----------------------------------------------------------------------------
// Lex.c
// Client module for List ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){
  int line_count;
  FILE *in, *out;
  char line[MAX_LEN];
  List L = newList();
  bool check;
  
  if (argc != 3){
    fprintf(stderr, "Lex Error in main(): Incorrect number of command line arguments\nUsage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  in = fopen(argv[1], "r");
  if (in == NULL){
    fprintf(stderr, "Lex Error in main(): Unable to open %s for reading\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  out = fopen(argv[2], "w");
  if (out == NULL){
    fprintf(stderr, "Lex Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  line_count = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    line_count++;
  }
  
  char** arr = malloc(line_count*sizeof(char*));
  rewind(in);
  check = 1; // check is false when current line index has been added to list 
  int j = 0; // inner loop counter
  
  for(int i = 0; i < line_count; i++){
    fgets(line, MAX_LEN, in);
    arr[i] = calloc(strlen(line) + 1, sizeof(char));
    memcpy(arr[i], line, strlen(line)+1);
    printf(line);
    if (i == 0){
      append(L, i);
      check = 0;
    }
    
    moveFront(L);
    while(check && j < length(L)){ 
      if(strcmp(arr[get(L)], line) > 0){
	insertBefore(L, i);
	movePrev(L);
	check = 0;
      } else if(j == length(L)-1){
      	append(L, i);
      	check = 0;
      }
   
      j++;
      moveNext(L);
    }
    j = 0;
    check = 1;
  }
  moveFront(L);
  while(index(L) >= 0){
    fprintf(out, arr[get(L)]);
    moveNext(L);
  }
  
  for(int i = 0; i < line_count; i++){
    free(arr[i]);
  }

  free(arr);
  freeList(&L);
  fclose(in);
  fclose(out);
}
