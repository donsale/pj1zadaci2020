#pragma once
#include <climits>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <vector>

namespace zadatak6 {
class Graph {
 public:
  Graph(std::string);
  void add(void);
  void connect(int, int, int);
  void bfs(int, const std::function<void(int)> &);
  void dfs(int, const std::function<void(int)> &);
  std::vector<int> shortestPath(int source, int destination);
  std::vector<int> firstToLastShortestPath();
  bool isBipartite();
  int shortestHamiltonian();

 protected:
  struct Node;
  struct Edge {
    int cost;
    Node *destination;

    Edge(int cost, Node *dest) : cost(cost), destination(dest) {}
    auto operator<=>(const Edge &other) const {
      return destination->id <=> other.destination->id;
    }
  };

  struct Node {
   public:
    Node(int);

    int id;
    std::set<Edge> neighbours;

    struct DefaultIterator {
      void advance(Node **currentNode);
    };

    struct BfsIterator {
      void advance(Node **curentNode);

     private:
      std::set<int> visited;
      std::queue<Node *> toVisit;
    };

    struct DfsIterator {
      void advance(Node **curentNode);

     private:
      std::set<int> visited;
      std::stack<Node *> toVisit;
    };

    template <class IteratorType>
    class iterator {
      Node *currentNode;

     public:
      explicit iterator(Node *) noexcept;
      iterator(const iterator<DefaultIterator> &);
      iterator &operator++() noexcept;
      iterator operator++(int) noexcept;
      bool operator==(const iterator &other) const noexcept;
      bool operator!=(const iterator &other) const noexcept;
      int &operator*() const noexcept;

     private:
      IteratorType it = IteratorType();

      friend class iterator<BfsIterator>;
      friend class iterator<DfsIterator>;
    };

    iterator<DefaultIterator> begin() {
      return iterator<DefaultIterator>(this);
    }
    iterator<DefaultIterator> end() {
      return iterator<DefaultIterator>(nullptr);
    }
  };

  void tsp(std::vector<bool> &, int, int, int, int &);
  std::vector<Node> nodes;

  // po default-u ostavljamo da je bfs iterator dostupan sa vana
 public:
  Node::iterator<Node::BfsIterator> begin() { return nodes[0].begin(); }
  Node::iterator<Node::BfsIterator> end() { return nodes[0].end(); }
};

class UnweightedGraph : virtual public Graph {
 public:
  UnweightedGraph(std::string);
};

class UndirectedGraph : virtual public Graph {
 public:
  UndirectedGraph(std::string);
};

class UndirectedUnweightedGraph : public UnweightedGraph,
                                  public UndirectedGraph {
 public:
  UndirectedUnweightedGraph(std::string);
};

}  // namespace zadatak6