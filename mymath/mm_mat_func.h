#ifndef mm_mat_func_h
#define mm_mat_func_h

#include "mm_common.h"
#include "mm_mat2_impl.h"
#include "mm_mat3_impl.h"
#include "mm_mat4_impl.h"
#include "mm_vec_func.h"

#define MYMATH_VECMULMAT_FUNC(t) \
  inline mm::impl::vec2i<t> operator*( const mm::impl::vec2i<t>& vec, const mm::impl::mat2i<t>& mat ) \
  { return mm::impl::vec2i<t>( mm::dot( vec, mat[0] ), mm::dot( vec, mat[1] ) ); } \
  inline mm::impl::vec3i<t> operator*( const mm::impl::vec3i<t>& vec, const mm::impl::mat3i<t>& mat ) \
  { return mm::impl::vec3i<t>( mm::dot( vec, mat[0] ), mm::dot( vec, mat[1] ), mm::dot( vec, mat[2] ) ); } \
  inline mm::impl::vec4i<t> operator*( const mm::impl::vec4i<t>& vec, const mm::impl::mat4i<t>& mat ) \
  { return mm::impl::vec4i<t>( mm::dot( vec, mat[0] ), mm::dot( vec, mat[1] ), mm::dot( vec, mat[2] ), mm::dot( vec, mat[3] ) ); }

#define MYMATH_MATMULVEC_FUNC(t) \
  inline mm::impl::vec2i<t> operator* ( const mm::impl::mat2i<t>& mat, const mm::impl::vec2i<t>& vec ) \
  { \
    mm::impl::vec2i<t> r0( mat[0].x, mat[1].x ); \
    mm::impl::vec2i<t> r1( mat[0].y, mat[1].y ); \
    return mm::impl::vec2i<t>( mm::dot( vec, r0 ), mm::dot( vec, r1 ) ); \
  } \
  inline mm::impl::vec3i<t> operator* ( const mm::impl::mat3i<t>& mat, const mm::impl::vec3i<t>& vec ) \
  { \
    mm::impl::vec3i<t> r0( mat[0].x, mat[1].x, mat[2].x ); \
    mm::impl::vec3i<t> r1( mat[0].y, mat[1].y, mat[2].y ); \
    mm::impl::vec3i<t> r2( mat[0].z, mat[1].z, mat[2].z ); \
    return mm::impl::vec3i<t>( mm::dot( vec, r0 ), mm::dot( vec, r1 ), mm::dot( vec, r2 ) ); \
  } \
  inline mm::impl::vec4i<t> operator*( const mm::impl::mat4i<t>& mat, const mm::impl::vec4i<t>& vec ) \
  { \
    mm::impl::vec4i<t> r0( mat[0].x, mat[1].x, mat[2].x, mat[3].x ); \
    mm::impl::vec4i<t> r1( mat[0].y, mat[1].y, mat[2].y, mat[3].y ); \
    mm::impl::vec4i<t> r2( mat[0].z, mat[1].z, mat[2].z, mat[3].z ); \
    mm::impl::vec4i<t> r3( mat[0].w, mat[1].w, mat[2].w, mat[3].w ); \
    return mm::impl::vec4i<t>( mm::dot( vec, r0 ), mm::dot( vec, r1 ), mm::dot( vec, r2 ), mm::dot( vec, r3 ) ); \
  }

#define MYMATH_VECMULEQUALMAT_FUNC(t) \
  inline const mm::impl::vec2i<t>& operator*=( mm::impl::vec2i<t>& vec, const mm::impl::mat2i<t>& mat ) \
  { \
    mm::impl::vec2i<t> res = vec * mat; \
    vec = res; \
    return vec; \
  } \
  inline const mm::impl::vec3i<t>& operator*=( mm::impl::vec3i<t>& vec, const mm::impl::mat3i<t>& mat ) \
  { \
    mm::impl::vec3i<t> res = vec * mat; \
    vec = res; \
    return vec; \
  } \
  inline const mm::impl::vec4i<t>& operator*=( mm::impl::vec4i<t>& vec, const mm::impl::mat4i<t>& mat ) \
  { \
    mm::impl::vec4i<t> res = vec * mat; \
    vec = res; \
    return vec; \
  }

template< typename t >
inline mm::impl::mat2i<t> operator* ( const mm::impl::mat2i<t>& a, const mm::impl::mat2i<t>& b )
{
  mm::impl::vec2i<t> r0( a[0].x, a[1].x );
  mm::impl::vec2i<t> r1( a[0].y, a[1].y );
  mm::impl::vec2i<t> c0 = b[0];
  mm::impl::vec2i<t> c1 = b[1];
  return mm::impl::mat2i<t>( mm::dot( r0, c0 ), mm::dot( r1, c0 ),
                             mm::dot( r0, c1 ), mm::dot( r1, c1 ) );
}

