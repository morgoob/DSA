//-----------------------------------------------------------------------------
// Order.cpp
// pa7 client for Dictionary ADT
//
// Usage: ./Order <input file> <output file>
//
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

// printDict()
// Prints two string representations of the Dictionary to the output file.
// First: "key : value", in alphabetical order, one per line
// Second: keys only, one per line, order obtianed from pre-order tee walk  
void printDict(std::ofstream &, Dictionary &);

// Reads in lines of input file, each line being a unique string, then inserts
// the strings as keys into a Dictionary. The corresponding values are the
// line numbers
int main(int argc, char* argv[]){
  std::ifstream in;
  std::ofstream out;
  std::string line;
  std::string tokenBuffer;
  int line_count = 0;
  
  if(argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
    return(EXIT_FAILURE);
  }

  in.open(argv[1]);
  if(!in.is_open()){
    std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
    return(EXIT_FAILURE);
  }

  out.open(argv[2]);
  if(!out.is_open()){
    std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
  }

  Dictionary D;
  while(getline(in, line)){
    line_count++;
    D.setValue(line, line_count);
  }

  printDict(out, D);
  in.close();
  out.close();
  return(EXIT_SUCCESS);
}

// printDict()
// Prints two string representations of the Dictionary to the output file.
// First: "key : value", in alphabetical order, one per line
// Second: keys only, one per line, order obtianed from pre-order tee walk  
void printDict(std::ofstream &out, Dictionary &D){
  out << D.to_string() << std::endl;
  out << D.pre_string() << std::endl;
}
