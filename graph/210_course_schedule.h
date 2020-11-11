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
 I implemented both
*/

class Solution {
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
   Solutoin#1 using DFS approach  with graph coloring to detect the cycle.
   I have used both approaches i.e. graph coloring and indegree based. I found
   indegree based approach much simpler.
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
   Solution#2 is using indegree approach. It is relatively simple. Just do the
   usual topplogical sort. If the size of the result set is not as expected that
   means there were a cycle.
  */
  vector<int> findOrder_indegree(int numCourses,
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
};

void test_course_schedule_210() {
  vector<vector<int>> prerequisites{{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  Solution s;
  // numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
  CHECK(s.findOrder(4, prerequisites), {0, 2, 1, 3});
  CHECK(s.findOrder_indegree(4, prerequisites), {0, 2, 1, 3});
  // Cycle test
  prerequisites.push_back({1, 3});
  CHECK(s.findOrder(4, prerequisites), {});
  CHECK(s.findOrder_indegree(4, prerequisites), {});
  PRINT_MSG;
}