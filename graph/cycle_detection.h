#include "../my_util.h"
/*
https://leetcode.com/problems/course-schedule-ii/

There are a total of n courses you have to take labelled from 0 to n - 1.

Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi]
this means you must take the course bi before the course ai.

Given the total number of courses numCourses and a list of the prerequisite
pairs, return the ordering of courses you should take to finish all courses.

If there are many valid answers, return any of them. If it is impossible to
finish all courses, return an empty array.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should
have finished course 0. So the correct course order is [0,1]. Example 2:

Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should
have finished both courses 1 and 2. Both courses 1 and 2 should be taken after
you finished course 0. So one correct course order is [0,1,2,3]. Another correct
ordering is [0,2,1,3]. Example 3:

Input: numCourses = 1, prerequisites = []
Output: [0]
*/

/*
 We learn to  print the path and detect cycle using topological sort.
 I implemented both.  Refer Alien dictionary code, there I choose visited
 structure as map. It is simplified further.
*/

class Solution_210 {
 public:
  bool dfs(vector<vector<int>>& graph, int node, vector<int>& visited,
           vector<int>& result) {
    visited[node] = 1;  // Colored Grey
    // cout << "Node Colored Grey " << node << endl;
    for (int i = 0; i < graph[node].size(); i++) {
      if (visited[graph[node][i]] == 1)
        return true;
      else if (visited[graph[node][i]] == 0)
        if (dfs(graph, graph[node][i], visited, result)) return true;
    }
    visited[node] = 2;  // Colored black
    // cout << "Node Colored Black " << node << endl;
    result.push_back(node);
    return false;
  }
  /*
   Solution#1
   This is recursive DFS solution using the graph coloring. We will have to have
   loop to cover all forests.
  */
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> result;
    vector<int> visited(numCourses, 0);
    bool deadlock = false;
    for (int i = 0; i < prerequisites.size(); i++) {
      // We are given graph in the form of edge list. Make Adjancency list first
      //[3,1] indicates  1 --> 3
      graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }
    /*
      when used for topological sort you do a DFS on every nodes. If one of the
      children is already visited by a previous DFS (colored black). Then it is
      already pushed in the output vector and so you the dependency is already
      done.
    */
    for (int i = 0; i < graph.size(); i++) {
      if (deadlock || visited[i] == 1) {
        // cout << "Cycle detected \n";
        break;
      }
      if (visited[i] == 0) {
        deadlock = dfs(graph, i, visited, result);
      }
    }
    if (deadlock) result.clear();
    reverse(result.begin(), result.end());
    return result;
  }
  /*
   Solution#2 is iterative DFS approach. It is using indegree approach. It is
   relatively simple. Just do the usual topological sort. If the size of the
   result set is not as expected that means there were a cycle.
   Note#1 - We don't have to have separate visited structure.
   Note#2 - We could use BFS as well. Why does the queue work? Because we are
   adding only children who have no incoming edge. What if we would need to
   detect the nodes where the cycle discovered? In that, I would have preferred
   the iterative approach in the deadlock_detection.h
  */
  vector<int> findOrder_indegree_dfs(int numCourses,
                                     vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> result;
    vector<int> indegree(numCourses, 0);
    for (int i = 0; i < prerequisites.size(); i++) {
      // [3,1] indicates  1 --> 3
      graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
      indegree[prerequisites[i][0]]++;
    }
    vector<int> stack;
    for (int i = 0; i < indegree.size(); i++) {
      if (indegree[i] == 0) stack.push_back(indegree[i]);
    }

    while (stack.empty() == false) {
      int node = stack.back();
      stack.pop_back();
      result.push_back(node);
      for (int i = 0; i < graph[node].size(); i++) {
        indegree[graph[node][i]]--;
        if (indegree[graph[node][i]] == 0) stack.push_back(graph[node][i]);
      }
    }
    // If size of the result is not same as number of vertices then we have
    // cycle.
    if (result.size() != numCourses) result.clear();
    return result;
  }
  vector<int> findOrder_indegree_bfs(int numCourses,
                                     vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> result;
    vector<int> indegree(numCourses, 0);
    for (int i = 0; i < prerequisites.size(); i++) {
      // [3,1] indicates  1 --> 3
      graph[prerequisites[i][1]].push_back(prerequisites[i][0]);
      indegree[prerequisites[i][0]]++;
    }
    queue<int> q;
    for (int i = 0; i < indegree.size(); i++) {
      if (indegree[i] == 0) q.push(indegree[i]);
    }

    while (q.empty() == false) {
      int node = q.front();
      q.pop();
      result.push_back(node);
      for (int i = 0; i < graph[node].size(); i++) {
        indegree[graph[node][i]]--;
        if (indegree[graph[node][i]] == 0) q.push(graph[node][i]);
      }
    }
    // If size of the result is not same as number of vertices then we have
    // cycle.
    if (result.size() != numCourses) result.clear();
    return result;
  }
};

