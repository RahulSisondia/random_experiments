#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Summary : This program checks if there exists a connection between source and
// target nodes in a directed graph. We construct a graph with the info given in
// the form of Match_result.
// A team represents a vertex.

struct Match_result {
  string winning_team, losing_team;
};
/*
  We are given graph in the form of edge list. Convert that into adjacency list
  We can represent the graph using this hashmap since we know there will
  be no duplicate  node.
*/
unordered_map<string, unordered_set<string>>
build_graph(const vector<Match_result> &matches) {
  unordered_map<string, unordered_set<string>> graph;
  for (const auto &match : matches) {
    graph[match.winning_team].emplace(match.losing_team);
  }
  return graph;
}

bool is_reachable(const unordered_map<string, unordered_set<string>> &graph,
                  const string &curr, const string &dest,
                  unordered_set<string> &visited) {
  if (curr == dest)
    return true;
  // We have already visisted node or it does not exist in the graph.
  else if (visited.find(curr) != visited.end() ||
           graph.find(curr) == graph.end()) {
    return false;
  }
  // We could store the path in a result vector and add the node here.
  visited.emplace(curr);
  // Fetch the neighors
  const auto &team_list = graph.at(curr);
  return any_of(begin(team_list), end(team_list), [&](const string &team) {
    return is_reachable(graph, team, dest, visited);
  });
}

bool can_team_A_beat_team_B(const vector<Match_result> &matches,
                            const string &team_a, const string &team_b) {
  unordered_set<string> visited;
  if (is_reachable(build_graph(matches), team_a, team_b, visited)) {
    for (auto itr = visited.begin(); itr != visited.end(); itr++) {
      cout << *itr << " ";
    }
    cout << team_b << endl;
    return true;
  }
  cout << "not exists" << endl;
  return false;
}

void test_team_game() {
  vector<Match_result> mr{
      {"A", "B"}, {"B", "C"}, {"C", "A"}, {"D", "E"}, {"A", "D"}};
  cout << can_team_A_beat_team_B(mr, "C", "B") << endl;
  cout << can_team_A_beat_team_B(mr, "B", "A") << endl;
  cout << can_team_A_beat_team_B(mr, "A", "D") << endl;
  cout << can_team_A_beat_team_B(mr, "A", "E") << endl;
  cout << can_team_A_beat_team_B(mr, "B", "D") << endl;
  cout << can_team_A_beat_team_B(mr, "E", "C") << endl;
}