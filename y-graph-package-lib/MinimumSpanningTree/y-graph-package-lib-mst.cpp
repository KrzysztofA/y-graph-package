#include "y-graph-package-lib-mst.hpp"

using namespace yasuzume;

typedef std::vector<int>::iterator vector_iterator;

typedef utils::Stopwatch Stopwatch;

int main()
{
  graph::UndirectedGraph    new_graph {};
  graph::mst::Kruskals      kruskals {};
  graph::mst::Prims         prims {};
  graph::mst::Boruvka       boruvka {};
  graph::mst::ReverseDelete reverse_delete {};

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

  std::println( "{}", new_graph.get_graph_table_stringified() );
  utils::breakln();

  Stopwatch::start();
  auto new_graph_mst_kruskals { kruskals.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Kruskal's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_kruskals.get_edges() ) std::println( "{}", edge->get_stringified() );
  utils::breakln( 2 );

  std::println( "{}", new_graph_mst_kruskals.get_graph_table_stringified() );

  Stopwatch::start();
  auto new_graph_mst_prims { prims.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Prims's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_prims.get_edges() ) std::println( "{}", edge->get_stringified() );
  utils::breakln( 2 );

  std::println( "{}", new_graph_mst_prims.get_graph_table_stringified() );

  Stopwatch::start();
  auto new_graph_mst_boruvka { boruvka.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Boruvka's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_boruvka.get_edges() ) std::println( "{}", edge->get_stringified() );
  utils::breakln( 2 );

  std::println( "{}", new_graph_mst_boruvka.get_graph_table_stringified() );

  Stopwatch::start();
  auto new_graph_mst_reverse_delete { reverse_delete.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Reverse DeleteS ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_reverse_delete.get_edges() ) std::println( "{}", edge->get_stringified() );
  utils::breakln( 2 );

  std::println( "{}", new_graph_mst_reverse_delete.get_graph_table_stringified() );

  return 0;
}
