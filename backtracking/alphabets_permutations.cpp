// Given an input string of numbers like 121, find all permutations of that
// number in the same order for the corresponding letters for each number so 121
// = > 1 2 1, 12 1, and 1 21 which is ABA, LA, and AT.

#include <iostream>
#include <map>
#include <vector>

using namespace std;

void find_permutations(string num, int index, vector<string>& set,
                       vector<vector<string>>& res) {
  if (index == num.size()) {
    res.push_back(set);
  }
  for (int i = 0; i < num.size(); i++) {
    if (i + 1 < num.size()) {
    }
  }
}

vector<vector<string>> permutations(std::string num) {
  std::map<int, char> alphabets;
  for (int i = 1; i <= 26; i++) {
    alphabets[i] = 'A' + i - 1;
  }

  vector<vector<string>> result;
  vector<string> set;
  return result;
}
int main() { return 0; }
