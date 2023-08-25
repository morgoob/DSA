//-----------------------------------------------------------------------------
// DictionaryClient.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

#define NUM_KEYS 200
#define TESTS_PER_FN 5

// Dictionary_test()
// Calls all function tests and outputs to "output.txt"
void Dictionary_test();

// <function name>_test()
// Tests given Dictionary function, focuses on edge cases
bool size_test(std::ofstream &, Dictionary &, int);
bool contains_test(std::ofstream &, Dictionary &, keyType, bool);
bool getValue_test(std::ofstream &, Dictionary &, keyType, valType);
bool hasCurrent_test(std::ofstream &, Dictionary &, bool);
bool currentKey_test(std::ofstream &, Dictionary &, keyType);
bool currentVal_test(std::ofstream &, Dictionary &, keyType, valType);
bool setValue_test(std::ofstream &, Dictionary &, keyType, valType);
bool remove_test(std::ofstream &, Dictionary &, keyType);
bool begin_test(std::ofstream &, Dictionary &, keyType);
bool end_test(std::ofstream &, Dictionary &, keyType);
bool next_test(std::ofstream &, Dictionary &, keyType);
bool prev_test(std::ofstream &, Dictionary &, keyType);
bool equals_test(std::ofstream &, Dictionary &, Dictionary &, bool);
bool clear_test(std::ofstream &, Dictionary &);

int main(){
  std::cout << "**********Dictionary Test**********" << std::endl;
  std::cout << "Test output will be redirected to 'output.txt'" << std::endl;
  
  Dictionary_test();
  return(EXIT_SUCCESS);
}

