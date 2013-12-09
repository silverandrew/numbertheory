#include <iostream>

//odd - multiply by 3, add 1
//even - divide by 2
//check number of times it takes to get to 1
//andrew silver

/*
Collatz Conjecture - Start with a number n > 1. Find the number of steps it takes to reach one using the following process: If n is even, divide it by 2. If n is odd, multiply it by 3 and add 1. [EpicDavi (Python)][rramchand (Java)]
 */

//updates November 2013 - next implement using strings to allow for bigger numbers. this will be difficult because need to come up with a way to divide each "number" in a string digit by digit, same with multiplication

//idea - what if using multiple strings, once a number gets to a certain length, make another string for it? could also work on the palindromeconjecture.cpp

unsigned int divide(unsigned const int n,unsigned const int counter){

  if(n &0x1){ //if odd
    if(n == 1){
      return counter;
    }
         return divide (3*n + 1, counter+ 1); //recall function
  }

  else{ //if even
    return divide (n/2, counter + 1);
  }

}

int main(){

  unsigned int n = 1;
  while(n != 0){
  std::cout << "Enter a number greater than 0 to determine the number of steps to reach 1. Enter number 0 or less to quit." << std::endl;
  std::cin >> n;
  if(n > 0){
  unsigned const int counter = 0;
  std::cout << divide(n, counter) << std::endl;
  }
}

  return 0;
}
