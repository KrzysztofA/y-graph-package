#include "y-graph-package-lib-sorts.hpp"

using namespace yasuzume;
using namespace yasuzume::sorts;

typedef std::vector<int>::iterator vector_iterator;

typedef utils::Stopwatch Stopwatch;

int main()
{
  std::vector test_container {
    0, 1, 23, 31, 1, 2, 3, 45, 656, 123, 234, 12, 423, 0, 54, 32, 12, 12, 11, 21, 564, 223, 445, 999, 42, 420, 69, 71,
    821, 2, 12, 34, 24, 25, 26, 30, 40, 49, 87, 99, 70, 21, 1024, 12512, 125, 12454, 210, 21, 212, 214, 51, 521, 215,
    215, 2, 3, 12, 11, 11, 18, 19, 221, 231, 321, 23, 43, 64, 64, 32, 12, 59, 39, 28, 27, 27, 129, 342, 124, 22, 11, 89,
    29, 22, 33, 21, 21, 4, 5, 2, 64, 64
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
  std::vector<int> test_container11( test_container.size() );
  std::vector<int> test_container12( test_container.size() );
  std::vector<int> test_container13( test_container.size() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container2.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container3.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container4.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container5.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container6.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container7.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container8.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container9.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container10.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container11.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container12.begin() );
  std::ranges::copy( test_container.begin(), test_container.end(), test_container13.begin() );

  BubbleSort<std::vector<int>>             bubble_sort {};
  BubbleSortNonRecursive<std::vector<int>> bubble_sort_non_recursive {};
  InsertionSort<std::vector<int>>          insertion_sort {};
  SelectionSort<std::vector<int>>          selection_sort {};
  QuickSort<std::vector<int>>              quick_sort {};
  MergeSort<std::vector<int>>              merge_sort {};
  StandardLibrarySort<std::vector<int>>    std_sort {};
  StableStandardSort<std::vector<int>>     std_stable {};
  QuickSortAtomic<std::vector<int>>        quick_sort_atomic {};
  HashSort<std::vector<int>>               hash_sort { []( const int    _a ) { return _a; } };
  CountingSort<std::vector<int>>           counting_sort( []( const int _a ) { return _a; }, []( const size_t _a ) { return static_cast<int>( _a ); } );

  std::println( "BUBBLE SORT\n" );
  utils::print_container( test_container );
  utils::Stopwatch::start();
  bubble_sort( std::begin( test_container ), std::end( test_container ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container );
  utils::breakln();

  std::println( "BUBBLE SORT NON RECURSIVE\n" );
  utils::print_container( test_container9 );
  utils::Stopwatch::start();
  bubble_sort_non_recursive( std::begin( test_container9 ), std::end( test_container9 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container9 );
  utils::breakln();

  std::println( "INSERTION SORT\n" );
  utils::print_container( test_container2 );
  utils::Stopwatch::start();
  insertion_sort( std::begin( test_container2 ), std::end( test_container2 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container2 );
  utils::breakln();

  std::println( "SELECTION SORT\n" );
  utils::print_container( test_container3 );
  utils::Stopwatch::start();
  selection_sort( std::begin( test_container3 ), std::end( test_container3 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container3 );
  utils::breakln();

  std::println( "QUICK SORT\n" );
  utils::print_container( test_container4 );
  utils::Stopwatch::start();
  quick_sort( std::begin( test_container4 ), std::end( test_container4 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container4 );
  utils::breakln();

  std::println( "MERGE SORT\n" );
  utils::print_container( test_container5 );
  utils::Stopwatch::start();
  merge_sort( std::begin( test_container5 ), std::end( test_container5 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container5 );
  utils::breakln();

  std::println( "STD::SORT\n" );
  utils::print_container( test_container6 );
  utils::Stopwatch::start();
  std_sort( std::begin( test_container6 ), std::end( test_container6 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container6 );
  utils::breakln();

  std::println( "STD::STABLE SORT\n" );
  utils::print_container( test_container7 );
  utils::Stopwatch::start();
  std_stable( std::begin( test_container7 ), std::end( test_container7 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container7 );
  utils::breakln();

  std::println( "QUICK SORT ATOMIC\n" );
  utils::print_container( test_container8 );
  utils::Stopwatch::start();
  quick_sort_atomic( std::begin( test_container8 ), std::end( test_container8 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container8 );
  utils::breakln();

  std::println( "HASH SORT\n" );
  utils::print_container( test_container10 );
  utils::Stopwatch::start();
  hash_sort( std::begin( test_container10 ), std::end( test_container10 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container10 );
  utils::breakln();

  std::println( "COUNTING SORT\n" );
  utils::print_container( test_container11 );
  utils::Stopwatch::start();
  counting_sort( std::begin( test_container11 ), std::end( test_container11 ) );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container11 );
  utils::breakln();

  std::println( "HASH SORT KNOWING MAX VALUE\n" );
  utils::print_container( test_container12 );
  utils::Stopwatch::start();
  hash_sort( std::begin( test_container12 ), std::end( test_container12 ), 12512 );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container10 );
  utils::breakln();

  std::println( "COUNTING SORT KNOWING MAX VALUE\n" );
  utils::print_container( test_container13 );
  utils::Stopwatch::start();
  counting_sort( std::begin( test_container13 ), std::end( test_container13 ), 12512 );
  std::println( "\n {} time\n", utils::Stopwatch::end() );
  utils::print_container( test_container11 );
  utils::breakln();

  return 0;
}