template< typename t >
inline mm::impl::mat3i<t> operator* ( const mm::impl::mat3i<t>& a, const mm::impl::mat3i<t>& b )
{
  mm::impl::vec3i<t> r0( a[0].x, a[1].x, a[2].x );
  mm::impl::vec3i<t> r1( a[0].y, a[1].y, a[2].y );
  mm::impl::vec3i<t> r2( a[0].z, a[1].z, a[2].z );
  mm::impl::vec3i<t> c0 = b[0];
  mm::impl::vec3i<t> c1 = b[1];
  mm::impl::vec3i<t> c2 = b[2];
  return mm::impl::mat3i<t>( mm::dot( r0, c0 ), mm::dot( r1, c0 ), mm::dot( r2, c0 ),
                             mm::dot( r0, c1 ), mm::dot( r1, c1 ), mm::dot( r2, c1 ),
                             mm::dot( r0, c2 ), mm::dot( r1, c2 ), mm::dot( r2, c2 ) );
}

template< typename t >
inline mm::impl::mat4i<t> operator* ( const mm::impl::mat4i<t>& a, const mm::impl::mat4i<t>& b )
{
  mm::impl::vec4i<t> r0( a[0].x, a[1].x, a[2].x, a[3].x );
  mm::impl::vec4i<t> r1( a[0].y, a[1].y, a[2].y, a[3].y );
  mm::impl::vec4i<t> r2( a[0].z, a[1].z, a[2].z, a[3].z );
  mm::impl::vec4i<t> r3( a[0].w, a[1].w, a[2].w, a[3].w );
  mm::impl::vec4i<t> c0 = b[0];
  mm::impl::vec4i<t> c1 = b[1];
  mm::impl::vec4i<t> c2 = b[2];
  mm::impl::vec4i<t> c3 = b[3];
  return mm::impl::mat4i<t>( mm::dot( r0, c0 ), mm::dot( r1, c0 ), mm::dot( r2, c0 ), mm::dot( r3, c0 ),
                             mm::dot( r0, c1 ), mm::dot( r1, c1 ), mm::dot( r2, c1 ), mm::dot( r3, c1 ),
                             mm::dot( r0, c2 ), mm::dot( r1, c2 ), mm::dot( r2, c2 ), mm::dot( r3, c2 ),
                             mm::dot( r0, c3 ), mm::dot( r1, c3 ), mm::dot( r2, c3 ), mm::dot( r3, c3 ) );
}

template< typename t >
inline mm::impl::mat2i<t> operator*( const mm::impl::mat2i<t>& mat, const t& num )
{
  return mm::impl::mat2i<t>( mat[0] * mm::impl::vec2i<t>( num ), mat[1] * mm::impl::vec2i<t>( num ) );
}

template< typename t >
inline mm::impl::mat3i<t> operator*( const mm::impl::mat3i<t>& mat, const t& num )
{
  return mm::impl::mat3i<t>( mat[0] * mm::impl::vec3i<t>( num ), mat[1] * mm::impl::vec3i<t>( num ), mat[2] * mm::impl::vec3i<t>( num ) );
}

template< typename t >
inline mm::impl::mat4i<t> operator*( const mm::impl::mat4i<t>& mat, const t& num )
{
  return mm::impl::mat4i<t>( mat[0] * mm::impl::vec4i<t>( num ), mat[1] * mm::impl::vec4i<t>( num ), mat[2] * mm::impl::vec4i<t>( num ), mat[3] * mm::impl::vec4i<t>( num ) );
}

template< typename t >
inline mm::impl::mat2i<t> operator*( const t& num, const mm::impl::mat2i<t>& mat )
{
  return mat * num;
}

template< typename t >
inline mm::impl::mat3i<t> operator*( const t& num, const mm::impl::mat3i<t>& mat )
{
  return mat * num;
}

template< typename t >
inline mm::impl::mat4i<t> operator*( const t& num, const mm::impl::mat4i<t>& mat )
{
  return mat * num;
}

template< typename t >
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::mat2i<t>& mat )
{
  return output << "( " << mat[0].x << ", " << mat[1].x << "\n  "
         /*__________*/ << mat[0].y << ", " << mat[1].y << " )\n";
}

template< typename t >
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::mat3i<t>& mat )
{
  return output << "( " << mat[0].x << ", " << mat[1].x << ", " << mat[2].x << "\n  "
         /*__________*/ << mat[0].y << ", " << mat[1].y << ", " << mat[2].y << "\n  "
         /*__________*/ << mat[0].z << ", " << mat[1].z << ", " << mat[2].z << " )\n";
}

