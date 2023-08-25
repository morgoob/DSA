//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include "Graph.h"
#include "List.h"


typedef struct GraphObj {
  int order; // number of vertices
  int size; // number of edges
  int source; // most recent source for BFS
  List *adj;
  int *color;
  int *p;
  int *d;
} GraphObj;

// newGraph()
// Returns a Graph pointing to a newly created GraphObj with n vertices and
// no edges. Arrays are length n + 1, indices 1 thru n are used. 
Graph newGraph(int n){
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->order = n;
  G->size = 0;
  G->source = NIL;
  
  // Arrays
  G->adj = calloc((G->order+1), sizeof(List*));
  G->color = calloc((G->order+1), sizeof(int*));
  G->p = calloc((G->order+1), sizeof(int*));
  G->d = calloc((G->order+1), sizeof(int*));

  for (int i = 1; i < G->order + 1; i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->p[i] = NIL;
    G->d[i] = INF;
  }
  return(G);
}

// freeeGraph()
// Frees all heap memory associated with the Graph *pG, then sets *pG to NULL
void freeGraph(Graph* pG){
  if (pG != NULL && *pG != NULL){
    free((*pG)->color);
    free((*pG)->p);
    free((*pG)->d);
    for (int i = 0; i < (*pG)->order + 1; i++){
      freeList(&(*pG)->adj[i]);
    }
    free((*pG)->adj);
    free(*pG);
    *pG = NULL;
  }
}

/*** Access functions ***/

// getOrder()
// Returns order of G
// Pre: G != NULL
int getOrder(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getOrder() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return(G->order);
}

// getSize()
// Returns size of G
// Pre: G != NULL
int getSize(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getSize() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return(G->size);
}

// get Source()
// Returns the sourse vertex most recently used in function BFS() or NIL if
// BFS() hasn't been called
// Pre: G != NULL
int getSource(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getSource() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return(G->source);
}


// getParent()
// Returns the parent of vertex u in the Breadth-First tree created by BFS(),
// or NIL if BFS() hasn't been called
// Pre: G != NULL, u is in range 1 -> order
int getParent(Graph G, int u){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getParent() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling getParent() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  return(G->p[u]);
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u or NIL if
// BFS() hasn't been called
// Pre: G != NULL, u is in range 1 -> order
int getDist(Graph G, int u){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getDist() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling getDist() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }

  return(G->d[u]);
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to
// u, or appends to L the value NIL if no such path exists.
// Pre: G != NULL, getSource(G) != NULL,
/////// BFS must be called b4 getPath()
void getPath(List L, Graph G, int u){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getPath() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling getPath() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL){
    fprintf(stderr, "Graph Error: Calling getPath() before BFS() has been called\n");
    exit(EXIT_FAILURE);
  }
  
  if(G->source == u){
    append(L, u);
  } else if (G->p[u] == NIL){
    moveFront(L);
    prepend(L, NIL);
    return;
  } else {
    getPath(L, G, G->p[u]);
    append(L, u);
  }
}


/*** Manipulation procedures ***/

// makeNull() 
// Deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling makeNull() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < G->order + 1; i++){
    List L = G->adj[i];
    while(length(L) > 0){
      deleteFront(L);
    }
  }
  
  G->size = 0;
}

// insertSort()
// Helper function for addEdge() and addArc()
// inserts y into x's adjacency List in sorted order
// No preconditions, private and safe fn 
void insertSort(Graph G, int x, int y){
  List L = G->adj[x];

  if(length(L) == 0){
    append(L, y);
    return;
  }
  
  moveFront(L);
  for (int i = 0; i < length(L); i++){
    if(get(L) > y){
      insertBefore(L, y);
      return;
    } else if (i == length(L) - 1 && get(L) != y){
      append(L, y);
      return;
    }
    moveNext(L);
  }
}

// addEdge()
// Inserts a new edge joining u to v 
// Pre: G != NULL, u,v are in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling addEdge() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling addEdge() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > G->order) {
    fprintf(stderr, "Graph Error: Calling addEdge() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  insertSort(G, u, v);
  insertSort(G, v, u);
  G->size++;
}


// addArc()
// Inserts a new directed edge from u to v
// Pre: G != NULL, u,v are in range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling addArc() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling addArc() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > G->order) {
    fprintf(stderr, "Graph Error: Calling addArc() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  insertSort(G, u, v);
  G->size++;
}

// BFS)()
// Runs BFS algorithm on Graph G with source s 
// Pre: G != NULL
void BFS(Graph G, int s){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling BFS() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (s < 1 || s > G->order) {
    fprintf(stderr, "Graph Error: Calling BFS() with a source vertex out of range\n");
    exit(EXIT_FAILURE);
  }
  
  int x, y;
  G->source = s;
  for (int i = 1; i < G->order + 1; i++){
    if (i != s){
      G->color[i] = WHITE;
      G->p[i] = NIL;
      G->d[i] = INF;
    }
  }
  G->color[s] = GRAY;
  G->d[s] = 0;
  G->p[s] = NIL;

  List adj_x;
  // make List to serve as FIFO queue
  List Q = newList();
  append(Q, s);
  
  while(length(Q) != 0){
    x = front(Q);
    deleteFront(Q);
    adj_x = G->adj[x];
    moveFront(adj_x);
    while(index(adj_x) >= 0){
      y = get(adj_x);
      if(G->color[y] == WHITE){
	G->color[y] = GRAY;
	G->d[y] = G->d[x] + 1;
	G->p[y] = x;
	append(Q, y);
      }
      G->color[x] = BLACK;
      moveNext(adj_x);
    }
  }
  freeList(&Q);
}


/*** Other operations ***/

// printGraph()
// Prints adjacency list representation of G to the file pointed to by out
// Pre: G != NULL, out != NULL
void printGraph(FILE* out, Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling printGraph() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (out == NULL) {
    fprintf(stderr, "Graph Error: unable to open file for writing in printGraph()\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i < G->order + 1; i++){
    List L = G->adj[i];
    moveFront(L);
    fprintf(out, "%d: ", i);
    if (length(L) == 0){
      fprintf(out, "\n");
    }
    for(int j = 0; j < length(L); j++){
      if(j == length(L)-1){
	fprintf(out, "%d\n", get(L));
      } else {
	fprintf(out, "%d ", get(L));
      }
      moveNext(L);
    }
  }
}


