#include <algorithm>  // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap

#include "../my_util.h"

int main() {
  int myints[] = {10, 20, 30, 5, 15};
  std::vector<int> v(myints, myints + 5);
  PRINTV("Before making heap:");
  PRINT(v);
  std::make_heap(v.begin(), v.end());
  PRINTV("After making heap:");
  PRINT(v);
  PRINTV("initial max heap : ", v.front());
  /*
  Rearranges the elements in the heap range [first,last) in such a way that the
  part considered a heap is shortened by one: The element with the highest value
  is moved to (last-1).
   Move the first element to end of the vector.
  */
  std::pop_heap(v.begin(), v.end());
  v.pop_back();
  PRINTV("max heap after pop : ", v.front());
  v.push_back(99);
  std::push_heap(v.begin(), v.end());
  PRINTV("max heap after push: ", v.front());
  PRINTV("Before Sorting:");
  PRINT(v);
  // Apply heap sort on the container. Before this call the container maintains
  // the heap properties. All of them are lost.
  std::sort_heap(v.begin(), v.end());

  PRINTV("Sorted container:");
  PRINT(v);
  std::make_heap(v.begin(), v.end(), [](const auto& arg1, const auto& arg2) {
    if (arg1 > arg2) return true;
    return false;
  });
  PRINTV("initial min heap   : ", v.front());
  return 0;
}
