/**
 * @file hash_function.cpp   Custom hash function implementation.
 *
 * @brief Provides my personal implementation of a 
 *        Hash function. Uses a combination of
 *        multiplication and division methods. 
 *
 * @author Remington Breeze
 * @date 10/10/17
 */

/* This assignment originated at UC Riverside.*/

/** 
 * My hashing function uses a combination of multiplcation and modulus methods.
 * It first converts the string input into a large integer.
 * Then it divides this number to make it easier to work with, and multiplies it by
 *   an arbitrary constant. 
 * It then takes the fractional component of the result, multiplies it by another 
 *   arbitrary constant, and returns the value of it modulus the hash table size.
 * Although the multiplication method takes more resources, my hash function is still 
 *   O(1) and has a uniform distribution. 
 *
 * I used the notes from http://www.ecst.csuchico.edu/~jchallinger/1718F-csci311/notes/12-hashTables.html
 *   to help me create my function. 
 */
 
#include <string>
#include <math.h>
#include <iostream>
#include "hash.h"

using std::string;

int Hash::hf ( string ins ) {
  long key = 0, j = 0; 
  for (int i = ins.length(); i > 0; i--) {
    key += (long) ins[j] * pow(128, i);
    j++;
  }
  key = key / pow(10, ins.length()*2); 
  // constant = sqrt(pi) / 2
  float constant = 0.886226925; 
  // multiply key by constant
  float step_one = key * constant; 
  // take fractional component of step_one
  float fraction = step_one - floor(step_one); 
  // multiply fractional component by m and take floor
  int step_two = floor(fraction * HASH_TABLE_SIZE); 
  // multiply by 10 pi and modulo
  return (int) (step_two * 3.14159265 * 10) % HASH_TABLE_SIZE;

}

