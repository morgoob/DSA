//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

// structs---------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
  void* data;
  Node next;
  Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back; 
  Node cursor;
  int length;
  int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode ()
// Returns reference to new Node object. Initializes next and data fields
Node newNode(void* data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

// freeNode ()
// Frees HEAP memory and pointed to by *pN, sets *pN to NULL
void freeNode(Node* pN){
  free(*pN);
  *pN = NULL;
}

// newList()
// Returns reference to new empty List object
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
  if (pL != NULL && *pL != NULL){
    while (length(*pL) != 0) {
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L 
// Pre: L != NULL, 
int length(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
// Pre: L != NULL, 
int index(List L){
   if (L == NULL){
    fprintf(stderr, "List Error: Calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
   }
   if (L->cursor == NULL || L->index < 0) return -1;
   return(L->index); 
}

// front()
// Returns front element of L. Pre: length() > 0
// Pre: L != NULL, 
void* front(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling front() on empty List\n");
    exit(EXIT_FAILURE);
  }
  
  return(L->front->data); 
}

// back()
// Returns back element of L. Pre: length() > 0
// Pre: L != NULL, 
void* back(List L){
   if (L == NULL){
     fprintf(stderr, "List Error: Calling back() on NULL List reference\n");
     exit(EXIT_FAILURE);
   }
   if (L->length == 0){
     fprintf(stderr, "List Error: Calling back() on empty List\n");
     exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L. Pre: length() > 0, index >= 0
// Pre: L != NULL, 
void* get(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling get() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(L->index < 0){
    fprintf(stderr, "List Error: Calling get() on index < 0\n");
    exit(EXIT_FAILURE);
  }

  return(L->cursor->data);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L){
  if (L == NULL) {
    L = newList();
    return; 
  }
  if (L->length == 0) return;
  while (L->length > 0){
    deleteFront(L);
  }
}

// set()
// Overwrites the cursor element's data with  x
// Pre: L != NULL, length() > 0, index() > 0
void set(List L, void* x){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling set() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling set() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1 || L->cursor == NULL) {
    fprintf(stderr, "List Error: Calling set() on undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  
  L->cursor->data = x;
}

// moveFront()
// Sets cursor under the front element. Does nothing if isEmpty()
// Pre:  L != NULL, length() > 0
void moveFront(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) return;

  L->cursor = L->front;
  L->index = 0;
}

// moveBack()
// Sets cursor under the back element. Does nothing if isEmpty()
// Pre:  L != NULL, length() > 0
void moveBack(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling moveBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0) return;

  L->cursor = L->back;
  L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: L != NULL, 
void movePrev(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1 || L->cursor == NULL) return;
  if (index(L) == 0){
    L->cursor = NULL;
    L->index = -1;
    return;
  }
  
  L->cursor = L->cursor->prev;
  L->index--;
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: L != NULL, 
void moveNext(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling moveNext() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1 || L->cursor == NULL) return;
  if(L->cursor == L->back){
    L->cursor = NULL;
    L->index = -1;
    return;
  }
  
  L->cursor = L->cursor->next;
  L->index++;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion
// takes place before front element
// Pre: L != NULL, 
void prepend(List L, void* x){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling prepend() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->index >= 0) L->index++;
  
  Node temp = newNode(x);

  if(L->length == 0){
    L->back = temp;
  } else {
    L->front->prev = temp;
  }

  temp->next = L->front;
  L->front = temp;
  L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
// Pre: L != NULL, 
void append(List L, void* x){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  
  Node temp = newNode(x);

  if(L->length == 0){
    L->front = temp;
  } else {
    L->back->next = temp;
    temp->prev = L->back;
  }

  L->back = temp;
  L->length++;
}
 
// insertBefore()
// Insert new element before cursor.
// Pre:  L != NULL, length()>0, index()>=0
void insertBefore(List L, void* x){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling insertBefore() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0 || L->cursor == NULL){
    fprintf(stderr, "List Error: Calling insertBefore() on undefined cursor\n");
    exit(EXIT_FAILURE);
  }

  Node temp = newNode(x);
  Node cursor_prev = L->cursor->prev;

  L->cursor->prev = temp;
  temp->next = L->cursor;
  
  if (L->cursor == L->front){
    L->front = temp;
  } else if (cursor_prev != NULL){
    cursor_prev->next = temp;
    temp->prev = cursor_prev;
  }

  L->index++;
  L->length++;
}


// insertAfter()
// Insert new element after cursor.
// Pre:  L != NULL, length()>0, index()>=0
void insertAfter(List L, void* x){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling insertAfter() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling insertAfter() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0 || L->cursor == NULL){
    fprintf(stderr, "List Error: Calling insertAfter() on undefined cursor\n");
    exit(EXIT_FAILURE);
  }

  Node temp = newNode (x);
  Node cursor_next = L->cursor->next;

  L->cursor->next = temp;
  temp->prev = L->cursor;

  if(L->cursor == L->back){
    L->back = temp;
  } else if (cursor_next != NULL){
    cursor_next->prev = temp;
    temp->next = cursor_next;
  }

  L->length++;
}

// deleteFront()
// Delete the front element. Pre:  L != NULL, length()>0
void deleteFront(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling deleteFront() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->front == L->cursor){
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->index--;
  }
  
  Node temp = L->front;

  if (L->length > 1){
    L->front = L->front->next;
  } else {
    L->front = L->back = NULL;
  }

  L->length--;
  freeNode(&temp);
}

// deleteBack()
// Delete the back element. Pre:  L != NULL, length()>0
void deleteBack(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling deleteBack() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->back == L->cursor){
    L->cursor = NULL;
    L->index = -1;
  }
  
  Node temp = L->back;
  Node back_prev = L->back->prev;
  
  if (L->front == L->back){
    L->front = NULL;
  } else {
    back_prev->next = NULL;
  }
  
  L->back = back_prev;
  back_prev = NULL;
  L->length--;
  freeNode (&temp);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre:  L != NULL, length()>0, index()>=0
void delete(List L){
  if (L == NULL){
    fprintf(stderr, "List Error: Calling delete() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->length == 0){
    fprintf(stderr, "List Error: Calling delete() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1 || L->cursor == NULL){
    fprintf(stderr, "List Error: Calling delete() on undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == L->front) {
    deleteFront(L);
    return;
  }
  if (L->cursor == L->back) {
    deleteBack(L);
    return;
  }
  
  Node temp = L->cursor;
  Node next = L->cursor->next;
  Node prev = L->cursor->prev;
  
  next->prev = prev;
  prev->next = next;
  temp->next = temp->prev = NULL;
  freeNode(&temp);
  L->length--;
}

/////// NOT suitable to use with generic pointers ///////
// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
// Pre: out != NULL, L != NULL 
/* void printList(FILE* out, List L){ */
/*   if (L == NULL){ */
/*     fprintf(stderr, "List Error: Calling printList() on NULL List reference\n"); */
/*     exit(EXIT_FAILURE); */
/*   } */
/*   if (out == NULL){ */
/*     fprintf(stderr, "List Error: unable to open file for writing in printList()\n"); */
/*     exit(EXIT_FAILURE); */
/*   } */
/*   if (L->length == 0){ */
/*     return; */
/*   } */

/*   Node temp = L->front; */

/*   if(temp->next == NULL){ */
/*     fprintf(out, "%d", temp->data); */
/*     return; */
/*   } */
  
/*   while(temp != NULL){ */
/*     if (temp->next == NULL) { */
/*       fprintf(out, "%d", temp->data); */
/*     } else { */
/*       fprintf(out, "%d ", temp->data); */
/*     } */
/*     temp = temp->next; */
/*   } */
/* } */

// Other operations -----------------------------------------------------------

// * NOT implemented yet * 
// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B);

