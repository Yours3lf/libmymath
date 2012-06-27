#ifndef mm_common_h
#define mm_common_h

#include <iostream>
#include <cmath>
#include <algorithm>
#include <assert.h>

namespace mymath
{
  static const float pi = 3.1415926535897932384626433832795f;
  static const float two_pi = 2.0f * pi;
  static const float pi_div_180 = pi / 180.0f;
  static const float inv_pi_div_180 = 180.0f / pi;

  static const double dpi = 3.1415926535897932384626433832795;
  static const double dtwo_pi = 2.0 * dpi;
  static const double dpi_div_180 = dpi / 180.0;
  static const double dinv_pi_div_180 = 180.0 / dpi;

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
}

namespace mm = mymath;

#endif
