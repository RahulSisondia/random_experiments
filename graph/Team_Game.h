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
                  unordered_set<string> *visited_ptr) {
  unordered_set<string> &visited = *visited_ptr;
  if (curr == dest)
    return true;
  else if (visited.find(curr) != visited.end() ||
           graph.find(curr) == graph.end()) {
    return false;
  }
  visited.emplace(curr);
  // Fetch the neighors
  const auto &team_list = graph.at(curr);
  return any_of(begin(team_list), end(team_list), [&](const string &team) {
    return is_reachable(graph, team, dest, visited_ptr);
  });
}

bool can_team_A_beat_team_B(const vector<Match_result> &matches,
                            const string &team_a, const string &team_b) {
  auto visited = make_unique<unordered_set<string>>();
  if (is_reachable(build_graph(matches), team_a, team_b, visited.get())) {
    for (auto itr = visited->begin(); itr != visited->end(); itr++) {
      cout << *itr << " ";
    }
    cout << team_b << endl;
    return true;
  }
  cout << "not exists" << endl;
  return false;
}
