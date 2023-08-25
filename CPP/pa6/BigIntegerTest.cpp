//-----------------------------------------------------------------------------
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

// <function name>_test()
// Tests edge cases on all functions
void BigInteger_test();
bool sign_test(BigInteger &, int);
bool compare_test(BigInteger &, BigInteger &, int);
bool add_test(BigInteger &, BigInteger &, std::string);
bool sub_test(BigInteger &, BigInteger &, std::string);
bool mult_test(BigInteger &, BigInteger &,std::string);	      
bool makeZero_test(BigInteger &);

int main(){
  std::cout << "**********BigInteger Test**********" << std::endl;
  std::cout << "Test output will be redirected to 'output.txt'" << std::endl;

  BigInteger_test();
  return(EXIT_SUCCESS);
}

void BigInteger_test(){
  std::string bigint1 = "123456789123456789"; 
  std::string bigint2 = "-987654321987654321";
  std::string add_12 = "-864197532864197532";
  std::string sub_12 = "1111111111111111110";
  std::string sub_21 = "-1111111111111111110";
  std::string mult_12 = "-121932631356500531347203169112635269";

  BigInteger A, B;
  try {
    A = BigInteger(bigint1);
    B = BigInteger(bigint2);
  } catch (std::invalid_argument& e){
    std::cout << "Exception caught: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  
  std::ofstream out;
  std::string outfile = "output.txt";

  out.open(outfile);
  if(!out.is_open()){
    std::cerr << "Unable to open " << outfile << " for writing. Exiting..." << std::endl;
    return;
  }

  out << "**********BigInteger Test**********" << std::endl;

  out << std::endl << "**********sign() test**********" << std::endl;
  if(sign_test(A, 1)){
    out << "sign() test 1: PASSED" << std::endl;
  } else {
    out << "sign() test 1: FAILED" << std::endl;
  }
  if(sign_test(B, -1)){
    out << "sign() test 2: PASSED" << std::endl;
  } else {
    out << "sign() test 2: FAILED" << std::endl;
  }

  out << std::endl << "**********compare() test**********" << std::endl;
  if(compare_test(A, B, 1)){
    out << "compare() test 1: PASSED" << std::endl;
  } else {
    out << "compare() test 1: FAILED" << std::endl;
  }
  if(compare_test(B, A, -1)){
    out << "compare() test 2: PASSED" << std::endl;
  } else {
    out << "compare() test 2: FAILED" << std::endl;
  }
  if(compare_test(A, A, 0)){
    out << "compare() test 3: PASSED" << std::endl;
  } else {
    out << "compare() test 3: FAILED" << std::endl;
  }
  if(compare_test(B, B, 0)){
    out << "compare() test 3: PASSED" << std::endl;
  } else {
    out << "compare() test 3: FAILED" << std::endl;
  }
  
  out << std::endl << "**********add() test**********" << std::endl;
  if(add_test(A, B, add_12)){
    out << "add() test: PASSED" << std::endl;
  } else {
    out << "add() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********sub() test**********" << std::endl;
  if(sub_test(A, B, sub_12)){
    out << "sub() test 1: PASSED" << std::endl;
  } else {
    out << "sub() test 1: FAILED" << std::endl;
  }  
  if(sub_test(B, A, sub_21)){
    out << "sub() test 2: PASSED" << std::endl;
  } else {
    out << "sub() test 2: FAILED" << std::endl;
  }
  if(sub_test(A, A, "0")){
    out << "sub() test 3: PASSED" << std::endl;
  } else {
    out << "sub() test 3: FAILED" << std::endl;
  }
  if(sub_test(B, B, "0")){
    out << "sub() test 4: PASSED" << std::endl;
  } else {
    out << "sub() test 4: FAILED" << std::endl;
  }

  out << std::endl << "**********mult() test**********" << std::endl;
  if(mult_test(A, B, mult_12)){
    out << "mult() test: PASSED" << std::endl;
  } else {
    out << "mult() test: FAILED" << std::endl;
  }
  
  out << std::endl << "**********makeZero() test**********" << std::endl;
  if(makeZero_test(A)){
    out << "makeZero() test 1: PASSED" << std::endl;
  } else {
    out << "makeZero() test 1: FAILED" << std::endl;
  }
  if(makeZero_test(B)){
    out << "makeZero() test 2: PASSED" << std::endl;
  } else {
    out << "makeZero() test 2: FAILED" << std::endl;
  }
}

bool sign_test(BigInteger &A, int expected){
  return(A.sign() == expected);
}

bool compare_test(BigInteger &A, BigInteger &B, int expected){
  return(A.compare(B) == expected);
}

bool add_test(BigInteger &A, BigInteger &B, std::string expected){
  BigInteger add = A.add(B);
  std::string add_str = add.to_string();
  return(add_str == expected);
}

bool sub_test(BigInteger &A, BigInteger &B, std::string expected){
  BigInteger sub = A.sub(B);
  std::string sub_str = sub.to_string();
   // std::cout << "Expected: " << expected << std::endl;
  // std::cout << "Result: " << mult << std::endl; 
  return(sub_str == expected);
}

bool mult_test(BigInteger &A, BigInteger &B, std::string expected){
  BigInteger mult = A.mult(B);
  std::string mult_str = mult.to_string();
  // std::cout << std::endl << "Mult: " << std::endl;
  // std::cout << "Expected: " << expected << std::endl;
  // std::cout << "Result:   " << mult << std::endl;
  return(mult_str == expected);
}

bool makeZero_test(BigInteger &A){
  A.makeZero();
  return(A.sign() == 0);
}

