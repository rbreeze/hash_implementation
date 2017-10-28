/**
 * @file hash.cpp   Hash Class function implementations.
 *
 * @brief Provides functions for the Hash class. 
 *        Includes default constructor and all other 
 *        Hash class functionality.
 *    
 *
 * @author Remington Breeze
 * @date 10/10/17
 */

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include "hash.h"

using std::endl;
using std::cout; 
using std::ofstream; 
using std::ifstream;

// default constructor, initializes hash table
Hash::Hash() {
  collisions = 0; 
  runningAvgListLength = 0; 
  longestList = 0; 
}

// removes an item from the hash table (function argument "word")
void Hash::remove(string word) {
  // generate key from search query
  int key = hf(word); 
  // iterate through list at key position and delete word
  for (list<string>::iterator i = hashTable[key].begin(); i != hashTable[key].end(); ++i) {
    if (*i == word) hashTable[key].erase(i);
  }
  // update runningAvgListLength
  double ca = currentAvgListLen(); 
  runningAvgListLength = (ca + runningAvgListLength) / 2.0;
  return;
}

// prints hash table
void Hash::print() {
  for (int j = 0; j < HASH_TABLE_SIZE; j++) {
    cout << j << ":\t"; 
    for (list<string>::iterator i = hashTable[j].begin(); i != hashTable[j].end(); ++i) {
      cout << *i << ", ";
    }
    cout << endl;
  }
}

// processes file and adds contents to hash table, uses string function argument as filename
void Hash::processFile(string filename) {
  // open the file at location "filename"
  ifstream file; 
  file.open(filename);
  string input; 
  // loop through the file
  while (file >> input) {
    // generate key for each word
    int key = hf(input);
    // update collisions count if there's a collision here
    if (hashTable[key].size() > 0) collisions++; 
    // push the word to it's correct location in the table
    hashTable[key].push_back(input);
    // update longestList if this list is now the biggest
    if (hashTable[key].size() > longestList) longestList = hashTable[key].size(); 
    // update runningAvgListLength
    double ca = currentAvgListLen(); 
    runningAvgListLength = (ca + runningAvgListLength) / 2.0;
  }
  file.close(); 
  return; 
}

// searches hash table for function argument "word" (a string)
bool Hash::search(string word) {
  // generate key from search query
  int key = hf(word); 
  if (hashTable[key].front() != "") {
    for (list<string>::iterator i = hashTable[key].begin(); i != hashTable[key].end(); ++i) {
      if (*i == word) return true; 
    } return false; 
  } else return false; 
}

// writes standard output to file, which is specified as a function argument
void Hash::output(string filename) {
  // create a file at location "filename"
  ofstream file; 
  file.open(filename);
    for (int j = 0; j < HASH_TABLE_SIZE; j++) {
    file << j << ":\t"; 
    for (list<string>::iterator i = hashTable[j].begin(); i != hashTable[j].end(); ++i) {
      file << *i << ", ";
    }
    file << endl;
  }
  file.close();
  return; 
}

// returns the load factor of the hash table
double Hash::loadFactor() {
  int load = 0; 
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    load+=hashTable[i].size(); 
  }
  return (double) load / HASH_TABLE_SIZE; 
}

double Hash::currentAvgListLen() {
  int totalItems = 0, nonEmptyLists = 0; 
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    totalItems += hashTable[i].size(); 
    if (!hashTable[i].empty())
      nonEmptyLists++; 
  }
  return (double) totalItems / nonEmptyLists; 
}

void Hash::printStats() {
  cout << "Total Collisions = " << collisions << endl;
  cout << "Longest List Ever = " << longestList << endl;
  cout << "Average List Length Over Time = " << runningAvgListLength << endl;
  cout << "Load Factor = " << loadFactor() << endl;
}