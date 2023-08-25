//-----------------------------------------------------------------------------
// FindPath.c
// Client module for Graph ADT
// Usage: ./FindPath <input file> <output file>
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

int main(int argc, char* argv[]){
  int row_index, col_index, entry_1, entry_2, line_count;
  FILE *in, *out;
  char line[MAX_LEN];
  char* token;
  int n, toki; // n = number of vertices = first line of input file
  int **arr;
  
  if (argc != 3){
    fprintf(stderr, "FindPath Error in main(): Incorrect number of command line arguments\nUsage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  in = fopen(argv[1], "r");
  if (in == NULL){
    fprintf(stderr, "FindPath Error in main(): Unable to open %s for reading\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  out = fopen(argv[2], "w");
  if (out == NULL){
    fprintf(stderr, "FindPath Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }

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

  int dist;
  bool breakPoint1 = false;
  bool breakPoint2 = false;
  bool zeros = false;
  List Path = newList();
  Graph G = newGraph(n);
  
  for(int i = 1; i < line_count; i++){
    entry_1 = arr[i][0];
    entry_2 = arr[i][1];
    zeros = entry_1 == 0 && entry_2 == 0;
    if(zeros && !breakPoint1){
      breakPoint1 = true;
    } else if (zeros && !breakPoint2 && breakPoint1){
      breakPoint2 = true;
    }
    
    if(!breakPoint1) {
      addEdge(G, entry_1, entry_2);
    } else if (breakPoint1 && zeros && !breakPoint2){
      printGraph(out, G);
    }
    
    if(breakPoint1 && !zeros) {
      BFS(G, entry_1);
      getPath(Path, G, entry_2);
      dist = getDist(G, entry_2);
      if (dist == INF) {
	fprintf(out, "\nThe distance from %d to %d is infinity\n", entry_1, entry_2);

      } else {
	fprintf(out, "\nThe distance from %d to %d is %d\n", entry_1, entry_2, dist);
      }
      moveFront(Path);
      if (get(Path) == NIL){
	fprintf(out, "No %d-%d path exists", entry_1, entry_2);
      } else {
	fprintf(out, "A shortest %d-%d path is:", entry_1, entry_2);
	while(index(Path) >= 0){
	  fprintf(out, " %d", get(Path));
	  moveNext(Path);
	}
      }
      fprintf(out, "\n");
      while(length(Path) > 0){
	deleteFront(Path);
      }	
    }
  }
  
  for(int i = 0; i < line_count; i++){
    free(arr[i]);
  }
  
  free(arr);
  freeGraph(&G);
} 
