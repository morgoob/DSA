//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <stdexcept>
#include <climits>
#include <algorithm>

#include "Dictionary.h"
#define RED 1
#define BLACK 0

// Class Constructors & Destructors ----------------------------------------

// Private Node constructor 
Dictionary::Node::Node(keyType k, valType v){
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  color = BLACK;
}

Dictionary::Node::Node(keyType k, valType v, Node* N){
  key = k;
  val = v;
  parent = N;
  left = N;
  right = N;
}

// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
  nil = new Node("\000", INT_MIN);
  nil->parent = nil;
  nil->right = nil;
  nil->left = nil;
  root = nil;
  current = nil;
  num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
  // Start as empty Dictionary
  nil = new Node("\000", INT_MIN);
  nil->parent = nil;
  nil->right = nil;
  nil->left = nil;
  root = nil;
  current = nil;
  num_pairs = 0;

  preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
  clear();
  delete nil;
}

// Private Helper Functions -------------------------------------------------

// inOrderStringKeys()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of keys only, separated by a single space
void Dictionary::inOrderStringKeys(std::string& s, Node* R) const{
   if (R != nil){
    inOrderStringKeys(s, R->left);
    s += R->key + ' '; 
    inOrderStringKeys(s, R->right);
  }
}

// Dictionary::inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
  if (R != nil){
    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + '\n'; 
    inOrderString(s, R->right);
  }
}

// Dictionary::preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
  if (R != nil){
    s += R->key + '\n'; 
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// Dictionary::preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
// N = nil node in other tree 
void Dictionary::preOrderCopy(Node* R, Node* N){
  if(R != N){
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
  }
}

// Dictionary::postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
  if(R != nil){
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    //remove(R->key);
    RB_Delete(R);
  }
}

// Dictionary::search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
  if(R->key == k || R == nil){
    return(R);
  } else if (k < R->key){
    return(search(R->left, k));
  } else {
    // k > R->key
    return(search(R->right, k));
  }
}

// Dictionary::findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
  if(R == nil) return(nil);
  while(R->left != nil){
    R = R->left;
    
  }
  return(R);
}

// Dictionary::findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
  if(R == nil) return(nil);
  while(R->right != nil){
    R = R->right;
  }
  return(R);
}

// Dictionary::findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
  if(N == findMax(root) || N == nil) return(nil);

  std::string inOrder, token;
  inOrderStringKeys(inOrder, root);

  size_t begin, end;
  bool foundNkey = false;
  keyType Nkey, key;
  Nkey = N->key;  
  begin = std::min(inOrder.find_first_not_of(" ", 0), inOrder.length());
  end = std::min(inOrder.find_first_of(" ", begin), inOrder.length());
  token = inOrder.substr(begin, end-begin);
  while(token != ""){
    if(foundNkey) {
      return(search(root, token));
    }
    if(token == Nkey) foundNkey = true;
    begin = std::min(inOrder.find_first_not_of(" ", end+1), inOrder.length());
    end = std::min(inOrder.find_first_of(" ", begin), inOrder.length());
    token = inOrder.substr(begin, end-begin);
  }
  return(nil);
}

