#include "../Headers/Prims.hpp"

namespace yasuzume::graph::mst
{
  UndirectedGraph Prims::create_minimum_spanning_tree( const UndirectedGraph& _graph )
  {
    // Prims has upper hand as graph representation in a table is already made

    const auto distance_matrix { _graph.get_graph_table_representation() };
    UndirectedGraph minimum_spanning_tree { UndirectedGraph::create_new_graph_from_nodes( _graph ) };
    std::set explored_indexes { 0 };

    while( std::ssize( explored_indexes ) < std::ssize( minimum_spanning_tree.get_nodes() ) )
    {
      auto saved_index { 0 };
      auto shortest_val { INFINITY };
      auto lowest_index { 0 };
      for( const auto& i : explored_indexes )
      {
        auto s { distance_matrix.at( i ) };

        // Select first row with the lowest value cross out that row, move to a row with the index of the column, select lowest value, repeat

        for( auto j { 0 }; j < std::ssize( s ); j++ )
        {
          if( i == j ) continue;
          if( explored_indexes.contains( j ) ) continue;
          if( s.at( j ) < shortest_val )
          {
            shortest_val = s.at( j );
            lowest_index = j;
            saved_index = i;
          }
        }
      }
      explored_indexes.emplace( lowest_index );
      minimum_spanning_tree.add_connection( saved_index, lowest_index, shortest_val );
    }
    return minimum_spanning_tree;
  }
}
