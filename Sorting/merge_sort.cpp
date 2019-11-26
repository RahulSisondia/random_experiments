// Sorting.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Merge_sort {
public:
  void merge(vector<int> &vect, vector<int> &v1, vector<int> &v2) {
    int i1 = 0, i2 = 0;
    vect.clear();
    while (i1 < v1.size() && i2 < v2.size()) {
      if (v1[i1] < v2[i2]) {
        vect.push_back(v1[i1]);
        i1++;
      } else {
        vect.push_back(v2[i2]);
        i2++;
      }
    }
    while (i1 < v1.size()) {
      vect.push_back(v1[i1]);
      i1++;
    }
    while (i2 < v2.size()) {
      vect.push_back(v2[i2]);
      i2++;
    }
  }

  void sort(vector<int> &vect) {
    if (vect.size() < 2)
      return;
    auto middle = vect.size() / 2;
    vector<int> v1, v2;

    for (auto i = 0; i < middle; i++)
      v1.push_back(vect[i]);
    for (auto i = middle; i < vect.size(); i++)
      v2.push_back(vect[i]);
    sort(v1);
    sort(v2);
    merge(vect, v1, v2);
  }
};

int main() {
  vector<int> vect{4, 2, 4, 1, 0, 10, 8};
	Merge_sort ms;
    ms.sort(vect);
	std::copy(vect.begin(), vect.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

}
