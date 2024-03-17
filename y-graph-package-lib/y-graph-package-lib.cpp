#include "y-graph-package-lib.hpp"

#include <Boruvka.hpp>
#include <print>

template< typename T >
void print_container( const T& );

constexpr void breakln( const int& = 1 );

typedef std::vector<int>::iterator vector_iterator;

typedef yasuzume::utils::Stopwatch Stopwatch;

int main()
{
  std::vector test_container {
    0, 1, 23, 31, 1, 2, 3, 45, 656, 123, 234, 12, 423, 0, 54, 32, 12, 12, 11, 21, 564, 223, 445, 999, 42, 420, 69, 71,
    821, 2, 12, 34, 24, 25, 26, 30, 40, 49, 87, 99, 70, 21, 1024, 12512, 125, 12454, 210, 21, 212, 214, 51, 521, 215,
    215
  };
  std::vector<int> test_container2( test_container.size() );
  std::vector<int> test_container3( test_container.size() );
  std::vector<int> test_container4( test_container.size() );
  std::vector<int> test_container5( test_container.size() );
  std::vector<int> test_container6( test_container.size() );
  std::vector<int> test_container7( test_container.size() );
  std::vector<int> test_container8( test_container.size() );
  std::vector<int> test_container9( test_container.size() );
  std::vector<int> test_container10( test_container.size() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container2.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container3.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container4.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container5.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container6.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container7.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container8.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container9.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container10.begin() );

  yasuzume::sorts::BubbleSort<std::vector<int>>             bubble_sort {};
  yasuzume::sorts::BubbleSortNonRecursive<std::vector<int>> bubble_sort_non_recursive {};
  yasuzume::sorts::InsertionSort<std::vector<int>>          insertion_sort {};
  yasuzume::sorts::SelectionSort<std::vector<int>>          selection_sort {};
  yasuzume::sorts::QuickSort<std::vector<int>>              quick_sort {};
  yasuzume::sorts::MergeSort<std::vector<int>>              merge_sort {};
  yasuzume::sorts::StandardLibrarySort<std::vector<int>>    std_sort {};
  yasuzume::sorts::StableStandardSort<std::vector<int>>     std_stable {};
  yasuzume::sorts::QuickSortAtomic<std::vector<int>>        quick_sort_atomic {};
  yasuzume::sorts::HashSort<std::vector<int>>               hash_sort { []( int a ) { return a; } };

  std::println( "BUBBLE SORT\n" );
  print_container( test_container );
  Stopwatch::start();
  bubble_sort( std::begin( test_container ), std::end( test_container ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container );
  breakln();

  std::println( "BUBBLE SORT NON RECURSIVE\n" );
  print_container( test_container9 );
  Stopwatch::start();
  bubble_sort_non_recursive( std::begin( test_container9 ), std::end( test_container9 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container9 );
  breakln();

  std::println( "INSERTION SORT\n" );
  print_container( test_container2 );
  Stopwatch::start();
  insertion_sort( std::begin( test_container2 ), std::end( test_container2 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container2 );
  breakln();

  std::println( "SELECTION SORT\n" );
  print_container( test_container3 );
  Stopwatch::start();
  selection_sort( std::begin( test_container3 ), std::end( test_container3 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container3 );
  breakln();

  std::println( "QUICK SORT\n" );
  print_container( test_container4 );
  Stopwatch::start();
  quick_sort( std::begin( test_container4 ), std::end( test_container4 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container4 );
  breakln();

  std::println( "MERGE SORT\n" );
  print_container( test_container5 );
  Stopwatch::start();
  merge_sort( std::begin( test_container5 ), std::end( test_container5 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container5 );
  breakln();

  std::println( "STD::SORT\n" );
  print_container( test_container6 );
  Stopwatch::start();
  std_sort( std::begin( test_container6 ), std::end( test_container6 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container6 );
  breakln();

  std::println( "STD::STABLE SORT\n" );
  print_container( test_container7 );
  Stopwatch::start();
  std_stable( std::begin( test_container7 ), std::end( test_container7 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container7 );
  breakln();

  std::println( "QUICK SORT ATOMIC\n" );
  print_container( test_container8 );
  Stopwatch::start();
  quick_sort_atomic( std::begin( test_container8 ), std::end( test_container8 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container8 );
  breakln();

  std::println( "HASH SORT\n" );
  print_container( test_container10 );
  Stopwatch::start();
  hash_sort( std::begin( test_container10 ), std::end( test_container10 ) );
  std::println( "\n {} time\n", Stopwatch::end() );
  print_container( test_container10 );
  breakln();

  yasuzume::graph::UndirectedGraph new_graph {};
  yasuzume::graph::mst::Kruskals   kruskals {};
  yasuzume::graph::mst::Prims      prims {};
  yasuzume::graph::mst::Boruvka    boruvka {};
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
  breakln( 2 );

  std::println( "{}", new_graph.get_graph_table_stringified() );
  breakln();

  Stopwatch::start();
  auto new_graph_mst_kruskals { kruskals.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Kruskal's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_kruskals.get_edges() ) std::println( "{}", edge->get_stringified() );
  breakln( 2 );

  std::println( "{}", new_graph_mst_kruskals.get_graph_table_stringified() );

  Stopwatch::start();
  auto new_graph_mst_prims { prims.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Prims's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_prims.get_edges() ) std::println( "{}", edge->get_stringified() );
  breakln( 2 );

  std::println( "{}", new_graph_mst_prims.get_graph_table_stringified() );

  Stopwatch::start();
  auto new_graph_mst_boruvka { boruvka.create_minimum_spanning_tree( new_graph ) };
  Stopwatch::end();
  std::println( "With Boruvka's ({}):", Stopwatch::last_record() );
  for( const auto& edge : new_graph_mst_boruvka.get_edges() ) std::println( "{}", edge->get_stringified() );
  breakln( 2 );

  std::println( "{}", new_graph_mst_boruvka.get_graph_table_stringified() );

  return 0;
}

constexpr void breakln( const int& _lines )
{
  for( auto i { 0 }; i < _lines; i++ ) std::println( "" );
}

template< typename T >
void print_container( const T& _container )
{
  std::print( "[ " );
  for( size_t i { 0 }; i < _container.size(); i++ ) std::print( "{}{} ", _container.at( i ), i != _container.size() - 1 ? "," : " ]" );
  std::println( "" );
}
