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
#define INF -1
#define NIL -2
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
// Returns order of G
// Pre: G != NULL
int getOrder(Graph G);

// getSize()
// Returns size of G
// Pre: G != NULL
int getSize(Graph G);

// get Source()
// Returns the sourse vertex most recently used in function BFS() or NIL if
// BFS() hasn't been called
// Pre: G != NULL
int getSource(Graph G);


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() hasn't been called
// Pre: G != NULL
int getParent(Graph G, int u);

// getDist()
// Returns the distance from the most recent BFS source to vertex u or NIL if
// BFS() hasn't been called
// Pre: G != NULL
int getDist(Graph G, int u);

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to
// u, or appensd to L the value NIL if no such path exists.
// Pre: G != NULL, getSource(G) != NULL,
/////// BFS must be called b4 getPath()
void getPath(List L, Graph G, int u);


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

// BFS)()
// Runs BFS algorithm on Graph G with source s 
// Pre: G != NULL
void BFS(Graph G, int s);


/*** Other operations ***/

// printGraph()
// Prints adjacency list representation of G to the file pointed to by out
// Pre: G != NULL, out != NULL
void printGraph(FILE* out, Graph G);

#endif 