template< typename t >
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::mat4i<t>& mat )
{
  return output << "( " << mat[0].x << ", " << mat[1].x << ", " << mat[2].x << ", " << mat[3].x << "\n  "
         /*__________*/ << mat[0].y << ", " << mat[1].y << ", " << mat[2].y << ", " << mat[3].y << "\n  "
         /*__________*/ << mat[0].z << ", " << mat[1].z << ", " << mat[2].z << ", " << mat[3].z << "\n  "
         /*__________*/ << mat[0].w << ", " << mat[1].w << ", " << mat[2].w << ", " << mat[3].w << " )\n";
}

MYMATH_VECMULMAT_FUNC( float )
MYMATH_VECMULMAT_FUNC( double )

MYMATH_MATMULVEC_FUNC( float )
MYMATH_MATMULVEC_FUNC( double )

MYMATH_VECMULEQUALMAT_FUNC( float )
MYMATH_VECMULEQUALMAT_FUNC( double )

namespace mymath
{
  template< typename t >
  inline impl::mat2i<t> transpose( const impl::mat2i<t>& mat )
  {
    return impl::mat2i<t>( mat[0].x, mat[1].x,
                           mat[0].y, mat[1].y );
  }

  template< typename t >
  inline impl::mat3i<t> transpose( const impl::mat3i<t>& mat )
  {
    return impl::mat3i<t>( mat[0].x, mat[1].x, mat[2].x,
                           mat[0].y, mat[1].y, mat[2].y,
                           mat[0].z, mat[1].z, mat[2].z );
  }

  template< typename t >
  inline impl::mat4i<t> transpose( const impl::mat4i<t>& mat )
  {
    return impl::mat4i<t>( mat[0].x, mat[1].x, mat[2].x, mat[3].x,
                           mat[0].y, mat[1].y, mat[2].y, mat[3].y,
                           mat[0].z, mat[1].z, mat[2].z, mat[3].z,
                           mat[0].w, mat[1].w, mat[2].w, mat[3].w );
  }

  template< typename t >
  inline t determinant( const impl::mat2i<t>& mat )
  {
    return mat[0].x * mat[1].y - mat[1].x * mat[0].y;
  }

  template< typename t >
  inline t determinant( const impl::mat3i<t>& mat )
  {
    return dot( cross( mat[0], mat[1] ), mat[2] );
  }

  template< typename t >
  inline t determinant( const impl::mat4i<t>& mat )
  {
    impl::mat3i<t> m0( mat[1].y, mat[2].y, mat[3].y,
                       mat[1].z, mat[2].z, mat[3].z,
                       mat[1].w, mat[2].w, mat[3].w );
    impl::mat3i<t> m1( mat[1].x, mat[2].x, mat[3].x,
                       mat[1].z, mat[2].z, mat[3].z,
                       mat[1].w, mat[2].w, mat[3].w );
    impl::mat3i<t> m2( mat[1].x, mat[2].x, mat[3].x,
                       mat[1].y, mat[2].y, mat[3].y,
                       mat[1].w, mat[2].w, mat[3].w );
    impl::mat3i<t> m3( mat[1].x, mat[2].x, mat[3].x,
                       mat[1].y, mat[2].y, mat[3].y,
                       mat[1].z, mat[2].z, mat[3].z );
    return mat[0].x * determinant( m0 ) - mat[0].y * determinant( m1 ) + mat[0].z * determinant( m2 ) - mat[0].w * determinant( m3 );
  }

  template< typename t >
  inline impl::mat2i<t> inverse( const impl::mat2i<t>& mat )
  {
    assert( determinant( mat ) != 0 );
    return ::operator*( impl::mat2i<t>( mat[1].y, -mat[0].y, -mat[1].x, mat[0].x ), ( ( t )1 / determinant( mat ) ) );
  }

  template< typename t >
  inline impl::mat3i<t> inverse( const impl::mat3i<t>& mat )
  {
    assert( determinant( mat ) != 0 );

    return ::operator*( impl::mat3i<t>( determinant( impl::mat2i<t>( mat[1].y, mat[1].z,
                                        mat[2].y, mat[2].z ) ),
                                        -determinant( impl::mat2i<t>( mat[0].y, mat[0].z,
                                            mat[2].y, mat[2].z ) ),
                                        determinant( impl::mat2i<t>( mat[0].y, mat[0].z,
                                            mat[1].y, mat[1].z ) ),
                                        -determinant( impl::mat2i<t>( mat[1].x, mat[1].z,
                                            mat[2].x, mat[2].z ) ),
                                        determinant( impl::mat2i<t>( mat[0].x, mat[0].z,
                                            mat[2].x, mat[2].z ) ),
                                        -determinant( impl::mat2i<t>( mat[0].x, mat[0].z,
                                            mat[1].x, mat[1].z ) ),
                                        determinant( impl::mat2i<t>( mat[1].x, mat[1].y,
                                            mat[2].x, mat[2].y ) ),
                                        -determinant( impl::mat2i<t>( mat[0].x, mat[0].y,
                                            mat[2].x, mat[2].y ) ),
                                        determinant( impl::mat2i<t>( mat[0].x, mat[0].y,
                                            mat[1].x, mat[1].y ) )
                                      ), ( ( t )1 / determinant( mat ) ) );
  }

