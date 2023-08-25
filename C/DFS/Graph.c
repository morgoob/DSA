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
  List *adj;
  int *color;
  int *p;
  int *d;
  int *f;
} GraphObj;

// newGraph()
// Returns a Graph pointing to a newly created GraphObj with n vertices and
// no edges. Arrays are length n + 1, indices 1 thru n are used. 
Graph newGraph(int n){
  Graph G;
  G = malloc(sizeof(GraphObj));
  G->order = n;
  G->size = 0;
  
  // Arrays
  G->adj = calloc((G->order+1), sizeof(List*));
  G->color = calloc((G->order+1), sizeof(int*));
  G->p = calloc((G->order+1), sizeof(int*));
  G->d = calloc((G->order+1), sizeof(int*));
  G->f = calloc((G->order+1), sizeof(int*));
  
  for (int i = 1; i < G->order + 1; i++){
    G->adj[i] = newList();
    G->color[i] = WHITE;
    G->p[i] = NIL;
    G->d[i] = UNDEF;
    G->f[i] = UNDEF;
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
    free((*pG)->f);

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
// Returns order (# of vertices) of G
// Pre: G != NULL
int getOrder(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getOrder() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  
  return(G->order);
}

// getSize()
// Returns size (# of edges) of G
// Pre: G != NULL
int getSize(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getSize() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  
  return(G->size);
}

// getParent()
// Returns the parent of vertex u 
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
// getDiscover()
// Returns the discover time of vertex u
// Pre: G != NULL, u is in range 1 -> order
int getDiscover(Graph G, int u){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getDiscover() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling getDiscover() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }

  return(G->d[u]);
}

// getFinish()
// Returns the finish time of vertex u
// Pre: G != NULL, u is in range 1 -> order
int getFinish(Graph G, int u){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling getFinish() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > G->order) {
    fprintf(stderr, "Graph Error: Calling getFinish() with a vertex out of range\n");
    exit(EXIT_FAILURE);
  }

  return(G->f[u]);
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

// Visit()
// Private helper function for DFS()
void Visit(Graph G, List finish_times, int *time, int x){
  int y;
  List adj_x = G->adj[x];
  G->d[x] = ++(*time);
  G->color[x] = GRAY;
  moveFront(adj_x);

  while(index(adj_x) >= 0){
    y = get(adj_x);
    if(G->color[y] == WHITE){
      G->p[y] = x;
      Visit(G, finish_times, time, y);
    }
    moveNext(adj_x);
  }

  G->color[x] = BLACK;
  G->f[x] = ++(*time);
  prepend(finish_times, x);
}

// DFS()
// Runs DFS algorithm on Graph G  
// List S defines order in which vertices are to be processed
// When DFS is complete, it will store the vertices by decreasing
// finish times (S is a stack in this case)
// Pre: G != NULL, S != NULL, length(S) == get Order(G)
void DFS(Graph G, List S){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling DFS() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(S == NULL){
    fprintf(stderr, "Graph Error: Calling DFS() with NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(S) != G->order){
    fprintf(stderr, "Graph Error: Calling DFS() with List S such that length(S) != getOrder(G)\n");
    exit(EXIT_FAILURE);
  }

  moveFront(S);
  while(index(S) >= 0){
    if(get(S) < 0 || get(S) > G->order){
      fprintf(stderr, "Graph Error: Calling DFS() With List S that contains vertex out of range\n");
      exit(EXIT_FAILURE);
    }
    moveNext(S);
  }

  List finish_times = newList();
  int time = 0;
  
  for(int i = 1; i <= G->order; i++){
    G->color[i] = WHITE;
    G->p[i] = NIL;
  }
  
  int popped;
  while(length(S) > 0){
    popped = front(S);
    deleteFront(S);  
    if(G->color[popped] == WHITE){
      Visit(G, finish_times, &time, popped);
    }
  }
  
  moveFront(finish_times);
  while (index(finish_times) >= 0){
    append(S, get(finish_times));
    moveNext(finish_times);
  }
  
  freeList(&finish_times);
}


/*** Other operations ***/

// transpose()
// Returns a reference to a new Graph object representing the transpose of G
// Pre: Graph != NULL
Graph transpose(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling transpose() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  Graph G_t = newGraph(G->order);

  if(G->order == 0) return G_t;
  List adj_i;
  for(int i = 1; i < G->order + 1; i++){
    adj_i = G->adj[i];
    if(length(adj_i) > 0){
      moveFront(adj_i);
      while(index(adj_i) >= 0){
	addArc(G_t, get(adj_i), i);
	moveNext(adj_i);
      }
    }
  }

  return(G_t);
}

// copyGraph()
// Returns a reference to a new Graph that is a copy of G.
// Pre: Graph != NULL
Graph copyGraph(Graph G){
  if (G == NULL){
    fprintf(stderr, "Graph Error: Calling copyGraph() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }

  List adj_G, adj_Gc;
  Graph G_c = newGraph(G->order);

  for(int i = 0; i < G->order + 1; i++){
    adj_G = G->adj[i];
    adj_Gc = G_c->adj[i];
    moveFront(adj_G);
    while(index(adj_G) >= 0){
      append(adj_Gc, get(adj_G));
    }
  }
  
  return(G_c);
}


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

// printGraphTable()
// For debugging and gathering more info on Graph G
// Prints to stdout
// Pre: G != NULL
void printGraphTable(Graph G){
  if(G == NULL){
    fprintf(stderr, "Graph Error: Calling printGraphTable() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(G->order == 0){
    fprintf(stderr, "Graph Error: Calling printGraphTable() on Graph with order 0\n");
    exit(EXIT_FAILURE);
  }

  printf("V | p | d | f\n");
  for(int i = 1; i <= G->order; i++){
    printf("%d | %d | %d | %d\n", i, G->p[i], G->d[i], G->f[i]);
  }
}


