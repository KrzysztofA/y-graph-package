#ifndef Y_GRAPH_GRAPHS_HPP
#define Y_GRAPH_GRAPHS_HPP

#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "Nodes.hpp"

namespace yasuzume::graph
{
  /**
   * @brief Base for the graph classes, will consist of all necessary functions for all algorithms to use
   */
  class Graph
  {
  public:
    static Graph create_new_graph_from_nodes( const Graph& );

    Graph() = default;
    Graph( const Graph& ) = default;
    Graph( Graph&& ) noexcept = default;
    Graph&  operator=( const Graph& ) = default;
    Graph&  operator=( Graph&& ) noexcept = default;
    virtual ~Graph() noexcept = default;

    void                                                     add_node( const std::string& );
    [[nodiscard]] std::set<std::shared_ptr<GraphNode::Edge>> get_edges() const;
    [[nodiscard]] std::vector<std::shared_ptr<GraphNode>>    get_nodes() const;
    [[nodiscard]] std::shared_ptr<GraphNode>                 get_node( const std::string& _name ) const;
    void                                                     add_edge( const std::shared_ptr<GraphNode::Edge>& );
    [[nodiscard]] std::vector<std::vector<float>>            get_graph_table_representation() const;
    [[nodiscard]] float                                      get_total_graph_weight() const;
    [[nodiscard]] std::string                                get_graph_table_stringified() const;
    void                                                     manually_override_longest_node_name( const long long& );

  protected:
    std::unordered_map<std::string, std::pair<int, std::shared_ptr<GraphNode>>> nodes_set {};
    std::vector<std::shared_ptr<GraphNode>>                                     nodes_vector {};
    std::set<std::shared_ptr<GraphNode::Edge>>                                  edges {};
    std::vector<std::vector<float>>                                             graph_table_representation { {} };
    long long                                                                   longest_node_name { 3 };
  };

  /**  
   * @brief Graph where all edges are undirected
   */
  class UndirectedGraph final : public Graph
  {
  public:
    UndirectedGraph() = default;
    UndirectedGraph( const UndirectedGraph& ) = default;
    explicit UndirectedGraph( const Graph& );
    UndirectedGraph( UndirectedGraph&& ) noexcept = default;
    UndirectedGraph& operator=( const UndirectedGraph& ) = default;
    UndirectedGraph& operator=( UndirectedGraph&& ) noexcept = default;
    virtual          ~UndirectedGraph() override = default;

    void add_connection( int, int, float );
    void add_connection( const std::string&, const std::string&, float );
  };

  /**
   * @brief Graph where edges can follow any direction
   */
  class DirectedGraph final : public Graph
  {
  public:
    DirectedGraph() = default;
    DirectedGraph( const DirectedGraph& ) = default;
    explicit DirectedGraph( const Graph& );
    DirectedGraph( DirectedGraph&& ) noexcept = default;
    DirectedGraph& operator=( const DirectedGraph& ) = default;
    DirectedGraph& operator=( DirectedGraph&& ) noexcept = default;
    virtual          ~DirectedGraph() override = default;

    void add_connection( int, int, float, Direction );
    void add_connection( std::string, std::string, float, Direction );
  };

  /**
   * @brief Graph in shape of a grid or "maze", nodes are by default connected with all adjacent nodes and be either passable (1) or not passable (0)
   */
  class Grid : Graph {};

  /**
   * @brief Graph in shape of a grid or "maze", nodes are by default connected with all adjacent nodes and have either negative cost (-x) or be not passable (0)
   */
  class WeightedGrid : Graph {};
}

#endif // !Y_GRAPH_GRAPHS_HPP
