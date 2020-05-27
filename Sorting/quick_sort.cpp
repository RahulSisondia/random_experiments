#include <iostream>
#include <vector>
using namespace std;

/*
  Best case :
  height of the tree :
  n/2/2/2/2 = 1
  n/2^k = 1
  n = 2^k
  k = log n.
  Steps at each level o(n).
  therefore complexity = O(n*logn)

  Worst case:
  height of the tree : n
  Steps at each level o(n).
*/
class Quick_sort {
 public:
  Quick_sort() {}

 private:
  vector<int> m_vect;
  /*
   Note : high is basically infinity here. It is the actual size of the array.
   First thing we do is to decrement it.
   inspired from : https://youtu.be/7h1s2SojIRw @ 12:53
   Read Wiki page as well - https://en.wikipedia.org/wiki/Quicksort
  */
  int partition_first_element(size_t low, size_t high) {
    int pivot = m_vect[low];
    auto i = low;
    auto j = high;
    while (i < j) {
      do {  // Keep on incrementing i till value is less than pivot.
        i++;
      } while (i < high && m_vect[i] < pivot);
      do {  // Keep on decressing i till value is greater than pivot.
        j--;
      } while (j >= low && m_vect[j] > pivot);
      if (i < j) swap(m_vect[i], m_vect[j]);
    }
    swap(m_vect[low], m_vect[j]);
    return j;
  }
  /*
    Paritioning with the lower or middle element doesn't make much difference.
    it is no better than choosing the first element as pivot.
    usually choosing median of the array performs better on almost sorted array.

  */
  int partition_middle_element(size_t low, size_t high) {
    // Just replace the midle element witht the first element and then do
    // partition as usual
    int mi = low + (high - low) / 2;
    swap(m_vect[mi], m_vect[low]);
    return partition_first_element(low, high);
  }

  void q_sort(size_t low, size_t high) {
    if (low < high) {
      auto middle = partition_first_element(low, high);
      q_sort(low, middle);
      q_sort(middle + 1, high);
    }
  }

 public:
  vector<int>& sort(vector<int> vect) {
    m_vect = vect;
    q_sort(0, m_vect.size());
    return m_vect;
  }
};

int main() {
  Quick_sort qs;
  for (int num : qs.sort({10, 3, 4, 1, 2, 6, 8, 7, 5, 9})) {
    cout << num << " ";
  }
  cout << endl;
  for (int num : qs.sort({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})) {
    cout << num << " ";
  }
  cout << endl;
  for (int num : qs.sort({10, 9, 8, 7, 6, 5, 4, 3, 2, 1})) {
    cout << num << " ";
  }
  cout << endl;
  for (int num : qs.sort({10, 9, 8, 7, -6, 5, -4, 3, 2, 1})) {
    cout << num << " ";
  }
  cout << endl;
  return 0;
}
