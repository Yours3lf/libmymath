#ifndef mm_vec_func_h
#define mm_vec_func_h

#include "mm_common.h"

namespace mymath
{
  //equal
#define MYMATH_EQUAL_FUNC(t) \
  inline bool equal( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return a.x == b.x && a.y == b.y; } \
  inline bool equal( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return a.x == b.x && a.y == b.y && a.z == b.z; } \
  inline bool equal( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w; }

  //notEqual
#define MYMATH_NOTEQUAL_FUNC(t) \
  inline bool notEqual( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return !equal( a, b ); } \
  inline bool notEqual( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return !equal( a, b ); } \
  inline bool notEqual( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return !equal( a, b ); }

  MYMATH_EQUAL_FUNC( float )
  MYMATH_EQUAL_FUNC( int )
  MYMATH_EQUAL_FUNC( unsigned int )

  MYMATH_NOTEQUAL_FUNC( float )
  MYMATH_NOTEQUAL_FUNC( int )
  MYMATH_NOTEQUAL_FUNC( unsigned int )
}

//operator*
#define MYMATH_OPERATORMUL_FUNC(t) \
  inline mm::impl::vec2i<t> operator* ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( a.x * b.x, a.y * b.y ); } \
  inline mm::impl::vec3i<t> operator* ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( a.x * b.x, a.y * b.y, a.z * b.z ); } \
  inline mm::impl::vec4i<t> operator* ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w ); }

//operator/
#define MYMATH_OPERATORDIV_FUNC(t) \
  inline mm::impl::vec2i<t> operator/ ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { assert( b.x != (t)0 && b.y != (t)0 ); \
    mm::impl::vec2i<t> tmp = mm::impl::vec2i<t>( ( t )1 / b.x, ( t )1 / b.y ); \
    return a * tmp; } \
  inline mm::impl::vec3i<t> operator/ ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { assert( b.x != (t)0 && b.y != (t)0 && b.z != (t)0 ); \
    mm::impl::vec3i<t> tmp = mm::impl::vec3i<t>( ( t )1 / b.x, ( t )1 / b.y, ( t )1 / b.z ); \
    return a * tmp; } \
  inline mm::impl::vec4i<t> operator/ ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { assert(  b.x != (t)0 && b.y != (t)0 && b.z != (t)0 && b.w != (t)0 ); \
    mm::impl::vec4i<t> tmp = mm::impl::vec4i<t>( ( t )1 / b.x, ( t )1 / b.y, ( t )1 / b.z, ( t )1 / b.w ); \
    return a * tmp; }

//operator+
#define MYMATH_OPERATORPLUS_FUNC(t) \
  inline mm::impl::vec2i<t> operator+ ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( a.x + b.x, a.y + b.y ); } \
  inline mm::impl::vec3i<t> operator+ ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( a.x + b.x, a.y + b.y, a.z + b.z ); } \
  inline mm::impl::vec4i<t> operator+ ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w ); }

//operator-
#define MYMATH_OPERATORMINUS_FUNC(t) \
  inline mm::impl::vec2i<t> operator- ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( a.x - b.x, a.y - b.y ); } \
  inline mm::impl::vec3i<t> operator- ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( a.x - b.x, a.y - b.y, a.z - b.z ); } \
  inline mm::impl::vec4i<t> operator- ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w ); }

//operator%
#define MYMATH_OPERATORMOD_FUNC(t) \
  inline mm::impl::vec2i<t> operator% ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y ); } \
  inline mm::impl::vec3i<t> operator% ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y, ( int )a.z % ( int )b.z ); } \
  inline mm::impl::vec4i<t> operator% ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y, ( int )a.z % ( int )b.z, ( int )a.w % ( int )b.w ); }

//operator<<
#define MYMATH_OPERATORBITLEFT_FUNC(t) \
  inline mm::impl::vec2i<t> operator<< ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x << ( int )b.x, ( int )a.y << ( int )b.y ); } \
  inline mm::impl::vec3i<t> operator<< ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x << ( int )b.x, ( int )a.y << ( int )b.y, ( int )a.z << ( int )b.z ); } \
  inline mm::impl::vec4i<t> operator<< ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x << ( int )b.x, ( int )a.y << ( int )b.y, ( int )a.z << ( int )b.z, ( int )a.w << ( int )b.w ); }

