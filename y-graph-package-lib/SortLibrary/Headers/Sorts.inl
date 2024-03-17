#ifndef Y_SORTS_LIB_INL
#define Y_SORTS_LIB_INL

#include <algorithm>
#include <functional>
#include <LinkedList.inl>
#include <thread>
#include <unordered_set>


#ifdef _DEBUG

#include <print>

#endif

/*
 * Header only namespace containing all the sorts used for comparison exercise,
 * also includes std::sort for comparison enclosed in a functor.
 */
namespace yasuzume::sorts
{
#pragma region Defaults

  inline auto standard_determinant { [] <typename T>( const T& _x, const T& _y ) { return _x < _y; } };

#pragma endregion

#pragma region Bases

  template< std::ranges::range C > // Needs to be iterable
  class Sort
  {
  public:
    Sort() = default;
    // Copy constructor
    Sort( Sort& ) = default;
    // Move constructor
    Sort( Sort&& ) noexcept = default;
    // Copy assignment operator
    Sort& operator=( const Sort& ) = default;
    // Move assignment operator
    Sort& operator=( Sort&& ) noexcept = default;
    // Destructor
    virtual ~Sort() = default;

    /**
     * @brief Sort in given range
     */
    virtual void operator()( typename C::iterator, typename C::iterator ) = 0;

    /**
     * @brief Sort given container
     */
    virtual void operator()( C& ) = 0;

#ifdef _DEBUG

    /**
     * @brief Print the current state of the sorted range, useful in exploring behaviour
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    void print( typename C::iterator _begin, typename C::iterator _end )
    {
      for( auto i { _begin }; i != _end; ++i ) std::print( "{} ", *i );
      std::println( "" );
    }

#endif
  };

  template< std::ranges::range C > // Needs to be iterable
  class Comparison : public Sort<C>
  {
  public:
    /**
     * @brief Change determinant to a custom one
     * @param _determinant determinant lambda, condition for the sort
     */
    virtual void set_determinant(
      std::function<bool( const typename C::value_type&, const typename C::value_type& )> _determinant )
    {
      determinant_ = std::move( _determinant );
    }

  protected:
    std::function<bool( const typename C::value_type&, const typename C::value_type& )> determinant_ {
      standard_determinant
    };
  };

  template< typename T >
  concept Hashable = requires( T _a )
  {
    { std::hash<T> {}( _a ) } -> std::convertible_to<std::size_t>;
  };

  template< typename C, typename T >
  concept HashableRange = requires( C _c )
  {
    { std::hash<T> {}( std::begin( _c ) ) } -> std::convertible_to<std::size_t>;
    { std::hash<T> {}( std::end( _c ) ) } -> std::convertible_to<std::size_t>;
  };

  template< std::ranges::range C > // C needs to be a range of T
  class Key : public Sort<C>
  {
  public:
    explicit Key( std::function<size_t( const typename C::value_type& )> _key ) : key( std::move( _key ) ) {}

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end, const size_t& _max_size ) = 0;

    /**
     * @brief Change key to a custom one
     * @param _key determinant key, condition for the placement in the vector
     */
    virtual void set_key(
      std::function<size_t( const typename C::value_type& )> _key )
    {
      key = std::move( _key );
    }

  protected:
    std::function<size_t( const typename C::value_type& )> key {};
  };

  template< std::ranges::range C > // C needs to be a range of T
  class ReversibleKey : public Key<C>
  {
  public:
    explicit ReversibleKey( std::function<size_t( const typename C::value_type& )> _key, std::function<const typename C::value_type( const size_t )> _builder ) : Key<C>( _key ), builder( std::move( _builder ) ) {}

    /**
     * @brief Change builder function to a new one
     * @param _builder determinant builder, function that converts size_t to class type
     */
    virtual void set_builder(
      std::function<size_t( const typename C::value_type& )> _builder )
    {
      builder = std::move( _builder );
    }

  protected:
    std::function<const typename C::value_type( const size_t )> builder {};
  };


