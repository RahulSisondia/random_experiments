#include <exception>

#include "../my_util.h"
/*
 Learings : Avoid using iterators in the itvw propblems.
 May get caught up in the syntex issues and difficult to
 get pointer right.
 Better have used two variable and accessed the vector v[inner][outer]
*/
class Vector2D {
 public:
  Vector2D(const vector<vector<int>>& v) {
    m_2ditr = v.cbegin();
    m_2ditr_end = v.cend();
    // Filter our the empty rows from the begining.
    while (m_2ditr != m_2ditr_end && m_2ditr->size() == 0) m_2ditr++;
    if (m_2ditr != m_2ditr_end) m_itr = m_2ditr->cbegin();
  }
  int next() {
    int value;
    if (m_2ditr == m_2ditr_end && m_itr == m_2ditr->cend())
      throw "Out of range";
    if (m_itr != m_2ditr->cend()) value = *m_itr++;
    while (m_2ditr != m_2ditr_end && m_itr == m_2ditr->cend()) {
      m_2ditr++;  // Filter out empty rows.
      if (m_2ditr != m_2ditr_end) m_itr = m_2ditr->cbegin();
    }
    return value;
  }
  bool hasNext() { return (m_2ditr != m_2ditr_end); }

 private:
  std::vector<int>::const_iterator m_itr;
  std::vector<vector<int>>::const_iterator m_2ditr;
  std::vector<vector<int>>::const_iterator m_2ditr_end;
};

void test_flatten_vector() {
  vector<vector<int>> v{{0}};
  // Warning : If you pass the vector {{0}} dirctly as argument then it will be
  // a temporary vector. It will be destroyed, hence invalidates the itrs
  Vector2D twodv(v);
  twodv.hasNext();
  twodv.next();
  PRINT_MSG;
}