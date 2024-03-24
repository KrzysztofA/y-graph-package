#ifndef Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL
#define Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL

#include <string>

#include <Graphs.hpp>
#include <Nodes.hpp>
#include <sstream>
#include <utility>

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode> NodePtr;

namespace yasuzume::graph::shortest_path
{
  class ShortestPathTree final
  {
  public:
    explicit ShortestPathTree( NodePtr _starting_node ) : starting_node( std::move( _starting_node ) ) {}
    ShortestPathTree( const ShortestPathTree& ) = default;
    ShortestPathTree( ShortestPathTree&& ) noexcept = default;
    ShortestPathTree& operator=( const ShortestPathTree& ) = default;
    ShortestPathTree& operator=( ShortestPathTree&& ) noexcept = default;
    ~ShortestPathTree() noexcept = default;

    struct ShortestPathNode
    {
      ShortestPathNode( NodePtr _node, NodePtr _predecessor, const float _cumulated_weight ) : node( std::move( _node ) ), predecessor( std::move( _predecessor ) ), cumulated_weight( _cumulated_weight ) {}
      ShortestPathNode( const ShortestPathNode& ) = default;
      ShortestPathNode( ShortestPathNode&& ) noexcept = default;
      ShortestPathNode& operator=( const ShortestPathNode& ) = default;
      ShortestPathNode& operator=( ShortestPathNode&& ) noexcept = default;
      ~ShortestPathNode() noexcept = default;

      void set_predecessor_weight( NodePtr _predecessor, const float _weight )
      {
        predecessor = std::move( _predecessor );
        cumulated_weight = _weight;
      }

      void set_predecessor_weight_leading( NodePtr _predecessor, const float _weight, EdgePtr _leading_edge )
      {
        predecessor = std::move( _predecessor );
        cumulated_weight = _weight;
        leading_edge = std::move( _leading_edge );
      }

      NodePtr node;
      NodePtr predecessor;
      EdgePtr leading_edge;
      float cumulated_weight;
    };

    [[nodiscard]] std::string get_stringified() const
    {
      std::stringstream sstream{};
      sstream << "Tree:\n";
      sstream << starting_node->get_name() << ": [\n";
      for( const auto& i : tree )
      {
        if( i.second.predecessor == nullptr ) continue;
        sstream << "  " << i.first->get_name() << ": [ ";
        sstream << i.second.predecessor->get_name() << " ";
        sstream << "] = " << i.second.cumulated_weight << "\n";
      }
      sstream << "]\nPath: [ ";
      for( const auto& i : path ) if( i != nullptr ) sstream << i->get_stringified() << ", ";
      sstream << " ]";
      return sstream.str();
    }

    static ShortestPathNode create_shortest_path_node_to_self( const NodePtr& _node )
    {
      return ShortestPathNode { _node, _node, 0 };
    }

    static ShortestPathNode create_shortest_path_node( const NodePtr& _node, const NodePtr& _predecessor )
    {
      return ShortestPathNode { _node, _predecessor, INFINITY };
    }

    NodePtr get_starting_node()
    {
      return starting_node;
    }

    std::vector<EdgePtr> path;
    std::unordered_map<NodePtr, ShortestPathNode> tree;

  private:
    NodePtr starting_node;
  };

  class ShortestPath
  {
  public:
    ShortestPath() = default;
    ShortestPath( const ShortestPath& ) = default;
    ShortestPath( ShortestPath&& ) noexcept = default;
    ShortestPath& operator=( const ShortestPath& ) = default;
    ShortestPath& operator=( ShortestPath&& ) noexcept = default;
    virtual ~ShortestPath() noexcept = default;

    virtual ShortestPathTree create_shortest_path( const NodePtr&, const UndirectedGraph& ) = 0;
    virtual ShortestPathTree create_shortest_path( const NodePtr&, const DirectedGraph& ) = 0;
    // virtual Grid create_shortest_path( const NodePtr&, const Grid& ) = 0;
    // virtual WeightedGrid create_shortest_path( const NodePtr&, const WeightedGrid& ) = 0;

  protected:
    static ShortestPathTree initialize_shortest_path_tree( const NodePtr& _starting_node, const std::vector<NodePtr>& _nodes )
    {
      ShortestPathTree shortest_path { _starting_node };

      for( auto& node : _nodes ) shortest_path.tree.emplace( std::make_pair( node, ShortestPathTree::create_shortest_path_node( node, nullptr ) ) );
      shortest_path.tree.at( _starting_node ).set_predecessor_weight( _starting_node, 0 );

      return shortest_path;
    }
  };
}

#endif // !Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL
