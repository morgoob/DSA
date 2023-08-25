//-----------------------------------------------------------------------------
// BigInteger.cpp
// Implementation file for BigInteger ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "List.h"
#include "BigInteger.h"

// Global Constants -----------------------------------------------------------

const int POWER = 9;
const int BASE = 1000000000;

// Helper Function Prototypes -------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L);

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn);

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L);

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p);

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m);

// Class Constructors & Destructors -------------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
  signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
  if(s.length() == 0){
    throw std::invalid_argument("BigInteger: Constructor: empty string");
  }

  if(s[0] == '-'){
    signum = -1;
    s.erase(0, 1);
  } else if (s[0] == '+'){
    signum = 1;
    s.erase(0, 1);
  } else {
    signum = 1;
  }

  int strlen = s.length();
  int str_loops = strlen/POWER;
  int remainder = strlen%POWER;
  std::string substr;

  for(int i = 1; i <= str_loops; i++){
    substr = s.substr((strlen-i*POWER), POWER);
    for(int j = 0; j < POWER; j++){
      if(!isdigit(substr[j])){
	throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
      }
    }
    digits.moveFront(); 
    digits.insertBefore((ListElement) std::stol(substr));
  }
  
  if(remainder > 0){
    substr = s.substr(0, remainder);
    digits.moveFront();
    digits.insertBefore((ListElement) std::stol(substr));
  }
}
// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
  // Starts as zero state
  signum = 0;
  
  List N_digits = N.digits;
  int length = N_digits.length();
  
  N_digits.moveFront();
  while(N_digits.position() < length){
    digits.insertBefore(N_digits.moveNext());
  }
  signum = N.signum;
}

// Optional Destuctor
// ~BigInteger::BigInteger()
// ~BigInteger::BigInteger(){


// Access functions ---------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
  return(signum);
}

// compare()
// Returns -1, 1 or 0 according to whether *this* BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
  int comp = 0;
  ListElement this_LE, N_LE;
  List N_list = N.digits;
  List this_list = digits;

  // remove leading zeros from lists
  normalizeList(this_list);
  normalizeList(N_list);
  
  int N_length = N_list.length();
  int this_length = this_list.length();

  if(N.signum == -1 && signum == 1) return(1); 
  if(N.signum == 1 && signum == -1) return(-1);
  if(N.signum == 0 && signum == 0) return(0);
  
  if(this_length > N_length) {
    if(signum == -1){
      // this is a larger negative, therefore <
      return(-1);
    } else {
      // this is a larger positive, therefore >
      return(1);
    }
  } else if (N_length > this_length){
    if(signum == -1){
      // this is smaller negative, therefore >
      return(1);
    } else {
      // this is smaller positive, therefore <
      return(-1);
    }
  }
 
  this_list.moveFront();
  N_list.moveFront();
  while(comp == 0 && N_list.position() < N_length && this_list.position() < this_length){
    this_LE = this_list.moveNext();
    N_LE = N_list.moveNext();
    if(this_LE < N_LE){
      comp = -1; 
    } else if (this_LE > N_LE){
      comp = 1;
    }
  }

  if(signum == -1) comp*=-1;
  return(comp);
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
  signum = 0;
  digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
  signum = signum*-1;
}

// Helper Functions --------------------------------------------------------

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
  scalarMultList(L, -1);
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
  int carry = 0;
  List normalized;
  
  L.moveFront();
  while(L.position() < L.length()){
    if(L.moveNext() == (ListElement) 0){
      L.eraseBefore();
    } else {
      L.moveBack();
    }
  } 

  L.moveBack();
  while(L.position() > 0){
    long elmnt = (long) L.movePrev();
    if(elmnt > BASE){
      // subtract base, positive carry
      L.setAfter(elmnt-BASE+carry);
      carry = 1;
    } else if (elmnt < 0){
      // add base, negative carry
      L.setAfter(elmnt+BASE+carry);
      carry = -1;
    } else {
      // add previous carry, nothing else
      L.setAfter(elmnt+carry);
      carry = 0;
    }
  }
  
  if(carry == -1){
    return(-1);
  } else if (carry == 1){
    L.moveFront();
    L.insertBefore((ListElement) 1);
  }
  
  if(L.length() > 0){
    return(1);
  }
  return(0);
}

