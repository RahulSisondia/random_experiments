#pragma once
/*
Given a list of airline tickets represented by pairs of departure and arrival
airports [from, to], reconstruct the itinerary in order. All of the tickets
belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:

If there are multiple valid itineraries, you should return the itinerary that
has the smallest lexical order when read as a single string. For example, the
itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"]. All
airports are represented by three capital letters (IATA code). You may assume
all tickets form at least one valid itinerary. One must use all the tickets once
and only once. Example 1:

Input: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Output: ["JFK", "MUC", "LHR", "SFO", "SJC"]
Example 2:

Input: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is
["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.
*/

#include <functional>

#include "../my_util.h"
/*
This is my first approach to this solution. But it fails for the test case :

[["JFK","KUL"],["JFK","NRT"],["NRT","JFK"]]
Output:
["JFK","KUL","NRT", "JFK"]
Expected:
["JFK","NRT","JFK","KUL"]

The above outout is wrong since KUL, NRT means we have a ticket from KUL to NRT
but that's not the case. Problem asks to visit all the cities. Hence, expected
output is correct :-( .
Therefore, if we go KUL then we are stuck there. Why does
it produce outut like that ?? There are two reasons :
 - I am using BFS approach which is greedy in nature. It alone is not
  sufficient, we need backtracking along with greedy here.
 - Since it is BFS, I am processing all children together.

It means we have to try all possible route and print once found a
valid route i.e. backtracking which requires recursion hence DFS based solution
would do.
*/

class Solution_332 {
 private:
  map<string, vector<string>> graph;
  vector<string> reconstruct_itinerary(const std::string& starting_city) {
    priority_queue<string, vector<string>,
                   std::function<bool(const string&, const string&)>>
        pq([](const string& s1, const auto& s2) {
          return (s1.compare(s2) > 0);
        });
    set<string> visited;
    vector<string> result;
    pq.emplace(starting_city);
    while (pq.empty() == false) {
      const auto src = pq.top();
      pq.pop();
      // cout << "src " << src << endl;
      result.push_back(src);
      if (visited.find(src) == visited.end()) {
        auto itr = graph.find(src);
        if (itr != graph.end()) {
          for (auto dest : itr->second) {
            // cout << "dest " << dest << endl;
            pq.emplace(dest);
          }
        }
        visited.emplace(src);
      }
    }
    return result;
  }

 public:
  vector<string> findItinerary(vector<vector<string>>& tickets) {
    for (auto v : tickets) {
      graph[v[0]].push_back(v[1]);
    }
    return reconstruct_itinerary("JFK");
  }
};

/*
We have an excellent explanation here.
https://leetcode.com/problems/reconstruct-itinerary/discuss/897615/C++-DFS-Euler-Walk-O(E-Log-E)-Solution
Notice the difference in the previous solution, and, here or
iterative version of DFS. Here we are processing one child at a time.

• To find the Eulerian path, inspired from the original
  Hierzolher's algorithm, we simply change one condition of loop, rather than
  stopping at the starting point, we stop at the vertex where we do not have any
  unvisited edges.
• The essential step is that starting from the fixed starting
  vertex (airport 'JFK'), we keep following the ordered and unused edges
  (flights) until we get stuck at certain vertex where we have no more unvisited
  outgoing edges.
• The point that we got stuck would be the last airport that we
  visit. And then we follow the visited vertex (airport) backwards, we would
  obtain the final itinerary.
*/
class Solution_332_euler_path {
 public:
  vector<string> findItinerary(vector<vector<string>>& tickets) {
    /* Set is an ordered container, it stores the values in sorted order */
    unordered_map<string, multiset<string>> graph;
    for (int i = 0; i < tickets.size(); i++) {
      string u = tickets[i][0];
      string v = tickets[i][1];
      graph[u].insert(v);
    }
    vector<string> ans;
    stack<string> st;
    st.push("JFK");
    while (!st.empty()) {
      string curr = st.top();
      // Notice, here, we didn't pop the curr from the stack yet. That we
      // usually do in DFS or Topological sort.
      if (graph[curr].size() == 0) {
        ans.push_back(curr);
        st.pop();  // We pop the node now since there is no more outgoing edges
                   // to it.
      } else {
        // This is the first node in lexicograohical order. We don't add any
        // more children here instead, process it first. it is kind of mimicking
        // the recursive DFS.
        auto dest = graph[curr].begin();
        st.push(*dest);
        graph[curr].erase(dest);
      }
    }
    reverse(ans.begin(), ans.end());
    return ans;
  }
};
/*
Reconstruct Itinerary solution comes from Euler walk (visit each edge only once)
where we choose edge whose destination node is lexicographically smaller. Push
node in to result vector while all its edges are already visited which insures
that lexical smaller nodes are inserted first in to result vector. Finally our
itenary order will be the reverse of the result vector as node that finished
first are inserted first in the result vector and it is lexically smaller.
*/
class Solution332_euler_path_recursive_DFS {
 public:
  // itenary list
  vector<string> result;

  void dfs(string node, unordered_map<string, multiset<string>>& graph) {
    // process node's edges
    if (graph.count(node)) {
      // If node has any edge call DFS with the edge destination node
      // also remove the edge as we will not visit the edge again (Euler walk)
      while (!graph[node].empty()) {
        string child = *graph[node].begin();
        graph[node].erase(child);
        dfs(child, graph);
      }
    }

    // push node in to result when all its edges are processed
    result.push_back(node);
  }

  vector<string> findItinerary(vector<vector<string>>& tickets) {
    // graph adjacency list
    unordered_map<string, multiset<string>> graph;

    // populate graph adjacency list
    for (int i = 0; i < tickets.size(); i++)
      graph[tickets[i][0]].emplace(tickets[i][1]);

    // run DFS starting from JFK
    dfs("JFK", graph);

    // reverse result vector to get itenary list order
    reverse(result.begin(), result.end());

    return result;
  }
};

void resonstruct_itinerary() {
  Solution_332 s;
  vector<vector<string>> itinerary = {{"JFK", "SFO"},
                                      {"JFK", "ATL"},
                                      {"SFO", "ATL"},
                                      {"ATL", "JFK"},
                                      {"ATL", "SFO"}};

  CHECK(s.findItinerary(itinerary), {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"});
  Solution332_euler_path_recursive_DFS sr_dfs;
  CHECK(sr_dfs.findItinerary(itinerary),
        {"JFK", "ATL", "JFK", "SFO", "ATL", "SFO"});
  PRINT_MSG;
}
