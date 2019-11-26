// Hashing.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <iostream>

#include "EPI13.7_Sliding_Window.h"

int main() {
  file_smallest_sub_array({"apple", "banana", "apple", "apple", "dog", "cat",
                           "apple", "dog", "banana", "apple", "cat", "dog"},
                          {"banana", "cat"});
  return 0;
}
