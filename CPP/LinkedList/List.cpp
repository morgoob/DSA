//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <stdexcept>
#include <climits>
#include "List.h"

// Private Constructor --------------------------------------------------------


// Class Constructors & Destructors -------------------------------------------
List::Node::Node(ListElement x){
  data = x;
  next = nullptr;
  prev = nullptr;
}

// Creates new List in the empty state.
List::List(){
  frontDummy = new Node((ListElement) INT_MIN); 
  backDummy = new Node((ListElement) INT_MAX);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;  
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
  // Starts as empty List
  frontDummy = new Node((ListElement) INT_MIN); 
  backDummy = new Node((ListElement) INT_MAX);
  frontDummy->next = backDummy;
  backDummy->prev = frontDummy;  
  beforeCursor = frontDummy;
  afterCursor = backDummy;
  num_elements = 0;
  pos_cursor = 0;
  
  // Copy contents
  Node* temp = L.frontDummy->next;
  while(temp != nullptr && temp != L.backDummy){
    this->insertBefore(temp->data);
    temp = temp->next;
  }
  moveFront();
}

// Destructor
List::~List(){
  clear();
  delete frontDummy;
  delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
  return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
  if(num_elements <= 0){
    throw std::length_error("List: front(): length of List is <= 0");
  }
  return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
  if(num_elements <= 0){
    throw std::length_error("List: back(): length of List is <= 0");
  }
  return(backDummy->prev->data);
 
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
  return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
  if(pos_cursor >= num_elements){
    throw std::range_error("List: peekNext(): cursor position is >= length of List");
  }
  return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
  if(pos_cursor <= 0){
    throw std::range_error("List: peekPrev(): cursor position is <= 0");
  }
  return(beforeCursor->data);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
  if(num_elements == 0) return;
  moveFront();
  while(num_elements > 0){
    eraseAfter();
  }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
  if(pos_cursor == 0) return;
  beforeCursor = frontDummy;
  afterCursor = frontDummy->next;
  pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
  if(pos_cursor == num_elements) return;
  afterCursor = backDummy;
  beforeCursor = backDummy->prev;
  pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: moveNext(): cursor position is >= length");
  }
  ListElement data = afterCursor->data;
  afterCursor = afterCursor->next;
  beforeCursor = beforeCursor->next;
  pos_cursor++;
  return(data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
  if(pos_cursor <= 0){
    throw std::range_error("List: movePrev(): cursor position is <= 0");
  }
  ListElement data = beforeCursor->data;
  beforeCursor = beforeCursor->prev;
  afterCursor = afterCursor->prev;
  pos_cursor--;
  return(data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
  Node* newNode = new Node(x);
  Node* temp = afterCursor;
  newNode->prev = beforeCursor;
  beforeCursor->next = newNode;
  newNode->next = temp;
  temp->prev = newNode;
  afterCursor = newNode;
  num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
  Node* newNode = new Node(x);
  Node* temp = beforeCursor;
  newNode->next = afterCursor;
  afterCursor->prev = newNode;
  newNode->prev = temp;
  temp->next = newNode;
  beforeCursor = newNode;
  num_elements++;
  pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: setAfter(): cursor position is >= length of List");
  }
  afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
  if(pos_cursor <= 0){
    throw std::range_error("List: setBefore(): cursor position is <= 0");
  }
  beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
  if(pos_cursor >= num_elements){
    throw std::range_error("List: eraseAfter(): cursor position is >= length of List");
  }
  Node* after = afterCursor;
  Node* nextN = afterCursor->next;
  beforeCursor->next = nextN;
  nextN->prev = beforeCursor;
  afterCursor = nextN;
  num_elements--;
  delete after;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
  if(pos_cursor <= 0){
    throw std::range_error("List: eraseBefore(): cursor position is <= 0");
  }
  Node* before = beforeCursor;
  Node* prevN = beforeCursor->prev;
  prevN->next = afterCursor;
  afterCursor->prev = prevN;
  beforeCursor = prevN;
  num_elements--;
  pos_cursor--;
  delete before;
}


// Other Functions ------------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
  if(pos_cursor == num_elements - 1){
    return(-1);
  }
  while(afterCursor != backDummy){
    moveNext();
    if(peekPrev() == x){
      return(pos_cursor);
    }
  }
  return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
  if(pos_cursor == 0){
    return(-1);
  }
  while(beforeCursor != frontDummy){
    movePrev();
    if(pos_cursor < num_elements){
      if(peekNext() == x){
      	return(pos_cursor);
      }
    }
  }
  return(-1);
}
 
// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
  if(num_elements <= 1) return;
  Node* current = frontDummy->next;  
  for(int i = 1; i < num_elements; i++){
    int nodeIndex = i;
    for(Node* temp = current->next; temp != backDummy; temp = temp->next){
      nodeIndex++;
      if(current->data == temp->data){
	if(temp == beforeCursor){
	  eraseBefore();
	} else if (temp == afterCursor){
	  eraseAfter();
	} else {
	  Node* toDelete = temp;
	  Node* afterTemp = temp->next;
	  Node* beforeTemp = temp->prev;
	  beforeTemp->next = afterTemp;
	  afterTemp->prev = beforeTemp;
	  if(toDelete != backDummy && toDelete != frontDummy){
	    delete toDelete;
	  }
	  num_elements--;
	  if(nodeIndex <= pos_cursor) pos_cursor--;
	}
      }
    }
    current = current->next;
  }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
  List concatted;
  Node* thisPtr = this->frontDummy->next;
  Node* Lptr = L.frontDummy->next;
  while(thisPtr != backDummy){
    concatted.insertAfter(thisPtr->data);
    thisPtr = thisPtr->next;
    concatted.moveBack();
  }
  while(Lptr != L.backDummy){
    concatted.insertAfter(Lptr->data);
    Lptr = Lptr->next;
    concatted.moveBack();
  }
  concatted.moveFront();
  return(concatted);
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
  Node* ptr = nullptr;
  std::string str = "(";
  for(ptr = frontDummy->next; ptr != backDummy; ptr = ptr->next){
    // if(ptr == afterCursor){
    //   str += " | ";
    // }
    if(ptr == frontDummy->next){
      str += std::to_string((int) ptr->data);
    } else {
      str += ", " + std::to_string((int) ptr->data);
    }
  }
  // if(ptr == afterCursor) str+= " | ";
  str += ")";
  return str;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
  if(this->num_elements == 0 && R.num_elements == 0) return true;
  
  Node* thisPtr = this->frontDummy;
  Node* Rptr = R.frontDummy;
  bool eq = this->num_elements == R.num_elements;
  while(eq && thisPtr != nullptr){
    eq = (thisPtr->data == Rptr->data);
    thisPtr = thisPtr->next;
    Rptr = Rptr->next;
  }
  return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
  return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
  return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
  if(this != &L){
    List temp = L;

    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(pos_cursor, temp.pos_cursor);
    std::swap(num_elements, temp.num_elements);
  }

  return *this;

}
