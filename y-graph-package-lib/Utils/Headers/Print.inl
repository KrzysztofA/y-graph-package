#ifndef Y_UTILS_PRINT_INL
#define Y_UTILS_PRINT_INL

#include <print>

namespace yasuzume::utils
{
  constexpr void breakln( const int& _lines = 1 )
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
}

#endif // !Y_UTILS_PRINT_INL