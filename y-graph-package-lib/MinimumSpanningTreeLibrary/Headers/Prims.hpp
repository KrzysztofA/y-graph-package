#ifndef Y_GRAPH_MST_PRIMS_HPP
#define Y_GRAPH_MST_PRIMS_HPP

#include "./MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Prims final : public MinimumSpanningTreeAlgorithm
  {
    virtual Graph create_minimum_spanning_tree( const Graph& ) override;
  };
}

#endif // !Y_GRAPH_MST_PRIMS_HPP