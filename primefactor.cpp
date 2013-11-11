/*

@author: Andrew Silver (with Ryan)
@assignment: practice for Exam 1
@date: September 28, 2013

Program to compute the prime factorization of a number. This can also test if a number is prime, because if n is prime, then the only prime factor of n should be n itself.

 */

#include <iostream>

int factor(const int n, int mod){
  if (mod <= n){ //if not at the end
    if (n % mod == 0){ //if mod is a factor -i.e. it divides evenly, it will be prime
    std::cout << mod << " ";
    return factor(n/mod, 2); //simplify the problem, restart at 2
  }
  else
    return factor(n, ++mod); //try dividing by the next-largest integer
  }
  std::cout << std::endl;
  return 0;
}

int main(){
  int n = 2; //input, must ge greater than or equal to 2
  int mod = 2; //what modding by
  std::cin >> n;
  factor(n, mod);
  return 0;
}