#pragma endregion

#pragma region Standard_Sorts

#pragma region Comparison_Sorts

  /**
   * @brief Bubble sort, comparison sort checking positions next to each other and swapping them if
   * determinant is met, if at least one swap occurred during iteration, recursive call is made
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Needs to be iterable
  class BubbleSort final : public Comparison<C>
  {
  public:
    /**
     * @brief Iterates over provided range, arguments must be of iterator to previously provided type
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      was_sorted_ = false; // Checks if container was sorted in this iteration
      for( auto i { _begin }; i != _end - 1; ++i )
        // Compare container position i with container position i + 1, swap if position i has greater value
        // Mark as sorted this iteration
        if( Comparison<C>::determinant_( *std::next( i ), *i ) )
        {
          std::swap( *std::next( i ), *i );
          was_sorted_ = true;
        }
#ifdef _DEBUG

      Sort<C>::print( _begin, _end );

#endif

      if( was_sorted_ ) operator()( _begin, _end );
    }

    /**
     * @brief Iterates over whole container
     * @param _container iterable container
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }

    void sort( typename C::iterator _begin, typename C::iterator _end )
    {
      operator()( _begin, _end );
    }

  private:
    bool was_sorted_ { false };
  };

  /**
   * @brief Bubble sort, comparison sort checking positions next to each other and swapping them if
   * determinant is met, if at least one swap occurred during iteration, the loop repeats
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Needs to be iterable
  class BubbleSortNonRecursive final : public Comparison<C>
  {
  public:
    /**
     * @brief Iterates over provided range, arguments must be of iterator to previously provided type
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      do
      {
        was_sorted_ = false;
        for( auto i { _begin }; i != _end - 1; ++i )
          // Compare container position i with container position i + 1, swap if position i has greater value
          // Mark as sorted this iteration
          if( Comparison<C>::determinant_( *std::next( i ), *i ) )
          {
            std::swap( *std::next( i ), *i );
            was_sorted_ = true;
          }
#ifdef _DEBUG

        Sort<C>::print( _begin, _end );

#endif
      } while( was_sorted_ );
    }

    /**
     * @brief Iterates over whole container
     * @param _container iterable container
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }

  private:
    bool was_sorted_ { false };
  };

  /**
   * @brief Insertion sort, comparison sort comparing ith and i-1 th positions in the container, if determinant is met for i and i-1 position,
   * starts comparing ith position with i-2 and so on until i == 0 or until determinant is no longer met, swapping this element step by step
   * @tparam C iterable container
   */
  template< typename C > // Needs to be iterable
  class InsertionSort final : public Comparison<C>
  {
  public:
    /**
     * @brief Sorts elements of a given range using insertion sort and given determinant
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      auto j { _begin };
      for( auto i { _begin }; i != _end; ++i )
      {
        j = i;
        // Start comparing container at position j with previous positions,
        // as long as the determinant is met
        while( j != _begin && Comparison<C>::determinant_( *j, *std::prev( j ) ) )
        {
          std::swap( *std::prev( j ), *j );
          --j;
        }

#ifdef _DEBUG

        Sort<C>::print( _begin, _end );

#endif
      }
    }

    /**
     * @brief sorts over entire container using insertion sort
     * @param _container container to be sorted
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  /**
   * @brief Selection sort, comparison sort selecting a single item and then comparing it with all next items by some determinant, then it swaps
   * the positions of selected item and the item the determinant was met for the last time
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Must be iterable
  class SelectionSort final : public Comparison<C>
  {
  public:
    /**
     * @brief Sorts elements of a given range using selection sort and given determinant
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      auto k { _begin };
      for( auto i { _begin }; i != _end; ++i )
      {
        // Look for determinant match in next positioned elements and note the last position determinant matched
        for( auto j { std::next( i ) }; j != _end; ++j ) if( Comparison<C>::determinant_( *j, *k ) ) k = j;

        // Swap position compared with the position determinant matched last time
        if( k != i ) std::swap( *i, *k );
        k = std::next( i );
#ifdef _DEBUG

        Sort<C>::print( _begin, _end );

#endif
      }
    }

    /**
     * @brief sorts over entire container using selection sort
     * @param _container container to be sorted
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  /**
   * @brief Quick sort, partitioning sort that swaps elements around the chosen pivot, it repeats it on each side of the pivot and so on,
   * until the pivot is sorted. Sort is multi-thread safe, but this is its single-thread implementation.
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Needs to be iterable
  class QuickSort final : public Comparison<C>
  {
  public:
    /**
     * @brief sorts over a given range using quick sort
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      if( _begin == _end ) return; // When low and high are equal _end execution

#ifdef _DEBUG

      Sort<C>::print( _begin, _end );

#endif

      auto pivot = *std::next( _begin, std::distance( _begin, _end ) / 2 );
      // Select pivot of the first division
      auto                                                          first_pivot_loc {
        std::partition( _begin, _end, [ &pivot, this ]( const auto& _x )
                        {
                          return Comparison<C>::determinant_( _x, pivot );
                        }
        )
      };

      // Select pivot of the second division
      auto                                                                   second_pivot_loc {
        std::partition( first_pivot_loc, _end, [ &pivot, this ]( const auto& _x )
                        {
                          return !Comparison<C>::determinant_( pivot, _x );
                        }
        )
      };
      operator()( _begin, first_pivot_loc ); // Divide container based on partition pivot
      operator()( second_pivot_loc, _end );
    }

    /**
     * @brief sorts over a container using quick sort
     * @param _container container to be sorted
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  /**
   * @brief Merge Sort is a sort of type divide and conquer, where all items in a list are halved until the size of each part is 1, then
   * these items are compared and merged together until the array is fully sorted.
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Needs to be iterable
  class MergeSort final : public Comparison<C>
  {
  public:
    /**
     * @brief sorts over a range using merge sort
     * @param _begin beginning of a range
     * @param _end end of a range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      //temporary_list_ = C(std::distance(_begin, _end));
      merge_sort( _begin, _end );
    }

    /**
     * @brief sorts over a container using merge sort
     * @param _container sorted container
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }

    /**
     * @brief divide step of the merge sort, divides the ranges recursively until they are atomic
     * @param _begin beginning of the range
     * @param _end ending of the range
     */
    void merge_sort( typename C::iterator _begin, typename C::iterator _end )
    {
      auto dist = std::distance( _begin, _end ); // Calculate range
      if( dist < 2 ) return; // If range is less than 2, skip

      // Measure midpoint
      auto mid = std::next( _begin, dist / 2 );

      // Divide into 2 halves
      merge_sort( _begin, mid );
      merge_sort( mid, _end );

      // Merge and sort halves
      merge( _begin, _end, C( std::distance( _begin, _end ) ) );

#ifdef _DEBUG

      Sort<C>::print( _begin, _end );

#endif
    }

    void sort( typename C::iterator _begin, typename C::iterator _end )
    {
      operator()( _begin, _end );
    }

  private:
    /**
     * @brief Merging and sorting step, implemented on iterators for cleaner code and better performance
     * @param _begin beginning of the range
     * @param _end end of the range
     * @param _temporary_list empty array of size of the range
     */
    void merge( typename C::iterator _begin, typename C::iterator _end, C _temporary_list )
    {
      // Get all extra iterators - for the middle, for beginning of the range, for middle again and for temporary list
      auto mid = std::next( _begin, std::distance( _begin, _end ) / 2 );
      auto i { _begin }, j { mid };
      auto z { std::begin( _temporary_list ) };

      // Sorting step - takes ranges from the beginning to half and from half to _end. Compare both
      // iterator values and append to temporary list one chosen by determinant, advance chosen one
      while( i != mid && j != _end )
      {
        if( Comparison<C>::determinant_( *i, *j ) )
        {
          *z = *i;
          std::advance( i, 1 );
        }
        else
        {
          *z = *j;
          std::advance( j, 1 );
        }
        std::advance( z, 1 );
      }

      // Copy remaining of the range that was not fully explored
      if( i != mid ) std::ranges::copy( i, mid, z );
      if( j != _end ) std::ranges::copy( j, _end, z );

      // Copy temporary array in place of original array
      std::ranges::copy( std::begin( _temporary_list ), std::end( _temporary_list ), _begin );
    }
  };

