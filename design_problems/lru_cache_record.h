#include <fstream>

#include "../my_util.h"
/*
 Design and Implement the LRU in-memory cache for a text file search.
 Text file has number of lines(millions of the entries). Each line represent
 First Name, Last Name, Age. separated by the white spaces.
 - Design and implement an algorithm to search the data using first name and
    return all matched records.
 - Design should provide a way to keep most recent searched in cache.
 - Cache should be auto updated with the most recent searched and should also
   remove the least recent searches.
 - Cache size should be limited.
 - Provide the functionality to write/read cache to the file.
 - program should be initialized from the cache file. (if the cache file does
   not exists initialize the empty cache)

First name is the key.  There would be multiple values that match the key. We
need to return all of them.
- Flush the Cache Entries
- Read and Write from the file.
  - File could be
  {
      Rahul Sisondia 35
      Vivek Singh  32
      Atharv Kapoor 46
      Rahul Sharma  45
  }
 - Hmm should be able to searialize the records
*/
/*
 - Ideas for possible improvements
   - Input arg validation
   - A better implementation would have been using LFU + LRU. I realized that
 after I implemented the following solution.
   - It has a major assumption that last accessed record is evicted from the
 cache in case if it is full.
*/
class LRU_cache {
 public:
  LRU_cache(int capacity);
  void flush();  // Clear the cache

  void read(const std::string& file_path);
  // Write the cache entries to the file
  void write(const std::string& file_path);
  /*
    Adds the key and values to the cache.
    Key may have multiple values. There is no duplication check in the cache.
    Maximum values that could be stored upto the capacity specified in the
    beginning of initialzing cache.

    @param first_name [IN]  First name if the key.
    @param last_name [IN]   Last name
  */
  void put(const std::string first_name, const std::string last_name,
           const int age);
  /*
    Returns an array of records that matches all the records.
  */
  vector<string> get(const std::string first_name);

 private:
  struct Record {
    std::string first_name;
    std::string last_name;
    int age;
  };
  using llist_itr = std::list<std::list<Record>>::iterator;
  void update_cache(llist_itr& ll_itr, const std::string old_key,
                    const std::string first_name, const std::string last_name,
                    const int age);
  int m_capacity;
  int m_size;
  // For every key there is a list. That stores all the records pertatining to
  // that key.
  std::list<std::list<Record>> m_llist;
  /* key is the first name, value is the index of the list in the array of lists
   */
  unordered_map<std::string, llist_itr> m_lru;
};

LRU_cache::LRU_cache(int capacity)
    : m_capacity(capacity), m_size(0), m_llist(), m_lru() {}

/*
   (1) Assuming there could be duplicate entries with the same last_name and
   age. Since it is not specified in the problem stmt.
   (2) Assuming inputs are
   valid. Will add validations if time permits
   Learnings : Notice, we use std:end() to extract the last element
   of list of list.
 */
void LRU_cache::put(const std::string first_name, const std::string last_name,
                    const int age) {
  llist_itr ll_itr;
  auto map_itr(m_lru.find(first_name));
  std::string old_key;
  // There could be two situations now.
  // (1) key exists in the LRU
  if (map_itr != m_lru.end()) {
    ll_itr = map_itr->second;
    if (m_size == m_capacity) {
      old_key = ll_itr->back().first_name;
      ll_itr->pop_back();  // Evict the last node in this list.
    }
  } else {
    if (m_size == m_capacity) {
      ll_itr = std::prev(m_llist.end());
      old_key = ll_itr->back().first_name;
      ll_itr->pop_back();  // Evict the last node in this list.
    } else {
      m_llist.push_front(std::list<Record>());
      ll_itr = m_llist.begin();
      m_size++;
    }
  }
  update_cache(ll_itr, old_key, first_name, last_name, age);
}

vector<string> LRU_cache::get(const std::string first_name) {
  vector<string> result;
  auto lru_itr(m_lru.find(first_name));
  if (lru_itr != m_lru.end()) {
    auto lst = lru_itr->second;
    std::list<Record> new_list;
    for (auto lst_itr : *lst) {
      string record = lst_itr.first_name + " " + lst_itr.last_name + " " +
                      to_string(lst_itr.age);
      result.push_back(record);
      // The record accessed last should be the most accessed in the new list.
      new_list.push_front(lst_itr);
    }
    // Remove the last accessed list.
    m_llist.erase(lst);
    // Move the most recently accessed list in the begnning.
    m_llist.push_front(new_list);
    // Update the itrator in the map
    lru_itr->second = m_llist.begin();
  }
  return result;
}

void LRU_cache::update_cache(llist_itr& ll_itr, const std::string old_key,
                             const std::string first_name,
                             const std::string last_name, const int age) {
  if (ll_itr->empty()) {
    if (old_key.empty() == false) m_lru.erase(old_key);

    // Most recently accessed node is the first list in the list of lists
    m_llist.splice(m_llist.begin(), m_llist, ll_itr);
    // Most recently added node is at the front.
    m_llist.front().push_front({first_name, last_name, age});
    // update the LRU
    m_lru[first_name] = m_llist.begin();
  } else
    // Update the list.
    ll_itr->push_front({first_name, last_name, age});
}

void LRU_cache::flush() {
  m_lru.clear();
  m_llist.clear();
}

void LRU_cache::read(const std::string& file_path) {
  string line;
  ifstream file(file_path);
  string first_name;
  string last_name;
  string age;
  // Assuming file is valid. Is delimited by one spaces.
  // Will add validations if time permits.
  if (file.is_open()) {
    while (getline(file, line)) {
      auto pos = line.find_first_of(' ');
      first_name = line.substr(0, pos);
      auto new_pos = line.find(' ', pos + 1);
      last_name = line.substr(pos + 1, new_pos - pos + 1);
      new_pos = line.find(' ', new_pos + 1);
      age = line.substr(new_pos + 1);
      put(first_name, last_name, stoi(age));
    }
    file.close();
  } else
    cout << "Invalid File";  // Could throw exception as well.
}

void LRU_cache::write(const std::string& file_path) {
  ofstream file(file_path);
  if (file.is_open()) {
    for (auto lru_itr : m_lru) {
      for (const auto& record : get(lru_itr.first)) {
        file << record;
      }
    }
    file.close();
  } else
    cout << "Invalid File";  // Could throw exception as well.
}

void test_LRU_cache_record() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  LRU_cache lru_cache(2);
  lru_cache.put("Rahul", "Sisondia", 35);
  CHECK(lru_cache.get("Rahul"), {"Rahul Sisondia 35"});
  lru_cache.put("Vivek", "Sisondia", 35);
  lru_cache.put("Rahul", "Sharma", 12);
  CHECK(lru_cache.get("Rahul"), {"Rahul Sharma 12"});
  CHECK(lru_cache.get("Vivek"), {"Vivek Sisondia 35"});
  lru_cache.put("Atharv", "Singh", 23);
  CHECK(lru_cache.get("Vivek"), {"Vivek Sisondia 35"});
  CHECK(lru_cache.get("Rahul"), {});  // Since already evicted
  CHECK(lru_cache.get("Atharv"), {"Atharv Singh 23"});
  lru_cache.put("Vivek", "Sisondia", 35);
  CHECK(lru_cache.get("Vivek"), {"Vivek Sisondia 35"});
}