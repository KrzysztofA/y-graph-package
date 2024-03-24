#ifndef Y_GRAPH_DFS_HPP
#define Y_GRAPH_DFS_HPP

#include <PathSearch.inl>

namespace yasuzume::graph
{
  class DFS final : public PathSearch
  {
  public:
    DFS() = default;
    DFS( const DFS& ) = default;
    DFS( DFS&& ) noexcept = default;
    DFS&    operator=( const DFS& ) = default;
    DFS&    operator=( DFS&& ) noexcept = default;
    virtual ~DFS() noexcept override = default;

    virtual Path path_search( const NodePtr&, const NodePtr& ) override;
    virtual ConnectedTree connected_search( const NodePtr& ) override;
  };
}

#endif // !Y_GRAPH_DFS_HPP
