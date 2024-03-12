#ifndef Y_GRAPH_MST_REVERSE_DELETE_HPP
#define Y_GRAPH_MST_REVERSE_DELETE_HPP

#include "MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class ReverseDelete final : public MinimumSpanningTreeAlgorithm
  {
  public:
    ReverseDelete() = default;
    ReverseDelete( const ReverseDelete& ) = default;
    ReverseDelete( ReverseDelete&& ) noexcept = default;
    ReverseDelete& operator=( const ReverseDelete& ) = default;
    ReverseDelete& operator=( ReverseDelete&& ) noexcept = default;
    virtual ~ReverseDelete() noexcept override = default;

    virtual UndirectedGraph create_minimum_spanning_tree( const UndirectedGraph& ) override;
  };
}

#endif // !Y_GRAPH_MST_REVERSE_DELETE_HPP