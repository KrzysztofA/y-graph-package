#ifndef Y_GRAPH_MST_PRIMS_HPP
#define Y_GRAPH_MST_PRIMS_HPP

#include "./MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Prims final : public MinimumSpanningTreeAlgorithm
  {
  public:
    Prims() = default;
    Prims( const Prims& ) = default;
    Prims( Prims&& ) noexcept = default;
    Prims& operator=( const Prims& ) = default;
    Prims& operator=( Prims&& ) noexcept = default;
    virtual ~Prims() noexcept override = default;

    virtual UndirectedGraph create_minimum_spanning_tree( const UndirectedGraph& ) override;
  };
}

#endif // !Y_GRAPH_MST_PRIMS_HPP