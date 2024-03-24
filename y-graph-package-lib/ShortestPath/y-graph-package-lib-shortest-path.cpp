#include "y-graph-package-lib-shortest-path.hpp"

using namespace yasuzume;

typedef utils::Stopwatch Stopwatch;

int main()
{
  graph::UndirectedGraph         new_graph {};
  graph::shortest_path::Dijkstra dijkstra {};
  graph::shortest_path::BellmanFord bellman_ford {};

  new_graph.add_node( "A" );
  new_graph.add_node( "B" );
  new_graph.add_node( "C" );
  new_graph.add_node( "D" );
  new_graph.add_node( "E" );
  new_graph.add_node( "F" );
  new_graph.add_node( "G" );

  new_graph.add_connection( 0, 1, 25 );
  new_graph.add_connection( 0, 2, 15 );
  new_graph.add_connection( 0, 4, 24 );
  new_graph.add_connection( 1, 2, 26 );
  new_graph.add_connection( 1, 4, 28 );
  new_graph.add_connection( 1, 5, 14 );
  new_graph.add_connection( 1, 6, 24 );
  new_graph.add_connection( 2, 2, 22 );
  new_graph.add_connection( 2, 4, 11 );
  new_graph.add_connection( 2, 6, 14 );
  new_graph.add_connection( 3, 4, 17 );
  new_graph.add_connection( 3, 4, 2 );
  new_graph.add_connection( 3, 5, 8 );
  new_graph.add_connection( 3, 6, 9 );
  new_graph.add_connection( 4, 5, 11 );
  new_graph.add_connection( 4, 6, 14 );
  new_graph.add_connection( 5, 5, 16 );
  new_graph.add_connection( 5, 6, 19 );
  new_graph.add_connection( 5, 6, 21 );

  std::println( "Original Graph:" );
  for( const auto& edge : new_graph.get_edges() ) std::println( "{}", edge->get_stringified() );
  utils::breakln( 2 );

  Stopwatch::start();
  auto shortest_path_djikstra { dijkstra.create_shortest_path( new_graph.get_node( "A" ), new_graph ) };
  Stopwatch::end();
  std::println( "With Dijkstra's ({}):", Stopwatch::last_record() );
  std::println( "{}", shortest_path_djikstra.get_stringified() );

  Stopwatch::start();
  auto shortest_path_bellman_ford { bellman_ford.create_shortest_path( new_graph.get_node( "A" ), new_graph ) };
  Stopwatch::end();
  std::println( "With Bellman Ford's ({}):", Stopwatch::last_record() );
  std::println( "{}", shortest_path_bellman_ford.get_stringified() );

  return 0;
}
