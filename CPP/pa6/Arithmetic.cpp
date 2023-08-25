//-----------------------------------------------------------------------------
// Arithmetic.cpp
// pa6 client for BigInteger ADT
//
// Usage: ./Arithmetic <input file> <output file>
//
// by Morgan Lloyd, moclloyd@ucsc.edu
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "BigInteger.h"
#define MAX_LINES 2

// Calculates and prints to output file the following:
// A, B, A+B, A-B, A-A, 3A-2B, A*B, A*A, B*B, 9*A*A*A*A-16*B*B*B*B*B
void arithmetic(std::ofstream &, BigInteger &, BigInteger &);

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
  
  BigInteger A, B;
  while(getline(in, line) && line_count < MAX_LINES){
    if(line.length() > 0){
      line_count++;
      try{
	if(line_count == 1) {
	  A = BigInteger(line);
	} else {
	  B = BigInteger(line);
	}
      } catch(std::invalid_argument& e){
	std::cerr << "Exception caught: " << e.what() << std::endl;
	return(EXIT_FAILURE);
      }
    }
  }

  arithmetic(out, A, B);
  in.close();
  out.close();
  return(EXIT_SUCCESS);
}

// Calculates and prints to output file the following:
// A, B, A+B, A-B, A-A, 3A-2B, A*B, A*A, B*B, 9*A*A*A*A-16*B*B*B*B*B
void arithmetic(std::ofstream &out, BigInteger &A, BigInteger &B){
  // A
  out << A << std::endl << std::endl;
  
  // B
  out << B << std::endl << std::endl;
  
  // A+B
  out << A+B << std::endl << std::endl;
  
  // A-B
  out << A-B << std::endl << std::endl;
  
  // A-A
  out << A-A << std::endl << std::endl;

  // 3A-2B
  BigInteger three = BigInteger("3");
  BigInteger two = BigInteger("2");
  BigInteger threeA = A.mult(three);
  BigInteger twoB = B.mult(two);
  out << threeA-twoB << std::endl << std::endl;

  // A*B
  out << A*B << std::endl << std::endl;

  // A*A
  out << A*A << std::endl << std::endl;

  // B*B
  out << B*B << std::endl << std::endl;

  // 9A^4 + 16B^5
  BigInteger nineA4 = BigInteger("9")*A*A*A*A;
  BigInteger sixteenB5 = BigInteger("16")*B*B*B*B*B;
  out << nineA4+sixteenB5 << std::endl << std::endl;
}