// Dictionary::findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
  if(N == findMin(root) || N == nil) return(nil);
  std::string inOrder, token;
  inOrderStringKeys(inOrder, root);

  size_t begin, end;
  std::string prevNode;

  begin = std::min(inOrder.find_first_not_of(" ", 0), inOrder.length());
  end = std::min(inOrder.find_first_of(" ", begin), inOrder.length());
  token = inOrder.substr(begin, end-begin);
  while(token != ""){ 
    if(token == N->key) {
      return(search(root, prevNode));
    }
    prevNode = token;
    begin = std::min(inOrder.find_first_not_of(" ", end+1), inOrder.length());
    end = std::min(inOrder.find_first_of(" ", begin), inOrder.length());
    token = inOrder.substr(begin, end-begin);
  }
  return(nil);
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* x){
  Node* y = x->right;
  
  // turn y's left subtree into x's right subtree
  x->right = y->left;
  if(y->left != nil){
    y->left->parent = x;
  }
  
  // link y's parent to x
  y->parent = x->parent;
  if (x->parent == nil){
    root = y;
  } else if (x ==  x->parent->left){
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  
  // put x on y's left
  y->left = x;
  x->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* x){
  Node* y = x->left;

  // turn y's right subtree into x's right subtree
  x->left = y->right;
  if(y->right != nil){
    y->right->parent = x;
  }
  
  // link y's parent to x
  y->parent = x->parent;
  if(x->parent == nil){
    root = y;
  } else if (x == x->parent->right){
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  
  // put x on y's right
  y->right = x;
  x->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* z){
  Node* y;
  while(z->parent->color == RED){
    if(z->parent == z->parent->parent->left){
      y = z->parent->parent->right;
      if(y->color == RED){
	z->parent->color = BLACK;       // case 1
	y->color = BLACK;               // case 1
	z->parent->parent->color = RED; // case 1
	z = z->parent->parent;          // case 1
      } else {
	if (z == z->parent->right){
	  z = z->parent;                // case 2
	  LeftRotate(z);                // case 2
	}
	z->parent->color = BLACK;       // case 3   
	z->parent->parent->color = RED; // case 3
	RightRotate(z->parent->parent); // case 3
      }
    } else {
      y = z->parent->parent->left;
      if(y->color == RED){
	z->parent->color = BLACK;       // case 4
	y->color = BLACK;               // case 4   
	z->parent->parent->color = RED; // case 4
	z = z->parent->parent;          // case 4
      } else {
	if(z == z->parent->left){
	  z = z->parent;                // case 5
	  RightRotate(z);               // case 5
	}
	z->parent->color = BLACK;       // case 6
	z->parent->parent->color = RED; // case 6
	LeftRotate(z->parent->parent);  // case 6 
      }
    }
  }
  root->color = BLACK;
}

// RB_RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
  if(u->parent == nil){
    root = v;
  } else if (u == u->parent->left){
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* x){
  while(x != root && x->color == BLACK){
    if(x == x->parent->left){
      Node* w = x->parent->right;
      if(w->color == RED){
	w->color = BLACK;                            // case 1
	x->parent->color = RED;                      // case 1
	LeftRotate(x->parent);                       // case 1
	w = x->parent->right;                        // case 1
      }
      if(w->left->color == BLACK && w->right->color == BLACK){
	w->color = RED;                              // case 2
	x = x->parent;                               // case 2
      } else {
	if(w->right->color == BLACK){
	  w->left->color = BLACK;                    // case 3
	  w->color = RED;                            // case 3
	  RightRotate(w);                            // case 3
	  w = x->parent->right;                      // case 3
	}
	w->color = x->parent->color;                 // case 4
	x->parent->color = BLACK;                    // case 4
	w->right->color = BLACK;                     // case 4
	LeftRotate(x->parent);                       // case 4
	x = root;                                    // case 4
      }
    } else {
      Node* w = x->parent->left;
      if(w->color == RED){
	w->color = BLACK;                            // case 5
	x->parent->color = RED;                      // case 5
	RightRotate(x->parent);                      // case 5
	w = x->parent->left;                         // case 5
      }
      if(w->right->color == BLACK && w->left->color == BLACK){
	w->color = RED;                              // case 6
	x = x->parent;                               // case 6
      } else {
	if(w->left->color == BLACK){
	  w->right->color = BLACK;                   // case 7
	  w->color = RED;                            // case 7
	  LeftRotate(w);                             // case 7
	  w = x->parent->left;                       // case 7
	}
	w->color = x->parent->color;                 // case 8
	x->parent->color = BLACK;                    // case 8
	w->left->color = BLACK;                      // case 8
	RightRotate(x->parent);                      // case 8
	x = root;                                    // case 8
      }
    }
  }
  x->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* z){
  Node* x;
  Node* y = z;
  int og_color = y->color;

  if(z == nil) return;
  if(z->left == nil){
    x = z->right;
    RB_Transplant(z, z->right);
  } else if (z->right == nil){
    x = z->left;
    RB_Transplant(z, z->left);
  } else {
    y = findMin(z->right);
    og_color = y->color;
    x = y->right;
    if(y->parent == z){
      x->parent = y;
    } else {
      RB_Transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    RB_Transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if(og_color == BLACK){
    RB_DeleteFixUp(x);
  }
  delete z;
  num_pairs--;
}


// Access functions --------------------------------------------------------

// Dictionary::size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
  return(num_pairs);
}

// Dictionary::contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
  if(num_pairs == 0) return(false);
  return(search(root, k) != nil);
}

// Dictionary::getValue()
// Returns a reference to the value corresponding to key k.
// Pre: Dictionary::contains(k)
valType& Dictionary::getValue(keyType k) const{
  if(!contains(k)){
    throw std::logic_error("Dictionary: getValue: Dictionary does not contain key k");
  }
  return(search(root, k)->val);
}

// Dictionary::hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
  return(current != nil);
}

// Dictionary::currentKey()
// Returns the current key.
// Pre: Dictionary::hasCurrent() 
keyType Dictionary::currentKey() const{
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: currentKey: current undefined");
  }
  return(current->key);
}