void Dictionary_test(){
  std::ofstream out;
  std::string outfile = "output.txt";

  out.open(outfile);
  if(!out.is_open()){
    std::cerr << "Unable to open " << outfile << " for writing. Exiting..." << std::endl;
    return;
  }

  Dictionary D;
  
  out << "**********Dictionary Test**********" << std::endl;
  
  out << std::endl << "**********size() Test**********" << std::endl;
  if(size_test(out, D, 0)){
    out << "size() test 1: PASSED" << std::endl;
  } else {
    out << "size() test 1: FAILED" << std::endl;
  }
  for(int i = 0; i < NUM_KEYS; i++){
    D.setValue(std::to_string(i), i);
  }

  if(size_test(out, D, NUM_KEYS)){
    out << "size() test 2: PASSED" << std::endl;
  } else {
    out << "size() test 2: FAILED" << std::endl;
  }
  
  out << std::endl << "**********contains() Test**********" << std::endl;
  for(int i = 0; i < TESTS_PER_FN; i++){
    if(contains_test(out, D, std::to_string(i), true)){
      out << "contains() test " << i << ": PASSED" << std::endl;
    } else {
      out << "contains() test " << i << ": FAILED" << std::endl;
    }
  }
  out << std::endl << "**********next() Test**********" << std::endl;
  if(next_test(out, D, std::to_string(1))){
    out << "next() test: PASSED" << std::endl;
  } else {
    out << "next() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********prev() Test**********" << std::endl;
  if(prev_test(out, D, std::to_string(0))){
    out << "prev() test: PASSED" << std::endl;
  } else {
    out << "prev() test: FAILED" << std::endl;
  } 
  out << std::endl << "**********getValue() Test**********" << std::endl;
  for(int i = 0; i < TESTS_PER_FN; i++){
    if(getValue_test(out, D, std::to_string(i), i)){
      out << "getValue() test " << i << ": PASSED" << std::endl;
    } else {
      out << "getValue() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********hasCurrent() Test**********" << std::endl;
  D.begin();
  if(hasCurrent_test(out, D, true)){
    out << "hasCurrent() test: PASSED" << std::endl;
  } else {
    out << "hasCurrent() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********currentKey() Test**********" << std::endl;
  D.begin();
  for(int i = 0; i < TESTS_PER_FN; i++){
    if(currentKey_test(out, D, std::to_string(i))){
      out << "currentKey() test " << i << ": PASSED" << std::endl;
    } else {
      out << "currentKey() test " << i << ": FAILED" << std::endl;
    }
    D.next();
  }
  
  out << std::endl << "**********currentVal() Test**********" << std::endl;
  D.begin();
  for(int i = 0; i < TESTS_PER_FN; i++){
    if(currentVal_test(out, D, std::to_string(i), i)){
      out << "currentVal() test " << i << ": PASSED" << std::endl;
    } else {
      out << "currentVal() test " << i << ": FAILED" << std::endl;
    }
    D.next();
  }
  
  out << std::endl << "**********setValue() Test**********" << std::endl;
  for(int i = 0; i < TESTS_PER_FN; i++){
    if(setValue_test(out, D, std::to_string(NUM_KEYS +i), NUM_KEYS+i)){
      out << "setValue() test " << i << ": PASSED" << std::endl;
    } else {
      out << "setValue() test " << i << ": FAILED" << std::endl;
    }
  }
  
  out << std::endl << "**********begin() Test**********" << std::endl;
  if(begin_test(out, D, std::to_string(0))){
    out << "begin() test: PASSED" << std::endl;
  } else {
    out << "begin() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********end() Test**********" << std::endl;
  if(end_test(out, D, std::to_string(NUM_KEYS+TESTS_PER_FN))){
    out << "end() test: PASSED" << std::endl;
  } else {
    out << "end() test: FAILED" << std::endl;
  }

  out << std::endl << "**********remove() Test**********" << std::endl;
  for(int i = 0; i < NUM_KEYS; i++){
    if(remove_test(out, D, std::to_string(NUM_KEYS-i))){
      if(i%50 == 0) {
  	out << "remove() test " << i/50 << ": PASSED" << std::endl;
      }
    } else {
      out << "remove() test " << i/50 << ": FAILED" << std::endl;
    }
  }
  

  
  Dictionary E;
  out << std::endl << "**********equals() Test**********" << std::endl;
  if(equals_test(out, D, E, false)){
    out << "equals() test 1: PASSED" << std::endl;
  } else {
    out << "equals() test 1: FAILED" << std::endl;
  }
  E = D;
  if(equals_test(out, D, E, true)){
    out << "equals() test 1: PASSED" << std::endl;
  } else {
    out << "equals() test 1: FAILED" << std::endl;
  } 

  out << std::endl << "**********clear() Test**********" << std::endl;
  if(clear_test(out, D)){
    out << "clear() test: PASSED" << std::endl;
  } else {
    out << "clear() test: FAILED" << std::endl;
  }
 
}

bool size_test(std::ofstream &out, Dictionary &D, int expected){
  return(D.size() == expected);
}

bool contains_test(std::ofstream &out, Dictionary &D, keyType k, bool expected){
  return(D.contains(k) == expected);
}

bool getValue_test(std::ofstream &out, Dictionary &D, keyType k, valType expected){
  valType val = -1;
  try {
    val = D.getValue(k);
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(val == expected);
}

bool hasCurrent_test(std::ofstream &out, Dictionary &D, bool expected){
  return(D.hasCurrent() == expected);
}

bool currentKey_test(std::ofstream &out, Dictionary &D, keyType expected){
  keyType k = "Not the expected key";
  try {
    k = D.currentKey();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(k == expected);
}

bool currentVal_test(std::ofstream &out, Dictionary &D, keyType k, valType expected){
  valType v = -1;
  try {
    v = D.currentVal();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(v == expected);
}

bool setValue_test(std::ofstream &out, Dictionary &D, keyType k, valType v){
  if(D.contains(k)) D.remove(k);
  D.setValue(k, v);
  D.begin();
  return(D.contains(k));
}

bool remove_test(std::ofstream &out, Dictionary &D, keyType k){
  try {
    D.remove(k);
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  D.begin();
  return(!D.contains(k));
}

// parameter expected is first key in dictionary
bool begin_test(std::ofstream &out, Dictionary &D, keyType expected){
  keyType k = "Not the first key";
  D.begin();
  try{
    k = D.currentKey();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(k == expected);
}

// parameter expected is last key in dictionary
bool end_test(std::ofstream &out, Dictionary &D, keyType expected){
  keyType k = "Not the last key";
  D.end();
  try{
    k = D.currentKey();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(k == expected);
}

// Expected is the second key in the dictionary 
bool next_test(std::ofstream &out, Dictionary &D, keyType expected){
  keyType k = "Not expected key";
  D.begin(); 
  try {
    D.next();
    k = D.currentKey();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(k == expected);
}

// Expected is the first key in the dictionary
bool prev_test(std::ofstream &out, Dictionary &D, keyType expected){
  keyType k = "Not expected key";
  D.end();
  try {
    D.prev();
    k = D.currentKey();
  } catch(std::logic_error &e){
    out << "Exception caught: " << e.what() << std::endl;
    return(false);
  }
  return(k == expected);
}

bool equals_test(std::ofstream &out, Dictionary &D, Dictionary &E, bool expected){
  return(D.equals(E) == expected);
}

bool clear_test(std::ofstream &out, Dictionary &D){
  D.clear();
  return(D.size() == 0);
}
