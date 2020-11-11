#include "../my_util.h"
/*
https://leetcode.com/problems/uncommon-words-from-two-sentences/
- If we don't wish to use stringstream them we can make a third string
C = A + " " + B
and parse that string to insert the tockens in the map.

*/
class Solution_884 {
 public:
  vector<string> uncommonFromSentences(string A, string B) {
    map<string, int> hash;
    vector<string> result;
    stringstream ss(A);
    string str;
    while (getline(ss, str, ' ')) {
      if (hash.find(str) != hash.end())
        hash[str] = hash[str] + 1;
      else
        hash[str] = 1;
    }
    // clear stringstream
    std::stringstream().swap(ss);
    str.clear();
    ss << B;
    while (getline(ss, str, ' ')) {
      if (hash.find(str) != hash.end())
        hash[str] = hash[str] + 1;
      else
        hash[str] = 1;
    }
    for (auto p : hash) {
      if (p.second == 1) result.emplace_back(p.first);
    }
    return result;
  }
};

void uncommon_words_884() {
  string A = "this apple is sweet";
  string B = "this apple is sour";
  Solution_884 s;

  CHECK(s.uncommonFromSentences(A, B), {"sour", "sweet"});
  cout << "uncommon_words_884 passed." << endl;
  return;
}