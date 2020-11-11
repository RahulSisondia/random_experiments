#include <iostream>

#include "../my_util.h"

using namespace std;

std::string reverse_string(std::string str) {
  size_t start = 0;
  size_t end = str.size() - 1;
  while (start < end) {
    swap(str[start], str[end]);
    start++;
    --end;
  }
  return str;
}

void test_string_reverse() {
  CHECK(reverse_string("Cat"), std::string("taC"));
  CHECK(reverse_string("The Daily Byte"), std::string("etyB yliaD ehT"));
  CHECK(reverse_string("civic"), std::string("civic"));
}
int main() {
  test_string_reverse();
  return 0;
}