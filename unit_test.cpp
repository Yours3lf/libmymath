#include <iostream>
#include <iomanip>
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

bool MAT2_EQUAL( const mat2& A, const mat2& B )
{
  return (mm::all( mm::equal( A[0], B[0] ) ) &&
    mm::all( mm::equal( A[1], B[1] ) ));
}

bool MAT3_EQUAL( const mat3& A, const mat3& B )
{
  return (mm::all( mm::equal( A[0], B[0] ) ) &&
    mm::all( mm::equal( A[1], B[1] ) ) &&
    mm::all( mm::equal( A[2], B[2] ) ));
}

bool MAT4_EQUAL( const mat4& A, const mat4& B )
{
  return (mm::all( mm::equal( A[0], B[0] ) ) &&
    mm::all( mm::equal( A[1], B[1] ) ) &&
    mm::all( mm::equal( A[2], B[2] ) ) &&
    mm::all( mm::equal( A[3], B[3] ) ));
}

bool QUAT_EQUAL( const quat& q1, const quat& q2 )
{
  return mm::all( mm::equal( q1.value, q2.value ) ) || mm::all( mm::equal( q1.value, (q2*-1.f).value ) );
}

int main( int argc, char** args )
{
  //vec4 v = vec4( 1, 2, 3, 4 );
  //v.wxzy = vec4( 1, 2, 3, 4 );

  {
    //common.h tests
    for( float eps = mm::epsilon, i = mm::epsilon; i < 100; i += (eps *= 2) )
    {
      UNIT_TEST( mm::impl::is_eq( mm::inversesqrt( i ), 1.0f / std::sqrt( i ) ) );
    }

    UNIT_TEST( mm::step( 2, -1 ) == 0 );
    UNIT_TEST( mm::step( -1, 2 ) == 1 );

    for( float eps = mm::epsilon, i = mm::epsilon; i < 1; i += (eps *= 2) )
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

    UNIT_TEST( mm::isnan( nanf( 0 ) ) == true );
    UNIT_TEST( mm::isnan( 0 ) == false );

    UNIT_TEST( mm::isinf( INFINITY ) == true );
    UNIT_TEST( mm::isinf( 0 ) == false );

    UNIT_TEST( mm::min( 1, 2 ) == 1 );
    UNIT_TEST( mm::min( 1, -2 ) == -2 );
    UNIT_TEST( mm::min( 1, 0 ) == 0 );

    UNIT_TEST( mm::max( 1, 2 ) == 2 );
    UNIT_TEST( mm::max( 1, -2 ) == 1 );
    UNIT_TEST( mm::max( 1, 0 ) == 1 );
  }

  {
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

    a = vec2( 1, 2 );
    UNIT_TEST( a.x == 1 );
    UNIT_TEST( a.y == 2 );
    UNIT_TEST( a.r == 1 );
    UNIT_TEST( a.g == 2 );
    UNIT_TEST( a.s == 1 );
    UNIT_TEST( a.t == 2 );
    UNIT_TEST( mm::all( mm::equal( vec2( 1, 1 ), vec2( 1 ) ) ) );
    UNIT_TEST( a[0] == 1 );
    UNIT_TEST( a[1] == 2 );
    UNIT_TEST( mm::all( mm::equal( (a *= 2), vec2( 2, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (a /= 2), vec2( 1, 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (a += a), vec2( 2, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (a -= a), vec2( 0, 0 ) ) ) );
    ivec2 ai = ivec2( 10 );
    uvec2 au = uvec2( 10 );
    UNIT_TEST( mm::all( mm::equal( (ai %= ivec2( 3 )), ivec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au %= uvec2( 3 )), uvec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (ai <<= ivec2( 1 )), ivec2( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au <<= uvec2( 1 )), uvec2( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (ai >>= ivec2( 1 )), ivec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au >>= uvec2( 1 )), uvec2( 1 ) ) ) );
    ai = ivec2( 255 );
    au = uvec2( 255 );
    UNIT_TEST( mm::all( mm::equal( (ai &= ivec2( 259 )), ivec2( 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au &= uvec2( 259 )), uvec2( 3 ) ) ) );
    ai = ivec2( 255 );
    au = uvec2( 255 );
    UNIT_TEST( mm::all( mm::equal( (ai ^= ivec2( 259 )), ivec2( 508 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au ^= uvec2( 259 )), uvec2( 508 ) ) ) );
    ai = ivec2( 255 );
    au = uvec2( 255 );
    UNIT_TEST( mm::all( mm::equal( (ai |= ivec2( 259 )), ivec2( 511 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (au |= uvec2( 259 )), uvec2( 511 ) ) ) );

    a = vec2( 1, 2 );
    UNIT_TEST( mm::all( mm::equal( ++a, vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( a++, vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( --a, vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( a--, vec2( 2, 3 ) ) ) );
    UNIT_TEST( a.length() == 2 );
  }

  {
    //vec3 tests
    vec3 b = vec3( 1, 2, 3 );
#ifndef MYMATH_FAST_COMPILE
    UNIT_TEST( mm::all( mm::equal( b.zyx = b.xyz, vec3( 3, 2, 1 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.zyx *= b.xyz, vec3( 3, 4, 3 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.zyx /= b.zyx, vec3( 1, 1, 1 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.zyx += b.xyz, vec3( 4, 4, 4 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST(mm::all(mm::equal(b.zyx -= b.zyx, vec3(0, 0, 0))));
#endif
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
#ifndef MYMATH_FAST_COMPILE
    UNIT_TEST( mm::all( mm::equal( b.xy = b.xx, vec2( 1, 1 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.xy *= b.yy, vec2( 2, 4 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.xy /= b.xy, vec2( 1, 1 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( b.xy += b.xy, vec2( 2, 4 ) ) ) );
    b = vec3( 1, 2, 3 );
    UNIT_TEST(mm::all(mm::equal(b.xy -= b.xy, vec2(0, 0))));
#endif

    UNIT_TEST( mm::all( mm::equal( b = uvec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b = ivec3( 1, 2, 3 ), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b = vec3( uvec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b = vec3( ivec3( 1, 2, 3 ) ), vec3( 1, 2, 3 ) ) ) );

    b = vec3( 1, 2, 3 );
    UNIT_TEST( b.x == 1 );
    UNIT_TEST( b.y == 2 );
    UNIT_TEST( b.z == 3 );
    UNIT_TEST( b.r == 1 );
    UNIT_TEST( b.g == 2 );
    UNIT_TEST( b.b == 3 );
    UNIT_TEST( b.s == 1 );
    UNIT_TEST( b.t == 2 );
    UNIT_TEST( b.q == 3 );
    UNIT_TEST( mm::all( mm::equal( vec3( 1, 1, 1 ), vec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec3( 1, 2, 3 ), vec3( vec2( 1, 2 ), 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec3( 1, 2, 3 ), vec3( 1, vec2( 2, 3 ) ) ) ) );
    UNIT_TEST( b[0] == 1 );
    UNIT_TEST( b[1] == 2 );
    UNIT_TEST( b[2] == 3 );
    UNIT_TEST( mm::all( mm::equal( (b *= 2), vec3( 2, 4, 6 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (b /= 2), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (b += b), vec3( 2, 4, 6 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (b -= b), vec3( 0, 0, 0 ) ) ) );
    ivec3 bi = ivec3( 10 );
    uvec3 bu = uvec3( 10 );
    UNIT_TEST( mm::all( mm::equal( (bi %= ivec3( 3 )), ivec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu %= uvec3( 3 )), uvec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bi <<= ivec3( 1 )), ivec3( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu <<= uvec3( 1 )), uvec3( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bi >>= ivec3( 1 )), ivec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu >>= uvec3( 1 )), uvec3( 1 ) ) ) );
    bi = ivec3( 255 );
    bu = uvec3( 255 );
    UNIT_TEST( mm::all( mm::equal( (bi &= ivec3( 259 )), ivec3( 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu &= uvec3( 259 )), uvec3( 3 ) ) ) );
    bi = ivec3( 255 );
    bu = uvec3( 255 );
    UNIT_TEST( mm::all( mm::equal( (bi ^= ivec3( 259 )), ivec3( 508 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu ^= uvec3( 259 )), uvec3( 508 ) ) ) );
    bi = ivec3( 255 );
    bu = uvec3( 255 );
    UNIT_TEST( mm::all( mm::equal( (bi |= ivec3( 259 )), ivec3( 511 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (bu |= uvec3( 259 )), uvec3( 511 ) ) ) );

    b = vec3( 1, 2, 3 );
    UNIT_TEST( mm::all( mm::equal( ++b, vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b++, vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( --b, vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b--, vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( b.length() == 3 );
  }

  {
    //vec4 tests
    vec4 c = vec4( 1, 2, 3, 4 );
#ifndef MYMATH_FAST_COMPILE
    UNIT_TEST( mm::all( mm::equal( c.wzyx = c.xyzw, vec4( 4, 3, 2, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.wzyx *= c.xyzw, vec4( 4, 6, 6, 4 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.wzyx /= c.wzyx, vec4( 1, 1, 1, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.wzyx += c.xyzw, vec4( 5, 5, 5, 5 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST(mm::all(mm::equal(c.wzyx -= c.wzyx, vec4(0, 0, 0, 0))));
#endif
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
#ifndef MYMATH_FAST_COMPILE
    UNIT_TEST( mm::all( mm::equal( c.zyx = c.zyx, vec3( 3, 2, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xyz *= c.xyz, vec3( 1, 4, 9 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xyz /= c.xyz, vec3( 1, 1, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xyz += c.xyz, vec3( 2, 4, 6 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST(mm::all(mm::equal(c.xyz -= c.xyz, vec3(0, 0, 0))));
#endif
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xx = c.xx, vec2( 1, 1 ) ) ) );
#ifndef MYMATH_FAST_COMPILE
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xy = c.xx, vec2( 1, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xy *= c.yy, vec2( 2, 4 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xy /= c.xy, vec2( 1, 1 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( c.xy += c.xy, vec2( 2, 4 ) ) ) );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST(mm::all(mm::equal(c.xy -= c.xy, vec2(0, 0))));
#endif

    UNIT_TEST( mm::all( mm::equal( c = uvec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c = ivec4( 1, 2, 3, 4 ), vec4( 1, 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c = vec4( uvec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c = vec4( ivec4( 1, 2, 3, 4 ) ), vec4( 1, 2, 3, 4 ) ) ) );

    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( c.x == 1 );
    UNIT_TEST( c.y == 2 );
    UNIT_TEST( c.z == 3 );
    UNIT_TEST( c.w == 4 );
    UNIT_TEST( c.r == 1 );
    UNIT_TEST( c.g == 2 );
    UNIT_TEST( c.b == 3 );
    UNIT_TEST( c.a == 4 );
    UNIT_TEST( c.s == 1 );
    UNIT_TEST( c.t == 2 );
    UNIT_TEST( c.q == 3 );
    UNIT_TEST( c.p == 4 );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 1, 1, 1 ), vec4( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( vec3( 1, 2, 3 ), 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( 1, vec3( 2, 3, 4 ) ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( vec2( 1, 2 ), vec2( 3, 4 ) ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( vec2( 1, 2 ), 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( 1, vec2( 2, 3 ), 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( vec4( 1, 2, 3, 4 ), vec4( 1, 2, vec2( 3, 4 ) ) ) ) );
    UNIT_TEST( c[0] == 1 );
    UNIT_TEST( c[1] == 2 );
    UNIT_TEST( c[2] == 3 );
    UNIT_TEST( c[3] == 4 );
    UNIT_TEST( mm::all( mm::equal( (c *= 2), vec4( 2, 4, 6, 8 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (c /= 2), vec4( 1, 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (c += c), vec4( 2, 4, 6, 8 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (c -= c), vec4( 0, 0, 0, 0 ) ) ) );
    ivec4 ci = ivec4( 10 );
    uvec4 cu = uvec4( 10 );
    UNIT_TEST( mm::all( mm::equal( (ci %= ivec4( 3 )), ivec4( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu %= uvec4( 3 )), uvec4( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (ci <<= ivec4( 1 )), ivec4( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu <<= uvec4( 1 )), uvec4( 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (ci >>= ivec4( 1 )), ivec4( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu >>= uvec4( 1 )), uvec4( 1 ) ) ) );
    ci = ivec4( 255 );
    cu = uvec4( 255 );
    UNIT_TEST( mm::all( mm::equal( (ci &= ivec4( 259 )), ivec4( 3 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu &= uvec4( 259 )), uvec4( 3 ) ) ) );
    ci = ivec4( 255 );
    cu = uvec4( 255 );
    UNIT_TEST( mm::all( mm::equal( (ci ^= ivec4( 259 )), ivec4( 508 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu ^= uvec4( 259 )), uvec4( 508 ) ) ) );
    ci = ivec4( 255 );
    cu = uvec4( 255 );
    UNIT_TEST( mm::all( mm::equal( (ci |= ivec4( 259 )), ivec4( 511 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (cu |= uvec4( 259 )), uvec4( 511 ) ) ) );

    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( ++c, vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c++, vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( --c, vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c--, vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( c.length() == 4 );
  }

  {
    //swizzle out tests
    vec2 a = vec2( 1, 2 );
    vec3 b = vec3( 1, 2, 3 );
    vec4 c = vec4( 1, 2, 3, 4 );
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
  }

  {
    //vec func tests
    vec2 a;
    vec3 b;
    vec4 c;

    UNIT_TEST( mm::all( mm::equal( mm::not( bvec2( true, false ) ), bvec2( false, true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::not( bvec3( true, false, true ) ), bvec3( false, true, false ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::not( bvec4( true, false, true, false ) ), bvec4( false, true, false, true ) ) ) );
    UNIT_TEST( mm::all( mm::notEqual( mm::not( bvec2( true, false ) ), bvec2( true, false ) ) ) );
    UNIT_TEST( mm::all( mm::notEqual( mm::not( bvec3( true, false, true ) ), bvec3( true, false, true ) ) ) );
    UNIT_TEST( mm::all( mm::notEqual( mm::not( bvec4( true, false, true, false ) ), bvec4( true, false, true, false ) ) ) );
    UNIT_TEST( mm::any( bvec2( true, false ) ) == true );
    UNIT_TEST( mm::any( bvec3( true, false, false ) ) == true );
    UNIT_TEST( mm::any( bvec4( true, false, false, false ) ) == true );
    UNIT_TEST( mm::any( bvec2( false, false ) ) == false );
    UNIT_TEST( mm::any( bvec3( false, false, false ) ) == false );
    UNIT_TEST( mm::any( bvec4( false, false, false, false ) ) == false );
    UNIT_TEST( mm::all( bvec2( true, false ) ) == false );
    UNIT_TEST( mm::all( bvec3( true, false, false ) ) == false );
    UNIT_TEST( mm::all( bvec4( true, false, false, false ) ) == false );
    UNIT_TEST( mm::all( bvec2( true, true ) ) == true );
    UNIT_TEST( mm::all( bvec3( true, true, true ) ) == true );
    UNIT_TEST( mm::all( bvec4( true, true, true, true ) ) == true );

    UNIT_TEST( mm::all( mm::equal( -vec2( 1 ), vec2( -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( -vec3( 1 ), vec3( -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( -vec4( 1 ), vec4( -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( -vec2( -1 ), vec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( -vec3( -1 ), vec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( -vec4( -1 ), vec4( 1 ) ) ) );

    UNIT_TEST( mm::all( mm::lessThan( vec2( 1, 2 ), vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThan( vec2( -3, 2 ), vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThan( vec3( 1, 2, 3 ), vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThan( vec3( -3, 2, 3 ), vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThan( vec4( 1, 2, 3, 4 ), vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThan( vec4( -3, 2, 3, 4 ), vec4( 2, 3, 4, 5 ) ) ) );

    UNIT_TEST( mm::all( mm::greaterThan( vec2( 2, 3 ), vec2( 1, 2 ) ) ) );
    UNIT_TEST( mm::all( mm::greaterThan( vec3( 2, 3, 4 ), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::greaterThan( vec4( 2, 3, 4, 5 ), vec4( 1, 2, 3, 4 ) ) ) );

    UNIT_TEST( mm::all( mm::lessThanEqual( vec2( 2, 2 ), vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThanEqual( vec2( -3, 2 ), vec2( 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThanEqual( vec3( 2, 2, 3 ), vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThanEqual( vec3( -3, 2, 3 ), vec3( 2, 3, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThanEqual( vec4( 2, 2, 3, 4 ), vec4( 2, 3, 4, 5 ) ) ) );
    UNIT_TEST( mm::all( mm::lessThanEqual( vec4( -3, 2, 3, 4 ), vec4( 2, 3, 4, 5 ) ) ) );

    UNIT_TEST( mm::all( mm::greaterThanEqual( vec2( 1, 3 ), vec2( 1, 2 ) ) ) );
    UNIT_TEST( mm::all( mm::greaterThanEqual( vec3( 1, 3, 4 ), vec3( 1, 2, 3 ) ) ) );
    UNIT_TEST( mm::all( mm::greaterThanEqual( vec4( 1, 3, 4, 5 ), vec4( 1, 2, 3, 4 ) ) ) );

    a = vec2( 1, 2 );
    b = vec3( 1, 2, 3 );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( a*a, vec2( 1, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b*b, vec3( 1, 4, 9 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c*c, vec4( 1, 4, 9, 16 ) ) ) );
    a = vec2( 1, 2 );
    b = vec3( 1, 2, 3 );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( a / a, vec2( 1, 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b / b, vec3( 1, 1, 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c / c, vec4( 1, 1, 1, 1 ) ) ) );
    a = vec2( 1, 2 );
    b = vec3( 1, 2, 3 );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( a + a, vec2( 2, 4 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b + b, vec3( 2, 4, 6 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c + c, vec4( 2, 4, 6, 8 ) ) ) );
    a = vec2( 1, 2 );
    b = vec3( 1, 2, 3 );
    c = vec4( 1, 2, 3, 4 );
    UNIT_TEST( mm::all( mm::equal( a - a, vec2( 0, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b - b, vec3( 0, 0, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c - c, vec4( 0, 0, 0, 0 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::sin( vec2( 0 ) ), vec2( 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::sin( vec2( pi / 2 ) ), vec2( 1 ) ) ) );
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
    UNIT_TEST( mm::all( mm::equal( mm::tan( vec2( pi / 6 ) ), vec2( 0.57735f ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::tan( vec2( -pi / 6 ) ), vec2( -0.57735f ) ) ) );
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

    UNIT_TEST( mm::dot( vec2( 1 ), vec2( 2 ) ) == 4 );
    UNIT_TEST( mm::dot( vec2( 1, 0 ), vec2( -1, 0 ) ) == -1 );
    UNIT_TEST( mm::dot( vec2( 1, 0 ), vec2( 1, 0 ) ) == 1 );
    UNIT_TEST( mm::dot( vec3( 1 ), vec3( 2 ) ) == 6 );
    UNIT_TEST( mm::dot( vec3( 1, 0, 0 ), vec3( -1, 0, 0 ) ) == -1 );
    UNIT_TEST( mm::dot( vec3( 1, 0, 0 ), vec3( 1, 0, 0 ) ) == 1 );
    UNIT_TEST( mm::dot( vec4( 1 ), vec4( 2 ) ) == 8 );
    UNIT_TEST( mm::dot( vec4( 1, 0, 0, 0 ), vec4( -1, 0, 0, 0 ) ) == -1 );
    UNIT_TEST( mm::dot( vec4( 1, 0, 0, 0 ), vec4( 1, 0, 0, 0 ) ) == 1 );

    UNIT_TEST( mm::impl::is_eq( mm::length( vec2( 1, 2 ) ), std::sqrt( 5.0f ) ) );
    UNIT_TEST( mm::impl::is_eq( mm::length( vec3( 2, 3, 4 ) ), std::sqrt( 29.0f ) ) );
    UNIT_TEST( mm::impl::is_eq( mm::length( vec4( 2, 3, 4, 5 ) ), std::sqrt( 54.0f ) ) );

    UNIT_TEST( mm::impl::is_eq( mm::distance( vec2( 1, 2 ), vec2( 1, 3 ) ), 1 ) );
    UNIT_TEST( mm::impl::is_eq( mm::distance( vec2( 1, -2 ), vec2( 1, 3 ) ), 5 ) );
    UNIT_TEST( mm::impl::is_eq( mm::distance( vec3( 1, 2, 4 ), vec3( 1, 3, 4 ) ), 1 ) );
    UNIT_TEST( mm::impl::is_eq( mm::distance( vec3( 1, -2, 4 ), vec3( 1, 3, 4 ) ), 5 ) );
    UNIT_TEST( mm::impl::is_eq( mm::distance( vec4( 1, 2, 4, 5 ), vec4( 1, 3, 4, 5 ) ), 1 ) );
    UNIT_TEST( mm::impl::is_eq( mm::distance( vec4( 1, -2, 4, 5 ), vec4( 1, 3, 4, 5 ) ), 5 ) );

    UNIT_TEST( mm::all( mm::equal( mm::normalize( vec2( 1 ) ), vec2( 0.7071 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::normalize( vec3( 1 ) ), vec3( 0.57735 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::normalize( vec4( 1 ) ), vec4( 0.5 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::reflect( vec2( -1 ), vec2( 0, 1 ) ), vec2( -1, 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::reflect( vec3( -1 ), vec3( 0, 1, 0 ) ), vec3( -1, 1, -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::reflect( vec4( -1 ), vec4( 0, 1, 0, 0 ) ), vec4( -1, 1, -1, -1 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::refract( vec2( -1 ), vec2( 0, 1 ), 0.5 ), vec2( -0.5, -1.0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::refract( vec3( -1 ), vec3( 0, 1, 0 ), 0.5 ), vec3( -0.5, -1.0, -0.5 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::refract( vec4( -1 ), vec4( 0, 1, 0, 0 ), 0.5 ), vec4( -0.5, -1.0, -0.5, -0.5 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec2( -1 ), vec2( 1 ), vec2( 0, 1 ) ), vec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec2( 1 ), vec2( -1 ), vec2( 0, 1 ) ), vec2( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec3( -1 ), vec3( 1 ), vec3( 0, 1, 0 ) ), vec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec3( 1 ), vec3( -1 ), vec3( 0, 1, 0 ) ), vec3( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec4( -1 ), vec4( 1 ), vec4( 0, 1, 0, 0 ) ), vec4( 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::faceforward( vec4( 1 ), vec4( -1 ), vec4( 0, 1, 0, 0 ) ), vec4( 1 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec2( nanf( 0 ) ) ), bvec2( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec2( 0 ) ), bvec2( false ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec3( nanf( 0 ) ) ), bvec3( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec3( 0 ) ), bvec3( false ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec4( nanf( 0 ) ) ), bvec4( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isnan( vec4( 0 ) ), bvec4( false ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec2( INFINITY ) ), bvec2( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec2( 0 ) ), bvec2( false ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec3( INFINITY ) ), bvec3( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec3( 0 ) ), bvec3( false ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec4( INFINITY ) ), bvec4( true ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mm::isinf( vec4( 0 ) ), bvec4( false ) ) ) );

    UNIT_TEST( mm::all( mm::equal( mm::cross( vec3( 1, 0, 0 ), vec3( 0, 1, 0 ) ), vec3( 0, 0, 1 ) ) ) );
  }

  {
    //mat2 tests
    //generated in Matlab using:
    //randn( 2 ), randn( 3 ), randn( 4 )
    mat2 ma = mat2::identity;

    UNIT_TEST( MAT2_EQUAL( ma, mat2( vec2( 1, 0 ), vec2( 0, 1 ) ) ) );
    UNIT_TEST( MAT2_EQUAL( ma, mat2( 1 ) ) );

    UNIT_TEST( ma[0].x == 1 );
    UNIT_TEST( ma[0].y == 0 );

    ma = mat2( 0.2147, 1.0665,
      0.16, 2.6088 );

    UNIT_TEST( MAT2_EQUAL( (ma *= mm::inverse( ma )), mat2::identity ) );
    UNIT_TEST( MAT2_EQUAL( (ma *= 2), mat2( 2 ) ) );
    UNIT_TEST( MAT2_EQUAL( (++ma), mat2( 3, 1, 1, 3 ) ) );
    UNIT_TEST( MAT2_EQUAL( (ma++), mat2( 3, 1, 1, 3 ) ) );
    UNIT_TEST( MAT2_EQUAL( (--ma), mat2( 3, 1, 1, 3 ) ) );
    UNIT_TEST( MAT2_EQUAL( (ma--), mat2( 3, 1, 1, 3 ) ) );
  }

  {
    //mat3 tests
    mat3 mb = mat3::identity;
    const mm::vec3 arbitraryAxis( 10, 11, 12 );

    UNIT_TEST( MAT3_EQUAL( mat3( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ), mat3( quat( std::sqrt( 2.f ), arbitraryAxis ) ) ) );
    UNIT_TEST( MAT3_EQUAL( mb, mat3( vec3( 1, 0, 0 ), vec3( 0, 1, 0 ), vec3( 0, 0, 1 ) ) ) );
    UNIT_TEST( MAT3_EQUAL( mb, mat3( 1 ) ) );

    UNIT_TEST( mb[1].x == 0 );
    UNIT_TEST( mb[1].y == 1 );

    UNIT_TEST( MAT3_EQUAL( mat3( 2 ), mat3( mat4( 2 ) ) ) );

    mb = mat3( 0.0313, -2.0781, -1.6148,
      0.5045, 0.5253, -0.7856,
      -1.1963, -0.6228, -0.2589 );

    UNIT_TEST( MAT3_EQUAL( (mb *= mm::inverse( mb )), mat3::identity ) );
    UNIT_TEST( MAT3_EQUAL( (mb *= 2), mat3( 2 ) ) );
    UNIT_TEST( MAT3_EQUAL( (++mb), mat3( 3, 1, 1, 1, 3, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT3_EQUAL( (mb++), mat3( 3, 1, 1, 1, 3, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT3_EQUAL( (--mb), mat3( 3, 1, 1, 1, 3, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT3_EQUAL( (mb--), mat3( 3, 1, 1, 1, 3, 1, 1, 1, 3 ) ) );
  }

  {
    //mat4 tests
    mat4 mc = mat4::identity;
    const mm::vec3 arbitraryAxis( 10, 11, 12 );

    UNIT_TEST( MAT4_EQUAL( mat4( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ), mat4( quat( std::sqrt( 2.f ), arbitraryAxis ) ) ) );
    UNIT_TEST( MAT4_EQUAL( mc, mat4( vec4( 1, 0, 0, 0 ), vec4( 0, 1, 0, 0 ), vec4( 0, 0, 1, 0 ), vec4( 0, 0, 0, 1 ) ) ) );
    UNIT_TEST( MAT4_EQUAL( mc, mat4( 1 ) ) );

    UNIT_TEST( mc[2].y == 0 );
    UNIT_TEST( mc[2].z == 1 );

    UNIT_TEST( MAT4_EQUAL( mat4( 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1 ), mat4( mat3( 2 ) ) ) );
    UNIT_TEST( MAT4_EQUAL( mat4( 2 ), mat4( mat2( 2 ), mat2( 0 ), mat2( 0 ), mat2( 2 ) ) ) );

    mc = mat4( 0.3854, -0.0806, -0.8362, 0.4866,
      -1.2877, -1.8971, 0.6112, -1.3552,
      1.6993, -1.5248, -0.0907, 0.6628,
      -1.2859, 0.1765, -0.4029, 0.0235 );

    UNIT_TEST( MAT4_EQUAL( (mc *= mm::inverse( mc )), mat4::identity ) );
    UNIT_TEST( MAT4_EQUAL( (mc *= 2), mat4( 2 ) ) );
    UNIT_TEST( MAT4_EQUAL( (++mc), mat4( 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT4_EQUAL( (mc++), mat4( 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT4_EQUAL( (--mc), mat4( 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3 ) ) );
    UNIT_TEST( MAT4_EQUAL( (mc--), mat4( 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3 ) ) );
  }

  {
    //mat func tests
    vec2 a = vec2( 1, 2 );
    vec3 b = vec3( 1, 2, 3 );
    vec4 c = vec4( 1, 2, 3, 4 );
    mat2 ma = mat2( 1, 2, 3, 4 );
    mat3 mb = mat3( 1, 2, 3, 4, 5, 6, 7, 8, 9 );
    mat4 mc = mat4( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 );

    UNIT_TEST( mm::all( mm::equal( a * ma, vec2( 5, 11 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( b * mb, vec3( 14, 32, 50 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( c * mc, vec4( 30, 70, 110, 150 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( ma * a, vec2( 7, 10 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mb * b, vec3( 30, 36, 42 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( mc * c, vec4( 90, 100, 110, 120 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( (a *= ma), vec2( 5, 11 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (b *= mb), vec3( 14, 32, 50 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( (c *= mc), vec4( 30, 70, 110, 150 ) ) ) );

    UNIT_TEST( MAT2_EQUAL( ma * ma, mat2( 7, 10, 15, 22 ) ) );
    UNIT_TEST( MAT3_EQUAL( mb * mb, mat3( 30, 36, 42, 66, 81, 96, 102, 126, 150 ) ) );
    UNIT_TEST( MAT4_EQUAL( mc * mc, mat4( 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 ) ) );

    UNIT_TEST( MAT2_EQUAL( ma * (float)2, mat2( 2, 4, 6, 8 ) ) );
    UNIT_TEST( MAT3_EQUAL( mb * (float)2, mat3( 2, 4, 6, 8, 10, 12, 14, 16, 18 ) ) );
    UNIT_TEST( MAT4_EQUAL( mc * (float)2, mat4( 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 ) ) );

    UNIT_TEST( MAT2_EQUAL( ma, mm::transpose( mm::transpose( ma ) ) ) );
    UNIT_TEST( MAT3_EQUAL( mb, mm::transpose( mm::transpose( mb ) ) ) );
    UNIT_TEST( MAT4_EQUAL( mc, mm::transpose( mm::transpose( mc ) ) ) );

    UNIT_TEST( determinant( ma ) == -2 );
    UNIT_TEST( determinant( mb ) == 0 );
    UNIT_TEST( determinant( mc ) == 0 );

    UNIT_TEST( MAT2_EQUAL( matrixCompMult( ma, ma ), mat2( 1, 4, 9, 16 ) ) );
    UNIT_TEST( MAT3_EQUAL( matrixCompMult( mb, mb ), mat3( 1, 4, 9, 16, 25, 36, 49, 64, 81 ) ) );
    UNIT_TEST( MAT4_EQUAL( matrixCompMult( mc, mc ), mat4( 1, 4, 9, 16, 25, 36, 49, 64, 81, 100, 121, 144, 169, 196, 225, 256 ) ) );
  }

  {
    //util functions
    mm::camera<float> cam;
    mm::frame<float> f;
    f.set_perspective( radians( 45 ), 1, 1, 100 );
    mat4 inv_mvp = inverse( f.projection_matrix * cam.get_matrix() );
    UNIT_TEST( mm::all( mm::equal( unproject( vec3( 0.0, 0.0, -1.0 ), inv_mvp ), vec3( 0, 0, -1 ) ) ) );

    UNIT_TEST( mm::all( mm::equal( create_rotation( radians( 90 ), vec3( 0, 0, 1 ) ) * vec4( 1, 0, 0, 1 ), vec4( 0, 1, 0, 1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( create_scale( vec3( 2 ) ) * vec4( 2 ), vec4( 4, 4, 4, 2 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( create_translation( vec3( 1, 0, 0 ) ) * vec4( 0, 1, 0, 1 ), vec4( 1, 1, 0, 1 ) ) ) );

    UNIT_TEST( mm::impl::is_eq( get_angle( vec2( 1, 0 ), vec2( 0, 1 ) ), radians( 90 ) ) );
    UNIT_TEST( mm::impl::is_eq( get_angle( vec3( 1, 0, 0 ), vec3( 0, 1, 0 ) ), radians( 90 ) ) );
    UNIT_TEST( mm::impl::is_eq( get_angle( vec4( 1, 0, 0, 0 ), vec4( 0, 1, 0, 0 ) ), radians( 90 ) ) );

    UNIT_TEST( mm::all( mm::equal( find_normal( vec3( 1, 0, 0 ), vec3( -1, 0, 0 ), vec3( 1, 0, 1 ) ), vec3( 0, 1, 0 ) ) ) );

    vec3 vertices[3] = { vec3( 1, 0, 0 ), vec3( -1, 0, 0 ), vec3( 1, 0, 1 ) };
    vec2 texcoords[3] = { vec2( 1, 0 ), vec2( 0, 0 ), vec2( 0, 1 ) };
    UNIT_TEST( mm::all( mm::equal( calc_tangent( vertices, texcoords, vec3( 0, 1, 0 ) ), vec3( 1, 0, 0 ) ) ) );

    UNIT_TEST( is_pow_2( 2 ) == true );
    UNIT_TEST( is_pow_2( 3 ) == false );
    UNIT_TEST( is_pow_2( 0 ) == true );
  }

  {
    //quaternion tests
    const mm::vec3 arbitraryAxis( 10, 11, 12 );

    UNIT_TEST( QUAT_EQUAL( quat(), quat( 0, arbitraryAxis ) ) );
    UNIT_TEST( QUAT_EQUAL( quat( 1, arbitraryAxis ), quat( 1, arbitraryAxis * 5 ) ) );
    UNIT_TEST( QUAT_EQUAL( quat( pi, arbitraryAxis ), quat( 3 * pi, arbitraryAxis ) ) );

    UNIT_TEST( mm::all( mm::equal( normalize( quat( vec4( 10, 20, 30, 40 ) ) ).value, normalize( vec4( 10, 20, 30, 40 ) ) ) ) );

    UNIT_TEST( QUAT_EQUAL( quat( std::sqrt( 2.f ), arbitraryAxis ), quat_cast( mat4( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ) ) ) );
    UNIT_TEST( QUAT_EQUAL( quat( std::sqrt( 2.f ), arbitraryAxis ), quat_cast( mat3( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ) ) ) );
    UNIT_TEST( MAT4_EQUAL( mat4( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ), mat4_cast( quat( std::sqrt( 2.f ), arbitraryAxis ) ) ) );
    UNIT_TEST( MAT3_EQUAL( mat3( create_rotation( std::sqrt( 2.f ), arbitraryAxis ) ), mat3_cast( quat( std::sqrt( 2.f ), arbitraryAxis ) ) ) );

    UNIT_TEST( mm::all( mm::equal( rotate_vector( quat( pi / 2, vec3( 1, 0, 0 ) ) * quat( pi / 2, vec3( 0, 1, 0 ) ), vec3( 1, 0, 0 ) ), vec3( 0, 1, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( rotate_vector( quat( pi / 2, vec3( 0, 1, 0 ) ) * quat( pi / 2, vec3( 1, 0, 0 ) ), vec3( 1, 0, 0 ) ), vec3( 0, 0, -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( rotate_vector( quat( pi / 2.1, vec3( 1, 0, 0 ) ) * quat( pi / 2, vec3( 0, 1, 0 ) ), vec3( 1, 0, 0 ) ), vec3( 0, 1, 0 ) ) ) == false );
    UNIT_TEST( mm::all( mm::equal( rotate_vector( quat( pi / 2.1, vec3( 0, 1, 0 ) ) * quat( pi / 2, vec3( 1, 0, 0 ) ), vec3( 1, 0, 0 ) ), vec3( 0, 0, -1 ) ) ) == false );

    UNIT_TEST( QUAT_EQUAL( quat( pi / 2, vec3( 1, 0, 0 ) ) * quat( pi / 2, vec3( 0, 1, 0 ) ), quat( pi / 2, vec3( 1, 0, 0 ) ) *= quat( pi / 2, vec3( 0, 1, 0 ) ) ) );

    UNIT_TEST( QUAT_EQUAL( quat( 1, arbitraryAxis ) * inverse( quat( 1, arbitraryAxis ) ), quat( 0, arbitraryAxis ) ) );

    UNIT_TEST( QUAT_EQUAL( mix( quat( 0, arbitraryAxis ), quat( pi, arbitraryAxis ), 0.5f ), quat( pi / 2, arbitraryAxis ) ) );
    UNIT_TEST( QUAT_EQUAL( slerp( quat( 0, arbitraryAxis ), quat( pi, arbitraryAxis ), 0.5f ), quat( pi / 2, arbitraryAxis ) ) );

    //TODO this test with the hard wired value might not be the best solution
    UNIT_TEST( QUAT_EQUAL( mix( quat( 0, arbitraryAxis ), quat( pi, arbitraryAxis ), 0.25f ), quat( 0.643501341343, arbitraryAxis ) ) );
    UNIT_TEST( QUAT_EQUAL( mix( quat( 0, arbitraryAxis ), quat( pi, arbitraryAxis ), 0.25f ), quat( pi / 4, arbitraryAxis ) ) == false );
    UNIT_TEST( QUAT_EQUAL( slerp( quat( 0, arbitraryAxis ), quat( pi, arbitraryAxis ), 0.25f ), quat( pi / 4, arbitraryAxis ) ) );

    UNIT_TEST( QUAT_EQUAL( get_rotation( vec3( 1, 0, 0 ), vec3( 0, 1, 0 ) ), quat( pi / 2, vec3( 0, 0, 1 ) ) ) );
    UNIT_TEST( QUAT_EQUAL( get_rotation( vec3( 0, 0, 1 ), vec3( 0, 1, 0 ) ), quat( -pi / 2, vec3( 1, 0, 0 ) ) ) );
  }

  {
    //frame functions
    //TODO
    //how do you test this???
  }

  {
    //camera functions
    mm::camera<float> cam;
    cam.lookat( vec3( 1, 0, 0 ), vec3( 0, 0, 0 ), vec3( 0, 1, 0 ) );
    mat4 cam_mat = cam.get_matrix();
    UNIT_TEST( MAT4_EQUAL( cam_mat, mat4( 0, 0, -1, 0, 0, 1, 0, 0, 1, 0, 0, 0, -1, 0, 0, 1 ) ) );

    cam.translate( vec3( -1, 0, 0 ) );
    UNIT_TEST( mm::all( mm::equal( cam.pos, vec3( 0 ) ) ) );

    cam.move_forward( 1 );
    UNIT_TEST( mm::all( mm::equal( cam.pos, vec3( -1, 0, 0 ) ) ) );

    cam.move_up( 1 );
    UNIT_TEST( mm::all( mm::equal( cam.pos, vec3( -1, 1, 0 ) ) ) );

    cam.move_right( 1 );
    UNIT_TEST( mm::all( mm::equal( cam.pos, vec3( -1, 1, -1 ) ) ) );

    cam = camera<float>();
    cam.rotate_x( radians( 90 ) );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( 0, 1, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 0, 0, 1 ) ) ) );

    cam = camera<float>();
    cam.rotate_y( radians( 90 ) );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( -1, 0, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 0, 1, 0 ) ) ) );

    cam = camera<float>();
    cam.rotate_z( radians( 90 ) );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( 0, 0, -1 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 1, 0, 0 ) ) ) );

    cam = camera<float>();
    cam.rotate( radians( 90 ), vec3( 1, 1, 0 ) );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( -0.7071, 0.7071, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 0.5, 0.5, 0.7071 ) ) ) );

    cam.set_from_matrix( cam_mat );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( -1, 0, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 0, 1, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.pos, vec3( 1, 0, 0 ) ) ) );

    cam = camera<float>();
    cam.rotate( radians( 90 ), vec3( 0, 1, 0 ) );
    cam.rotate_x( radians( 90 ) );
    UNIT_TEST( mm::all( mm::equal( cam.view_dir, vec3( 0, 1, 0 ) ) ) );
    UNIT_TEST( mm::all( mm::equal( cam.up_vector, vec3( 1, 0, 0 ) ) ) );
    cam_mat = cam.get_matrix();
    UNIT_TEST( MAT4_EQUAL( cam_mat, mat4( 0, 0, -1, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1 ) ) );
  }

  system( "PAUSE" );

  return 0;
}