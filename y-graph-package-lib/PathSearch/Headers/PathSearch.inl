#ifndef Y_GRAPH_PATH_SEARCH_INL
#define Y_GRAPH_PATH_SEARCH_INL

#include <Graphs.hpp>
#include <memory>
#include <sstream>

typedef std::shared_ptr<yasuzume::graph::GraphNode::Edge> EdgePtr;
typedef std::shared_ptr<yasuzume::graph::GraphNode> NodePtr;

namespace yasuzume::graph
{
  struct Path
  {
    Path() = default;
    Path( const Path& ) = default;
    Path( Path&& ) noexcept = default;
    Path& operator=( const Path& ) = default;
    Path& operator=( Path&& ) noexcept = default;
    ~Path() noexcept = default;

    std::vector<EdgePtr> path {};
    float                weight = 0;
  };

  struct ConnectedTree
  {
    ConnectedTree() = default;
    ConnectedTree( const ConnectedTree& ) = default;
    ConnectedTree( ConnectedTree&& ) noexcept = default;
    ConnectedTree& operator=( const ConnectedTree& ) = default;
    ConnectedTree& operator=( ConnectedTree&& ) noexcept = default;
    ~ConnectedTree() noexcept = default;

    NodePtr starting_node;
    std::vector<NodePtr> path {};

    [[nodiscard]] std::string get_stringified() const
    {
      std::stringstream sstream;
      sstream << starting_node->get_name() << ": [";
      for( const auto& node : path ) sstream << " -" << node->get_name() << "- ";
      sstream << "]";
      return sstream.str();
    }
  };

  class PathSearch
  {
  public:
    PathSearch() = default;
    PathSearch( const PathSearch& ) = default;
    PathSearch( PathSearch&& ) noexcept = default;
    PathSearch& operator=( const PathSearch& ) = default;
    PathSearch& operator=( PathSearch&& ) noexcept = default;
    virtual     ~PathSearch() noexcept = default;

    virtual Path path_search( const NodePtr&, const NodePtr& ) = 0;
    virtual ConnectedTree connected_search( const NodePtr& ) = 0;
  };

}

#endif // !Y_GRAPH_PATH_SEARCH_INL
