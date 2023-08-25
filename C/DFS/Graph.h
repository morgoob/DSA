//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

#ifndef GRAPH_H_INCLUDE
#define GRAPH_H_INCLUDE 
#define UNDEF  -1
#define NIL 0
#define WHITE 1
#define GRAY 2
#define BLACK 3

/*** Structs ***/
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// newGraph()
// Returns a Graph pointing to a newly created GraphObj with n vertices and
// no edges
Graph newGraph(int n);

// freeeGraph()
// Frees all heap memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder()
// Returns order (# of vertices) of G
// Pre: G != NULL
int getOrder(Graph G);

// getSize()
// Returns size (# of edges) of G
// Pre: G != NULL
int getSize(Graph G);


// getParent()
// Returns the parent of vertex u 
// Pre: G != NULL, u is in range 1 -> order
int getParent(Graph G, int u);

// getDiscover()
// Returns the discover time of vertex u
// Pre: G != NULL, u is in range 1 -> order
int getDiscover(Graph G, int u);

// getFinish()
// Returns the finish time of vertex u
// Pre: G != NULL, u is in range 1 -> order
int getFinish(Graph G, int u);


/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v 
// Pre: G != NULL, u,v are in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v
// Pre: G != NULL, u,v are in range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

// DFS()
// Runs DFS algorithm on Graph G
// List S defines order in which vertices are to be processed
// When DFS is complete, it will store the vertices by decreasing
// finish times (S is a stack in this case)
// Pre: G != NULL, S != NULL, length(S) == get Order(G)
void DFS(Graph G, List S);

/*** Other operations ***/

// transpose()
// Returns a reference to a new Graph object representing the transpose of G
// Pre: Graph != NULL
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new Graph that is a copy of G.
// Pre: Graph != NULL
Graph copyGraph(Graph G);

// printGraph()
// Prints adjacency list representation of G to the file pointed to by out
// Pre: G != NULL, out != NULL
void printGraph(FILE* out, Graph G);

// printGraphTable()
// For debugging and gathering more info on Graph G
// Prints to stdout
// Pre: G != NULL
void printGraphTable(Graph G);
 
#endif 
