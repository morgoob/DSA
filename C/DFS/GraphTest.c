//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for Graph ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

#define N 12

void graph_test(Graph, FILE*);
bool order_test(Graph, int);
bool size_test(Graph, int);
bool makeNull_test(Graph);
bool addEdge_test(Graph);
bool addArc_test(Graph);
bool freeGraph_test(Graph);

int main(int argc, char* argv[]){
  Graph G = newGraph(N);
  FILE *out;

  out = fopen("output.txt", "w");
  if (out == NULL){
    fprintf(stderr, "GraphTest Error in main(): Unable to open %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }
 
  fprintf(stdout, "**********Graph ADT Test**********\n");
  fprintf(stdout, "Test results will be redirected to: \"output.txt\"\n");
  graph_test(G, out);
  fclose(out);
}

void graph_test(Graph G, FILE* out){
  fprintf(out, "**********Graph ADT Test**********\n\n");

  // getOrder() Test
  fprintf(out, "**********getOrder() Test**********\n");
  if (order_test(G, N)){
    fprintf(out, "getOrder() test: PASSED\n");
  } else {
    fprintf(out, "getOrder() test: FAILED\n");
  }
  fprintf(out, "\n");
  
  // addEdge() / getSize() Test
  fprintf(out, "**********getSize() with addEdge() Test**********\n");
  for (int i = 1; i < N-2; i++) {
    addEdge(G, i, i+1);
    if (size_test(G, i)){
      fprintf(out, "getSize() with addEdge() test #%d: PASSED\n", i);
    } else {
      fprintf(out, "getSize() with addEdge() test #%d: FAILED\n", i);
    }
  }
  fprintf(out, "Graph before makeNull():\n");
  printGraph(out, G); 
  fprintf(out, "\n");

  // makeNull() Test
  fprintf(out, "**********makeNull() Test after addEdge()**********\n");
  if(makeNull_test(G)){
    fprintf(out, "makeNull() test: PASSED\n");
  } else {
    fprintf(out, "makeNull() test: FAILED\n");
  }
  fprintf(out, "Graph after makeNull():\n");
  printGraph(out, G);
  fprintf(out, "\n");
   
  // addArc() / getSize() Test
  fprintf(out, "**********getSize() with addArc() Test**********\n");
  for (int i = 1; i < N-2; i++) {
    addArc(G, i, i+1);
    if (size_test(G, i)){
      fprintf(out, "getSize() with addArc() test #%d: PASSED\n", i);
    } else {
      fprintf(out, "getSize() with addArc() test #%d: FAILED\n", i);
    }
  }
  fprintf(out, "Graph before makeNull():\n");
  printGraph(out, G);
  fprintf(out, "\n");

  // makeNull() Test
  fprintf(out, "**********makeNull() Test after addArc()**********\n");
  if(makeNull_test(G)){
    fprintf(out, "makeNull() test: PASSED\n");
  } else {
    fprintf(out, "makeNull() test: FAILED\n");
  }
  fprintf(out, "Graph after makeNull():\n");
  printGraph(out, G);
}

bool order_test(Graph G, int expected){
  if(getOrder(G) == expected){
    return true;
  }
  return false;
}

bool size_test(Graph G, int expected){
  if(getSize(G) == expected){
    return true;
  }
  return false;
}

bool makeNull_test(Graph G){
  makeNull(G);
  if(getSize(G) == 0){
    return true;
  }
  return false;
}
