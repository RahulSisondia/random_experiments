#include <iostream>

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

int main() {
  cout << "Cat :" << reverse_string("Cat") << endl;
  cout << "The Daily Byte :" << reverse_string("The Daily Byte") << endl;
  cout << "civic :" << reverse_string("civic") << endl;
  return 0;
}