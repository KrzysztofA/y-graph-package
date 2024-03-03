#ifndef Y_UTILS_NUMERIC_INL
#define Y_UTILS_NUMERIC_INL

#include <functional>

namespace yasuzume::utils
{
  /**
   * @brief Compares 2 numbers with epsilon
   * @tparam N Numeric non-integer type
   * @param _x comparable 1
   * @param _y comparable 2
   * @return true if both are "equal" false if not
   */
  template< typename N >
  bool compare_almost( const N& _x, const N& _y )
  {
    return std::fabs( _x - _y ) < std::numeric_limits< N >::epsilon();
  }

  /**
   * @brief Compares 2 numbers with epsilon
   * @tparam N Numeric non-integer type
   * @param _x comparable 1
   * @param _y comparable 2
   * @param _tolerance how much gap between variables is tolerated
   * @return true if both are apart within given tolerance false if not
   */
  template< typename N >
  bool compare_with_tolerance( const N& _x, const N& _y, const N& _tolerance )
  {
    return std::fabs( _x - _y ) < _tolerance;
  }
}

#endif // !Y_UTILS_NUMERIC_INL