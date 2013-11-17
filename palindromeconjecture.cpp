//Andrew Silver, C++ attempt to implement the palindrome conjecture in number theory, crashes at 32,561.

//see http://mathworld.wolfram.com/PalindromicNumberConjecture.html for more inormation. Basic idea: can you take an integer, reverse all the digits, sum the original and reverse, and get a palindrome? if not, if you apply the operation an infite amount of times, would you get a palindrome? Code compiles November 10, 2013

//neat test case: 89 takes 24 steps

/*
for 196

operation # 40320
for this operation, sum is 										 and the size of the sum is 40322 digits.

*/


#include <iostream>
#include <vector>

//str1.compare(str2) == 0, they are equivalent
//str.size returns size

//note: 32561 seg faults, as does 196. By using strings exclusively for receiving the original number, avoiding integer overflow

//for 999999, which is divisible by 3 and 9, the last operation before seg faulting calculated 16703 digits with no palindrome.

std::string flip_string( std::string original ){ //create the forward string from a reverse string, or a reverse string from a forward string

  std::string flipped = ""; //the string that is the flipped string after the for lop

  for ( std::string::reverse_iterator itb = original.rbegin(); itb != original.rend(); ++itb ) { //create the forward integer string from the reversed integer string
    flipped.push_back (*itb); //concat the character
}
  return flipped; //return the flipped string
}

//check if a string is a palindrome
bool isPalindrome( std::string original ){
  std::string check = flip_string( original ); //return the flipped string
  if( original.compare(check) == 0 ){ //if the flipped string is the same as the original, i.e. it is a palindrome, return true, otherwise return false, it is not a palindrome. 0 if they are equivalent strings
    return true;
  }
  return false;
}

//reverse a string and add it
bool reverse_and_add ( std::string forward, std::size_t counter ){
  std::string reverse = flip_string(forward); //get forward integer string
  std::string result = ""; //final string, addition of integer with reversed integer
 std::string::reverse_iterator itb = reverse.rbegin(); //iterator through the reverse/backward string
 
 unsigned int cout = 0; //the sum from an addition, if the sum is >= 10, cout = 1
  for (std::string::reverse_iterator itf = forward.rbegin(); itf != forward.rend(); ++itf) { //iterate through the forward string and add the integers, starting at the final digit

    //process needs to happen recursively (and be implemented in the above method as well) starting at the last digit, if the sum of those digits is >= 10, it needs to carry over to the next sum
    //flip string for the final result

    std::size_t sum = ( *itf ) + ( *itb ); //convert each of the individual integer digits to integers and sum the digits
    if( cout == 1 ){ //cout from previous addition
      sum += 1; //add cout
      cout = 0; //set cout to 0 for the next call
    }
    if( sum > 9 ){ //if the sum is >= 10 and no cout
      cout = 1; //add one to account for the tens place, converting to a char, this will be added at the addition of the next digit
    result.push_back( sum % 10 ); //add the digit in the ones place, it is in the range 0 to 9 inclusive, not converting to a char
    }
    else{ //if 0 <= sum <= 9, just add the digit normally 
      result.push_back( sum ); //converting to a character, not converting to character
    }
    ++itb; //increase the reverse string iterator as well, note the forward and reverse are the same length
}
  if( cout == 1 ){ //if there is a final cout after all additions were performed as above
    result.push_back( 1 ); //add a 1 to indicate the carry out from the final addition
  }
  //after this operation is completed, the result will be in the reverse order since addition started at the last digit and was stored starting at that digit. Flip the result.
  std::string final = flip_string(result);

      for( std::string::iterator it = final.begin(); it != final.end(); ++it ){ //cycle through the string and store the integer versions inside the new string, when reading in as a string, it stores every digit as a character, which uses up unneeded memory. For small numbers, probably more efficient than converting integers to strings.
	std::cout << (*it ) << std::endl;
      }

  std::cout << "iteration # " << counter << std::endl;
  //std::cout << "for this operation, reverse string is " << reverse << std::endl;
  // std::cout << "for this operation, forward string is " << forward << std::endl;
  std::cout << "for this iteration, the size of the sum is " << final.size() << " digits." << std::endl;
  std::cout << "" << std::endl; //newline 

  if ( !isPalindrome( final ) ){ //not a palindrome, perform the operation again on the integer string
    return reverse_and_add( final, ++counter ); //call this function again, increase total number of operations performed
  }
  else{
    std::cout << "conjecture holds. reached a palindrome in " << counter << " steps." << std::endl;
    std::cout << "" << std::endl; //newline
    return true; //reached a palindrome, conjecture holds
  }

}
/*
if wanted to input an integer instead of a string, could use this method to convert from an int to a string, but inputting strings is better at the start - saves work
bool start(int check) { //n >= 10
 std::string reverse = ""; //reversed integer string
  std::string result = ""; //final string, addition of integer with reversed integer
  for (int n = check; n != 0; n /= 10 ){ //while n is not equal to 0, divide it by ten and perform the mod operation, compiling a string in the reverse order
    reverse += ( n % 10 ); //add the last element, getting closer to the first, to the string. n % 10 returns the last integer in the sequence, while dividing by 10 each time gets rid of the last digit
  }
  return reverse_and_add ( reverse, 1 ); //let the reverse_and_add method do the work, passing in the reverse string and the counter that tracks the number of steps to reach a palindrome
}
*/
//main selection for program. PRECONDITION - NO NEGATIVE NUMBERS! otherwise, "anything" can happen
int main(){
  bool selection = true;
  std::string input;
  std::string first; //first attempt

  while ( selection != false ) {
    std::cout << "Enter an integer >= 10 to test the palindrome conjecture. Enter q to quit. ";
    std::cin >> input; //read in input
    std::cout << " " << std::endl; //prints a new line
    if( input == "q" || input == "Q" ){ //user enters 0
      std::cout << "goodbye." << std::endl;
      selection = false;
    }
    else{ //quit not selected
      for( std::string::iterator it = input.begin(); it != input.end(); ++it ){ //cycle through the string and store the integer versions inside the new string, when reading in as a string, it stores every digit as a character, which uses up unneeded memory. For small numbers, probably more efficient than converting integers to strings.
	first.push_back( *it - '0' ); //convert old array characters to integers and store in the new string
	std::cout << (*it - '0' ) << std::endl;
      }
      if(input[0] == '-' ){ //if the user entered a negative number, the minus sign should be ignored, make a new string without the minus sign (there's probably a way to optimize when making the reverse string)
	std::string check = first.substr(1); //make a substring ignoring the minus sign and run the program with that
    reverse_and_add(check, 1); //test the conjecture on an integer
    }
      else{ //nonnegative, normal case
	reverse_and_add(first, 1); //test conjecture on an integer
      }
  }
  }

  return 0;

}
