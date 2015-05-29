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
  UNIT_TEST( mm::all( mm::equal( a.yx = a.xy, vec2( 2, 1 ) ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::all( mm::equal( a.yx *= a.xy, vec2( 2, 2 ) ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::all( mm::equal( a.yx /= a.yx, vec2( 1, 1 ) ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::all( mm::equal( a.yx += a.xy, vec2( 3, 3 ) ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::all( mm::equal( a.yx -= a.yx, vec2( 0, 0 ) ) ) );
  a = vec2( 1, 2 );
  UNIT_TEST( mm::all( mm::equal( a.xx = a.xx, vec2( 1, 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( a = uvec2( 1, 2 ), vec2( 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a = ivec2( 1, 2 ), vec2( 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a = vec2( uvec2( 1, 2 ) ), vec2( 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a = vec2( ivec2( 1, 2 ) ), vec2( 1, 2 ) ) ) );

  //vec3 tests
  //TODO test basic functions
  vec3 b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.zyx = b.xyz, vec3( 3, 2, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.zyx *= b.xyz, vec3( 3, 4, 3 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.zyx /= b.zyx, vec3( 1, 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.zyx += b.xyz, vec3( 4, 4, 4 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.zyx -= b.zyx, vec3( 0, 0, 0 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xxx = b.xxx, vec3( 1, 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.yxx = b.yxx, vec3( 2, 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xyx = b.xyx, vec3( 1, 2, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xxy = b.xxy, vec3( 1, 1, 2 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xx = b.xx, vec2( 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xy = b.xx, vec2( 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xy *= b.yy, vec2( 2, 4 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xy /= b.xy, vec2( 1, 1 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xy += b.xy, vec2( 2, 4 ) ) ) );
  b = vec3( 1, 2, 3 );
  UNIT_TEST( mm::all( mm::equal( b.xy -= b.xy, vec2( 0, 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( b = uvec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b = ivec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b = vec3( uvec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b = vec3( ivec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) ) );

  //vec4 tests
  //TODO test basic functions
  vec4 c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.wzyx = c.xyzw, vec4( 4, 3, 2, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.wzyx *= c.xyzw, vec4( 4, 6, 6, 4 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.wzyx /= c.wzyx, vec4( 1, 1, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.wzyx += c.xyzw, vec4( 5, 5, 5, 5 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.wzyx -= c.wzyx, vec4( 0, 0, 0, 0 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xxxx = c.xxxx, vec4( 1, 1, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.yxxx = c.yxxx, vec4( 2, 1, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyxx = c.xyxx, vec4( 1, 2, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xxyx = c.xxyx, vec4( 1, 1, 2, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xxxy = c.xxxy, vec4( 1, 1, 1, 2 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.zyxx = c.zyxx, vec4( 3, 2, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.zxyx = c.zxyx, vec4( 3, 1, 2, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.zxxy = c.zxxy, vec4( 3, 1, 1, 2 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.yxx = c.yxx, vec3( 2, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyx = c.xyx, vec3( 1, 2, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xxy = c.xxy, vec3( 1, 1, 2 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.zyx = c.zyx, vec3( 3, 2, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyz *= c.xyz, vec3( 1, 4, 9 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyz /= c.xyz, vec3( 1, 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyz += c.xyz, vec3( 2, 4, 6 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xyz -= c.xyz, vec3( 0, 0, 0 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xx = c.xx, vec2( 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xy = c.xx, vec2( 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xy *= c.yy, vec2( 2, 4 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xy /= c.xy, vec2( 1, 1 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xy += c.xy, vec2( 2, 4 ) ) ) );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( c.xy -= c.xy, vec2( 0, 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( c = uvec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c = ivec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c = vec4( uvec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c = vec4( ivec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) ) );

  //swizzle out tests
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  //don't believe intellisense, this is valid code
  UNIT_TEST( mm::all( mm::equal( a.xxx, vec3( 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.yxx, vec3( 2, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xyx, vec3( 1, 2, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xxy, vec3( 1, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xxxx, vec4( 1, 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.yxxx, vec4( 2, 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xyxx, vec4( 1, 2, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xxyx, vec4( 1, 1, 2, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xxxy, vec4( 1, 1, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xyxy, vec4( 1, 2, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xyxy, vec4( 1, 2, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( a.xxyy, vec4( 1, 1, 2, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xxxx, vec4( 1, 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.yxxx, vec4( 2, 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xyxx, vec4( 1, 2, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xxyx, vec4( 1, 1, 2, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xxxy, vec4( 1, 1, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xyxy, vec4( 1, 2, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xyxy, vec4( 1, 2, 1, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.xxyy, vec4( 1, 1, 2, 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.yzxx, vec4( 2, 3, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.yxzx, vec4( 2, 1, 3, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b.yxxz, vec4( 2, 1, 1, 3 ) ) ) );

  //vec func tests
  //TODO test 
  //logic functions
  //negate
  //compare functions
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( a*a, vec2( 1, 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b*b, vec3( 1, 4, 9 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c*c, vec4( 1, 4, 9, 16 ) ) ) );
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( a/a, vec2( 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b/b, vec3( 1, 1, 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c/c, vec4( 1, 1, 1, 1 ) ) ) );
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( a+a, vec2( 2, 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b+b, vec3( 2, 4, 6 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c+c, vec4( 2, 4, 6, 8 ) ) ) );
  a = vec2( 1, 2 );
  b = vec3( 1, 2, 3 );
  c = vec4( 1, 2, 3, 4 );
  UNIT_TEST( mm::all( mm::equal( a-a, vec2( 0, 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( b-b, vec3( 0, 0, 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( c-c, vec4( 0, 0, 0, 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::sin( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec2( pi/2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec2( -pi / 2 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec3( pi / 2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec3( -pi / 2 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec4( pi / 2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sin( vec4( -pi / 2 ) ), vec4( -1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::cos( vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec2( pi ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec2( pi / 2 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec3( pi ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec3( pi / 2 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec4( 0 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec4( pi ) ), vec4( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cos( vec4( pi / 2 ) ), vec4( 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::tan( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec2( pi/6 ) ), vec2( 0.57735f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec2( -pi/6 ) ), vec2( -0.57735f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec3( pi / 6 ) ), vec3( 0.57735f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec3( -pi / 6 ) ), vec3( -0.57735f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec4( pi / 6 ) ), vec4( 0.57735f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tan( vec4( -pi / 6 ) ), vec4( -0.57735f ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::asin( vec2( -0.5 ) ), vec2( -0.5236 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec2( 0.5 ) ), vec2( 0.5236 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec3( -0.5 ) ), vec3( -0.5236 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec3( 0.5 ) ), vec3( 0.5236 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec4( -0.5 ) ), vec4( -0.5236 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asin( vec4( 0.5 ) ), vec4( 0.5236 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::acos( vec2( -0.5 ) ), vec2( 2.0944 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec2( 0 ) ), vec2( 1.5708 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec2( 0.5 ) ), vec2( 1.0472 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec3( -0.5 ) ), vec3( 2.0944 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec3( 0 ) ), vec3( 1.5708 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec3( 0.5 ) ), vec3( 1.0472 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec4( -0.5 ) ), vec4( 2.0944 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec4( 0 ) ), vec4( 1.5708 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acos( vec4( 0.5 ) ), vec4( 1.0472 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::atan( vec2( -0.5 ) ), vec2( -0.4636 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec2( 0.5 ) ), vec2( 0.4636 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec3( -0.5 ) ), vec3( -0.4636 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec3( 0.5 ) ), vec3( 0.4636 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec4( -0.5 ) ), vec4( -0.4636 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atan( vec4( 0.5 ) ), vec4( 0.4636 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec2( -0.5 ) ), vec2( -0.5211 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec2( 0.5 ) ), vec2( 0.5211 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec3( -0.5 ) ), vec3( -0.5211 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec3( 0.5 ) ), vec3( 0.5211 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec4( -0.5 ) ), vec4( -0.5211 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sinh( vec4( 0.5 ) ), vec4( 0.5211 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec2( -0.5 ) ), vec2( 1.1276 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec2( 0.5 ) ), vec2( 1.1276 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec3( -0.5 ) ), vec3( 1.1276 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec3( 0.5 ) ), vec3( 1.1276 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec4( -0.5 ) ), vec4( 1.1276 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec4( 0 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::cosh( vec4( 0.5 ) ), vec4( 1.1276 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec2( -0.5 ) ), vec2( -0.4621 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec2( 0.5 ) ), vec2( 0.4621 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec3( -0.5 ) ), vec3( -0.4621 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec3( 0.5 ) ), vec3( 0.4621 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec4( -0.5 ) ), vec4( -0.4621 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::tanh( vec4( 0.5 ) ), vec4( 0.4621 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec2( -0.5 ) ), vec2( -0.4812 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec2( 0.5 ) ), vec2( 0.4812 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec3( -0.5 ) ), vec3( -0.4812 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec3( 0.5 ) ), vec3( 0.4812 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec4( -0.5 ) ), vec4( -0.4812 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::asinh( vec4( 0.5 ) ), vec4( 0.4812 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::acosh( vec2( 2 ) ), vec2( 1.3170 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acosh( vec3( 2 ) ), vec3( 1.3170 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::acosh( vec4( 2 ) ), vec4( 1.3170 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec2( -0.5 ) ), vec2( -0.5493 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec2( 0.5 ) ), vec2( 0.5493 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec3( -0.5 ) ), vec3( -0.5493 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec3( 0.5 ) ), vec3( 0.5493 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec4( -0.5 ) ), vec4( -0.5493 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::atanh( vec4( 0.5 ) ), vec4( 0.5493 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::pow( vec2( 0.5 ), vec2( 2 ) ), vec2( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec2( 0.5 ), vec2( -2 ) ), vec2( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec2( 0.5 ), vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec3( 0.5 ), vec3( 2 ) ), vec3( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec3( 0.5 ), vec3( -2 ) ), vec3( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec3( 0.5 ), vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec4( 0.5 ), vec4( 2 ) ), vec4( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec4( 0.5 ), vec4( -2 ) ), vec4( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::pow( vec4( 0.5 ), vec4( 0 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::exp( vec2( 3 ) ), vec2( 20.0855 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec2( -3 ) ), vec2( 0.0498 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec3( 3 ) ), vec3( 20.0855 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec3( -3 ) ), vec3( 0.0498 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec4( 3 ) ), vec4( 20.0855 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec4( -3 ) ), vec4( 0.0498 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp( vec4( 0 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::log( vec2( 10 ) ), vec2( 2.3026 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::log( vec3( 10 ) ), vec3( 2.3026 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::log( vec4( 10 ) ), vec4( 2.3026 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec2( 4 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec3( 4 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec4( 4 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sqrt( vec4( 0 ) ), vec4( 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec2( 2 ) ), vec2( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec2( -2 ) ), vec2( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec3( 2 ) ), vec3( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec3( -2 ) ), vec3( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec4( 2 ) ), vec4( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec4( -2 ) ), vec4( 0.25 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::exp2( vec4( 0 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::inversesqrt( vec2( 4 ) ), vec2( 0.5 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::inversesqrt( vec3( 4 ) ), vec3( 0.5 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::inversesqrt( vec4( 4 ) ), vec4( 0.5 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::abs( vec2( 2 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec2( -2 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec3( 2 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec3( -2 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec4( 2 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec4( -2 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::abs( vec4( 0 ) ), vec4( 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::floor( vec2( 1.2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec2( 1.9 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec2( -1.2 ) ), vec2( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec2( -1.9 ) ), vec2( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec3( 1.2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec3( 1.9 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec3( -1.2 ) ), vec3( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec3( -1.9 ) ), vec3( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec4( 1.2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec4( 1.9 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec4( -1.2 ) ), vec4( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::floor( vec4( -1.9 ) ), vec4( -2 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec2( 1.2 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec2( 1.9 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec2( -1.2 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec2( -1.9 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec3( 1.2 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec3( 1.9 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec3( -1.2 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec3( -1.9 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec4( 1.2 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec4( 1.9 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec4( -1.2 ) ), vec4( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::ceil( vec4( -1.9 ) ), vec4( -1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::min( vec2( 1 ), vec2( 2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec2( 1 ), vec2( -2 ) ), vec2( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec2( 1 ), vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec3( 1 ), vec3( 2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec3( 1 ), vec3( -2 ) ), vec3( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec3( 1 ), vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec4( 1 ), vec4( 2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec4( 1 ), vec4( -2 ) ), vec4( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::min( vec4( 1 ), vec4( 0 ) ), vec4( 0 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::max( vec2( 1 ), vec2( 2 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec2( 1 ), vec2( -2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec2( 1 ), vec2( 0 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec3( 1 ), vec3( 2 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec3( 1 ), vec3( -2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec3( 1 ), vec3( 0 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec4( 1 ), vec4( 2 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec4( 1 ), vec4( -2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::max( vec4( 1 ), vec4( 0 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::sign( vec2( -2 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec2( 1 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec3( -2 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec3( 1 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec4( -2 ) ), vec4( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::sign( vec4( 1 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec2( 1.2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec2( 0 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec2( -1.2 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec3( 1.2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec3( 0 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec3( -1.2 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec4( 1.2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec4( 0 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::trunc( vec4( -1.2 ) ), vec4( -1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::round( vec2( 1.2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec2( 1.9 ) ), vec2( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec2( -1.2 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec2( -1.9 ) ), vec2( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec3( 1.2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec3( 1.9 ) ), vec3( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec3( -1.2 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec3( -1.9 ) ), vec3( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec4( 1.2 ) ), vec4( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec4( 1.9 ) ), vec4( 2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec4( -1.2 ) ), vec4( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::round( vec4( -1.9 ) ), vec4( -2 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::fract( vec2( 1.2 ) ), vec2( 0.2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fract( vec2( -1.2 ) ), vec2( -0.2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fract( vec3( 1.2 ) ), vec3( 0.2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fract( vec3( -1.2 ) ), vec3( -0.2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fract( vec4( 1.2 ) ), vec4( 0.2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fract( vec4( -1.2 ) ), vec4( -0.2 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::mod( vec2( 1.2 ), vec2( 0.8 ) ), vec2( 0.4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mod( vec2( 1.2 ), vec2( -0.8 ) ), vec2( -0.4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mod( vec3( 1.2 ), vec3( 0.8 ) ), vec3( 0.4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mod( vec3( 1.2 ), vec3( -0.8 ) ), vec3( -0.4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mod( vec4( 1.2 ), vec4( 0.8 ) ), vec4( 0.4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mod( vec4( 1.2 ), vec4( -0.8 ) ), vec4( -0.4 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::mix( vec2( 0.5 ), vec2( 0.4 ), vec2( 0.5 ) ), vec2( 0.45 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mix( vec2( 0.5 ), vec2( -0.4 ), vec2( 0.5 ) ), vec2( 0.05 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mix( vec3( 0.5 ), vec3( 0.4 ), vec3( 0.5 ) ), vec3( 0.45 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mix( vec3( 0.5 ), vec3( -0.4 ), vec3( 0.5 ) ), vec3( 0.05 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mix( vec4( 0.5 ), vec4( 0.4 ), vec4( 0.5 ) ), vec4( 0.45 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::mix( vec4( 0.5 ), vec4( -0.4 ), vec4( 0.5 ) ), vec4( 0.05 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::step( vec2( 2 ), vec2( -1 ) ), vec2( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::step( vec2( -1 ), vec2( 2 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::step( vec3( 2 ), vec3( -1 ) ), vec3( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::step( vec3( -1 ), vec3( 2 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::step( vec4( 2 ), vec4( -1 ) ), vec4( 0 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::step( vec4( -1 ), vec4( 2 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec2( -2 ), vec2( -1 ), vec2( 1 ) ), vec2( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec2( 2 ), vec2( -1 ), vec2( 1 ) ), vec2( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec3( -2 ), vec3( -1 ), vec3( 1 ) ), vec3( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec3( 2 ), vec3( -1 ), vec3( 1 ) ), vec3( 1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec4( -2 ), vec4( -1 ), vec4( 1 ) ), vec4( -1 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::clamp( vec4( 2 ), vec4( -1 ), vec4( 1 ) ), vec4( 1 ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::smoothstep( vec2( 1 ), vec2( 2 ), vec2( 1.6 ) ), vec2( 0.648f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::smoothstep( vec3( 1 ), vec3( 2 ), vec3( 1.6 ) ), vec3( 0.648f ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::smoothstep( vec4( 1 ), vec4( 2 ), vec4( 1.6 ) ), vec4( 0.648f ) ) ) );

  UNIT_TEST( mm::all( mm::equal( mm::fma( vec2( 2 ), vec2( 3 ), vec2( 4 ) ), vec2( 10 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec2( 2 ), vec2( -3 ), vec2( 4 ) ), vec2( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec2( 2 ), vec2( 0 ), vec2( 4 ) ), vec2( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec3( 2 ), vec3( 3 ), vec3( 4 ) ), vec3( 10 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec3( 2 ), vec3( -3 ), vec3( 4 ) ), vec3( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec3( 2 ), vec3( 0 ), vec3( 4 ) ), vec3( 4 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec4( 2 ), vec4( 3 ), vec4( 4 ) ), vec4( 10 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec4( 2 ), vec4( -3 ), vec4( 4 ) ), vec4( -2 ) ) ) );
  UNIT_TEST( mm::all( mm::equal( mm::fma( vec4( 2 ), vec4( 0 ), vec4( 4 ) ), vec4( 4 ) ) ) );

  //dot
  UNIT_TEST( mm::dot( vec2( 1 ), vec2( 2 ) ) == 4 );
  UNIT_TEST( mm::dot( vec2( 1, 0 ), vec2( -1, 0 ) ) == -1 );
  UNIT_TEST( mm::dot( vec2( 1, 0 ), vec2( 1, 0 ) ) == 1 );

  system( "PAUSE" );

  return 0;
}