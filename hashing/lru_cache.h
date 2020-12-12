#pragma once
#include "../my_util.h"

/*
  Key learnings-
  1. We store the value in the map only. List is used to store only keys.
  2. There are implementation specific goatchas. if the key is already existing
    in the map then we just need to update the list itr. Don't erase it.
  3. We erase the elements from the map and list both when the size of it is
  full.
*/
class LRUCache {
 public:
  LRUCache(int capacity) : m_capacity(capacity) {}

  int get(int key) {
    auto itr(m_map.find(key));
    if (itr != m_map.end()) {
      m_list.erase(itr->second.first);
      m_list.push_front(key);
      itr->second.first = m_list.begin();
      return itr->second.second;
    }
    return -1;
  }

  void put(int key, int value) {
    auto itr(m_map.find(key));
    // Key is already existing
    if (itr != m_map.end()) {
      m_list.erase(itr->second.first);
      m_list.push_front(key);
      itr->second.first = m_list.begin();
      itr->second.second = value;
    } else {
      // Key doesn't exist. There could be two situations.
      if (m_map.size() < m_capacity) {
        // size < capacity
        m_list.push_front(key);
        Pair p = {m_list.begin(), value};
        m_map.emplace(key, p);
      } else {
        // size >= capacity. Remove the last element from the list and it's
        // reference from the map.
        m_map.erase(m_list.back());  // Erase the key, value from map.
        m_list.pop_back();           // Erase the key from the list
        m_list.push_front(key);
        Pair p = {m_list.begin(), value};
        m_map.emplace(key, p);
      }
    }
  }

 private:
  using Pair = pair<std::list<int>::iterator, int>;
  int m_capacity;
  // Stores the keys only
  std::list<int> m_list;
  // Stores the key and value
  unordered_map<int, pair<std::list<int>::iterator, int>> m_map;
};
/*
https://leetcode.com/problems/lru-cache/
*/
void test_lru_cache_146() {
  {
    /*
    ["LRUCache","put","put","get","put","get","put","get","get","get"]
   [[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]
    */
    LRUCache *lru_cache = new LRUCache(2);
    lru_cache->put(1, 1);
    lru_cache->put(2, 2);
    CHECK(lru_cache->get(1), 1);
    lru_cache->put(3, 3);
    CHECK(lru_cache->get(2), -1);
    lru_cache->put(4, 4);
    CHECK(lru_cache->get(1), -1);
    CHECK(lru_cache->get(3), 3);
    CHECK(lru_cache->get(4), 4);
    delete lru_cache;
  }
  { /*
    ["LRUCache","put","put","get","put","put","get"]
    [[2],[2,1],[2,2],[2],[1,1],[4,1],[2]]
    */
    LRUCache lru_cache(2);
    lru_cache.put(2, 1);
    lru_cache.put(2, 2);
    CHECK(lru_cache.get(2), 2);
    lru_cache.put(1, 1);
    lru_cache.put(4, 1);
    CHECK(lru_cache.get(2), -1);
  }
  {
    /*
    ["LRUCache","put","put","get","put","get","get"]
    [[2],[2,1],[1,1],[2],[4,1],[1],[2]]
    */
    LRUCache lru_cache(2);
    lru_cache.put(2, 1);
    lru_cache.put(1, 1);
    CHECK(lru_cache.get(2), 1);
    lru_cache.put(4, 1);
    CHECK(lru_cache.get(1), -1);
    CHECK(lru_cache.get(2), 1);
  }
  PRINT_MSG;
}