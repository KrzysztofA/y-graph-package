#ifndef Y_GRAPH_GRAPHS_HPP
#define Y_GRAPH_GRAPHS_HPP

#include "Nodes.hpp"
#include <memory>
#include <vector>

namespace yasuzume::graph
{
  /**
   * @brief Base for the graph classes, will consist of all necessary functions for all algorithms to use
   */
  class Graph
  {
  public:

  private:
    std::vector<std::vector<float>> graph_table_representation;
  };

  /**
   * @brief Graph where all edges are undirected
   */
  class UndirectedGraph : Graph
  {

  };

  /**
   * @brief Graph where edges can follow any direction
   */
  class DirectedGraph : Graph
  {

  };

  /**
   * @brief Graph in shape of a grid or "maze", nodes are by default connected with all adjacent nodes and be either passable (1) or not passable (0)
   */
  class Grid : Graph
  {

  };

  /**
   * @brief Graph in shape of a grid or "maze", nodes are by default connected with all adjacent nodes and have either negative cost (-x) or be not passable (0)
   */
  class WeightedGrid : Graph
  {

  };
}

#endif // !Y_GRAPH_GRAPHS_HPP