//operator>>
#define MYMATH_OPERATORBITRIGHT_FUNC(t) \
  inline mm::impl::vec2i<t> operator>> ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x >> ( int )b.x, ( int )a.y >> ( int )b.y ); } \
  inline mm::impl::vec3i<t> operator>> ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x >> ( int )b.x, ( int )a.y >> ( int )b.y, ( int )a.z >> ( int )b.z ); } \
  inline mm::impl::vec4i<t> operator>> ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x >> ( int )b.x, ( int )a.y >> ( int )b.y, ( int )a.z >> ( int )b.z, ( int )a.w >> ( int )b.w ); }

//operator&
#define MYMATH_OPERATORBITAND_FUNC(t) \
  inline mm::impl::vec2i<t> operator& ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x & ( int )b.x, ( int )a.y & ( int )b.y ); } \
  inline mm::impl::vec3i<t> operator& ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x & ( int )b.x, ( int )a.y & ( int )b.y, ( int )a.z & ( int )b.z ); } \
  inline mm::impl::vec4i<t> operator& ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x & ( int )b.x, ( int )a.y & ( int )b.y, ( int )a.z & ( int )b.z, ( int )a.w & ( int )b.w ); }

//operator^
#define MYMATH_OPERATORBITXOR_FUNC(t) \
  inline mm::impl::vec2i<t> operator^( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x ^( int )b.x, ( int )a.y ^( int )b.y ); } \
  inline mm::impl::vec3i<t> operator^( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x ^( int )b.x, ( int )a.y ^( int )b.y, ( int )a.z ^( int )b.z ); } \
  inline mm::impl::vec4i<t> operator^( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x ^( int )b.x, ( int )a.y ^( int )b.y, ( int )a.z ^( int )b.z, ( int )a.w ^( int )b.w ); }

//operator|
#define MYMATH_OPERATORBITOR_FUNC(t) \
  inline mm::impl::vec2i<t> operator| ( const mm::impl::vec2i<t>& a, const mm::impl::vec2i<t>& b ) \
  { return mm::impl::vec2i<t>( ( int )a.x | ( int )b.x, ( int )a.y | ( int )b.y ); } \
  inline mm::impl::vec3i<t> operator| ( const mm::impl::vec3i<t>& a, const mm::impl::vec3i<t>& b ) \
  { return mm::impl::vec3i<t>( ( int )a.x | ( int )b.x, ( int )a.y | ( int )b.y, ( int )a.z | ( int )b.z ); } \
  inline mm::impl::vec4i<t> operator| ( const mm::impl::vec4i<t>& a, const mm::impl::vec4i<t>& b ) \
  { return mm::impl::vec4i<t>( ( int )a.x | ( int )b.x, ( int )a.y | ( int )b.y, ( int )a.z | ( int )b.z, ( int )a.w | ( int )b.w ); }

//negate
#define MYMATH_NEGATE_FUNC(t) \
  inline mm::impl::vec2i<t> operator- ( const mm::impl::vec2i<t>& vec ) \
  { return mm::impl::vec2i<t>( -vec.x, -vec.y ); } \
  inline mm::impl::vec3i<t> operator- ( const mm::impl::vec3i<t>& vec ) \
  { return mm::impl::vec3i<t>( -vec.x, -vec.y, -vec.z ); } \
  inline mm::impl::vec4i<t> operator- ( const mm::impl::vec4i<t>& vec ) \
  { return mm::impl::vec4i<t>( -vec.x, -vec.y, -vec.z, -vec.w ); }

//std::cout <<
#define MYMATH_COUT_FUNC(t) \
  inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec2i<t>& vec ) \
  { return output << "( " << vec.x << ", " << vec.y << " )\n"; } \
  inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec3i<t>& vec ) \
  { return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n"; } \
  inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec4i<t>& vec ) \
  { return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " )\n"; }


MYMATH_OPERATORMUL_FUNC( float )
MYMATH_OPERATORMUL_FUNC( double )
MYMATH_OPERATORMUL_FUNC( int )
MYMATH_OPERATORMUL_FUNC( unsigned int )

MYMATH_OPERATORDIV_FUNC( float )
MYMATH_OPERATORDIV_FUNC( double )
MYMATH_OPERATORDIV_FUNC( int )
MYMATH_OPERATORDIV_FUNC( unsigned int )

MYMATH_OPERATORPLUS_FUNC( float )
MYMATH_OPERATORPLUS_FUNC( double )
MYMATH_OPERATORPLUS_FUNC( int )
MYMATH_OPERATORPLUS_FUNC( unsigned int )

MYMATH_OPERATORMINUS_FUNC( float )
MYMATH_OPERATORMINUS_FUNC( double )
MYMATH_OPERATORMINUS_FUNC( int )
MYMATH_OPERATORMINUS_FUNC( unsigned int )