// normalizeListMult()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeListMult(List& L){
  int carry = 0;
  int base = 10;
  ListElement newLE;
  List normalized;

  L.moveFront();
  while(L.position() < L.length()){
    if(L.moveNext() == (ListElement) 0){
      L.eraseBefore();
    } else {
      break;
    }
  } 

  L.moveBack();
  while(L.position() > 0){
    long elmnt = (long) L.movePrev() + carry;
    //std::cout << "element + carry: " << elmnt << std::endl;
    if(elmnt >= base){
      // subtract base, positive carry
      carry = (elmnt/10)%10;
      newLE = (ListElement) elmnt-(base*carry);
      L.setAfter(newLE);
    } else if (elmnt < 0){
      // add base, negative carry
      carry = -1*((elmnt/10)%10);
      newLE = (ListElement) elmnt+(base*carry);
      L.setAfter(newLE);
    } else {
      // add previous carry, nothing else
      newLE = elmnt;
      L.setAfter(newLE);
      carry = 0;
    }
    //std::cout << "newLE: " << newLE << std::endl;
    //std::cout << "carry: " << carry << std::endl;
  }

  if(carry < 0) return(-1);
  if(carry != 0){
    L.moveFront();
    L.insertBefore((ListElement) carry);
    return(1);
  }
  return(1);
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
  S.clear();
  A.moveBack();
  B.moveBack();

  ListElement sum_LE;
  if(A.length() == 0 && B.length() == 0) return;
  while(A.position() > 0 && B.position() > 0){
    sum_LE = A.movePrev() + sgn*B.movePrev();
    S.moveFront();
    S.insertBefore(sum_LE);
  }
  while(A.position() > 0){
    S.moveFront();
    S.insertBefore(A.movePrev());
  }
  while(B.position() > 0){
    S.moveFront();
    S.insertBefore(sgn*B.movePrev());
  }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
  for(int i = 0; i < p; i++){
    L.moveBack();
    L.insertAfter((ListElement) 0);
  }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
  L.moveBack();
  while(L.position() > 0){
    ListElement elmnt = L.movePrev();
    L.setAfter(elmnt*m);
  }
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
  BigInteger add;
  int normalize;
  
  if(N.signum == -1 && signum == 1) {
    sumList(add.digits, digits, N.digits, -1);
    normalize = normalizeList(add.digits);
  } else if(N.signum == 1 && signum == -1) {
    sumList(add.digits, N.digits, digits, -1);
    normalize = normalizeList(add.digits);
  } else {
    sumList(add.digits, digits, N.digits, 1);
    normalize = normalizeList(add.digits);
    if(normalize != -1){
      add.signum = signum;
      return(add);
    }
  }

  if(normalize == -1){
    negateList(add.digits);
    normalizeList(add.digits);
    add.signum = -1;
  } else {
    add.signum = normalize;
  }
  return(add);
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
  BigInteger sub;
  int normalize;
  int comp = this->compare(N);

  if((signum == 0 && N.signum == 0) || comp == 0){
    sub.signum = 0;
    return(sub);
  }
  if(N.signum == -1 && signum == 1){
    // subtracting a negative -> add
    sumList(sub.digits, digits, N.digits, 1);
    normalize = normalizeList(sub.digits);
    sub.signum = 1;
  } else if (N.signum == 1 && signum == -1){
    // add and make sign negative
    sumList(sub.digits, digits, N.digits, 1);
    normalize = normalizeList(sub.digits);
    sub.signum = -1;
  } else if (signum == -1){
    // both negative 
    sumList(sub.digits, N.digits, digits, -1);
    normalize = normalizeList(sub.digits);
    sub.signum = comp;
  } else {
    // both positive
    sumList(sub.digits, digits, N.digits, -1);
    normalize = normalizeList(sub.digits);
    sub.signum = 1;
  }
  if(normalize == -1){
    negateList(sub.digits);
    normalizeList(sub.digits);
    sub.signum = -1;
  }
  
  return(sub);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
  int shift = 0;
  int scalarCount = 0;
  ListElement elmnt, scalar;
  List to_shift, prod, scalarMult, scalars;
  List N_digits = N.digits;
  List this_list = digits;
  if(signum == 0 || N.signum == 0){
    BigInteger mult;
    mult.signum = 0;
    return(mult);
  }

  N_digits.moveBack();
  while(N_digits.position() > 0){
    scalarCount = 0;
    elmnt = N_digits.movePrev();
    if(elmnt == 0) {
      for(int i = 0; i < POWER; i++){
	scalars.insertAfter(0);
      }
      scalarCount = POWER;
    }
    while(elmnt > 0){
      scalar = elmnt%10;
      elmnt /= 10;
      scalars.insertAfter(scalar);
      scalarCount++;
    }
    if(scalarCount < POWER){
      scalars.insertAfter(0);
    }
  }

  this_list.moveBack();
  while(this_list.position() > 0){
    elmnt = this_list.movePrev();
    if(elmnt == 0) to_shift.insertAfter((ListElement) 0);
    while(elmnt > 0){
      scalar = elmnt%10;
      elmnt /= 10;
      to_shift.insertAfter(scalar);
    }
  }

  //std::cout << "scalars: " << scalars << std::endl;
  // std::cout << "shifters: " << to_shift << std::endl;
  to_shift.moveBack();
  scalars.moveBack();
  while(scalars.position() > 0){
    scalar = scalars.movePrev();
    scalarMult = to_shift;
    //std::cout << std::endl << "Multiplying " << scalar << " times " << to_shift << std::endl;
    scalarMultList(scalarMult, scalar);
    //std::cout << "Result: " << scalarMult << std::endl;
    shiftList(scalarMult, shift);
    //std::cout << "After shift: " << scalarMult << std::endl;
    sumList(prod, prod, scalarMult, 1);
    //std::cout << "Before normalize: " << prod << std::endl;
    if(normalizeListMult(prod) == -1){
      negateList(prod);
      normalizeListMult(prod);
    }
    //std::cout << "After normalize: " << prod << std::endl;
    shift++;
  }
  //std::cout << prod.to_string() << std::endl;
  BigInteger mult = BigInteger(prod.to_string());
  if(signum == N.signum) {
    mult.signum = 1;
  } else {
    mult.signum = -1;
  }
  return(mult);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
  if(signum == 0) return "0";
  // remove leading zeros
  normalizeList(digits);
  
  std::string digit = "";
  std::string str = "";

  if(signum == -1) str += "-";
  int padding = 0;
  int length = digits.length();
  digits.moveFront();
  while(digits.position() < length){
    digit = std::to_string(digits.moveNext());
    // number of zeros to pad current ListElement with
    padding = POWER - digit.length();
    for(int i = 0; i < padding && digits.position() > 1; i++){
      str += "0";
    }
    str += digit;
  }
  return(str);
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
  return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
  if(A.BigInteger::compare(B) == 0) return(true);
  return(false);
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
  if(A.BigInteger::compare(B) == -1) return(true);
  return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
  int comp = A.BigInteger::compare(B);
  if(comp == -1 || comp == 0) return(true);
  return(false);
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
  if(A.BigInteger::compare(B) == 1) return(true);
  return(false);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
  int comp = A.BigInteger::compare(B);
  if(comp == 1 || comp == 0) return(true);
  return(false);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
  BigInteger add = A.BigInteger::add(B);
  return(add);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
   A = A.BigInteger::add(B);
  return(A);
 
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
  BigInteger sub = A.BigInteger::sub(B);
  return(sub);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
  A = A.BigInteger::sub(B);
  return(A);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
  BigInteger mult = A.BigInteger::mult(B);
  return(mult);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
  A = A.BigInteger::mult(B);
  return(A);
}


