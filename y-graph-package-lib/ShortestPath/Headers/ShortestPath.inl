#ifndef Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL
#define Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL

#include <string>

#include <Graphs.hpp>
#include <Nodes.hpp>
#include <sstream>

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode> NodePtr;

namespace yasuzume::graph::shortest_path
{
  class ShortestPathTree
  {
  public:
    explicit ShortestPathTree( NodePtr _starting_node ) : starting_node( std::move( _starting_node ) ) {}
    ShortestPathTree( const ShortestPathTree& ) = default;
    ShortestPathTree( ShortestPathTree&& ) noexcept = default;
    ShortestPathTree& operator=( const ShortestPathTree& ) = default;
    ShortestPathTree& operator=( ShortestPathTree&& ) noexcept = default;
    virtual ~ShortestPathTree() noexcept = default;

    std::string get_stringified()
    {
      std::stringstream sstream{};

      sstream << starting_node->get_name() << ": [\n";
      for( auto& i : tree )
      {
        sstream << "  " << i.first->get_name() << ": [ ";
        float weight { 0 };
        for( auto& j : i.second )
        {
          weight += j->get_weight();
          sstream << j->get_stringified() << " ";
        }
        sstream << "]\n";
      }
      sstream << "]";
      return sstream.str();
    }

    NodePtr get_starting_node()
    {
      return starting_node;
    }

    std::unordered_map<NodePtr, std::vector<EdgePtr>> tree;

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
    virtual Grid create_shortest_path( const NodePtr&, const Grid& ) = 0;
    virtual WeightedGrid create_shortest_path( const NodePtr&, const WeightedGrid& ) = 0;
  };
}

#endif // !Y_GRAPH_SHORTEST_PATH_SHORTEST_PATH_INL
