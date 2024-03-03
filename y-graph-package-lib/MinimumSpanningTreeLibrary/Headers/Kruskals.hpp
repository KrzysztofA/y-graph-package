#ifndef Y_GRAPH_MST_KRUSKALS_HPP
#define Y_GRAPH_MST_KRUSKALS_HPP

#include "./MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Kruskals final : public MinimumSpanningTreeAlgorithm
  {
    virtual Graph create_minimum_spanning_tree( const Graph& ) override;
  };
}

#endif // !Y_GRAPH_MST_KRUSKALS_HPP