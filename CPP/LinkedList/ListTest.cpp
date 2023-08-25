//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "List.h"
#define TESTS 5

// <function name>_test()
// Tests all functions outlined in List.cpp, focuses on edge cases
void List_test();
bool length_test(List &, int);
bool front_test(std::ofstream&, List &, ListElement);
bool back_test(std::ofstream&, List &, ListElement);
bool position_test(std::ofstream&, List &, int);
bool peekNext_test(std::ofstream&, List &, ListElement);
bool peekPrev_test(std::ofstream&, List &, ListElement);
bool clear_test(std::ofstream&, List &);
bool moveFront_test(std::ofstream&, List &);
bool moveBack_test(std::ofstream&, List &);
bool moveNext_test(std::ofstream&, List &);
bool movePrev_test(std::ofstream&, List &);
bool insertAfter_test(std::ofstream&, List &);
bool insertBefore_test(std::ofstream&, List &);
bool setAfter_test(std::ofstream&, List &);
bool setBefore_test(std::ofstream&, List &);
bool eraseAfter_test(std::ofstream&, List &);
bool eraseBefore_test(std::ofstream&, List &);
bool cleanup_test(std::ofstream&, List &);
bool equals_test(std::ofstream&, List &, List &, bool);

int main(){
  std::cout << "**********List Test**********" << std::endl;
  std::cout << "Test output will be redirected to 'output.txt'" << std::endl;

  List_test();
  return(EXIT_SUCCESS);
}

