#include "../my_util.h"

struct Vertex {
  enum class Color { White, Gray, Black } color = Color::White;
  size_t indegree = 0;
  string node;
  vector<Vertex*> edges;
  Vertex(string n) : node(n) {}
  /*  this --> that */
  void add_edge(Vertex* that) {
    edges.emplace_back(that);
    ++that->indegree;
  }
};

void print_graph(const vector<Vertex>& G) {
  for (auto v : G) {
    for (auto edge : v.edges) {
      cout << v.node << "  ---> " << edge->node << endl;
    }
  }
}

template <typename type>
class Node {
  type key;
};

// @TODO : Extend and make use of the class to track the vertex and edges.
template <typename t>
class Graph {
  // Weight, Neighbour
  using value = pair<Node<t>*, int>;
  using key = Node<t>*;
  unordered_map<key, unordered_set<value>> m_map;
  bool m_is_directed;

 public:
  bool is_directed() { return m_is_directed; }
  Graph(bool is_directed) : m_is_directed(is_directed), m_map() {}
  void add_edge(Node<t>* t1, Node<t>* t2, int weight = 0) {
    if (t1 == nullptr || t2 == nullptr)
      throw "Invalid Vertex. It cannot be nullptr ";

    m_map[t1].emplace(t2, weight);
    if (m_is_directed == false) {
      m_map[t2].emplace(t1, weight);
    }
  }
  bool is_vertex_exist(Node<t>* n) { return (m_map.find(*n) != m_map.end()); }
};