  template< typename t >
  inline impl::mat4i<t> inverse( const impl::mat4i<t>& mat )
  {
    assert( determinant( mat ) != 0 );

    return ::operator*( impl::mat4i<t>(
                          determinant( impl::mat3i<t>( mat[1].y, mat[2].y, mat[3].y,
                                       mat[1].z, mat[2].z, mat[3].z,
                                       mat[1].w, mat[2].w, mat[3].w ) ),
                          -determinant( impl::mat3i<t>( mat[0].y, mat[2].y, mat[3].y,
                                        mat[0].z, mat[2].z, mat[3].z,
                                        mat[0].w, mat[2].w, mat[3].w ) ),
                          determinant( impl::mat3i<t>( mat[0].y, mat[1].y, mat[3].y,
                                       mat[0].z, mat[1].z, mat[3].z,
                                       mat[0].w, mat[1].w, mat[3].w ) ),
                          -determinant( impl::mat3i<t>( mat[0].y, mat[1].y, mat[2].y,
                                        mat[0].z, mat[1].z, mat[2].z,
                                        mat[0].w, mat[1].w, mat[2].w ) ),
                          -determinant( impl::mat3i<t>( mat[1].x, mat[2].x, mat[3].x,
                                        mat[1].z, mat[2].z, mat[3].z,
                                        mat[1].w, mat[2].w, mat[3].w ) ),
                          determinant( impl::mat3i<t>( mat[0].x, mat[2].x, mat[3].x,
                                       mat[0].z, mat[2].z, mat[3].z,
                                       mat[0].w, mat[2].w, mat[3].w ) ),
                          -determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[3].x,
                                        mat[0].z, mat[1].z, mat[3].z,
                                        mat[0].w, mat[1].w, mat[3].w ) ),
                          determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[2].x,
                                       mat[0].z, mat[1].z, mat[2].z,
                                       mat[0].w, mat[1].w, mat[2].w ) ),
                          determinant( impl::mat3i<t>( mat[1].x, mat[2].x, mat[3].x,
                                       mat[1].y, mat[2].y, mat[3].y,
                                       mat[1].w, mat[2].w, mat[3].w ) ),
                          -determinant( impl::mat3i<t>( mat[0].x, mat[2].x, mat[3].x,
                                        mat[0].y, mat[2].y, mat[3].y,
                                        mat[0].w, mat[2].w, mat[3].w ) ),
                          determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[3].x,
                                       mat[0].y, mat[1].y, mat[3].y,
                                       mat[0].w, mat[1].w, mat[3].w ) ),
                          -determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[2].x,
                                        mat[0].y, mat[1].y, mat[2].y,
                                        mat[0].w, mat[1].w, mat[2].w ) ),
                          -determinant( impl::mat3i<t>( mat[1].x, mat[2].x, mat[3].x,
                                        mat[1].y, mat[2].y, mat[3].y,
                                        mat[1].z, mat[2].z, mat[3].z ) ),
                          determinant( impl::mat3i<t>( mat[0].x, mat[2].x, mat[3].x,
                                       mat[0].y, mat[2].y, mat[3].y,
                                       mat[0].z, mat[2].z, mat[3].z ) ),
                          -determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[3].x,
                                        mat[0].y, mat[1].y, mat[3].y,
                                        mat[0].z, mat[1].z, mat[3].z ) ),
                          determinant( impl::mat3i<t>( mat[0].x, mat[1].x, mat[2].x,
                                       mat[0].y, mat[1].y, mat[2].y,
                                       mat[0].z, mat[1].z, mat[2].z ) ) ), ( ( t )1 / determinant( mat ) ) );
  }

  template< typename t >
  inline impl::mat2i<t> matrixCompMult( const impl::mat2i<t>& a, const impl::mat2i<t>& b )
  {
    return impl::mat2i<t>( a[0] * b[0], a[1] * b[1] );
  }

  template< typename t >
  inline impl::mat3i<t> matrixCompMult( const impl::mat3i<t>& a, const impl::mat3i<t>& b )
  {
    return impl::mat3i<t>( a[0] * b[0], a[1] * b[1], a[2] * b[2] );
  }

  template< typename t >
  impl::mat4i<t> matrixCompMult( const impl::mat4i<t>& a, const impl::mat4i<t>& b )
  {
    return impl::mat4i<t>( a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3] );
  }
}

#endif



