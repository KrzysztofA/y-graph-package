#ifndef Y_UTILS_VALID_VALUE_INL
#define Y_UTILS_VALID_VALUE_INL

namespace yasuzume::utils
{
  template< typename T >
  struct ValidValue
  {
    ValidValue(): first(), second( false ) {}
    explicit ValidValue( T _val ) : first( _val ), second( false ) {}
    explicit ValidValue( T _val, const bool& _bool ) : first( _val ), second( _bool ) {}
    ValidValue( const ValidValue& ) = default;
    ValidValue( ValidValue&& ) noexcept = default;
    ValidValue& operator=( const ValidValue& ) = default;
    ValidValue& operator=( ValidValue&& ) noexcept = default;
    ~ValidValue() noexcept = default;

    T    first;
    bool second;

    [[nodiscard]] bool is_valid() const { return second; }
  };
}

#endif // !Y_UTILS_VALID_VALUE_INL
