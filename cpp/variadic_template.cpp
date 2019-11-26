#include <iostream>
// https://eli.thegreenplace.net/2014/variadic-templates-in-c/
// pair_comparer accepts any number of arguments and returns true if and only if
// they are pair-wise equal. The types are not enforced - everything that can be
// compared goes. For example:

// pair_comparer(1.5, 1.5, 2, 2, 6, 6)
// Returns true. But if we change the second argument to just 1, this won't
// compile since a double and int are not the same type.

// More interestingly, pair_comparer will only work for an even number of
// arguments because they are peeled off in pairs and the base case compares
// two. The following:

// pair_comparer(1.5, 1.5, 2, 2, 6, 6, 7)

template <typename T>
bool pair_comparer(T a, T b) {
  return a == b;
}

template <typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
  return a == b && pair_comparer(args...);
}

int main() {
  std::cout << pair_comparer(1.5, 1.5, 2, 2, 6, 6) << "\n";
  return 0;
}