#ifdef _WIN32
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif
MYMATH_OPERATORMOD_FUNC( float )
MYMATH_OPERATORMOD_FUNC( double )
MYMATH_OPERATORMOD_FUNC( int )
MYMATH_OPERATORMOD_FUNC( unsigned int )
#ifdef _WIN32
#pragma warning( pop )
#pragma warning( disable : 4244 )
#endif

MYMATH_OPERATORBITLEFT_FUNC( float )
MYMATH_OPERATORBITLEFT_FUNC( double )
MYMATH_OPERATORBITLEFT_FUNC( int )
MYMATH_OPERATORBITLEFT_FUNC( unsigned int )

MYMATH_OPERATORBITRIGHT_FUNC( float )
MYMATH_OPERATORBITRIGHT_FUNC( double )
MYMATH_OPERATORBITRIGHT_FUNC( int )
MYMATH_OPERATORBITRIGHT_FUNC( unsigned int )

MYMATH_OPERATORBITAND_FUNC( float )
MYMATH_OPERATORBITAND_FUNC( double )
MYMATH_OPERATORBITAND_FUNC( int )
MYMATH_OPERATORBITAND_FUNC( unsigned int )

MYMATH_OPERATORBITXOR_FUNC( float )
MYMATH_OPERATORBITXOR_FUNC( double )
MYMATH_OPERATORBITXOR_FUNC( int )
MYMATH_OPERATORBITXOR_FUNC( unsigned int )

MYMATH_OPERATORBITOR_FUNC( float )
MYMATH_OPERATORBITOR_FUNC( double )
MYMATH_OPERATORBITOR_FUNC( int )
MYMATH_OPERATORBITOR_FUNC( unsigned int )

MYMATH_NEGATE_FUNC( float )
MYMATH_NEGATE_FUNC( double )
MYMATH_NEGATE_FUNC( int )

MYMATH_COUT_FUNC( float )
MYMATH_COUT_FUNC( double )
MYMATH_COUT_FUNC( int )
MYMATH_COUT_FUNC( unsigned int )

namespace mymath
{
#define MYMATH_STD_VEC_FUNC(f, t) \
  inline impl::vec2i<t> f( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>(std::f(vec.x), std::f(vec.y)); } \
  inline impl::vec3i<t> f( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>(std::f(vec.x), std::f(vec.y), std::f(vec.z)); } \
  inline impl::vec4i<t> f( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>(std::f(vec.x), std::f(vec.y), std::f(vec.z), std::f(vec.w)); }

#define MYMATH_STD_2_VEC_FUNC(f, t) \
  inline impl::vec2i<t> f( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return impl::vec2i<t>(std::f(a.x, b.x), std::f(a.y, b.y)); } \
  inline impl::vec3i<t> f( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return impl::vec3i<t>(std::f(a.x, b.x), std::f(a.y, b.y), std::f(a.z, b.z)); } \
  inline impl::vec4i<t> f( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return impl::vec4i<t>(std::f(a.x, b.x), std::f(a.y, b.y), std::f(a.z, b.z), std::f(a.w, b.w)); }

  //lessThan
#define MYMATH_LESSTHAN_FUNC(t) \
  inline bool lessThan( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return a.x < b.x && a.y < b.y; } \
  inline bool lessThan( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return a.x < b.x && a.y < b.y && a.z < b.z; } \
  inline bool lessThan( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return a.x < b.x && a.y < b.y && a.z < b.z && a.w < b.w; }

  //greaterThan
#define MYMATH_GREATERTHAN_FUNC(t) \
  inline bool greaterThan( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return a.x > b.x && a.y > b.y; } \
  inline bool greaterThan( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return a.x > b.x && a.y > b.y && a.z > b.z; } \
  inline bool greaterThan( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return a.x > b.x && a.y > b.y && a.z > b.z && a.w > b.w; }

  //lessThanEqual
#define MYMATH_LESSTHANEQUAL_FUNC(t) \
  inline bool lessThanEqual( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return !greaterThan( a, b ); } \
  inline bool lessThanEqual( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return !greaterThan( a, b ); } \
  inline bool lessThanEqual( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return !greaterThan( a, b ); }

  //greaterThanEqual
#define MYMATH_GREATERTHANEQUAL_FUNC(t) \
  inline bool greaterThanEqual( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return !lessThan( a, b ); } \
  inline bool greaterThanEqual( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return !lessThan( a, b ); } \
  inline bool greaterThanEqual( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return !lessThan( a, b ); }

  //radians
#define MYMATH_RADIANS_FUNC(t) \
  inline impl::vec2i<t> radians( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( radians( vec.x ), radians( vec.y ) ); } \
  inline impl::vec3i<t> radians( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( radians( vec.x ), radians( vec.y ), radians( vec.z ) ); } \
  inline impl::vec4i<t> radians( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( radians( vec.x ), radians( vec.y ), radians( vec.z ), radians( vec.w ) ); }

