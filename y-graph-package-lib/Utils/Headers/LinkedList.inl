#ifndef Y_UTILS_LINKED_LIST_INL
#define Y_UTILS_LINKED_LIST_INL

namespace yasuzume::utils
{
  template< typename T >
  struct LinkedList
  {
    explicit LinkedList( T _val ) : value( std::move( _val ) ) {}
    LinkedList() = default;
    LinkedList( const LinkedList& ) = default;
    LinkedList( LinkedList&& ) noexcept = default;
    LinkedList& operator=( const LinkedList& ) = default;
    LinkedList& operator=( LinkedList&& ) noexcept = default;
    ~LinkedList() noexcept = default;

    T value;

    LinkedList<T>* next { nullptr };
  };
}

#endif // !Y_UTILS_LINKED_LIST_INL