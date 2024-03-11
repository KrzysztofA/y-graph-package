#ifndef Y_GRAPH_MST_BORUVKA_HPP
#define Y_GRAPH_MST_BORUVKA_HPP

#include "MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Boruvka final : public MinimumSpanningTreeAlgorithm
  {
    virtual UndirectedGraph create_minimum_spanning_tree( const UndirectedGraph& ) override;
  };
}

#endif // !Y_GRAPH_MST_BORUVKA_HPP