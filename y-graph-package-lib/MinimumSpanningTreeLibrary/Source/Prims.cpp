#include "../Headers/Prims.hpp"

namespace yasuzume::graph::mst
{
  Graph Prims::create_minimum_spanning_tree( const Graph& _graph )
  {
    // Prims has upper hand as graph representation in a table is already made

    const auto distance_matrix { _graph.get_graph_table_representation() };
    auto minimum_spanning_tree { Graph::create_new_graph_from_nodes( _graph ) };
    std::set<int> explored_indexes {};

    for( auto i { 0 }, k { 0 }; k < std::ssize( distance_matrix ); k++ )
    {
      auto s { distance_matrix.at( i ) };
      // Select first row with the lowest value cross out that row, move to a row with the index of the column, select lowest value, repeat
      auto shortest_val { INFINITY };
      auto lowest_index { 0 };

      for( auto j { 0 }; j < std::ssize( s ); j++ )
      {
        if( i == j ) continue;
        if( explored_indexes.contains( j ) ) continue;
        if( s.at( j ) < shortest_val )
        {
          shortest_val = s.at( j );
          lowest_index = j;
        }
      }
      explored_indexes.emplace( lowest_index );
      minimum_spanning_tree.add_undirected_connection( i, lowest_index, shortest_val );
      i = lowest_index;
    }

    return minimum_spanning_tree;
  }
}
