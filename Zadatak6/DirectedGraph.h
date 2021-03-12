#pragma once
class DirectedGraph {};
#pragma once
#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class DirectedWeightedGraph {
 public:
  // u konstruktoru u?itavamo fajl
  DirectedWeightedGraph(std::string filename);

  bool isTwoColorable();  // ovo je onaj dio sa true/false - algoritam ovdje
                          // ima: https://www.geeksforgeeks.org/bipartite-graph/
  // za najkra?i put izme?u dva ?vora možeš vraiti ili samo težinu puta ili i
  // put
  int shortestPath(
      int src,
      int dst);  // dijkstra npr
                 // https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
  int hamiltonCircuit();  // https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/?ref=rp

 protected:
  struct Edge;
  struct Node {
    Node(int id) : id(id) {}

    int id;
    std::vector<Edge> neighbors;

    class iterator {
      Node *currentNode;
      std::queue<Node *> toVisit;
      std::set<int> visited;

     public:
      iterator(Node *);
      iterator &operator++();
      iterator operator++(int);
      bool operator==(const iterator &other);
      bool operator!=(const iterator &other);
      int operator*();
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(nullptr); }
  };
  struct Edge {
    Node *dest;
    double cost;
  };

  void add(std::vector<double>);
  void connect(int, int, double);
  std::map<int, Node *> nodes;
  int nextIndex = 0;

 public:
  Node::iterator begin() { return nodes[0]->begin(); }
  Node::iterator end() { return nodes[0]->end(); }
};

// usmjereni netežinski
class DirectedUnweightedGraph : virtual public DirectedWeightedGraph {
 public:
  DirectedUnweightedGraph(std::string filename)
      : DirectedWeightedGraph(filename) {
    // ovdje treba samo pro?i kroz sve ?vorove i staviti težine svi edge-eva na
    // 1
    for (auto &node : nodes) {
      for (auto &edge : node.second->neighbors) edge.cost = 1;
    }
  }
};

// neusmjereni težinski
class UndirectedWeightedGraph : virtual public DirectedWeightedGraph {
 public:
  UndirectedWeightedGraph(std::string filename)
      : DirectedWeightedGraph(filename) {
    // ovdje treba pro?i kroz sve ?vorove i ako jedan ?vor ima vezu do drugog
    // treba i u drugome dodati vezu ka prvom

    for (auto &node : nodes) {
      for (auto &edge : node.second->neighbors)
        connect(edge.dest->id, node.first,
                edge.cost);  // ako vec postoji veza od node do edge.destId,
                             // dodamo i vezu edge.destId do node
    }
  }
};

// neusmjereni netežinski
class UndirectedUnweightedGraph : public DirectedUnweightedGraph,
                                  public UndirectedWeightedGraph {
 public:
  UndirectedUnweightedGraph(std::string filename)
      : DirectedWeightedGraph(filename),
        UndirectedWeightedGraph(filename),
        DirectedUnweightedGraph(filename) {}
};