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

  //vec2 tests
  vec2 a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.yx = a.xy, vec2( 2, 1 ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.yx *= a.xy, vec2( 2, 2 ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.yx /= a.yx, vec2( 1, 1 ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.yx += a.xy, vec2( 3, 3 ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.yx -= a.yx, vec2( 0, 0 ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::equal( a.xx = a.xx, vec2( 1, 1 ) ) );

  UNIT_TEST( mm::equal( a = uvec2( 1, 2 ), vec2( 1, 2 ) ) );
  UNIT_TEST( mm::equal( a = ivec2( 1, 2 ), vec2( 1, 2 ) ) );
  UNIT_TEST( mm::equal( a = vec2( uvec2( 1, 2 ) ), vec2( 1, 2 ) ) );
  UNIT_TEST( mm::equal( a = vec2( ivec2( 1, 2 ) ), vec2( 1, 2 ) ) );

  //vec3 tests
  vec3 b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.zyx = b.xyz, vec3( 3, 2, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.zyx *= b.xyz, vec3( 3, 4, 3 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.zyx /= b.zyx, vec3( 1, 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.zyx += b.xyz, vec3( 4, 4, 4 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.zyx -= b.zyx, vec3( 0, 0, 0 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xxx = b.xxx, vec3( 1, 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.yxx = b.yxx, vec3( 2, 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xyx = b.xyx, vec3( 1, 2, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xxy = b.xxy, vec3( 1, 1, 2 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xx = b.xx, vec2( 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xy = b.xx, vec2( 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xy *= b.yy, vec2( 2, 4 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xy /= b.xy, vec2( 1, 1 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xy += b.xy, vec2( 2, 4 ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::equal( b.xy -= b.xy, vec2( 0, 0 ) ) );

  UNIT_TEST( mm::equal( b = uvec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) );
  UNIT_TEST( mm::equal( b = ivec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) );
  UNIT_TEST( mm::equal( b = vec3( uvec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) );
  UNIT_TEST( mm::equal( b = vec3( ivec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) );

  //vec4 tests
  vec4 c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.wzyx = c.xyzw, vec4( 4, 3, 2, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.wzyx *= c.xyzw, vec4( 4, 6, 6, 4 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.wzyx /= c.wzyx, vec4( 1, 1, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.wzyx += c.xyzw, vec4( 5, 5, 5, 5 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.wzyx -= c.wzyx, vec4( 0, 0, 0, 0 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xxxx = c.xxxx, vec4( 1, 1, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.yxxx = c.yxxx, vec4( 2, 1, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyxx = c.xyxx, vec4( 1, 2, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xxyx = c.xxyx, vec4( 1, 1, 2, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xxxy = c.xxxy, vec4( 1, 1, 1, 2 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.zyxx = c.zyxx, vec4( 3, 2, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.zxyx = c.zxyx, vec4( 3, 1, 2, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.zxxy = c.zxxy, vec4( 3, 1, 1, 2 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.yxx = c.yxx, vec3( 2, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyx = c.xyx, vec3( 1, 2, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xxy = c.xxy, vec3( 1, 1, 2 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.zyx = c.zyx, vec3( 3, 2, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyz *= c.xyz, vec3( 1, 4, 9 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyz /= c.xyz, vec3( 1, 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyz += c.xyz, vec3( 2, 4, 6 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xyz -= c.xyz, vec3( 0, 0, 0 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xx = c.xx, vec2( 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xy = c.xx, vec2( 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xy *= c.yy, vec2( 2, 4 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xy /= c.xy, vec2( 1, 1 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xy += c.xy, vec2( 2, 4 ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::equal( c.xy -= c.xy, vec2( 0, 0 ) ) );

  UNIT_TEST( mm::equal( c = uvec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) );
  UNIT_TEST( mm::equal( c = ivec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) );
  UNIT_TEST( mm::equal( c = vec4( uvec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) );
  UNIT_TEST( mm::equal( c = vec4( ivec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) );

  //swizzle out tests
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  //don't believe intellisense, this is valid code
  UNIT_TEST( mm::equal( a.xxx, vec3( 1, 1, 1 ) ) );
  UNIT_TEST( mm::equal( a.yxx, vec3( 2, 1, 1 ) ) );
  UNIT_TEST( mm::equal( a.xyx, vec3( 1, 2, 1 ) ) );
  UNIT_TEST( mm::equal( a.xxy, vec3( 1, 1, 2 ) ) );
  UNIT_TEST( mm::equal( a.xxxx, vec4( 1, 1, 1, 1 ) ) );
  UNIT_TEST( mm::equal( a.yxxx, vec4( 2, 1, 1, 1 ) ) );
  UNIT_TEST( mm::equal( a.xyxx, vec4( 1, 2, 1, 1 ) ) );
  UNIT_TEST( mm::equal( a.xxyx, vec4( 1, 1, 2, 1 ) ) );
  UNIT_TEST( mm::equal( a.xxxy, vec4( 1, 1, 1, 2 ) ) );
  UNIT_TEST( mm::equal( a.xyxy, vec4( 1, 2, 1, 2 ) ) );
  UNIT_TEST( mm::equal( a.xyxy, vec4( 1, 2, 1, 2 ) ) );
  UNIT_TEST( mm::equal( a.xxyy, vec4( 1, 1, 2, 2 ) ) );
  UNIT_TEST( mm::equal( b.xxxx, vec4( 1, 1, 1, 1 ) ) );
  UNIT_TEST( mm::equal( b.yxxx, vec4( 2, 1, 1, 1 ) ) );
  UNIT_TEST( mm::equal( b.xyxx, vec4( 1, 2, 1, 1 ) ) );
  UNIT_TEST( mm::equal( b.xxyx, vec4( 1, 1, 2, 1 ) ) );
  UNIT_TEST( mm::equal( b.xxxy, vec4( 1, 1, 1, 2 ) ) );
  UNIT_TEST( mm::equal( b.xyxy, vec4( 1, 2, 1, 2 ) ) );
  UNIT_TEST( mm::equal( b.xyxy, vec4( 1, 2, 1, 2 ) ) );
  UNIT_TEST( mm::equal( b.xxyy, vec4( 1, 1, 2, 2 ) ) );
  UNIT_TEST( mm::equal( b.yzxx, vec4( 2, 3, 1, 1 ) ) );
  UNIT_TEST( mm::equal( b.yxzx, vec4( 2, 1, 3, 1 ) ) );
  UNIT_TEST( mm::equal( b.yxxz, vec4( 2, 1, 1, 3 ) ) );

  //vec func tests


  system( "PAUSE" );

  return 0;
}