void test_course_schedule_210() {
  vector<vector<int>> prerequisites{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  Solution_210 s;
  // numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
  CHECK(s.findOrder(4, prerequisites), {0, 2, 1, 3});
  CHECK(s.findOrder_indegree_dfs(4, prerequisites), {0, 2, 1, 3});
  CHECK(s.findOrder_indegree_bfs(4, prerequisites), {0, 1, 2, 3});
  // Cycle test
  prerequisites.push_back({1, 3});
  CHECK(s.findOrder(4, prerequisites), {});
  CHECK(s.findOrder_indegree_dfs(4, prerequisites), {});
  PRINT_MSG;
}

/*
269. Alien Dictionary
There is a new alien language that uses the English alphabet. However, the order
among letters are unknown to you.

You are given a list of strings words from the dictionary, where words are
sorted lexicographically by the rules of this new language.

Derive the order of letters in this language, and return it. If the given input
is invalid, return "". If there are multiple valid solutions, return any of
them.



Example 1:

Input: words = ["wrt","wrf","er","ett","rftt"]
Output: "wertf"
Example 2:

Input: words = ["z","x"]
Output: "zx"
Example 3:

Input: words = ["z","x","z"]
Output: ""
Explanation: The order is invalid, so return "".


Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 100
words[i] consists of only lowercase English letters.
*/

/*
 Lessons :
 1. Avoid using emplace()/insert() in case if you want to do upsert operation on
 map. Since these APIs ignore updates. Instead use [] . The former two APIs
 return pair to indicate if insert was successful or not. I ended up spending
 hours debudding the problem. C++17 added insert_or_assign() for this problem.

 2. We can use either BFS/DFS if we user incoming edge techinique.
 3. With coloring technique we can use DFS.
    If key is not found in the visisted map that indicates white color.
    If key is found with false then indicates Grey color
    If key is found with true that indicates Black color.

*/
/*
 Lessons :
 1. Avoid using emplace()/insert() in case if you want to do upsert operation on
 map. Since these APIs ignore updates. Instead use [] . The former two APIs
 return pair to indicate if insert was successful or not. I ended up spending
 hours debudding the problem. C++17 added insert_or_assign() for this problem.

 2. We can use either BFS/DFS if we use incoming edge techinique.
 3. With coloring technique we can use DFS.
    If key is not found in the visisted map that indicates white color.
    If key is found with false then indicates Grey color
    If key is found with true that indicates Black color.

*/
class Solution_269 {
 public:
  string alienOrder(vector<string>& words) {
    if (!build_graph(words)) return output;
    for (auto vertex : graph) {
      if (!dfs(vertex.first)) return "";
    }
    if (output.length() < visited.size()) return "";
    reverse(output.begin(), output.end());
    return output;
  }

 private:
  unordered_map<char, unordered_set<char>> graph;
  unordered_map<char, bool> visited;
  string output;
  bool build_graph(vector<string>& words) {
    // Intialize graph with unique letters.
    for (auto word : words) {
      for (auto ch : word) {
        graph.emplace(ch, unordered_set<char>{});
      }
    }

    for (int i = 0; i < words.size() - 1; i++) {
      string& source = words[i];
      string& target = words[i + 1];
      // if target is prefix of source then there is cycle. We cannot determine
      // the order.
      if (source.size() > target.size()) {
        bool is_prefix = (source.compare(0, target.size(), target) == 0);
        if (is_prefix) return false;
      }
      int j = 0;
      int length = min(source.size(), target.size());
      while (j < length) {
        if (source[j] != target[j]) {
          graph[source[j]].emplace(target[j]);
          break;
        }
        j++;
      }
    }
    return true;
  }
  bool dfs(char c) {
    if (visited.find(c) != visited.end()) return visited[c];

    visited[c] = false;  // equivalant to Grey

    unordered_set<char>& children = graph[c];
    for (auto child : children) {
      if (!dfs(child)) {
        /* There is cycle detected is color if grey i.e. false. */
        return false;
      }
    }
    visited[c] = true;  // equivalant to Black
    output += c;
    return true;
  }
};

void test_alien_dictionary_269() {
  {
    Solution_269 s;
    vector<string> v1 = {"wrt", "wrf", "er", "ett", "rftt"};
    assert(s.alienOrder(v1) == "wertf");
  }
  {
    Solution_269 s;
    vector<string> v2 = {"z", "x"};
    assert(s.alienOrder(v2) == "zx");
  }

  PRINT_MSG;
}
