#ifndef Y_GRAPH_MST_BORUVKA_HPP
#define Y_GRAPH_MST_BORUVKA_HPP

#include "MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Boruvka final : public MinimumSpanningTreeAlgorithm
  {
    virtual Graph create_minimum_spanning_tree( const Graph& ) override;
  };
}

#endif // !Y_GRAPH_MST_BORUVKA_HPP