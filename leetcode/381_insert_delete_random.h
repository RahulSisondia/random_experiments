#pragma once
// https://leetcode.com/articles/insert-delete-getrandom-o1-duplicates-allowed/

#include <functional>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Randomized {
 public:
  Randomized();
  bool insert(int num);
  int get();
  void remove(int num);

 private:
  unordered_map<int, unordered_set<int>> m_map;
  vector<int> m_vect;
};

Randomized::Randomized() : m_map(), m_vect() {}

bool Randomized::insert(int num) {
  m_vect.emplace_back(num);
  m_map[num].emplace(m_vect.size() - 1);  // Store the index of the vector
  return false;
}

void Randomized::remove(int num) {
  auto map_itr = m_map.find(num);
  if (map_itr != m_map.end()) {
    auto itr = map_itr->second.begin();
    int num = *itr;
    if (itr != map_itr->second.end()) {
      // Replace the last vector element to the first. so that we can remove
      // last vector element.
      m_vect[*itr] = m_vect.back();
      // If there are multiple element in the vector then just remove the first
      // index from the set
      //Otherewise remove the entry from the map
      if (map_itr->second.size() > 1)
        map_itr->second.erase(itr);
      else
        m_map.erase(map_itr);
      // since we moved the last element in the beginning of vector. Therefore,
      // we must update the entry in the vector as well.
      m_map[m_vect[num]].erase(m_vect.size() - 1);
      m_map[m_vect[num]].emplace(num);
      m_vect.pop_back();
    }
  }
}

int Randomized::get() {
  default_random_engine re(std::random_device{}());
  uniform_int_distribution<size_t> dist{0, m_vect.size() - 1};
  auto rand = bind(dist, re);
  int indx = rand();
  return m_vect[indx];
}

// Below code implementation is picked from Leetcode. It is smilar to my code
// but much simplified.
class RandomizedCollection {
 public:
  /** Initialize your data structure here. */
  RandomizedCollection() {}

  /** Inserts a value to the collection. Returns true if the collection did not
   * already contain the specified element. */
  bool insert(int val) {
    bool ans = indices.find(val) == indices.end();
    indices[val].insert(values.size());
    values.push_back(val);
    return ans;
  }

  /** Removes a value from the collection. Returns true if the collection
   * contained the specified element. */
  bool remove(int val) {
    if (indices.find(val) != indices.end()) {
      size_t i = *indices[val].begin();
      if (indices[val].size() == 1) {
        indices.erase(val);
      } else {
        indices[val].erase(indices[val].begin());
      }
      if (i < values.size() - 1) {
        values[i] = values.back();
        indices[values[i]].erase(values.size() - 1);
        indices[values[i]].insert(i);
      }
      values.pop_back();
      return true;
    }
    return false;
  }

  /** Get a random element from the collection. */
  int get() {
    int num = values[rand() % values.size()];
    std::cout << num << endl;
    return num;
  }

 private:
  unordered_map<int, unordered_set<int>> indices;
  vector<int> values;
};

void test_381() {
  Randomized rd;
  // RandomizedCollection rd;
  rd.insert(1);
  rd.insert(1);
  rd.insert(2);
  rd.insert(5);
  rd.insert(7);
  unordered_set<int> values = {1, 2, 5, 7};  //"Possible values are 1, 2,5,7"
  for (int i = 0; i < 10; i++) {
    assert(values.find(rd.get()) != values.end());
  }
  rd.insert(3);
  rd.remove(1);
  rd.remove(1);
  values.erase(1);
  values.insert(3);

  // Possible values are 3,2,5,7
  for (int i = 0; i < 10; i++) {
    assert(values.find(rd.get()) != values.end());
  }

  rd.remove(3);
  rd.remove(1);
  values.erase(3);
  values.erase(1);
  // "Possible values are 2,5,7"
  for (int i = 0; i < 10; i++) {
    assert(values.find(rd.get()) != values.end());
  }
  cout << "test_381 passed" << endl;
}