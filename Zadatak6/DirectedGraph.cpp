#include "DirectedGraph.h"

DirectedWeightedGraph::DirectedWeightedGraph(std::string filename) {
  std::ifstream file(filename);
  std::string currentLine;

  int currentNode = 0;
  if (file.is_open()) {
    while (std::getline(file, currentLine)) {
      std::stringstream stringStream(currentLine);
      std::vector<double> neighbours;
      double cost;
      while (stringStream >> cost) {
        neighbours.push_back(cost);
      }
      add(neighbours);
    }
  }
  file.close();
}
void DirectedWeightedGraph::add(std::vector<double> vec) {
  std::vector<Edge> neighbors;
  if (nextIndex == 0) {
    for (size_t i = 0; i < vec.size(); i++) {
      nodes.emplace(i, new Node(i));
    }
  }
  for (size_t i = 0; i < vec.size(); i++) {
    if (vec[i] > 0.0) {
      Edge e{nodes[i], vec[i]};
      neighbors.push_back(e);
    }
  }

  nodes[nextIndex]->neighbors = neighbors;
  nextIndex++;
}

void DirectedWeightedGraph::connect(int src, int dst, double weight) {
  Edge e{nodes[dst], weight};
  nodes[src]->neighbors.push_back(e);
}

bool DirectedWeightedGraph::isTwoColorable() { return false; }

int DirectedWeightedGraph::shortestPath(int src, int dst) { return 0; }

int DirectedWeightedGraph::hamiltonCircuit() { return 0; }

DirectedWeightedGraph::Node::iterator::iterator(
    DirectedWeightedGraph::Node* node)
    : currentNode(node) {}

DirectedWeightedGraph::Node::iterator&
DirectedWeightedGraph::Node::iterator::operator++() {
  for (auto& neighbor : currentNode->neighbors) {
    if (visited.count(neighbor.dest->id) == 0) {
      visited.insert(neighbor.dest->id);
      toVisit.push(neighbor.dest);
    }
  }
  visited.emplace(currentNode->id);
  if (!toVisit.empty()) {
    currentNode = toVisit.front();
    toVisit.pop();
  } else {
    currentNode = nullptr;
  }
  return *this;
}

DirectedWeightedGraph::Node::iterator
DirectedWeightedGraph::Node::iterator::operator++(int) {
  iterator tmp = *this;
  this->operator++();
  return tmp;
}

bool DirectedWeightedGraph::Node::iterator::operator==(const iterator& other) {
  return currentNode == other.currentNode;
}

bool DirectedWeightedGraph::Node::iterator::operator!=(const iterator& other) {
  return !(*this == other);
}

int DirectedWeightedGraph::Node::iterator::operator*() {
  return currentNode->id;
}