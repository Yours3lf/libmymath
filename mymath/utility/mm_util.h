#ifndef mm_util_h
#define mm_util_h

#include "mm_mat_func.h"
#include "mm_vec_func.h"
#include "mm_camera.h" 

#include <vector>

namespace mymath
{
#define MYMATH_UNPROJECT_FUNC(t) \
  MYMATH_INLINE impl::vec3i<t> unproject( const impl::vec3i<t>& ndc_pos, const impl::mat4i<t>& inv_mvp ) \
  { \
    impl::vec4i<t> obj_space = inv_mvp * impl::vec4i<t>( ndc_pos, 1 ); \
    return obj_space.xyz / obj_space.w; \
  }

#define MYMATH_CREATEROTATION_FUNC(t) \
  MYMATH_INLINE impl::mat4i<t> create_rotation( const t& angle, const impl::vec3i<t>& vec ) \
  { \
    assert( !impl::is_eq( length( vec ), (t)0 ) ); \
    t a = angle; \
    t s = std::sin( a ); \
    t c = std::cos( a ); \
    impl::vec3i<t> v = normalize( vec ); \
    t xx = v.x * v.x; \
    t yy = v.y * v.y; \
    t zz = v.z * v.z; \
    t xy = v.x * v.y; \
    t yz = v.y * v.z; \
    t zx = v.z * v.x; \
    t xs = v.x * s; \
    t ys = v.y * s; \
    t zs = v.z * s; \
    t oc = ( t )1 - c; \
    return impl::mat4i<t>( oc * xx + c, oc * xy + zs, oc * zx - ys, 0, \
                           oc * xy - zs, oc * yy + c, oc * yz + xs, 0, \
                           oc * zx + ys, oc * yz - xs, oc * zz + c, 0, \
                           0, 0, 0, 1 ); \
  }

#define MYMATH_CREATESCALE_FUNC(t) \
  MYMATH_INLINE impl::mat4i<t> create_scale( const impl::vec3i<t>& vec ) \
  { return impl::mat4i<t>( vec.x, 0, 0, 0, \
                           0, vec.y, 0, 0, \
                           0, 0, vec.z, 0, \
                           0, 0, 0, 1); }

#define MYMATH_CREATETRANSLATION_FUNC(t) \
  MYMATH_INLINE impl::mat4i<t> create_translation( const impl::vec3i<t>& vec ) \
  { return impl::mat4i<t>( 1, 0, 0, 0, \
                           0, 1, 0, 0, \
                           0, 0, 1, 0, \
                           vec.x, vec.y, vec.z, 1 ); }

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

  MYMATH_UNPROJECT_FUNC( float )

    MYMATH_CREATEROTATION_FUNC( float )

    MYMATH_CREATESCALE_FUNC( float )

    MYMATH_CREATETRANSLATION_FUNC( float )

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

    template< typename t >
  MYMATH_INLINE impl::mat4i<t> perspective( const t& fovy, const t& aspect, const t& near, const t& far )
  {
    t top = near * std::tan( fovy * ( t )0.5 );
    t bottom = -top;
    t left = bottom * aspect;
    t right = -left;
    impl::mat4i<t> r = mat4::identity;
    r[0].x = ( (t)2 * near ) / ( right - left );
    r[1].y = ( (t)2 * near ) / ( top - bottom );
    r[2].x = ( right + left ) / ( right - left );
    r[2].y = ( top + bottom ) / ( top - bottom );
    r[2].z = -( far + near ) / ( far - near );
    r[2].w = -(t)1;
    r[3].z = -( (t)2 * far * near ) / ( far - near );
    r[3].w = (t)0;
    return r;
  }

  template< typename t >
  MYMATH_INLINE impl::mat4i<t> ortographic( const t& left, const t& right, const t& bottom, const t& top, const t& near, const t& far )
  {
    impl::mat4i<t> r = mat4::identity;
    r[0].x = (t)2 / ( right - left );
    r[1].y = (t)2 / ( top - bottom );
    r[2].z = -(t)2 / ( far - near );
    r[3].x = -( ( right + left ) / ( right - left ) );
    r[3].y = -( ( top + bottom ) / ( top - bottom ) );
    r[3].z = -( ( far + near ) / ( far - near ) );
    r[3].w = (t)1;
    return r;
  }

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

  //TODO unit test
  //this function transforms a position vector by a matrix
  //it also ensures that the last coordinate of the vector will always be one
  //ie. the vector returned will not be in homogenous coordinates
  template< class t, class u >
  MYMATH_INLINE t transform_position( const t& vector, const u& transformation)
  {
    t tmp = transformation * vector;
    if( !impl::is_eq(tmp[tmp.length()-1], 1.0f) ) tmp /= tmp[tmp.length()-1];
    return tmp;
  }

  //TODO unit test
  //this function transforms a direction vector by a matrix
  //it also ensures that the last coordinate of the vector will always be one
  //because the last coordinate is implicitly zero (the vector represents a direction)
  template< class t, class u >
  MYMATH_INLINE t transform_direction( const t& vector, const u& transformation )
  {
    t tmp = transformation * vector;
    return tmp;
  }

  //TODO unit test
  //this function transforms a normal vector by the inverse transpose of a transformation matrix
  //the matrix is assumed to contain the inverse transpose of the transformation
  MYMATH_INLINE impl::vec3i<float> transform_direction( const impl::vec3i<float>& normal, const impl::mat4i<float>& inverse_transpose_transformation )
  {
    return impl::mat3i<float>(inverse_transpose_transformation) * normal;
  }

  //TODO unit test
  //computes the following transformation
  //1) apply a
  //2) apply b
  template< class t >
  MYMATH_INLINE t concat_transformations( const t& a, const t& b )
  {
    returns b * a;
  }

  //TODO unit test
  //computes the inverse of the following transformation
  //1) apply a
  //2) apply b
  template< class t >
  MYMATH_INLINE t inv_concat_transformations( const t& inv_a, const t& inv_b )
  {
    returns inv_a * inv_b;
  }

  //TODO unit test
  //returns true if the transformation changes the handedness of the coordinate system
  MYMATH_INLINE bool swaps_handedness( const impl::mat4i<float>& transformation )
  {
    return determinant( impl::mat3i<float>(transformation) ) < 0;
  }
}

#endif