  //degrees
#define MYMATH_DEGREES_FUNC(t) \
  inline impl::vec2i<t> degrees( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( degrees( vec.x ), degrees( vec.y ) ); } \
  inline impl::vec3i<t> degrees( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( degrees( vec.x ), degrees( vec.y ), degrees( vec.z ) ); } \
  inline impl::vec4i<t> degrees( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( degrees( vec.x ), degrees( vec.y ), degrees( vec.z ), degrees( vec.w ) ); }

  //asinh
#define MYMATH_ASINH_FUNC(t) \
  inline impl::vec2i<t> asinh( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( asinh( vec.x ), asinh( vec.y ) ); } \
  inline impl::vec3i<t> asinh( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( asinh( vec.x ), asinh( vec.y ), asinh( vec.z ) ); } \
  inline impl::vec4i<t> asinh( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( asinh( vec.x ), asinh( vec.y ), asinh( vec.z ), asinh( vec.w ) ); }

  //acosh
#define MYMATH_ACOSH_FUNC(t) \
  inline impl::vec2i<t> acosh( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( acosh( vec.x ), acosh( vec.y ) ); } \
  inline impl::vec3i<t> acosh( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( acosh( vec.x ), acosh( vec.y ), acosh( vec.z ) ); } \
  inline impl::vec4i<t> acosh( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( acosh( vec.x ), acosh( vec.y ), acosh( vec.z ), acosh( vec.w ) ); }

  //atanh
#define MYMATH_ATANH_FUNC(t) \
  inline impl::vec2i<t> atanh( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( atanh( vec.x ), atanh( vec.y ) ); } \
  inline impl::vec3i<t> atanh( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( atanh( vec.x ), atanh( vec.y ), atanh( vec.z ) ); } \
  inline impl::vec4i<t> atanh( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( atanh( vec.x ), atanh( vec.y ), atanh( vec.w ), atanh( vec.w ) ); }

  //exp2
#define MYMATH_EXP2_FUNC(t) \
  inline impl::vec2i<t> exp2( const impl::vec2i<t>& vec ) \
  { return pow( impl::vec2i<t>( 2 ), vec ); } \
  inline impl::vec3i<t> exp2( const impl::vec3i<t>& vec ) \
  { return pow( impl::vec3i<t>( 2 ), vec ); } \
  inline impl::vec4i<t> exp2( const impl::vec4i<t>& vec ) \
  { return pow( impl::vec4i<t>( 2 ), vec ); }

  //log2
#define MYMATH_LOG2_FUNC(t) \
  inline impl::vec2i<t> log2( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( log2( vec.x ), log2( vec.y ) ); } \
  inline impl::vec3i<t> log2( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( log2( vec.x ), log2( vec.y ), log2( vec.z ) ); } \
  inline impl::vec4i<t> log2( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( log2( vec.x ), log2( vec.y ), log2( vec.z ), log2( vec.w ) ); }

  //inversesqrt
#define MYMATH_INVERSESQRT_FUNC(t) \
  inline impl::vec2i<t> inversesqrt( const impl::vec2i<t>& vec ) \
  { return sqrt( impl::vec2i<t>( 1 ) / vec ); } \
  inline impl::vec3i<t> inversesqrt( const impl::vec3i<t>& vec ) \
  { return sqrt( impl::vec3i<t>( 1 ) / vec ); } \
  inline impl::vec4i<t> inversesqrt( const impl::vec4i<t>& vec ) \
  { return sqrt( impl::vec4i<t>( 1 ) / vec ); }

  //sign
#define MYMATH_SIGN_FUNC(t) \
  inline impl::vec2i<t> sign( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( sign( vec.x ), sign( vec.y ) ); } \
  inline impl::vec3i<t> sign( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( sign( vec.x ), sign( vec.y ), sign( vec.z ) ); } \
  inline impl::vec4i<t> sign( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( sign( vec.x ), sign( vec.y ), sign( vec.z ), sign( vec.w ) ); }

  //trunc
#define MYMATH_TRUNC_FUNC(t) \
  inline impl::vec2i<t> trunc( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( trunc( vec.x ), trunc( vec.y ) ); } \
  inline impl::vec3i<t> trunc( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( trunc( vec.x ), trunc( vec.y ), trunc( vec.z ) ); } \
  inline impl::vec4i<t> trunc( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( trunc( vec.x ), trunc( vec.y ), trunc( vec.z ), trunc( vec.w ) ); }

