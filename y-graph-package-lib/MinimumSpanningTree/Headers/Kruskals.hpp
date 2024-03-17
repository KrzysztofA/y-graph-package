#ifndef Y_GRAPH_MST_KRUSKALS_HPP
#define Y_GRAPH_MST_KRUSKALS_HPP

#include "./MinimumSpanningTreeAlgorithm.inl"

namespace yasuzume::graph::mst
{
  class Kruskals final : public MinimumSpanningTreeAlgorithm
  {
  public:
    Kruskals() = default;
    Kruskals( const Kruskals& ) = default;
    Kruskals( Kruskals&& ) noexcept = default;
    Kruskals& operator=( const Kruskals& ) = default;
    Kruskals& operator=( Kruskals&& ) noexcept = default;
    virtual ~Kruskals() noexcept override = default;

    virtual UndirectedGraph create_minimum_spanning_tree( const UndirectedGraph& ) override;
  };
}

#endif // !Y_GRAPH_MST_KRUSKALS_HPP