#pragma endregion

  /**
   * @brief Hash Sort is not an in place sort, it creates an additional vector using hashed values for items, then it replaces old values with new values
   * @tparam C iterable container
   */
  template< std::ranges::range C > // Iterable container
  class HashSort final : Key<C>
  {
  public:
    explicit HashSort( const std::function<size_t( const typename C::value_type& )>& _key ): Key<C>( _key ) {}

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      size_t max_val { 0 };
      for( auto i { _begin }; i != _end; ++i ) if( this->key( *i ) > max_val ) max_val = *i; // Get Maximum Value
      operator()( _begin, _end, max_val );
    }

    template< typename T >
    struct Pair
    {
      Pair(): first(), second( false ) {}
      explicit Pair( T _val ) : first( _val ), second( false ) {}
      explicit Pair( T _val, const bool& _bool ) : first( _val ), second( _bool ) {}
      Pair( const Pair& ) = default;
      Pair( Pair&& ) noexcept = default;
      Pair& operator=( const Pair& ) = default;
      Pair& operator=( Pair&& ) noexcept = default;
      ~Pair() noexcept = default;

      T    first;
      bool second;
    };

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end, const size_t& _max_val ) override
    {
      std::vector<utils::LinkedList<Pair<typename C::value_type>>*> temp_vector;
      temp_vector.reserve( ( _max_val + 1 ) );
      for( size_t i { 0 }; i <= _max_val; i++ ) temp_vector.emplace_back( new utils::LinkedList<Pair<typename C::value_type>>() );
      for( auto i { _begin }; i != _end; ++i )
      {
        auto                                             key_val { this->key( *i ) };
        utils::LinkedList<Pair<typename C::value_type>>* place { temp_vector.at( key_val ) };
        while( place->value.second && place->next != nullptr ) place = place->next;
        if( place->next == nullptr ) place->next = new utils::LinkedList<Pair<typename C::value_type>>( Pair<typename C::value_type>( *i, true ) );
        else place->value = Pair( *i, true );
      }
      auto                                             j { std::begin( temp_vector ) };
      utils::LinkedList<Pair<typename C::value_type>>* k { *j };
      for( auto i { _begin }; i != _end && j != std::end( temp_vector ); )
      {
        if( k->value.second )
        {
          *i = k->value.first;
          ++i;

#ifdef _DEBUG

          Sort<C>::print( _begin, _end );

#endif
        }
        if( k->next == nullptr )
        {
          ++j;
          if( j != std::end( temp_vector ) ) k = *j;
        }
        else k = k->next;
      }
    }

    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  // TODO
  template< std::ranges::range C > // Iterable container
  class CountingSort final : ReversibleKey<C>
  {
  public:
    explicit CountingSort( const std::function<size_t( const typename C::value_type& )>& _key, const std::function<typename C::value_type( const size_t )> _builder ) : ReversibleKey<C>( _key, _builder ) {}

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      size_t max_val{ 0 };
      for( auto i { _begin }; i != _end; ++i ) if( this->key( *i ) > max_val ) max_val = *i; // Get Maximum Value
      operator()( _begin, _end, max_val );
    }

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end, const size_t& _max_val ) override
    {
      std::vector<int> temp_vector( _max_val + 1 );
      std::vector<typename C::value_type> result_vector {};
      std::ranges::fill( temp_vector.begin(), temp_vector.end(), 0 );
      for( auto i { _begin }; i != _end; ++i ) ++temp_vector.at( this->key( *i ) );
      size_t index { 0 };
      for( const auto& i : temp_vector )
      {
        for( auto k { 0 }; k < i; k++ ) result_vector.emplace_back( this->builder( index ) );
        ++index;
      }

      size_t j { 0 };
      for( auto i{ _begin }; i != _end; ++i, ++j )
      {
        *i = result_vector.at( j );
#ifdef _DEBUG

        Sort<C>::print( _begin, _end );

#endif
      }
    }

    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  // TODO
  template< std::ranges::range C > // Iterable container
  class RadixSort final : ReversibleKey<C>
  {
  public:
    explicit RadixSort( const std::function<size_t( const typename C::value_type& )>& _key, const std::function<typename C::value_type( const size_t )> _builder ) : ReversibleKey<C>( _key, _builder ) {}

    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      
    }

    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