// Dictionary::currentVal()
// Returns a reference to the current value.
// Pre: Dictionary::hasCurrent()
valType& Dictionary::currentVal() const{
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: currentVal: current undefined");
  }
  return(current->val);
}


// Manipulation procedures -------------------------------------------------

// Dictionary::clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
  while(num_pairs > 0){
    //remove(root->key);
    RB_Delete(root);
  }
  current = nil;
}

// Dictionary::setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
  Node* y = nil;
  Node* x = root;
  while(x != nil){
    y = x;
    if(k < x->key){
      x = x->left;
    } else if (k > x->key){
      x = x->right;
    } else {
      // z->key == x->key
      x->val = v;
      RB_InsertFixUp(x);
      return;
    }
  }

  Node* z = new Node(k, v, nil);
  z->parent = y;
  if(y == nil){
    // tree was empty
    root = z;
  } else if (z->key < y->key){
    y->left = z;
  } else {
    y->right = z;
  }
  num_pairs++;
  z->left = nil;
  z->right = nil;
  z->color = RED;
  RB_InsertFixUp(z);
}

// Dictionary::remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: Dictionary::contains(k).
void Dictionary::remove(keyType k){
  Node* z = search(root, k);
  if(z == nil){
    throw std::logic_error("Dictionary: remove: Dictionary does not contain key k");
  }
 
  if(z == current) current = nil;
  if(z->left == nil){
    RB_Transplant(z, z->right);
  } else if (z->right == nil){
    RB_Transplant(z, z->left);
  } else {
    Node* y = findMin(z->right);
    if(y->parent != z){
      RB_Transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    RB_Transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
  }
  delete z;
  num_pairs--;
}

// Dictionary::begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
  if(num_pairs > 0) current = findMin(root);
}

// Dictionary::end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
  if(num_pairs > 0) current = findMax(root);
}

// Dictionary::next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: Dictionary::hasCurrent()
void Dictionary::next(){
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: next: current undefined");
  }  
  current = findNext(current);
}
// Dictionary::prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: Dictionary::hasCurrent()
void Dictionary::prev(){
  if(!hasCurrent()){
    throw std::logic_error("Dictionary: prev: current undefined");
  }
  current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// Dictionary::to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
  std::string str;
  inOrderString(str, root);
  return(str);
}

// Dictionary::pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
  std::string str;
  preOrderString(str, root);
  return(str);
}

// Dictionary::equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
  std::string thisStr, Dstr;
  inOrderString(thisStr, root);
  D.inOrderString(Dstr, D.root);
  return(thisStr == Dstr);
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
  return(stream << D.Dictionary::to_string());
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
  return(A.Dictionary::equals(B));
}
  
// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
  clear();
  std::string preOrderD, token;
  preOrderD = D.pre_string();
  size_t begin, end;
  
  begin = std::min(preOrderD.find_first_not_of("\n", 0), preOrderD.length());
  end = std::min(preOrderD.find_first_of("\n", begin), preOrderD.length());
  token = preOrderD.substr(begin, end-begin);
  while(token != ""){
    Node* node = D.search(D.root, token);
    if(node != nil) setValue(node->key, node->val);
    begin = std::min(preOrderD.find_first_not_of("\n", end+1), preOrderD.length());
    end = std::min(preOrderD.find_first_of("\n", begin), preOrderD.length());
    token = preOrderD.substr(begin, end-begin);
  }
  return(*this);
}

