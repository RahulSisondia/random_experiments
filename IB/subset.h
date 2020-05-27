#include <algorithm>
#include <vector>

using namespace std;

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
  void generateSubsets(vector<int> &S, int index, vector<int> &current,
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
};


// Coding Puzzle solution
class Subset_cp {
public:
  vector<vector<int>> subsets(vector<int> &S) {
    vector<vector<int>> result;
    vector<int> current;
    sort(S.begin(), S.end());
    generateSubsets(S, 0, current, result);
    sort(result.begin(), result.end());
    return result;
  }

  void generateSubsets(vector<int> &S, int index, vector<int> &current,
                       vector<vector<int>> &result) {
    if (index >= S.size()) {
      //result.push_back(current);
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
