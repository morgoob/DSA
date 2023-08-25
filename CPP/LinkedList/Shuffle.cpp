//-----------------------------------------------------------------------------
// Shuffle.cpp
// pa5 client for List ADT
//
// For each n in the range 1 to n, program will perform shuffles until the list
// (0, 1, ..., n-1) is brought back to original order
//
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "List.h"

// Alters List arg by performing ONE shuffle operation  
void shuffle(List&);

int main(int argc, char* argv[]){
  if(argc != 2){
    std::cerr << "Usage: " << argv[0] << " <# of cards>" << std::endl;
    return(EXIT_FAILURE);
  }

  int shuffle_count = 0;
  int n = std::stoi(argv[1]);
  List L, Lcopy;
  
  std::cout << "deck size" << '\t' << "shuffle count" << std::endl;
  std::cout << "------------------------------" << std::endl;

  for(int i = 0; i < n; i++){
    L.moveBack();
    L.insertAfter((ListElement) i);
    Lcopy = L;
    shuffle(L);
    shuffle_count = 1;
    while(!(Lcopy == L)){
      shuffle(L);
      shuffle_count++;
    }
    std::cout << " " << i+1 << '\t' << '\t' << " " << shuffle_count << std::endl; 
  }
}
void shuffle(List &D){
  List leftD, rightD;
  bool even = true;
  int length, halfLength;

  leftD.clear();
  rightD.clear();
  length = D.length();
  if(length%2 != 0) even = false;
  halfLength = length/2;
  for(int i = 0; i < halfLength; i++){
    leftD.insertBefore((ListElement) D.front());
    D.moveFront();
    D.eraseAfter();
  }
  for(int j = 0; j < halfLength; j++){
    rightD.insertBefore((ListElement) D.front());
    D.moveFront();
    D.eraseAfter();
  }
  if(!even && D.length() > 0 ) {
    rightD.insertBefore((ListElement) D.front());
    D.eraseAfter();
  }

  rightD.moveFront();
  leftD.moveFront();
  D.moveFront();
  for(int i = 0; i < halfLength; i++){
    if(i != 0) D.moveNext();
    D.insertAfter(rightD.moveNext());
    D.moveNext();
    D.insertAfter(leftD.moveNext());
  }
  if(!even){
    D.moveBack();
    D.insertAfter(rightD.back());
  }
}