  //round
#define MYMATH_ROUND_FUNC(t) \
  inline impl::vec2i<t> round( const impl::vec2i<t>& vec ) \
  { return impl::vec2i<t>( round( vec.x ), round( vec.y ) ); } \
  inline impl::vec3i<t> round( const impl::vec3i<t>& vec ) \
  { return impl::vec3i<t>( round( vec.x ), round( vec.y ), round( vec.z ) ); } \
  inline impl::vec4i<t> round( const impl::vec4i<t>& vec ) \
  { return impl::vec4i<t>( round( vec.x ), round( vec.y ), round( vec.z ), round( vec.w ) ); }

  //fract
#define MYMATH_FRACT_FUNC(t) \
  inline impl::vec2i<t> fract( const impl::vec2i<t>& vec ) \
  { return vec - floor( vec ); } \
  inline impl::vec3i<t> fract( const impl ::vec3i<t>& vec ) \
  { return vec - floor( vec ); } \
  inline impl::vec4i<t> fract( const impl::vec4i<t>& vec ) \
  { return vec - floor( vec ); }

  //mod
#define MYMATH_MOD_FUNC(t) \
  inline impl::vec2i<t> mod( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return impl::vec2i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y ); } \
  inline impl::vec3i<t> mod( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return impl::vec3i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y, ( int )a.z % ( int )b.z ); } \
  inline impl::vec4i<t> mod( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return impl::vec4i<t>( ( int )a.x % ( int )b.x, ( int )a.y % ( int )b.y, ( int )a.z % ( int )b.z, ( int )a.w % ( int )b.w ); }

  //mix
