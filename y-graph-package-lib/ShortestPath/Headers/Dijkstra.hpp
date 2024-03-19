#ifndef Y_GRAPH_SHORTEST_PATH_DIJKSTRA_HPP
#define Y_GRAPH_SHORTEST_PATH_DIJKSTRA_HPP

#include <ShortestPath.inl>

namespace yasuzume::graph::shortest_path
{
  class Dijkstra : public ShortestPath
  {
  public:
    Dijkstra() = default;
    Dijkstra( const Dijkstra& ) = default;
    Dijkstra( Dijkstra&& ) noexcept = default;
    Dijkstra& operator=( const Dijkstra& ) = default;
    Dijkstra& operator=( Dijkstra&& ) noexcept = default;
    virtual   ~Dijkstra() noexcept override = default;

    virtual ShortestPathTree create_shortest_path( const NodePtr&, const UndirectedGraph& ) override;
    virtual ShortestPathTree create_shortest_path( const NodePtr&, const DirectedGraph& ) override;
    virtual Grid             create_shortest_path( const NodePtr&, const Grid& ) override;
    virtual WeightedGrid     create_shortest_path( const NodePtr&, const WeightedGrid& ) override;
  };
}

#endif // !Y_GRAPH_SHORTEST_PATH_DIJKSTRA_HPP
