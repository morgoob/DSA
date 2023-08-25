//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE
#define LIST_H_INCLUDE 


// structs---------------------------------------------------------------------

typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object
List newList(void); 

// freeList()
//  Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL); 


// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L 
int length(List L); 

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L);

// front()
// Returns front element of L.
// Pre: L != NULL, length() > 0
int front(List L); 

// back()
// Returns back element of L.
// Pre: L != NULL, length() > 0
int back(List L); 

// get()
// Returns cursor element of L.
// Pre: L != NULL, length() > 0, index >= 0
int get(List L); 

// equals()
// Returns true iff List A and List B are in same state, and returns false
// otherwise
// Pre: A != NULL and B != NULL
bool equals(List A, List B); 


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L);

// set()
// Overwrites the cursor element's data with  x
// Pre: L != NULL, length() > 0, index() > 0
void set(List L, int x); 

// moveFront()
// Sets cursor under the front element. Does nothing if isEmpty()
// Pre: L != NULL, length() > 0
void moveFront(List L); 

// moveBack()
// Sets cursor under the back element. Does nothing if isEmpty()
// Pre: L != NULL, length() > 0
void moveBack(List L); 

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
// Pre: L != NULL, 
void movePrev(List L); 

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L); 

// prepend()
// Insert new element into L. If L is non-empty, insertion
// takes place before front element
// Pre: L != NULL, 
void prepend(List L, int x); 

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
// Pre: L != NULL, 
void append(List L, int x); 

// insertBefore()
// Insert new element before cursor.
// Pre: L != NULL, length()>0, index()>=0
void insertBefore(List L, int x); 

// insertAfter()
// Insert new element after cursor.
// Pre: L != NULL, length()>0, index()>=0
void insertAfter(List L, int x); 

// deleteFront()
// Delete the front element.
// Pre: L != NULL, length()>0
void deleteFront(List L); 

// deleteBack()
// Delete the back element.
// Pre: L != NULL, length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined.
// Pre: L != NULL, length()>0, index()>=0
void delete(List L); 

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
// Pre: out != NULL, L != NULL
void printList(FILE* out, List L); 


// Other operations -----------------------------------------------------------

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new List is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L); 

// * NOT implemented yet *
// concatList()
// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B); 

#endif
