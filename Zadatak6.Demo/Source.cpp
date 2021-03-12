#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include "Graph.h"

using namespace zadatak6;

int main() {

   const std::string filename = "graph.data";

   Graph directedWeighted(filename);
   UnweightedGraph directedUnweighted(filename);
   UndirectedGraph undirectedWeighted(filename);
   UndirectedUnweightedGraph uug(filename);

   int src = 0;
   int dst = 0;
   std::cout << "BFS -> ";
   directedWeighted.bfs(0, [](const int& data) { std::cout << data << " "; });
   std::cout << std::endl;
   std::cout << "DFS -> ";
   directedWeighted.dfs(0, [](const int& data) { std::cout << data << " "; });
   std::cout << std::endl;
   std::cout << "Source node -> ";
   std::cin >> src;
   std::cout << "Destination node -> ";
   std::cin >> dst;
   std::vector<int> path = directedWeighted.shortestPath(src, dst);
   std::cout << "Shortest path from " << src << " to " << dst << " -> ";
   std::for_each(path.begin(), path.end(), [](int n) { std::cout << n << " ";
   }); std::cout << std::endl; std::cout << "Graph is " << (uug.isBipartite()
   ?
   "" : "not ") << "bipartite."; std::cout << std::endl; std::cout <<
   "Shortest path from first to last node -> "; path =
   directedUnweighted.firstToLastShortestPath(); std::for_each(path.begin(),
   path.end(), [](int n) { std::cout << n << " "; }); std::cout << std::endl;
   std::cout
      << "Shortest Hamiltonian circuit weight (undirected and weighted) -> "
      << undirectedWeighted.shortestHamiltonian() << std::endl;
   std::cout << "Shortest Hamiltonian circuit weight (directed and weighted)-> "
            << directedWeighted.shortestHamiltonian() << std::endl;

  return 0;
}