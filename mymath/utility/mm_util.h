#ifndef mm_util_h
#define mm_util_h

#include "../mm_mat_func.h"
#include "../mm_vec_func.h"
#include "../mm_camera.h" 

#include <vector>

namespace mymath
{
#define MYMATH_GETANGLE_FUNC(v, t) \
  MYMATH_INLINE t get_angle(const impl::v<t>& a, const impl::v<t>& b) \
  { return std::acos( dot( normalize(a), normalize(b) ) ); }

#define MYMATH_CLOSEENOUGH_FUNC(t) \
  MYMATH_INLINE bool close_enough( const t& candidate, const t& compare, const t& epsilon ) \
  { return ( std::abs( candidate - compare ) < epsilon ); }

#define MYMATH_FINDNORMAL_FUNC(t) \
  MYMATH_INLINE impl::vec3i<t> find_normal(const impl::vec3i<t>& a, const impl::vec3i<t>& b, const impl::vec3i<t>& c ) \
  { return normalize( cross( a - b, b - c ) ); }

#define MYMATH_CALCTANGENT_FUNC(t) \
  MYMATH_INLINE impl::vec3i<t> calc_tangent( const impl::vec3i<t> vertices[3], const impl::vec2i<t> texcoords[3], const impl::vec3i<t>& normal ) \
  { \
    impl::vec3i<t> dv2v1 = vertices[1] - vertices[0]; \
    impl::vec3i<t> dv3v1 = vertices[2] - vertices[0]; \
    t dc2c1t = texcoords[1][0] - texcoords[0][0]; \
    t dc2c1b = texcoords[1][1] - texcoords[0][1]; \
    t dc3c1t = texcoords[2][0] - texcoords[0][0]; \
    t dc3c1b = texcoords[2][1] - texcoords[0][1]; \
    t m = (t)1 / ( ( dc2c1t * dc3c1b ) - ( dc3c1t * dc2c1b ) ); \
    dv2v1 *= impl::vec3i<t>(dc3c1b); \
    dv3v1 *= impl::vec3i<t>(dc2c1b); \
    impl::vec3i<t> tangent = dv2v1 - dv3v1; \
    tangent *= impl::vec3i<t>(m); \
    tangent = normalize ( tangent ); \
    impl::vec3i<t> bitangent = cross ( normal, tangent ); \
    tangent = cross ( bitangent, normal ); \
    return normalize ( tangent ); \
  }

    MYMATH_GETANGLE_FUNC( vec2i, float )
    MYMATH_GETANGLE_FUNC( vec3i, float )
    MYMATH_GETANGLE_FUNC( vec4i, float )

#if MYMATH_DOUBLE_PRECISION == 1
    MYMATH_CREATEROTATION_FUNC( double )
    MYMATH_CREATESCALE_FUNC( double )
    MYMATH_CREATETRANSLATION_FUNC( double )
    MYMATH_GETANGLE_FUNC( vec2i, double )
    MYMATH_GETANGLE_FUNC( vec3i, double )
    MYMATH_GETANGLE_FUNC( vec4i, double )
#endif

    MYMATH_INLINE bool is_pow_2( const unsigned int& val )
  {
    if( val == 0 )
      return true;

    unsigned int pow2 = 1;

    while( val > pow2 )
    {
      pow2 *= 2;

      if( pow2 == val )
      {
        return true;
      }
    }

    return false;
  }

  MYMATH_CLOSEENOUGH_FUNC( float )
    MYMATH_FINDNORMAL_FUNC( float )
    MYMATH_CALCTANGENT_FUNC( float )

#if MYMATH_DOUBLE_PRECISION == 1
    MYMATH_CLOSEENOUGH_FUNC( double )
    MYMATH_FINDNORMAL_FUNC( double )
    MYMATH_CALCTANGENT_FUNC( double )
#endif

  template< class t >
  MYMATH_INLINE float length_squared( const t& v )
  {
    return dot( v, v );
  }

  //constructs a coordinate system from the normalized vector v1
  //v1, v2, v3 will contain the unit vectors of the new coordinate system
  MYMATH_INLINE void get_coord_unit_vectors( const impl::vec3i<float>& v1, impl::vec3i<float>& v2, impl::vec3i<float>& v3 )
  {
    if( std::abs( v1.x ) > std::abs( v1.y ) )
    {
      float inv_len = 1.0f / length( v1.xz );
      v2 = impl::vec3i<float>( -v1.z * inv_len, 0, v1.x * inv_len );
    }
    else
    {
      float inv_len = 1.0f / length( v1.yz );
      v2 = impl::vec3i<float>( 0, v1.z * inv_len, -v1.y * inv_len );
    }
    v3 = cross( v1, v2 );
  }

  //TODO unit test
  //fills v with the world space coordinates of the corners of the frustum define by the projection matrix
  //used to compute the inverse view-projection matrix
  MYMATH_INLINE void get_frustum_corners( std::vector<impl::vec4i<float> >& v, const impl::mat4i<float>& inv_viewproj )
  {
    int start = v.size();
    v.push_back( impl::vec4i<float>( -1,  1, -1, 1 ) ); //ntl
    v.push_back( impl::vec4i<float>( 1, 1, -1, 1 ) ); //ntr
    v.push_back( impl::vec4i<float>( -1, -1, -1, 1 ) ); //nbl
    v.push_back( impl::vec4i<float>( 1, -1, -1, 1 ) ); //nbr
    v.push_back( impl::vec4i<float>( -1, 1, 1, 1 ) ); //ftl
    v.push_back( impl::vec4i<float>( 1, 1, 1, 1 ) ); //ftr
    v.push_back( impl::vec4i<float>( -1, -1, 1, 1 ) ); //fbl
    v.push_back( impl::vec4i<float>( 1, -1, 1, 1 ) ); //fbr

    for( int c = start; c < v.size(); ++c )
    {
      v[c] = inv_viewproj * v[c]; //transform back to world space
    }

    for( int c = start; c < v.size( ); ++c )
    {
      v[c] = v[c] / v[c].w;
    }
  }

  //TODO unit test
  MYMATH_INLINE camera<float> lookat( const impl::vec3i<float>& eye, const impl::vec3i<float>& lookat, const impl::vec3i<float>& up )
  {
    camera<float> c;
    c.view_dir = normalize( lookat - eye );
    c.up_vector = normalize( up );
    c.pos = eye;
    impl::vec3i<float> right = normalize( cross( c.view_dir, c.up_vector ) );
    c.up_vector = normalize( cross( right, c.view_dir ) );
    return c;
  };
}

#endif
