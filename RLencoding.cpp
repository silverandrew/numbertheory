//Code for COP 3503 Computer Programming for CS Majors II Lab/HW - Andrew Silver Problem 1. Code compiles. with g++ -std=c++0x -o p1 p1.cpp on Ubuntu 12.04 and with current stuff on Mac OS X. Implementation of RLE encoding for the Lab 3 for COP3503. Version 6.0 - includes working implementation of new-style encoding for COP 3503 HW 6. 1 + 1 = 2 ---> 11 + 11 = 12. Single digits get 1s before, and the no digit check was commented out.

//for more information, look up variations of the run-length encoding algorithm. for hello world, it prints he2lo world. for 1111, it prints 41, etc.

#include <iostream>

bool makestring(char* p1){
  bool result = false;
  while (*p1){ //as long as the cstring is not at the delimiting whitespace.
    if (!(*p1 - '0' < 10 && *p1 - '0' >= 0)){ //casts the element to an int. If it was a character, then the output would be not between 1 and 9, and this would execute (since it is ! ). If it was an int, then the output would be nonzero (the value of the int) and because of the ! this following code would not evaluate.
      result = true; //no number found, so good to go
    }
    else { //if there is a number in the list.
      result = false;
      break;
    }
    ++p1; //go to the next address to check
  }
  return result; //if there is a 0 digit in the cstring that is not the whitespace, then it will obviously return false, since a number exists, and it does not need to cycle through any more positions
}

//this function takes a pointer to element at index 0 of an array (a cstring). It will cycle through and determine the length.
unsigned int lengthstring(char* p2){
  unsigned int length = 0;
  while (*p2){ //as long as the value at the address the pointer points to is not the delimiter 0. i.e., as long as the pointer does not point to the end of the array. Note that this does not include the delimiting 0 at the end in the calculation, as expected by the sample output. This could be added by just setting length to 1 at the start.
    ++length;
    ++p2; //goes to the next address in the array
  }
  return length;
}

//function takes a cstring and replaces matching characters with the number of times they match
char* matchingstring(char* p3){
  int looptimes = 0; //the number of times the loop has occured through the values
  unsigned int length = 0; //length of the inputted cstring, which will be called from the function lengthstring
  char counting = '1'; //conversion for counter to a char to be stored
  int counter = 1; //the counter to track how many times the same element appears, starts at 1.
  char* repeat = p3; //tracker pointer to store the character that repeats, I don't want to increment the original array, copies address of p3 into repeat
  length = lengthstring(p3);
  char* output = new char[length]();
  char* array = output; //gets the value of the array, i.e., the address of the first element
  while (*p3){ //while not at the end of the array, i.e. the delimiter
    if (*(p3 + 1) == *p3){ //if the next element in the array is equal to the current
      while (*(p3 + 1) == *repeat && counter != 11){ //runs until the next element in the array is different than the current element and the numbers for counter are between 1 and 10
        ++counter; //increase the counter to determine the number of repeats
        ++p3; //moves p3 forward in the array to keep checking for more repeats
      }
      if (counter >= 11){ //if the counter is greater than 10, then add a 0 for the first ten and keep going
        *array = '0';
        ++array;
        *array = *p3;
      }
      else if (counter == 10){
        *array = '0';
      }
      else {
        counting = (counter + '0'); //converts the int counter to a character
        *array = counting;
      }
      ++array;
      *array = *repeat;
    }
    else if ( ((*p3 - '0' >= 0) && (*p3 - '0' < 10)) && ( ( (((*p3 - '0')/10 == 0 ) && (looptimes != 1) && (*(p3 + 1) == ' ' || *(p3 + 1) == '\0') )) || ( (*(p3 + 1) == ' ') && (*(p3 - 1) == ' ')) || ( (*(p3 +1) == '\0') && (*(p3 - 1) == ' ')))  ) { //additional implementation to RLE encoding. If there is a digit by itself, a 1 comes before it. The ' ' statements don't seem to work in the beginning of the pointer, so I created a "looptimes" variable that increments each time p3 goes to the next index. This means that this condition will always be false and I wouldn't have random '1's everywhere.
      *array = '1'; //1 digit found
      ++array;
      *array = *p3;
      ++p3; //goes to next index in P3
      *repeat = *p3; //resets repeat to current element at p3
      ++array; //goes to the next index position for the array
    }
    else { //base case, if no matches are found, i.e. if the next element is not equal to the current
      *array = *p3;
      ++p3; //go to the next index in p3
      *repeat = *p3;
      ++array; //goes to next index position for the array
    }
    counter = 1;
    looptimes = 1; //once past the first element of the cstring, no longer run the first if condition
  }
  *array = '\0'; //adds the delimiting character to the end, making this a cstring
  return output; //returns a pointer to the first element of a cstring. Since the array was default initialized to 0, the last element will be '0'.
}

int main(){

  int const buffer_size = 256; 
  char buffer[ buffer_size ];

  std::cout << "Type a sentence and press [RETURN], please." << std::endl;
  std::cin.getline( buffer, buffer_size ); //grab the input from the shell

  while (lengthstring(buffer)) //as long as pointer length does not equal 0, i.e. the null string
  {

    unsigned int originallength = lengthstring(buffer); //length of the original cstring, originally checklength
    unsigned int RLElength = 0; //length of the new cstring, which will be checked later

    char* RLE = matchingstring(buffer); //grabs a pointer to the first element of the RLE encoded version of the array, originally pointer
    RLElength = lengthstring(RLE); //checks the length of RLE version
    while (*RLE){ //while not at a delimeter
      std::cout << *RLE;
      ++RLE; //go to the next index position
    }
    std::cout << "" <<std::endl;
    if(originallength >= RLElength){ //if the RLE compressed version is shorter than the original
      std::cout << "The RLE version is " << (originallength - RLElength) << " shorter than the original" << std::endl;
    }
    else { //when using new style RLE compression, the RLElength could actually be longer. 
      std::cout << "The RLE version is " << (RLElength - originallength) << " longer than the original" << std::endl;
    }
    if (lengthstring(buffer)){
      delete []RLE; //deletes the memory allocated for the encoded array
    }
    std::cout << "Type a sentence and press [RETURN], please." <<std::endl;
    std::cin.getline( buffer, buffer_size );
  }
  return 0;
}
