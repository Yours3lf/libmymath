#include <iostream>
#include <string>

//console coloring stuff
#include <Windows.h>
#include <wincon.h>

#include "mymath/mymath.h"
using namespace mymath;

HANDLE console_handle = GetStdHandle( STD_OUTPUT_HANDLE );

#define OUTPUT_ERRORS_ONLY

class unit_test
{
public:
  static void test( bool expr, const std::string& expr_str )
  {
    if( !expr )
    {
      SetConsoleTextAttribute( console_handle, FOREGROUND_RED );
      std::cerr << "Test failed: " << expr_str << std::endl;
    }
#ifndef OUTPUT_ERRORS_ONLY
    else
    {
      SetConsoleTextAttribute( console_handle, FOREGROUND_GREEN );
      std::cout << "Test successful: " << expr_str << std::endl;
    }
#endif
    SetConsoleTextAttribute( console_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
  }
};

#define STRINGIFY(S) (#S)
#define UNIT_TEST(S) unit_test::test(S, STRINGIFY(S))

int main( int argc, char** args )
{
  //common.h tests
  for( float eps = mm::epsilon, i = mm::epsilon; i < 100; i += ( eps *= 2 ) )
  {
    UNIT_TEST( mm::impl::is_eq( mm::inversesqrt( i ), 1.0f / std::sqrt(i) ) );
  }

  UNIT_TEST( mm::step( 2, -1 ) == 0 );
  UNIT_TEST( mm::step( -1, 2 ) == 1 );

  for( float eps = mm::epsilon, i = mm::epsilon; i < 1; i += ( eps *= 2 ) )
  {
    UNIT_TEST( mm::impl::is_eq( mm::mix( -1, 1, i ), i * 2 - 1 ) );
  }

  UNIT_TEST( mm::impl::is_eq( mm::fract( 1.2f ), 0.2f ) );
  UNIT_TEST( mm::impl::is_eq( mm::fract( -1.2f ), -0.2f ) );
  UNIT_TEST( mm::impl::is_eq( mm::fract( 0.0f ), 0.0f ) );

  UNIT_TEST( mm::impl::is_eq( mm::atan( 3, 2 ), 0.5880026f ) );
  UNIT_TEST( mm::impl::is_eq( mm::atan( -3, 2 ), -0.588f ) );

  UNIT_TEST( mm::impl::is_eq( mm::clamp( -2, -1, 1 ), -1 ) );
  UNIT_TEST( mm::impl::is_eq( mm::clamp( 2, -1, 1 ), 1 ) );

  UNIT_TEST( mm::impl::is_eq( mm::smoothstep( 1, 2, 3 ), 1 ) );
  UNIT_TEST( mm::impl::is_eq( mm::smoothstep( 1, 2, 0.5 ), 0 ) );
  UNIT_TEST( mm::impl::is_eq( mm::smoothstep( 1, 2, 1.5 ), 0.5f ) );
  UNIT_TEST( mm::impl::is_eq( mm::smoothstep( 1, 2, 1.6 ), 0.648f ) );

  UNIT_TEST( mm::fma( 2, 3, 4 ) == 10 );
  UNIT_TEST( mm::fma( 2, -3, 4 ) == -2 );
  UNIT_TEST( mm::fma( 2, 0, 4 ) == 4 );

  UNIT_TEST( mm::impl::is_eq( mm::radians( 360 ), two_pi ) );
  UNIT_TEST( mm::impl::is_eq( mm::degrees( pi ), 180 ) );

  UNIT_TEST( mm::sign( -2 ) == -1 );
  UNIT_TEST( mm::sign( 0 ) == 0 );
  UNIT_TEST( mm::sign( 2 ) == 1 );

  UNIT_TEST( mm::impl::is_eq( mm::asinh( -22 ), -3.784705763f ) );
  UNIT_TEST( mm::impl::is_eq( mm::asinh( 22 ), 3.784705763f ) );
  UNIT_TEST( mm::asinh( 0 ) == 0 );

  UNIT_TEST( mm::impl::is_eq( mm::acosh( 22 ), 3.7836727f ) );
  UNIT_TEST( mm::acosh( 1 ) == 0 );

  UNIT_TEST( mm::impl::is_eq( mm::atanh( -0.5 ), -0.549306144334f ) );
  UNIT_TEST( mm::impl::is_eq( mm::atanh( 0.5 ), 0.549306144334f ) );
  UNIT_TEST( mm::atanh( 0 ) == 0 );

  UNIT_TEST( mm::impl::is_eq( mm::log2( 22 ), 4.459431618637f ) );

  UNIT_TEST( mm::trunc( -1.9f ) == -1 );
  UNIT_TEST( mm::trunc( 1.9f ) == 1 );
  UNIT_TEST( mm::trunc( 0 ) == 0 );

  UNIT_TEST( mm::round( -1.9f ) == -2 );
  UNIT_TEST( mm::round( 1.9f ) == 2 );
  UNIT_TEST( mm::round( 0 ) == 0 );

  UNIT_TEST( mm::isnan( nanf(0) ) == true );
  UNIT_TEST( mm::isnan( 0 ) == false );

  UNIT_TEST( mm::isinf( INFINITY ) == true );
  UNIT_TEST( mm::isinf( 0 ) == false );

  UNIT_TEST( mm::min( 1, 2 ) == 1 );
  UNIT_TEST( mm::min( 1, -2 ) == -2 );
  UNIT_TEST( mm::min( 1, 0 ) == 0 );

  UNIT_TEST( mm::max( 1, 2 ) == 2 );
  UNIT_TEST( mm::max( 1, -2 ) == 1 );
  UNIT_TEST( mm::max( 1, 0 ) == 1 );

  system( "PAUSE" );

  return 0;
}