#include <cctype>
#include <iostream>
#include <string>

bool is_capitalized(std::string str) {
  if (str.empty()) return false;
  if (str.length() == 1) {
    if (isalpha(str[0]))
      return true;
    else
      return false;
  }
  enum class State { CAPS, SMALL } state = State::SMALL;
  if (isupper(str[0])) {
    if (isupper(str[1])) state = State::CAPS;
  }
  for (size_t i = 1; i < str.size(); i++) {
    if (!isalpha(str[i])) return false;
    if (state == State::CAPS && islower(str[i])) return false;
    if (state == State::SMALL && isupper(str[i])) return false;
  }
  return true;
}
int main() {
  std::cout << (is_capitalized("") == false);
  std::cout << (is_capitalized("A") == true);
  std::cout << (is_capitalized("u") == true);
  std::cout << (is_capitalized("USA") == true);
  std::cout << (is_capitalized("Usa") == true);
  std::cout << (is_capitalized("usa") == true);
  std::cout << (is_capitalized("uSa") == false);
  std::cout << (is_capitalized("usA") == false);
  return 0;
}