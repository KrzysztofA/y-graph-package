#include <Dijkstra.hpp>

namespace yasuzume::graph::shortest_path
{
  ShortestPathTree Dijkstra::create_shortest_path( const NodePtr& _starting_node, const UndirectedGraph& _graph )
  {
    ShortestPathTree shortest_path( _starting_node );

    for( auto& node : _graph.get_nodes() )
    {
      std::vector<EdgePtr> edges_temp {};
      shortest_path.tree.emplace( node, edges_temp );
    }

    _graph.get_graph_table_representation();

    

    return;
  }
1
0}