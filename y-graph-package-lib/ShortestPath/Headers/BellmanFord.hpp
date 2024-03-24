#ifndef Y_GRAPH_SHORTEST_PATH_BELLMAN_FORD_HPP
#define Y_GRAPH_SHORTEST_PATH_BELLMAN_FORD_HPP

#include <ShortestPath.inl>

namespace yasuzume::graph::shortest_path
{
  class BellmanFord final : public ShortestPath
  {
  public:
    BellmanFord() = default;
    BellmanFord( const BellmanFord& ) = default;
    BellmanFord( BellmanFord&& ) noexcept = default;
    BellmanFord& operator=( const BellmanFord& ) = default;
    BellmanFord& operator=( BellmanFord&& ) noexcept = default;
    virtual   ~BellmanFord() noexcept override = default;

    virtual ShortestPathTree create_shortest_path( const NodePtr&, const UndirectedGraph& ) override;
    virtual ShortestPathTree create_shortest_path( const NodePtr&, const DirectedGraph& ) override;
    // virtual Grid             create_shortest_path( const NodePtr&, const Grid& ) override;
    // virtual WeightedGrid     create_shortest_path( const NodePtr&, const WeightedGrid& ) override;
  };
}

#endif // !Y_GRAPH_SHORTEST_PATH_BELLMAN_FORD_HPP
