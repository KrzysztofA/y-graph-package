#ifndef Y_GRAPH_BFS_HPP
#define Y_GRAPH_BFS_HPP

#include <PathSearch.inl>

namespace yasuzume::graph
{
  class BFS final : public PathSearch
  {
  public:
    BFS() = default;
    BFS( const BFS& ) = default;
    BFS( BFS&& ) noexcept = default;
    BFS&    operator=( const BFS& ) = default;
    BFS&    operator=( BFS&& ) noexcept = default;
    virtual ~BFS() noexcept override = default;

    virtual Path path_search( const NodePtr&, const NodePtr& ) override;
  };
}

#endif // !Y_GRAPH_BFS_HPP
