#include <iostream>

//compute factorial recursively
int factorial(unsigned int n){

if (n == 0){ //base case
return 1;
}
else{ //not at 0, compute the factorial
return n * factorial(n - 1);
}

}

int main(){
std::cout << factorial(3) << std::endl;
return 0;

}
