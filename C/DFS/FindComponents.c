//-----------------------------------------------------------------------------
// FindComponents.c
// Client module for Graph ADT
// Usage: ./FindComponents <input file> <output file>
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
#include"Graph.h"

#define MAX_LEN 300
#define ARR_COLUMN 2

// read_file()
// Reads input file, assembles new Graph using newGraph() and addArc()
// Returns newly created Graph
Graph read_file(FILE*);

// find_SCCs()
// Runs DFS() on G and G_transpose, processing vertices in the second call
// by decreasing finish times from the first call to find
// Strongly-Connected-Components
Graph find_SCCs(FILE*, List, Graph);

// getComponent()
// After DFS has been run and List S holds SCCs, returns the first SCC as
// a char*
// Pre: List != NULL  
void print_SCCs(FILE*, List, Graph);

// getNumSCCs()
// After DFS has been run and List S holds SCCs, returns the number of SCCs
int getNumSCCs(List, Graph);

int main(int argc, char* argv[]){
  FILE *in, *out;
  Graph G;
  
  if (argc != 3){
    fprintf(stderr, "FindComponents Error in main(): Incorrect number of command line arguments\nUsage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  in = fopen(argv[1], "r");
  if (in == NULL){
    fprintf(stderr, "FindComponents Error in main(): Unable to open %s for reading\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  out = fopen(argv[2], "w");
  if (out == NULL){
    fprintf(stderr, "FindComponents Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  int numSCC;
  List S = newList();
  Graph G_t;
  
  G =  read_file(in);  
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  G_t = find_SCCs(out, S, G);
  numSCC = getNumSCCs(S, G_t);
  fprintf(out, "\nG contains %d strongly connected components:\n", numSCC);

  print_SCCs(out, S, G_t);
  /* for(int i = 1; i <= numSCC; i++){ */
  /*   fprintf(out, "Component %d:", i); */
  /*   fprintf(out, getComponent(S, G_t)); */
  /*   fprintf(out, "\n"); */
  /* } */
  
  fclose(in);
  fclose(out);
  freeList(&S);
  freeGraph(&G);
  freeGraph(&G_t);
} 

Graph read_file(FILE *in){
  // n = # of vertices, first line in input file
  int row_index, col_index, entry_1, entry_2, line_count, n, toki;
  int **arr;
  char line[MAX_LEN];
  char* token;
  bool zeros;
  Graph G;
  
  line_count = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    line_count++;
  }
  
  arr = (int**)malloc(line_count*sizeof(int*));
  for(int i = 0; i < line_count; i++){
    arr[i] = (int*)malloc(ARR_COLUMN*sizeof(int));
  }
  
  rewind(in);
  row_index = col_index = 0;
 
  while(row_index < line_count && fgets(line, MAX_LEN, in) != NULL){
    token = strtok(line, " \n");
    if(row_index == 0){
      n = atoi(token);
    }
    while(token != NULL && col_index < ARR_COLUMN) {
      toki = atoi(token);
      arr[row_index][col_index] = toki;
      token = strtok(NULL, " ");
      col_index++;
    }
    row_index++;
    col_index = 0;
  }

  if (n == 0){
    exit(EXIT_SUCCESS);
  }

  G = newGraph(n);
  for (int i = 1; i < line_count; i++){
    entry_1 = arr[i][0];
    entry_2 = arr[i][1];
    zeros = entry_1 == 0 && entry_2 == 0;
    if(!zeros){
      addArc(G, entry_1, entry_2);
    } else {
      break;
    }
  }
  
  for(int i = 0; i < line_count; i++){
    free(arr[i]);
  }
  
  free(arr);
  return(G);
}

Graph find_SCCs(FILE *out, List S, Graph G){
  Graph G_t = transpose(G);
  
  for (int i = 1; i <= getOrder(G); i++){
    append(S, i);
  }

  DFS(G, S);
  DFS(G_t, S);
  return(G_t);
}

void print_SCCs(FILE* out, List S, Graph G){
  if(S == NULL){
    fprintf(stderr, "FindComponents Error: Calling print_SCCs() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(G == NULL){
    fprintf(stderr, "FindComponents Error: Calling print_SCCs() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(S) == 0) return;

  int count = 0;
  List SCC = newList();
  
  // Read list S from end until NIL parent then read down to get topological order
  moveBack(S);
  while(index(S) >= 0){
    prepend(SCC, get(S));
    if(getParent(G, get(S)) == NIL){
      count++;
      fprintf(out, "Component %d: ", count);
      printList(out, SCC);
      fprintf(out, "\n");
      clear(SCC);
    }
    movePrev(S);
  }
}

int getNumSCCs(List S, Graph G){
   if(S == NULL){
    fprintf(stderr, "FindComponents Error in main: Calling getNumSCCs() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(S) == 0) return(0);

  int count = 0;
  moveFront(S);
  while(index(S) >= 0){
    if(getParent(G, get(S)) == NIL) {
      count++;
    }
    moveNext(S);
  }

  return(count);
}
