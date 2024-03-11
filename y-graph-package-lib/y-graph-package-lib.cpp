#include "y-graph-package-lib.hpp"

template< typename T >
void print_container( const T& );

typedef std::vector<int>::iterator vector_iterator;

typedef yasuzume::utils::Stopwatch Stopwatch;

int main()
{
  std::vector<int> test_container {
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
  std::ranges::copy( test_container.begin(), test_container.end(), test_container2.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container3.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container4.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container5.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container6.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container7.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container8.begin() );

  yasuzume::sorts::BubbleSort<std::vector<int>>          bubble_sort {};
  yasuzume::sorts::InsertionSort<std::vector<int>>       insertion_sort {};
  yasuzume::sorts::SelectionSort<std::vector<int>>       selection_sort {};
  yasuzume::sorts::QuickSort<std::vector<int>>           quick_sort {};
  yasuzume::sorts::MergeSort<std::vector<int>>           merge_sort {};
  yasuzume::sorts::StandardLibrarySort<std::vector<int>> std_sort {};
  yasuzume::sorts::StableStandardSort<std::vector<int>>  std_stable {};
  yasuzume::sorts::QuickSortAtomic<std::vector<int>>     quick_sort_atomic {};

  std::cout << "BUBBLE SORT\n\n";
  print_container( test_container );
  Stopwatch::start();
  bubble_sort( std::begin( test_container ), std::end( test_container ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container );
  std::cout << "\n";

  std::cout << "INSERTION SORT\n\n";
  print_container( test_container2 );
  Stopwatch::start();
  insertion_sort( std::begin( test_container2 ), std::end( test_container2 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container2 );
  std::cout << "\n";

  std::cout << "SELECTION SORT\n\n";
  print_container( test_container3 );
  Stopwatch::start();
  selection_sort( std::begin( test_container3 ), std::end( test_container3 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container3 );
  std::cout << "\n";

  std::cout << "QUICK SORT\n\n";
  print_container( test_container4 );
  Stopwatch::start();
  quick_sort( std::begin( test_container4 ), std::end( test_container4 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container4 );
  std::cout << "\n";

  std::cout << "MERGE SORT\n\n";
  print_container( test_container5 );
  Stopwatch::start();
  merge_sort( std::begin( test_container5 ), std::end( test_container5 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container5 );
  std::cout << "\n";

  std::cout << "STD::SORT\n\n";
  print_container( test_container6 );
  Stopwatch::start();
  std_sort( std::begin( test_container6 ), std::end( test_container6 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container6 );
  std::cout << "\n";

  std::cout << "STD::STABLE SORT\n\n";
  print_container( test_container7 );
  Stopwatch::start();
  std_stable( std::begin( test_container7 ), std::end( test_container7 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container7 );
  std::cout << "\n";


  std::cout << "QUICK SORT ATOMIC\n\n";
  print_container( test_container8 );
  Stopwatch::start();
  quick_sort_atomic( std::begin( test_container8 ), std::end( test_container8 ) );
  std::cout << "\n" << Stopwatch::end() << " time\n\n";
  print_container( test_container8 );
  std::cout << "\n";
  yasuzume::graph::UndirectedGraph new_graph {};
  yasuzume::graph::mst::Kruskals kruskals {};
  yasuzume::graph::mst::Prims prims {};
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

  std::cout << "Original Graph: \n";
  for( const auto& edge : new_graph.get_edges() )
  {
    std::cout << edge->get_stringified() << "\n";
  }
  std::cout << "\n\n";


  auto new_graph_mst_kruskals { kruskals.create_minimum_spanning_tree( new_graph ) };

  std::cout << "With Kruskal's: \n";
  for( const auto& edge : new_graph_mst_kruskals.get_edges() )
  {
    std::cout << edge->get_stringified() << "\n";
  }
  std::cout << "\n\n";

  auto new_graph_mst_prims { prims.create_minimum_spanning_tree( new_graph ) };

  std::cout << "With Prim's: \n";
  for( const auto& edge : new_graph_mst_prims.get_edges() )
  {
    std::cout << edge->get_stringified() << "\n";
  }
  std::cout << "\n\n";

  std::cout.width( 3 );
  std::cout << " " << " ";
  for( const auto& i : new_graph_mst_prims.get_nodes() )
  {
    std::cout.width( 3 );
    std::cout << i->get_name() << " | ";
  }
  std::cout << "\n";

  auto distance_matrix { new_graph_mst_prims.get_graph_table_representation() };

  for( auto i { 0 }; i < std::ssize( distance_matrix ) && i < std::ssize( new_graph_mst_prims.get_nodes() ); i++ )
  {
    std::cout.width( 3 );
    std::cout << new_graph_mst_prims.get_nodes().at( i )->get_name() << " ";
    for( const auto& j : distance_matrix.at( i ) )
    {
      std::cout.width( 3 );
      std::cout << j << " | ";
    }
    std::cout << "\n";
  }

  return 0;
}

template< typename T >
void print_container( const T& _container )
{
  std::cout << "[ ";
  for( size_t i { 0 }; i < _container.size(); i++ ) std::cout << _container.at( i ) << ( i != _container.size() - 1 ? ", " : " ]" );
  std::cout << "\n";
}