#define MYMATH_MIX_FUNC(t) \
  inline impl::vec2i<t> mix( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { return a * ( impl::vec2i<t>( 1 ) - c ) + b * c; } \
  inline impl::vec3i<t> mix( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { return a * ( impl::vec3i<t>( 1 ) - c ) + b * c; } \
  inline impl::vec4i<t> mix( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { return a * ( impl::vec4i<t>( 1 ) - c ) + b * c; }

  //step
#define MYMATH_STEP_FUNC(t) \
  inline impl::vec2i<t> step( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return ( b.x < a.x && b.y < a.y ) ? impl::vec2i<t>( 0 ) : impl::vec2i<t>( 1 ); } \
  inline impl::vec3i<t> step( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return ( b.x < a.x && b.y < a.y && b.z < a.z ) ? impl::vec3i<t>( 0 ) : impl::vec3i<t>( 1 ); } \
  inline impl::vec4i<t> step( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return ( b.x < a.x && b.y < a.y && b.z < a.z && b.w < a.w ) ? impl::vec4i<t>( 0 ) : impl::vec4i<t>( 1 ); }

  //clamp
#define MYMATH_CLAMP_FUNC(t) \
  inline impl::vec2i<t> clamp( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { return min( max( a, b ), c ); } \
  inline impl::vec3i<t> clamp( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { return min( max( a, b ), c ); } \
  inline impl::vec4i<t> clamp( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { return min( max( a, b ), c ); }

  //smoothstep
#define MYMATH_SMOOTHSTEP_FUNC(t) \
  inline impl::vec2i<t> smoothstep( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { impl::vec2i<t> u = ( c - a ) / ( b - a ); \
    u = clamp( u, impl::vec2i<t>( 0 ), impl::vec2i<t>( 1 ) ); \
    return u * u * ( impl::vec2i<t>( 3 ) - impl::vec2i<t>( 2 ) * u ); } \
  inline impl::vec3i<t> smoothstep( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { impl::vec3i<t> u = ( c - a ) / ( b - a ); \
    u = clamp( u, impl::vec3i<t>( 0 ), impl::vec3i<t>( 1 ) ); \
    return u * u * ( impl::vec3i<t>( 3 ) - impl::vec3i<t>( 2 ) * u ); } \
  inline impl::vec4i<t> smoothstep( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { impl::vec4i<t> u = ( c - a ) / ( b - a ); \
    u = clamp( u, impl::vec4i<t>( 0 ), impl::vec4i<t>( 1 ) ); \
    return u * u * ( impl::vec4i<t>( 3 ) - impl::vec4i<t>( 2 ) * u ); }

  //fma
#define MYMATH_FMA_FUNC(t) \
  inline impl::vec2i<t> fma( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { return a * b + c; } \
  inline impl::vec3i<t> fma( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { return a * b + c; } \
  inline impl::vec4i<t> fma( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { return a * b + c; }

  //dot
#define MYMATH_DOT_FUNC(t) \
  inline t dot( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return a.x * b.x + a.y * b.y; } \
  inline t dot( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return a.x * b.x + a.y * b.y + a.z * b.z; } \
  inline t dot( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

  //length
#define MYMATH_LENGTH_FUNC(t) \
  inline t length( const impl::vec2i<t>& vec ) \
  { return std::sqrt( dot( vec, vec ) ); } \
  inline t length( const impl::vec3i<t>& vec ) \
  { return std::sqrt( dot( vec, vec ) ); } \
  inline t length( const impl::vec4i<t>& vec ) \
  { return std::sqrt( dot( vec, vec ) ); }

  //distance
#define MYMATH_DISTANCE_FUNC(t) \
  inline t distance( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return length( a - b ); } \
  inline t distance( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return length( a - b ); } \
  inline t distance( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return length( a - b ); }

  //normalize
#define MYMATH_NORMALIZE_FUNC(t) \
  inline impl::vec2i<t> normalize( const impl::vec2i<t>& vec ) \
  { return vec / impl::vec2i<t>( length( vec ) ); } \
  inline impl::vec3i<t> normalize( const impl::vec3i<t>& vec ) \
  { return vec / impl::vec3i<t>( length( vec ) ); } \
  inline impl::vec4i<t> normalize( const impl::vec4i<t>& vec ) \
  { return vec / impl::vec4i<t>( length( vec ) ); }

  //reflect
#define MYMATH_REFLECT_FUNC(t) \
  inline impl::vec2i<t> reflect( const impl::vec2i<t>& a, const impl::vec2i<t>& b ) \
  { return a - impl::vec2i<t>( ( t )2 * dot( a, b ) ) * b; } \
  inline impl::vec3i<t> reflect( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return a - impl::vec3i<t>( ( t )2 * dot( a, b ) ) * b; } \
  inline impl::vec4i<t> reflect( const impl::vec4i<t>& a, const impl::vec4i<t>& b ) \
  { return a - impl::vec4i<t>( ( t )2 * dot( a, b ) ) * b; }

  //refract
#define MYMATH_REFRACT_FUNC(t) \
  inline impl::vec2i<t> refract( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { t k = ( impl::vec2i<t>( 1 ) - c * c * impl::vec2i<t>( ( t )1 - dot( a, b ) * dot( a, b ) ) ).x; \
    return k < ( t )0 ? impl::vec2i<t>( 0 ) : c * a - ( c * impl::vec2i<t>( dot( a, b ) ) + impl::vec2i<t>( std::sqrt( k ) ) ) * b; } \
  inline impl::vec3i<t> refract( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { t k = ( impl::vec3i<t>( 1 ) - c * c * impl::vec3i<t>( ( t )1 - dot( a, b ) * dot( a, b ) ) ).x; \
    return k < ( t )0 ? impl::vec3i<t>( 0 ) : c * a - ( c * impl::vec3i<t>( dot( a, b ) ) + impl::vec3i<t>( std::sqrt( k ) ) ) * b; } \
  inline impl::vec4i<t> refract( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { t k = ( impl::vec4i<t>( 1 ) - c * c * impl::vec4i<t>( ( t )1 - dot( a, b ) * dot( a, b ) ) ).x; \
    return k < ( t )0 ? impl::vec4i<t>( 0 ) : c * a - ( c * impl::vec4i<t>( dot( a, b ) ) + impl::vec4i<t>( std::sqrt( k ) ) ) * b; } \
   
  //faceforward
#define MYMATH_FACEFORWARD_FUNC(t) \
  inline impl::vec2i<t> faceforward( const impl::vec2i<t>& a, const impl::vec2i<t>& b, const impl::vec2i<t>& c ) \
  { return dot( b, c ) < ( t )0 ? a : -a; } \
  inline impl::vec3i<t> faceforward( const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { return dot( b, c ) < ( t )0 ? a : -a; } \
  inline impl::vec4i<t> faceforward( const impl::vec4i<t>& a, const impl::vec4i<t>& b, const impl::vec4i<t>& c ) \
  { return dot( b, c ) < ( t )0 ? a : -a; }

  //isnan
#define MYMATH_ISNAN_FUNC(t) \
  inline bool isnan( const impl::vec2i<t>& vec ) \
  { return isnan( vec.x ) || isnan( vec.y ); } \
  inline bool isnan( const impl::vec3i<t>& vec ) \
  {  return isnan( vec.x ) || isnan( vec.y ) || isnan( vec.z ); } \
  inline bool isnan( const impl::vec4i<t>& vec ) \
  { return isnan( vec.x ) || isnan( vec.y ) || isnan( vec.z ) || isnan( vec.w ); }

  //isinf
#define MYMATH_ISINF_FUNC(t) \
  inline bool isinf( const impl::vec2i<t>& vec ) \
  { return isinf( vec.x ) || isinf( vec.y ); } \
  inline bool isinf( const impl::vec3i<t>& vec ) \
  { return isinf( vec.x ) || isinf( vec.y ) || isinf( vec.z ); } \
  inline bool isinf( const impl::vec4i<t>& vec ) \
  { return isinf( vec.x ) || isinf( vec.y ) || isinf( vec.z ) || isinf( vec.w ); }

//cross only vec3
#define MYMATH_CROSS_FUNC(t) \
  inline impl::vec3i<t> cross( const impl::vec3i<t>& a, const impl::vec3i<t>& b ) \
  { return impl::vec3i<t>( a.y * b.z - b.y * a.z, -( a.x * b.z ) + b.x * a.z, a.x * b.y - b.x * a.y ); }

  //Trigonometric functions, only vecn and float is required
  MYMATH_STD_VEC_FUNC( sin, float )

  MYMATH_STD_VEC_FUNC( cos, float )

  MYMATH_STD_VEC_FUNC( tan, float )

  MYMATH_STD_VEC_FUNC( asin, float )

  MYMATH_STD_VEC_FUNC( acos, float )

  MYMATH_STD_VEC_FUNC( atan, float )

  MYMATH_STD_VEC_FUNC( sinh, float )

  MYMATH_STD_VEC_FUNC( cosh, float )

  MYMATH_STD_VEC_FUNC( tanh, float )

  MYMATH_RADIANS_FUNC( float )

  MYMATH_DEGREES_FUNC( float )

  MYMATH_ASINH_FUNC( float )

  MYMATH_ACOSH_FUNC( float )

  MYMATH_ATANH_FUNC( float )

  //Exponential function, float, double, vecn and dvecn is required
  MYMATH_STD_2_VEC_FUNC( pow, float )

  MYMATH_STD_VEC_FUNC( exp, float )

  MYMATH_STD_VEC_FUNC( log, float )

  MYMATH_STD_VEC_FUNC( sqrt, float )
  MYMATH_STD_VEC_FUNC( sqrt, double )

  MYMATH_EXP2_FUNC( float )

  MYMATH_LOG2_FUNC( float )

  MYMATH_INVERSESQRT_FUNC( float )
  MYMATH_INVERSESQRT_FUNC( double )

  //Common functions, float, double, vecn and dvecn is required
  MYMATH_STD_VEC_FUNC( abs, float )
  MYMATH_STD_VEC_FUNC( abs, double )
  MYMATH_STD_VEC_FUNC( abs, int )

  MYMATH_STD_VEC_FUNC( floor, float )
  MYMATH_STD_VEC_FUNC( floor, double )

  MYMATH_STD_VEC_FUNC( ceil, float )
  MYMATH_STD_VEC_FUNC( ceil, double )

#ifdef _WIN32
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#endif

  MYMATH_STD_2_VEC_FUNC( min, float )
  MYMATH_STD_2_VEC_FUNC( min, double )
  MYMATH_STD_2_VEC_FUNC( min, int )
  MYMATH_STD_2_VEC_FUNC( min, unsigned int )

  MYMATH_STD_2_VEC_FUNC( max, float )
  MYMATH_STD_2_VEC_FUNC( max, double )
  MYMATH_STD_2_VEC_FUNC( max, int )
  MYMATH_STD_2_VEC_FUNC( max, unsigned int )

  MYMATH_LESSTHAN_FUNC( float )
  MYMATH_LESSTHAN_FUNC( int )
  MYMATH_LESSTHAN_FUNC( unsigned int )

  MYMATH_GREATERTHAN_FUNC( float )
  MYMATH_GREATERTHAN_FUNC( int )
  MYMATH_GREATERTHAN_FUNC( unsigned int )

  MYMATH_LESSTHANEQUAL_FUNC( float )
  MYMATH_LESSTHANEQUAL_FUNC( int )
  MYMATH_LESSTHANEQUAL_FUNC( unsigned int )

  MYMATH_GREATERTHANEQUAL_FUNC( float )
  MYMATH_GREATERTHANEQUAL_FUNC( int )
  MYMATH_GREATERTHANEQUAL_FUNC( unsigned int )

  MYMATH_SIGN_FUNC( float )
  MYMATH_SIGN_FUNC( double )
  MYMATH_SIGN_FUNC( int )

  MYMATH_TRUNC_FUNC( float )
  MYMATH_TRUNC_FUNC( double )

  MYMATH_ROUND_FUNC( float )
  MYMATH_ROUND_FUNC( double )

  MYMATH_FRACT_FUNC( float )
  MYMATH_FRACT_FUNC( double )

  MYMATH_MOD_FUNC( float )
  MYMATH_MOD_FUNC( double )

  MYMATH_MIX_FUNC( float )
  MYMATH_MIX_FUNC( double )

  MYMATH_STEP_FUNC( float )
  MYMATH_STEP_FUNC( double )

  MYMATH_CLAMP_FUNC( float )
  MYMATH_CLAMP_FUNC( double )
  MYMATH_CLAMP_FUNC( int )
  MYMATH_CLAMP_FUNC( unsigned int )

  MYMATH_SMOOTHSTEP_FUNC( float )
  MYMATH_SMOOTHSTEP_FUNC( double )

  MYMATH_FMA_FUNC( float )
  MYMATH_FMA_FUNC( double )

  MYMATH_DOT_FUNC( float )
  MYMATH_DOT_FUNC( double )

  MYMATH_LENGTH_FUNC( float )
  MYMATH_LENGTH_FUNC( double )

  MYMATH_DISTANCE_FUNC( float )
  MYMATH_DISTANCE_FUNC( double )

  MYMATH_NORMALIZE_FUNC( float )
  MYMATH_NORMALIZE_FUNC( double )

  MYMATH_REFLECT_FUNC( float )
  MYMATH_REFLECT_FUNC( double )

  MYMATH_REFRACT_FUNC( float )
  MYMATH_REFRACT_FUNC( double )

  MYMATH_FACEFORWARD_FUNC( float )
  MYMATH_FACEFORWARD_FUNC( double )

  MYMATH_ISNAN_FUNC( float )
  MYMATH_ISNAN_FUNC( double )

  MYMATH_ISINF_FUNC( float )
  MYMATH_ISINF_FUNC( double )

  MYMATH_CROSS_FUNC( float )
  MYMATH_CROSS_FUNC( double )

  namespace impl
  {
    template<typename ty>
    template<int a, int b, int c, int d>
    const vec2i<ty>& vec2i<ty>::swizzle<a, b, c, d>::operator/=( const vec2i<ty>& other )
    {
      assert( notEqual( other, vec2i<ty>( 0 ) ) );
      vec2i<ty> tmp( ( ty )1 / other.x, ( ty )1 / other.y );
      v[a] *= tmp.x;
      v[b] *= tmp.y;
      return *( vec2i<ty>* )this;
    }

    template<typename ty>
    template<int a, int b, int c, int d>
    const vec3i<ty>& vec3i<ty>::swizzle<a, b, c, d>::operator/=( const vec3i<ty>& other )
    {
      assert( notEqual( other, vec3i<ty>( 0 ) ) );
      vec3i<ty> tmp( ( ty )1 / other.x, ( ty )1 / other.y, ( ty )1 / other.z );
      v[a] *= tmp.x;
      v[b] *= tmp.y;
      v[c] *= tmp.z;
      return *( vec3i<ty>* )this;
    }

    template<typename ty>
    template<int a, int b, int c, int d>
    const vec4i<ty>& vec4i<ty>::swizzle<a, b, c, d>::operator/=( const vec4i<ty>& other )
    {
      assert( notEqual( other, vec4i<ty>( 0 ) ) );
      vec4i<ty> tmp( ( ty )1 / other.x, ( ty )1 / other.y, ( ty )1 / other.z, ( ty )1 / other.w );
      v[a] *= tmp.x;
      v[b] *= tmp.y;
      v[c] *= tmp.z;
      v[d] *= tmp.w;
      return *( vec4i<ty>* )this;
    }

    template<typename ty>
    const vec2i<ty>& vec2i<ty>::operator/= ( const vec2i<ty>& vec )
    {
      vec2i<ty> tmp = vec2i<ty>( 1 ) / vec;
      x *= tmp.x;
      y *= tmp.y;
      return *this;
    }

    template<typename ty>
    const vec3i<ty>& vec3i<ty>::operator/= ( const vec3i<ty>& vec )
    {
      vec3i<ty> tmp = vec3i<ty>( 1 ) / vec;
      x *= tmp.x;
      y *= tmp.y;
      z *= tmp.z;
      return *this;
    }

    template<typename ty>
    const vec4i<ty>& vec4i<ty>::operator/= ( const vec4i<ty>& vec )
    {
      vec4i<ty> tmp = vec4i<ty>( 1 ) / vec;
      x *= tmp.x;
      y *= tmp.y;
      z *= tmp.z;
      w *= tmp.w;
      return *this;
    }
  }
}

#endif