#pragma endregion

#pragma region Multithreaded_Sorts

  template< std::ranges::range C >
  class QuickSortAtomic final : Comparison<C>
  {
  public:
    /**
     * @brief sorts over a given range using quick sort
     * @param _begin beginning of the range
     * @param _end end of the range
     */
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      if( _begin == _end ) return; // When low and high are equal end execution

#ifdef _DEBUG

      Sort<C>::print( _begin, _end );

#endif

      auto pivot = *std::next( _begin, std::distance( _begin, _end ) / 2 );
      // Select pivot of the first division
      auto                                                          first_pivot_loc {
        std::partition( _begin, _end, [ &pivot, this ]( const auto& _x )
                        {
                          return Comparison<C>::determinant_( _x, pivot );
                        }
        )
      };

      // Select pivot of the second division
      auto                                                                   second_pivot_loc {
        std::partition( first_pivot_loc, _end, [ &pivot, this ]( const auto& _x )
                        {
                          return !Comparison<C>::determinant_( pivot, _x );
                        }
        )
      };
      std::thread begin_to_pivot_thread( &QuickSortAtomic::sort, this, _begin, first_pivot_loc );
      // Divide container based on partition pivot
      std::thread pivot_to_end_thread( &QuickSortAtomic::sort, this, second_pivot_loc, _end );

      begin_to_pivot_thread.join();
      pivot_to_end_thread.join();
    }

    /**
     * @brief sorts over a container using quick sort
     * @param _container container to be sorted
     */
    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }

    void sort( typename C::iterator _begin, typename C::iterator _end )
    {
      operator()( _begin, _end );
    }
  };

  class MergeSortAtomic {};

  class RadixSortAtomic {};

#pragma endregion

#pragma region Library_Sorts

  /**
   * @brief Standard library sort, usually implemented as intro sort, provides fast execution times. Here wrapped as functor.
   * @tparam C container to iterate over
   */
  template< std::ranges::range C > // Iterable container
  class StandardLibrarySort final : Comparison<C>
  {
  public:
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      std::sort( _begin, _end, Comparison<C>::determinant_ );
    }

    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

  /**
   * @brief Stable Sort ensures that equal items after sorting have the same order as before. Tool of standard library, here wrapped as functor.
   * @tparam C container to iterate over
   */
  template< std::ranges::range C > // Iterable
  class StableStandardSort final : Comparison<C>
  {
  public:
    virtual void operator()( typename C::iterator _begin, typename C::iterator _end ) override
    {
      std::stable_sort( _begin, _end, Comparison<C>::determinant_ );
    }

    virtual void operator()( C& _container ) override
    {
      operator()( std::begin( _container ), std::end( _container ) );
    }
  };

#pragma endregion
}

#endif // Y_SORTS_LIB_INL