void List_test(){
  std::ofstream out;
  std::string outfile = "output.txt";

  out.open(outfile);
  if(!out.is_open()){
    std::cerr << "Unable to open " << outfile << " for writing. Exiting..." << std::endl;
    return;
  }

  List L;
  out << "**********List Test**********" << std::endl;

  out << std::endl << "**********length() Test**********" << std::endl;
  for(int i = 0; i <= TESTS; i++){
    if(i != 0){
      L.insertBefore((ListElement) i);
    }
    if(length_test(L, i)){
      out << "length() test " << i << ": PASSED" << std::endl;
    } else {
      out << "length() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********front() Test**********" << std::endl;
  if(front_test(out, L, (ListElement) 1)){
    out << "front() test: PASSED" << std::endl;
  } else {
    out << "front() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********back() Test**********" << std::endl;
  if(back_test(out, L, (ListElement) 5)){
    out << "back() test: PASSED" << std::endl;
  } else {
    out << "back() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********position() Test**********" << std::endl;
  L.moveFront();
  for(int i = 0; i < TESTS; i++){
    if(position_test(out, L, i)){
      out << "position() test " << i << ": PASSED" << std::endl;
    } else {
      out << "position() test " << i << ": FAILED" << std::endl;
    }
    L.moveNext();
  }
  
  out << std::endl << "**********peekNext() Test**********" << std::endl;
  L.moveFront();
  for(int i = 1; i < TESTS; i++){
    if(peekNext_test(out, L, (ListElement) i)){
      out << "peekNext() test " << i << ": PASSED" << std::endl;
    } else {
      out << "peekNext() test " << i << ": FAILED" << std::endl;
    }
    L.moveNext();
  }
  
  out << std::endl << "**********peekPrev() Test**********" << std::endl;
  L.moveBack();
  for(int i = TESTS; i > 0; i--){
    if(peekPrev_test(out, L, (ListElement) i)){
      out << "peekPrev() test " << i << ": PASSED" << std::endl;
    } else {
      out << "peekPrev() test " << i << ": FAILED" << std::endl;
    }
    L.movePrev();
  }
 
  out << std::endl << "**********moveFront() Test**********" << std::endl;
  if(moveFront_test(out, L)){
    out << "moveFront() test: PASSED" << std::endl;
  } else {
    out << "moveFront() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********moveBack() Test**********" << std::endl;
  if(moveBack_test(out, L)){
    out << "moveBack() test: PASSED" << std::endl;
  } else {
    out << "moveBack() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********moveNext() Test**********" << std::endl;
  L.moveFront();
  if(moveNext_test(out, L)){
    out << "moveNext() test: PASSED" << std::endl;
  } else {
    out << "moveNext() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********movePrev() Test**********" << std::endl;
  L.moveBack();
  if(movePrev_test(out, L)){
    out << "movePrev() test: PASSED" << std::endl;
  } else {
    out << "movePrev() test: FAILED" << std::endl;
  }

  out << std::endl << "**********insertAfter() Test**********" << std::endl;
  for(int i = 0; i < TESTS; i++){
    L.moveFront();
    if(insertAfter_test(out, L)){
      out << "insertAfter() test " << i << ": PASSED" << std::endl;
    } else {
      out << "insertAfter() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********insertBefore() Test**********" << std::endl;
  for(int i = 0; i < TESTS; i++){
    L.moveBack();
    if(insertBefore_test(out, L)){
      out << "insertBefore() test " << i << ": PASSED" << std::endl;
    } else {
      out << "insertBefore() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********setAfter() Test**********" << std::endl;
  for(int i = 0; i < TESTS; i++){
    L.moveFront();
    if(setAfter_test(out, L)){
      out << "setAfter() test " << i << ": PASSED" << std::endl;
    } else {
      out << "setAfter() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********setBefore() Test**********" << std::endl;
  for(int i = 0; i < TESTS; i++){
    L.moveBack();
    if(setBefore_test(out, L)){
      out << "setBefore() test " << i << ": PASSED" << std::endl;
    } else {
      out << "setBefore() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********eraseAfter() Test**********" << std::endl;

  L.moveFront();
  if(eraseAfter_test(out, L)){
    out << "eraseAfter() test: PASSED" << std::endl;
  } else {
    out << "eraseAfter() test: FAILED" << std::endl;
  }

  out << std::endl << "**********eraseBefore() Test**********" << std::endl;
  L.moveFront();
  L.moveNext();
  L.moveNext();
  L.moveNext();
  if(eraseBefore_test(out, L)){
    out << "eraseBefore() test: PASSED" << std::endl;
  } else {
    out << "eraseBefore() test: FAILED" << std::endl;
  }

  for(int i = 0; i < 5*TESTS; i++) {
    L.insertBefore((ListElement) 56);
    L.insertBefore((ListElement) 4);
  }
  L.moveFront();
  L.moveNext(); L.moveNext(); L.moveNext(); L.moveNext();
 
  out << std::endl << "**********cleanup() Test**********" << std::endl;
  if(cleanup_test(out, L)){
    out << "cleanup() test: PASSED" << std::endl;
  } else {
    out << "cleanup() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********equals() Test**********" << std::endl;
  List M = L;
  if(equals_test(out, L, M, true)){
    out << "equals() test: PASSED" << std::endl;
  } else {
    out << "equals() test: FAILED" << std::endl;
  }
 
  out << std::endl << "**********clear() Test**********" << std::endl;
  if(clear_test(out, L)){
    out << "clear() test: PASSED" << std::endl;
  } else {
    out << "clear() test: FAILED" << std::endl;
  }
  
  out.close();
}

bool length_test(List &L, int expected){
  return(L.length() == expected);
}

bool front_test(std::ofstream &out, List &L, ListElement expected){
  ListElement element;
  try{
    element = L.front();
  }catch(std::length_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool back_test(std::ofstream &out,  List &L, ListElement expected){
  ListElement element;
  try{
    element = L.back();
  }catch(std::length_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool position_test(std::ofstream &out,  List &L, int expected){
  return(L.position() == expected);
}

bool peekNext_test(std::ofstream &out,  List &L, ListElement expected){
  ListElement element;
  try{
    element = L.peekNext();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool peekPrev_test(std::ofstream &out,  List &L, ListElement expected){
  ListElement element;
  try{
    element = L.peekPrev();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool clear_test(std::ofstream &out,  List &L){
  L.clear();
  if(L.length() != 0) return(false);
  return(true);
}

bool moveFront_test(std::ofstream &out,  List &L){
  L.moveFront();
  if(L.position() != 0) return(false);
  return(true);
}

bool moveBack_test(std::ofstream &out,  List &L){
  L.moveBack();
  if(L.position() != L.length()) return(false);
  return true;
}

bool moveNext_test(std::ofstream &out,  List &L){
  ListElement expected, element;
  try{
    expected = L.peekNext();
    element = L.moveNext();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool movePrev_test(std::ofstream &out,  List &L){
  ListElement expected, element;
  try{
    expected = L.peekPrev();
    element = L.movePrev();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(element == expected);
}

bool insertAfter_test(std::ofstream &out,  List &L){
  ListElement element = 5;
  L.insertAfter(element);
  return(peekNext_test(out, L, element));
}

bool insertBefore_test(std::ofstream &out,  List &L){
  ListElement element = 4;
  L.insertBefore(element);
  return(peekPrev_test(out, L, element));
}

bool setAfter_test(std::ofstream &out,  List &L){
  ListElement element = 18;
  try{
    L.setAfter(element);
  }catch(std::range_error& e){
    out << "Excpetion caught: " << e.what() << std::endl;
    return(false);
  }
  return(peekNext_test(out, L, element));
}

bool setBefore_test(std::ofstream &out,  List &L){
  ListElement element = 18;
  try{
    L.setBefore(element);
  }catch(std::range_error& e){
    out << "Excpetion caught: " << e.what() << std::endl;
    return(false);
  }
  return(peekPrev_test(out, L, element));
}

bool eraseAfter_test(std::ofstream &out,  List &L){
  ListElement erased;
  int lengthBefore = L.length();
  try{
    erased = L.peekNext();
    L.eraseAfter();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  bool eq = L.length() == lengthBefore - 1;
  return eq && (!peekNext_test(out, L, erased)); 
}

bool eraseBefore_test(std::ofstream &out,  List &L){
  int lengthBefore = L.length();
  int posBefore = L.position();
  try{
    L.eraseBefore();
  }catch(std::range_error& e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  bool eq = L.length() == lengthBefore - 1;
  eq = eq && L.position() == posBefore - 1;
  return eq; 

}

bool cleanup_test(std::ofstream &out,  List &L){
  L.cleanup();
  return(true);
}

bool equals_test(std::ofstream &out,  List &L, List &M, bool expected){
  return((L == M) == expected);
}

