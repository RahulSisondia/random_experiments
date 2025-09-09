#pragma once
#include "../my_util.h"

/*
(1) The main intuition is that if the value is the not found in an snapshot then
we need to locate that in the immediate previous snapshot that might contain
the value.
For that I used a map for binary search that stores the values in the descending
order so that lower_bound() could give the immediate next key
(2) emplace/insert don't update the value if key already exist.
Use the operator [] or insert_or_assign() API added in C++17. */
class SnapshotArray_1146 {
  /* key, {snapshot_id, value} */
  unordered_map<int, map<int, int, std::greater<>>> m_dict;
  int m_snapshot_id{0};

public:
  SnapshotArray_1146(int length) : m_dict(length) {}

  void set(int index, int val) { m_dict[index][m_snapshot_id] = val; }

  int snap() {
    int current_snapshot_id = m_snapshot_id++;
    return current_snapshot_id;
  }

  int get(int index, int snap_id) {
    auto snapshots = m_dict.find(index);
    if (snapshots != m_dict.end()) {
      auto itr = snapshots->second.lower_bound(snap_id);
      return itr->second;
    }
    return 0;
  }
};

void test_snapshot_array() {
  {
    SnapshotArray_1146 snapshotArr(3);
    snapshotArr.set(0, 5);
    CHECK(snapshotArr.snap(), 0);
    snapshotArr.set(0, 6);
    CHECK(snapshotArr.get(0, 0), 5);
  }
  {
    SnapshotArray_1146 snapshotArr(3);
    snapshotArr.set(0, 4);
    snapshotArr.set(0, 16);
    snapshotArr.set(0, 13);
    CHECK(snapshotArr.snap(), 0);
    CHECK(snapshotArr.get(0, 0), 13);
  }
  {
    SnapshotArray_1146 snapshotArr(3);
    snapshotArr.set(0, 15);
    CHECK(snapshotArr.snap(), 0);
    CHECK(snapshotArr.snap(), 1);
    CHECK(snapshotArr.snap(), 2);
    CHECK(snapshotArr.get(0, 2), 0);
  }
  PRINT_MSG;
}
