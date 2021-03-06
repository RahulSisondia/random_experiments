// find_closest_int.cpp : Defines the entry point for the console application.
//
#include <iostream>

unsigned int lowestBitNotSet(unsigned int x) { return ~x & (x + 1); }

unsigned int lowestBitSet(unsigned int x) { return x & ~(x - 1); }

unsigned int closestInt(unsigned int x) {
  unsigned int ns = lowestBitNotSet(x);
  unsigned int s = lowestBitSet(x);
  if (ns > s) {
    x |= ns;
    x ^= ns >> 1;
  } else {
    x ^= s;
    x |= s >> 1;
  }
  return x;
}

int main() { std::cout << closestInt(14) << std::endl; }
