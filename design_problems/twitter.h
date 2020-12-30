#pragma once
#include "../my_util.h"

class Twitter {
 public:
  /** Initialize your data structure here. */
  Twitter() {}

  /** Compose a new tweet. */
  void postTweet(int userId, int tweetId) {
    pair<int, int> p{++counter, tweetId};
    auto& dq = tweets_map[userId];
    if (dq.size() == 10) {
      dq.pop_back();
    }
    dq.push_front(p);
  }

  /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item
   * in the news feed must be posted by users who the user followed or by the
   * user herself. Tweets must be ordered from most recent to least recent. */
  vector<int> getNewsFeed(int userId) {
    vector<int> result;
    auto user_itr = tweets_map.find(userId);
    auto following_itr = follow_map.find(userId);
    using P = pair<int, int>;
    struct DQ_itr {
      bool operator>(const DQ_itr& that) {
        // first variable is the timestamp
        return current->first < that.current->first;
      }
      deque<P>::const_iterator current;
      deque<P>::const_iterator end;
    };
    priority_queue<DQ_itr, vector<DQ_itr>, greater<>> min_heap;
    if (user_itr != tweets_map.end())
      min_heap.push(DQ_itr{user_itr->second.cbegin(), user_itr->second.cend()});

    if (following_itr != follow_map.end()) {
      for (auto& user : following_itr->second) {
        auto itr = tweets_map.find(user);
        if (itr != tweets_map.end()) {
          min_heap.push(DQ_itr{itr->second.cbegin(), itr->second.cend()});
        }
      }
    }
    while (!min_heap.empty()) {
      auto dq_itr = min_heap.top();
      min_heap.pop();
      if (dq_itr.current != dq_itr.end) {
        result.push_back(dq_itr.current->second);
        min_heap.push({next(dq_itr.current), dq_itr.end});
      }
      if (result.size() == 10) break;
    }
    return result;
  }

  /** Follower follows a followee. If the operation is invalid, it should be a
   * no-op. */
  void follow(int followerId, int followeeId) {
    if (followerId != followeeId) follow_map[followerId].emplace(followeeId);
  }

  /** Follower unfollows a followee. If the operation is invalid, it should be a
   * no-op. */
  void unfollow(int followerId, int followeeId) {
    auto itr = follow_map.find(followerId);
    if (itr != follow_map.end()) {
      auto fwee_itr = itr->second.find(followeeId);
      if (fwee_itr != itr->second.end()) itr->second.erase(fwee_itr);
    }
  }

 private:
  int counter = 0;
  unordered_map<int, unordered_set<int>> follow_map;
  /* pair of counter, tweetId */
  unordered_map<int, deque<pair<int, int>>> tweets_map;
};

void check_twitter() {
  /**
   * Your Twitter object will be instantiated and called as
   * such: Twitter* obj = new Twitter();
   * obj->postTweet(userId,tweetId);
   * vector<int> param_2 = obj->getNewsFeed(userId);
   * obj->follow(followerId,followeeId);
   * obj->unfollow(followerId,followeeId);
   */

  Twitter tw;
  tw.postTweet(1, 11);
  CHECK(tw.getNewsFeed(1), {11});
  tw.follow(1, 2);
  tw.postTweet(2, 21);
  tw.postTweet(1, 12);
  tw.postTweet(2, 22);
  tw.postTweet(1, 13);
  tw.follow(1, 3);
  tw.follow(1, 4);
  for (int i = 0; i < 7; i++) {
    tw.postTweet(4, 40 + i);
  }
  CHECK(tw.getNewsFeed(1), {46, 45, 44, 43, 42, 41, 40, 13, 22, 12});
  tw.unfollow(1, 4);
  CHECK(tw.getNewsFeed(1), {13, 22, 12, 21, 11});
  PRINT_MSG;
}