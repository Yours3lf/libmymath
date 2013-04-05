#ifndef mm_common_h
#define mm_common_h

#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>

//makes sure only explicit cast is available between vecn and float/double etc.
#define MYMATH_STRICT_GLSL 0

namespace mymath
{
  namespace impl
  {
    typedef int post; //this serves as a flag that an increment is a post increment
  }

  static const float pi = 3.1415926535897932384626433832795f;
  static const float two_pi = 2.0f * pi;
  static const float pi_div_180 = pi / 180.0f;
  static const float inv_pi_div_180 = 180.0f / pi;

  static const double dpi = 3.1415926535897932384626433832795;
  static const double dtwo_pi = 2.0 * dpi;
  static const double dpi_div_180 = dpi / 180.0;
  static const double dinv_pi_div_180 = 180.0 / dpi;

  inline float inversesqrt( const float& a )
  {
    return 1.0f / std::sqrt( a );
  }

  inline double inversesqrt( const double& a )
  {
    return 1.0 / std::sqrt( a );
  }

  inline float step( const float& a, const float& b )
  {
    return b < a ? 0 : 1;
  }

  inline double step( const double& a, const double& b )
  {
    return b < a ? 0 : 1;
  }

  inline float mix( const float& a, const float& b, const float& c )
  {
    return a * ( 1 - c ) + b * c;
  }

  inline double mix( const double& a, const double& b, const double& c )
  {
    return a * ( 1 - c ) + b * c;
  }

  inline float fract( const float& a )
  {
    return a - floor( a );
  }

  inline double fract( const double& a )
  {
    return a - floor( a );
  }

  inline float atan( const float& a, const float& b )
  {
    return std::atan( b / a );
  }

  inline double atan( const double& a, const double& b )
  {
    return std::atan( b / a );
  }

  inline float clamp( const float& a, const float& b, const float& c )
  {
    return std::min( std::max( a, b ), c );
  }

  inline double clamp( const double& a, const double& b, const double& c )
  {
    return std::min( std::max( a, b ), c );
  }

  inline float smoothstep( const float& a, const float& b, const float& c )
  {
    float u = ( c - a ) / ( b - a );
    u = clamp( u, 0, 1 );
    return u * u * ( 3 - 2 * u );
  }

  inline double smoothstep( const double& a, const double& b, const double& c )
  {
    double u = ( c - a ) / ( b - a );
    u = clamp( u, 0, 1 );
    return u * u * ( 3 - 2 * u );
  }

  inline float fma( const float& a, const float& b, const float& c )
  {
    return a * b + c;
  }

  inline double fma( const double& a, const double& b, const double& c )
  {
    return a * b + c;
  }

  inline float radians( const float& degrees )
  {
    return degrees * pi_div_180;
  }

  inline double radians( const double& degrees )
  {
    return degrees * dpi_div_180;
  }

  inline float degrees( const float& radians )
  {
    return radians * inv_pi_div_180;
  }

  inline double degrees( const double& radians )
  {
    return radians * dinv_pi_div_180;
  }

  inline float sign( const float& num )
  {
    if( num > 0.0f )
    {
      return 1.0f;
    }
    else if( num < 0.0f )
    {
      return -1.0f;
    }
    else
    {
      return num;
    }
  }

  inline double sign( const double& num )
  {
    if( num > 0.0 )
    {
      return 1.0;
    }
    else if( num < 0.0 )
    {
      return -1.0;
    }
    else
    {
      return num;
    }
  }

  inline int sign( const int& num )
  {
    if( num > 0 )
    {
      return 1;
    }
    else if( num < 0 )
    {
      return -1;
    }
    else
    {
      return num;
    }
  }

  inline float asinh( const float& num )
  {
    return std::log( num + std::sqrt( num * num + 1.0f ) );
  }

  inline double asinh( const double& num )
  {
    return std::log( num + std::sqrt( num * num + 1.0 ) );
  }

  inline float acosh( const float& num )
  {
    return std::log( num + std::sqrt( num * num - 1.0f ) );
  }

  inline double acosh( const double& num )
  {
    return std::log( num + std::sqrt( num * num - 1.0 ) );
  }

  inline float atanh( const float& num )
  {
    return std::log( ( 1.0f + num ) / ( 1.0f - num ) ) / 2.0f;
  }

  inline double atanh( const double& num )
  {
    return std::log( ( 1.0 + num ) / ( 1.0 - num ) ) / 2.0;
  }

  inline float log2( const float& num )
  {
    return std::log( num ) / std::log( 2.0f );
  }

  inline double log2( const double& num )
  {
    return std::log( num ) / std::log( 2.0 );
  }

  inline float trunc( const float& num )
  {
    return num < 0.0f ? -floor( -num ) : floor( num );
  }

  inline double trunc( const double& num )
  {
    return num < 0.0 ? -floor( -num ) : floor( num );
  }

  inline float round( const float& num )
  {
    if( num < 0 )
    {
      return float( int( num - 0.5f ) );
    }
    else
    {
      return float( int( num + 0.5f ) );
    }
  }

  inline double round( const double& num )
  {
    if( num < 0 )
    {
      return double( int( num - 0.5 ) );
    }
    else
    {
      return double( int( num + 0.5 ) );
    }
  }

  inline bool isnan( const float& num )
  {
#ifdef _WIN32
    return _isnan( num ) != 0;
#else
    return std::isnan( num );
#endif
  }

  inline bool isnan( const double& num )
  {
#ifdef _WIN32
    return _isnan( num ) != 0;
#else
    return std::isnan( num );
#endif
  }

  inline bool isinf( const float& num )
  {
#ifdef _WIN32
    return _fpclass( num ) == _FPCLASS_NINF || _fpclass( num ) == _FPCLASS_PINF;
#else
    return std::isinf( num );
#endif
  }

  inline bool isinf( const double& num )
  {
#ifdef _WIN32
    return _fpclass( num ) == _FPCLASS_NINF || _fpclass( num ) == _FPCLASS_PINF;
#else
    return std::isinf( num );
#endif
  }
}

namespace mm = mymath;

#endif
