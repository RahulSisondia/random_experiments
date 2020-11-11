#include "../my_util.h"

class Subset {
 public:
  vector<vector<int>> subsets(vector<int> &S) {
    vector<vector<int>> result;
    vector<int> current;
    sort(S.begin(), S.end());
    generateSubsets(S, 0, current, result);
    sort(result.begin(), result.end());
    return result;
  }
  void generateSubsets(const vector<int> &S, int index, vector<int> &current,
                       vector<vector<int>> &result) {
    if (index >= S.size()) {
      result.push_back(current);
      return;
    }
    // Handle the Repeating  value
    /* while ((index + 1 < S.size()) && S[index] == S[index + 1]) {
       index++;
     }*/
    // Ignore the current index.
    generateSubsets(S, index + 1, current, result);
    // Include the current index.
    current.push_back(S[index]);
    generateSubsets(S, index + 1, current, result);
    current.pop_back();
  }

  vector<vector<int>> subsets_2(vector<int> &S) {
    vector<vector<int>> result;
    vector<int> current;
    sort(S.begin(), S.end());
    generateSubsets_2(S, 0, current, result);
    sort(result.begin(), result.end());
    return result;
  }
  // If we don't pop the element that we included then create the copy of vector
  // for each subset by passning it by value.
  void generateSubsets_2(const vector<int> &S, int index, vector<int> current,
                         vector<vector<int>> &result) {
    if (index >= S.size()) {
      result.push_back(current);
      return;
    }
    // Handle the Repeating  value
    /* while ((index + 1 < S.size()) && S[index] == S[index + 1]) {
       index++;
     }*/
    // Ignore the current index.
    generateSubsets_2(S, index + 1, current, result);
    // Include the current index.
    current.push_back(S[index]);
    generateSubsets_2(S, index + 1, current, result);
  }

  // Here we are redusing the input vector. Not keeping track of index
  // explicitly. It doesn't look not so efficient approach. Sorted vector in
  // decreasing order first and have to pass the S as by value.
  vector<vector<int>> subsets_3(vector<int> &S) {
    vector<vector<int>> result;
    vector<int> current;
    sort(S.rbegin(), S.rend());
    generateSubsets_3(S, current, result);
    sort(result.begin(), result.end());
    return result;
  }
  void generateSubsets_3(vector<int> S, vector<int> current,
                         vector<vector<int>> &result) {
    if (S.size() == 0) {
      result.push_back(current);
      return;
    }
    auto op1 = current;
    auto op2 = current;
    op2.push_back(S.back());
    S.pop_back();
    // Exclude the current index.
    generateSubsets_3(S, op1, result);
    generateSubsets_3(S, op2, result);
  }
};

// Coding Puzzle solution
// We have to visulaize the subsets and print them with the help of loop.
class Subset_cp {
 public:
  vector<vector<int>> subsets(vector<int> &S) {
    vector<vector<int>> result;
    vector<int> current;
    sort(S.begin(), S.end());
    result.push_back(current);  // We have to push the empy subset here.
    generateSubsets(S, 0, current, result);
    sort(result.begin(), result.end());
    return result;
  }

  void generateSubsets(vector<int> &S, int index, vector<int> &current,
                          vector<vector<int>> &result) {
    if (index >= S.size()) {
      // result.push_back(current);
      return;
    }
    // Handle the Repeating  value
    /* while ((index + 1 < S.size()) && S[index] == S[index + 1]) {
       index++;
     }*/
    for (int i = index; i < S.size(); i++) {
      current.push_back(S[i]);
      result.push_back(current);
      generateSubsets(S, i + 1, current, result);
      current.pop_back();
    }
  }
};

void test_print_subset() {
  vector<int> vect{1, 2, 3};
  Subset_cp scp;
  CHECK(scp.subsets(vect),
        {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
  Subset s;
  CHECK(s.subsets(vect),
        {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
  CHECK(s.subsets_2(vect),
        {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
  CHECK(s.subsets_3(vect),
        {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}});
  PRINT_MSG;
}
