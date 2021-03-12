#pragma once

#include "GraphHeader.h"

namespace zadatak6 {
inline Graph::Node::Node(int id) : id(id) {}

void Graph::Node::DefaultIterator::advance(Node **currentNode) {
  throw std::logic_error("DefaultIterator should not be used.");
}

void Graph::Node::BfsIterator::advance(Node **currentNode) {
  for (Edge x : (*currentNode)->neighbours)
    if (visited.count(x.destination->id) == 0) {
      visited.emplace(x.destination->id);
      toVisit.push(x.destination);
    }
  visited.emplace((*currentNode)->id);
  if (!toVisit.empty()) {
    (*currentNode) = toVisit.front();
    toVisit.pop();
  } else {
    (*currentNode) = nullptr;
  }
}

void Graph::Node::DfsIterator::advance(Node **currentNode) {
  for (Edge x : (*currentNode)->neighbours)
    if (visited.count(x.destination->id) == 0) {
      visited.emplace(x.destination->id);
      toVisit.push(x.destination);
    }
  visited.emplace((*currentNode)->id);
  if (!toVisit.empty()) {
    (*currentNode) = toVisit.top();
    toVisit.pop();
  } else {
    (*currentNode) = nullptr;
  }
}

template <class IteratorType>
inline Graph::Node::iterator<IteratorType>::iterator(Node *n) noexcept
    : currentNode(n) {}

template <class IteratorType>
Graph::Node::iterator<IteratorType>::iterator(
    const iterator<DefaultIterator> &other) {
  currentNode = other.currentNode;
}

template <class IteratorType>
inline Graph::Node::iterator<IteratorType>
    &Graph::Node::iterator<IteratorType>::operator++() noexcept {
  it.advance(&currentNode);
  return *this;
}
template <class IteratorType>
inline Graph::Node::iterator<IteratorType>
Graph::Node::iterator<IteratorType>::operator++(int) noexcept {
  auto tmp = *this;
  ++(*this);
  return tmp;
}
template <class IteratorType>
inline bool Graph::Node::iterator<IteratorType>::operator==(
    const iterator &other) const noexcept {
  return currentNode == other.currentNode;
}
template <class IteratorType>
inline bool Graph::Node::iterator<IteratorType>::operator!=(
    const iterator &other) const noexcept {
  return !(*this == other);
}

template <class IteratorType>
inline int &Graph::Node::iterator<IteratorType>::operator*() const noexcept {
  return currentNode->id;
}

inline Graph::Graph(std::string fileName) {
  std::ifstream file(fileName);
  std::string as;

  int currentIteration = 0;
  if (file.is_open()) {
    while (std::getline(file, as)) {
      std::vector<int> curr;
      std::stringstream is(as);
      std::copy(std::istream_iterator<int>(is), std::istream_iterator<int>(),
                std::back_inserter(curr));

      if (currentIteration == 0)
        for (size_t i = 0; i < curr.size(); i++) add();

      for (size_t i = 0; i < curr.size(); i++)
        if (curr.at(i) > 0) connect(currentIteration, i, curr.at(i));

      currentIteration++;
    }
  }
  file.close();
}

inline void Graph::add(void) {
  int currentIndex = nodes.size();
  nodes.push_back(Node(currentIndex));
}

inline void Graph::connect(int id1, int id2, int cost) {
  Node *node1 = &nodes[id1];
  Node *node2 = &nodes[id2];
  node1->neighbours.emplace(cost, node2);
}

inline void Graph::bfs(int id, const std::function<void(int)> &f) {
  Node *startNode = &nodes[id];
  for (Graph::Node::iterator<Graph::Node::BfsIterator> it = startNode->begin();
       it != startNode->end(); it++) {
    f(*it);
  }
}
inline void Graph::dfs(int id, const std::function<void(int)> &f) {
  Node *startNode = &nodes[id];
  for (Graph::Node::iterator<Graph::Node::DfsIterator> it = startNode->begin();
       it != startNode->end(); it++) {
    f(*it);
  }
}

// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
inline std::vector<int> Graph::shortestPath(int source, int destination) {
  std::vector<int> dist(nodes.size(), INT_MAX);
  std::vector<int> prev(nodes.size(), -1);
  auto cmp = [&dist](Node *n1, Node *n2) {
    return dist[n1->id] > dist[n2->id];
  };
  std::priority_queue<Node *, std::vector<Node *>, decltype(cmp)> queue{cmp};

  dist[source] = 0;
  queue.push(&nodes[source]);

  while (!queue.empty()) {
    Node *u = queue.top();
    queue.pop();

    if (u->id == destination) break;

    for (auto &edge : u->neighbours) {
      int alt = dist[u->id] + edge.cost;
      if (alt < dist[edge.destination->id]) {
        dist[edge.destination->id] = alt;
        prev[edge.destination->id] = u->id;
        queue.push(edge.destination);
      }
    }
  }

  std::vector<int> path;
  int u = destination;
  while (u != -1) {
    path.push_back(u);
    u = prev[u];
  }
  std::reverse(path.begin(), path.end());
  return path;
}

inline std::vector<int> Graph::firstToLastShortestPath() {
  return shortestPath(0, nodes.size() - 1);
}

// https://www.geeksforgeeks.org/bipartite-graph/
inline bool Graph::isBipartite() {
  int src = 0;
  std::vector<int> colorVec(nodes.size(), -1);
  colorVec[src] = 1;

  Node *startNode = &nodes[src];
  for (Graph::Node::iterator<Graph::Node::BfsIterator> it = startNode->begin();
       it != startNode->end(); it++) {
    Node *currentNode = &nodes[*it];

    // Return false if there is a self-loop
    if (currentNode->neighbours.count({0, currentNode}) > 0) return false;

    for (auto &edge : currentNode->neighbours) {
      if (colorVec[edge.destination->id] == -1) {
        // Assign alternate color to this adjacent v of u
        colorVec[edge.destination->id] = 1 - colorVec[currentNode->id];
      } else if (colorVec[edge.destination->id] == colorVec[currentNode->id]) {
        return false;
      }
    }
  }
  return true;
}

inline int Graph::shortestHamiltonian() {
  std::vector<bool> visited(nodes.size(), false);
  visited[0] = true;
  int ans = INT_MAX;
  tsp(visited, 0, 1, 0, ans);
  return ans;
}

// Backtracking Travelling Salesman
inline void Graph::tsp(std::vector<bool> &visited, int currPos, int count,
                       int cost, int &ans) {
  if (count == nodes.size())
    for (auto &edge : nodes[currPos].neighbours)
      if (edge.destination->id == 0) {
        ans = std::min(ans, cost + edge.cost);
        return;
      }

  for (auto &edge : nodes[currPos].neighbours)
    if (!visited[edge.destination->id]) {
      visited[edge.destination->id] = true;
      tsp(visited, edge.destination->id, count + 1, cost + edge.cost, ans);
      visited[edge.destination->id] = false;
    }
}

UnweightedGraph::UnweightedGraph(std::string filename) : Graph(filename) {
  std::set<Edge> tmp;
  for (Node &node : this->nodes) {
    for (const Edge &edge : node.neighbours) {
      tmp.insert({1, edge.destination});
    }
    node.neighbours = tmp;
    tmp.clear();
  }
}
UndirectedGraph::UndirectedGraph(std::string filename) : Graph(filename) {
  for (auto &node : this->nodes)
    for (auto &edge : node.neighbours)
      connect(edge.destination->id, node.id, edge.cost);
}
UndirectedUnweightedGraph::UndirectedUnweightedGraph(std::string filename)
    : Graph(filename), UnweightedGraph(filename), UndirectedGraph(filename) {}

}  // namespace zadatak6