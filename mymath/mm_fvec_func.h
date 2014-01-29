#ifndef mm_vec_func_h
#define mm_vec_func_h

#include "mm_common.h"
#include "mm_sse.h"

namespace mymath
{
  inline bool equal( const impl::vec2i<float>& a, const impl::vec2i<float>& b )
  {
    impl::vec2i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y;
  }
  inline bool equal( const impl::vec3i<float>& a, const impl::vec3i<float>& b )
  {
    impl::vec3i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y && c.z;
  }
  inline bool equal( const impl::vec4i<float>& a, const impl::vec4i<float>& b )
  {
    impl::vec4i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y && c.z && c.w;
  }

  inline bool notEqual( const impl::vec2i<float>& a, const impl::vec2i<float>& b )
  {
    return !equal( a, b );
  }
  inline bool notEqual( const impl::vec3i<float>& a, const impl::vec3i<float>& b )
  {
    return !equal( a, b );
  }
  inline bool notEqual( const impl::vec4i<float>& a, const impl::vec4i<float>& b )
  {
    return !equal( a, b );
  }
}

//mul
inline mm::impl::vec2i<float> operator*( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator*( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator*( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}

//div
inline mm::impl::vec2i<float> operator/( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

inline mm::impl::vec3i<float> operator/( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) && !mm::impl::is_eq( b.z, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

inline mm::impl::vec4i<float> operator/( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) && !mm::impl::is_eq( b.z, ( float )0 ) && !mm::impl::is_eq( b.w, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

//add
inline mm::impl::vec2i<float> operator+( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator+( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator+( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}

//sub
inline mm::impl::vec2i<float> operator-( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator-( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator-( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}

//mod
inline mm::impl::vec2i<float> operator%( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return mm::impl::sse_mod_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator%( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return mm::impl::sse_mod_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator%( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return mm::impl::sse_mod_ps( a.d, b.d );
}

//TODO shift left
//TODO shift right

//and
inline mm::impl::vec2i<float> operator&( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator&( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator&( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}

//xor
inline mm::impl::vec2i<float> operator^( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator^( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator^( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}

//or
inline mm::impl::vec2i<float> operator|( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}
inline mm::impl::vec3i<float> operator|( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}
inline mm::impl::vec4i<float> operator|( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}

//negate
inline mm::impl::vec2i<float> operator-( const mm::impl::vec2i<float>& a )
{
  return mm::impl::sse_neg_ps( a.d );
}
inline mm::impl::vec3i<float> operator-( const mm::impl::vec3i<float>& a )
{
  return mm::impl::sse_neg_ps( a.d );
}
inline mm::impl::vec4i<float> operator-( const mm::impl::vec4i<float>& a )
{
  return mm::impl::sse_neg_ps( a.d );
}

//cout
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec2i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << " )\n";
}
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec3i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n";
}
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::vec4i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " )\n";
}

namespace mymath
{
//less
  inline bool lessThan( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    mm::impl::vec2i<float> v = _mm_cmplt_ps( a.d, b.d );
    return v.x && v.y;
  }
  inline bool lessThan( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    mm::impl::vec3i<float> v = _mm_cmplt_ps( a.d, b.d );
    return v.x && v.y && v.z;
  }
  inline bool lessThan( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    mm::impl::vec4i<float> v = _mm_cmplt_ps( a.d, b.d );
    return v.x && v.y && v.z && v.w;
  }

//greater
  inline bool greaterThan( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    mm::impl::vec2i<float> v = _mm_cmpgt_ps( a.d, b.d );
    return v.x && v.y;
  }
  inline bool greaterThan( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    mm::impl::vec3i<float> v = _mm_cmpgt_ps( a.d, b.d );
    return v.x && v.y && v.z;
  }
  inline bool greaterThan( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    mm::impl::vec4i<float> v = _mm_cmpgt_ps( a.d, b.d );
    return v.x && v.y && v.z && v.w;
  }

//less or equal
  inline bool lessThanEqual( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    mm::impl::vec2i<float> v = _mm_cmple_ps( a.d, b.d );
    return v.x && v.y;
  }
  inline bool lessThanEqual( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    mm::impl::vec3i<float> v = _mm_cmple_ps( a.d, b.d );
    return v.x && v.y && v.z;
  }
  inline bool lessThanEqual( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    mm::impl::vec4i<float> v = _mm_cmple_ps( a.d, b.d );
    return v.x && v.y && v.z && v.w;
  }

//greater or equal
  inline bool greaterThanEqual( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    mm::impl::vec2i<float> v = _mm_cmpge_ps( a.d, b.d );
    return v.x && v.y;
  }
  inline bool greaterThanEqual( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    mm::impl::vec3i<float> v = _mm_cmpge_ps( a.d, b.d );
    return v.x && v.y && v.z;
  }
  inline bool greaterThanEqual( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    mm::impl::vec4i<float> v = _mm_cmpge_ps( a.d, b.d );
    return v.x && v.y && v.z && v.w;
  }

//radians
  inline mm::impl::vec2i<float> radians( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_rad_ps( vec.d );
  }
  inline mm::impl::vec3i<float> radians( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_rad_ps( vec.d );
  }
  inline mm::impl::vec4i<float> radians( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_rad_ps( vec.d );
  }

//degrees
  inline mm::impl::vec2i<float> degrees( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_deg_ps( vec.d );
  }
  inline mm::impl::vec3i<float> degrees( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_deg_ps( vec.d );
  }
  inline mm::impl::vec4i<float> degrees( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_deg_ps( vec.d );
  }

//asinh
  inline mm::impl::vec2i<float> asinh( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_asinh_ps( vec.d );
  }
  inline mm::impl::vec3i<float> asinh( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_asinh_ps( vec.d );
  }
  inline mm::impl::vec4i<float> asinh( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_asinh_ps( vec.d );
  }

//acosh
  inline mm::impl::vec2i<float> acosh( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_acosh_ps( vec.d );
  }
  inline mm::impl::vec3i<float> acosh( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_acosh_ps( vec.d );
  }
  inline mm::impl::vec4i<float> acosh( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_acosh_ps( vec.d );
  }

//atanh
  inline mm::impl::vec2i<float> atanh( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_atanh_ps( vec.d );
  }
  inline mm::impl::vec3i<float> atanh( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_atanh_ps( vec.d );
  }
  inline mm::impl::vec4i<float> atanh( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_atanh_ps( vec.d );
  }

//exp2
  inline mm::impl::vec2i<float> exp2( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_exp2_ps( vec.d );
  }
  inline mm::impl::vec3i<float> exp2( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_exp2_ps( vec.d );
  }
  inline mm::impl::vec4i<float> exp2( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_exp2_ps( vec.d );
  }

//log2
  inline mm::impl::vec2i<float> log2( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_log2_ps( vec.d );
  }
  inline mm::impl::vec3i<float> log2( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_log2_ps( vec.d );
  }
  inline mm::impl::vec4i<float> log2( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_log2_ps( vec.d );
  }

//inversesqrt
  inline mm::impl::vec2i<float> inversesqrt( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_inversesqrt_ps( vec.d );
  }
  inline mm::impl::vec3i<float> inversesqrt( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_inversesqrt_ps( vec.d );
  }
  inline mm::impl::vec4i<float> inversesqrt( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_inversesqrt_ps( vec.d );
  }

//sign
  inline mm::impl::vec2i<float> sign( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_sign_ps( vec.d );
  }
  inline mm::impl::vec3i<float> sign( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_sign_ps( vec.d );
  }
  inline mm::impl::vec4i<float> sign( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_sign_ps( vec.d );
  }

//trunc
  inline mm::impl::vec2i<float> trunc( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_trunc_ps( vec.d );
  }
  inline mm::impl::vec3i<float> trunc( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_trunc_ps( vec.d );
  }
  inline mm::impl::vec4i<float> trunc( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_trunc_ps( vec.d );
  }

//round
  inline mm::impl::vec2i<float> round( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_round_ps( vec.d );
  }
  inline mm::impl::vec3i<float> round( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_round_ps( vec.d );
  }
  inline mm::impl::vec4i<float> round( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_round_ps( vec.d );
  }

//fract
  inline mm::impl::vec2i<float> fract( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_fract_ps( vec.d );
  }
  inline mm::impl::vec3i<float> fract( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_fract_ps( vec.d );
  }
  inline mm::impl::vec4i<float> fract( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_fract_ps( vec.d );
  }

//mod
  inline mm::impl::vec2i<float> mod( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return mm::impl::sse_mod_ps( a.d, b.d );
  }
  inline mm::impl::vec3i<float> mod( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_mod_ps( a.d, b.d );
  }
  inline mm::impl::vec4i<float> mod( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return mm::impl::sse_mod_ps( a.d, b.d );
  }

//mix
  inline mm::impl::vec2i<float> mix( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_mix_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> mix( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_mix_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> mix( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_mix_ps( a.d, b.d, c.d );
  }

//step
  inline mm::impl::vec2i<float> step( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return mm::impl::sse_step_ps( a.d, b.d );
  }
  inline mm::impl::vec3i<float> step( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_step_ps( a.d, b.d );
  }
  inline mm::impl::vec4i<float> step( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return mm::impl::sse_step_ps( a.d, b.d );
  }

//clamp
  inline mm::impl::vec2i<float> clamp( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_clp_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> clamp( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_clp_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> clamp( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_clp_ps( a.d, b.d, c.d );
  }

//smoothstep
  inline mm::impl::vec2i<float> smoothstep( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_smoothstep_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> smoothstep( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_smoothstep_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> smoothstep( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_smoothstep_ps( a.d, b.d, c.d );
  }

//fma
  inline mm::impl::vec2i<float> fma( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_fma_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> fma( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_fma_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> fma( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_fma_ps( a.d, b.d, c.d );
  }

//dot
  inline float dot( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return mm::impl::sse_dot_ps( a.d, b.d );
  }
  inline float dot( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_dot_ps( a.d, b.d );
  }
  inline float dot( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return mm::impl::sse_dot_ps( a.d, b.d );
  }

//length
  inline float length( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_length_ps( vec.d );
  }
  inline float length( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_length_ps( vec.d );
  }
  inline float length( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_length_ps( vec.d );
  }

//distance
  inline float distance( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return mm::impl::sse_distance_ps( a.d, b.d );
  }
  inline float distance( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_distance_ps( a.d, b.d );
  }
  inline float distance( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return mm::impl::sse_distance_ps( a.d, b.d );
  }

//normalize
  inline mm::impl::vec2i<float> normalize( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_normalize_ps( vec.d );
  }
  inline mm::impl::vec3i<float> normalize( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_normalize_ps( vec.d );
  }
  inline mm::impl::vec4i<float> normalize( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_normalize_ps( vec.d );
  }

//reflect
  inline mm::impl::vec2i<float> reflect( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return mm::impl::sse_reflect_ps( a.d, b.d );
  }
  inline mm::impl::vec3i<float> reflect( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_reflect_ps( a.d, b.d );
  }
  inline mm::impl::vec4i<float> reflect( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return mm::impl::sse_reflect_ps( a.d, b.d );
  }

//refract
  inline mm::impl::vec2i<float> refract( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_refract_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> refract( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_refract_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> refract( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_refract_ps( a.d, b.d, c.d );
  }

//faceforward
  inline mm::impl::vec2i<float> faceforward( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b, const mm::impl::vec2i<float>& c )
  {
    return mm::impl::sse_faceforward_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec3i<float> faceforward( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b, const mm::impl::vec3i<float>& c )
  {
    return mm::impl::sse_faceforward_ps( a.d, b.d, c.d );
  }
  inline mm::impl::vec4i<float> faceforward( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b, const mm::impl::vec4i<float>& c )
  {
    return mm::impl::sse_faceforward_ps( a.d, b.d, c.d );
  }

//TODO isnan, isinf

//cross
  inline mm::impl::vec3i<float> cross( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return mm::impl::sse_cross_ps( a.d, b.d );
  }

//floor
  inline mm::impl::vec2i<float> floor( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_floor_ps( vec.d );
  }
  inline mm::impl::vec3i<float> floor( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_floor_ps( vec.d );
  }
  inline mm::impl::vec4i<float> floor( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_floor_ps( vec.d );
  }

//sqrt
  inline mm::impl::vec2i<float> sqrt( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_sqrt_ps( vec.d );
  }
  inline mm::impl::vec3i<float> sqrt( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_sqrt_ps( vec.d );
  }
  inline mm::impl::vec4i<float> sqrt( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_sqrt_ps( vec.d );
  }

//sin
  inline mm::impl::vec2i<float> sin( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_sin_ps( vec.d );
  }
  inline mm::impl::vec3i<float> sin( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_sin_ps( vec.d );
  }
  inline mm::impl::vec4i<float> sin( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_sin_ps( vec.d );
  }

//cos
  inline mm::impl::vec2i<float> cos( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_cos_ps( vec.d );
  }
  inline mm::impl::vec3i<float> cos( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_cos_ps( vec.d );
  }
  inline mm::impl::vec4i<float> cos( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_cos_ps( vec.d );
  }

//tan
  inline mm::impl::vec2i<float> tan( const mm::impl::vec2i<float>& vec )
  {
    mm::impl::vec2i<float> s, c;
    mm::impl::sse_sincos_ps( vec.d, &s.d, &c.d );
    return _mm_div_ps( s.d, c.d );
  }
  inline mm::impl::vec3i<float> tan( const mm::impl::vec3i<float>& vec )
  {
    mm::impl::vec3i<float> s, c;
    mm::impl::sse_sincos_ps( vec.d, &s.d, &c.d );
    return _mm_div_ps( s.d, c.d );
  }
  inline mm::impl::vec4i<float> tan( const mm::impl::vec4i<float>& vec )
  {
    mm::impl::vec4i<float> s, c;
    mm::impl::sse_sincos_ps( vec.d, &s.d, &c.d );
    return _mm_div_ps( s.d, c.d );
  }

//asin
  inline mm::impl::vec2i<float> asin( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_asin_ps( vec.d );
  }
  inline mm::impl::vec3i<float> asin( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_asin_ps( vec.d );
  }
  inline mm::impl::vec4i<float> asin( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_asin_ps( vec.d );
  }

//acos
  inline mm::impl::vec2i<float> acos( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_acos_ps( vec.d );
  }
  inline mm::impl::vec3i<float> acos( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_acos_ps( vec.d );
  }
  inline mm::impl::vec4i<float> acos( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_acos_ps( vec.d );
  }

//atan
  inline mm::impl::vec2i<float> atan( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_atan_ps( vec.d );
  }
  inline mm::impl::vec3i<float> atan( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_atan_ps( vec.d );
  }
  inline mm::impl::vec4i<float> atan( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_atan_ps( vec.d );
  }

//abs
  inline mm::impl::vec2i<float> abs( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_abs_ps( vec.d );
  }
  inline mm::impl::vec3i<float> abs( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_abs_ps( vec.d );
  }
  inline mm::impl::vec4i<float> abs( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_abs_ps( vec.d );
  }

//pow
  inline mm::impl::vec2i<float> pow( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return exp2( log2( abs( a ) ) * b );
  }
  inline mm::impl::vec3i<float> pow( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return exp2( log2( abs( a ) ) * b );
  }
  inline mm::impl::vec4i<float> pow( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return exp2( log2( abs( a ) ) * b );
  }

//sinh
  inline mm::impl::vec2i<float> sinh( const mm::impl::vec2i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_sub_ps( etox.d, etominusx.d ), mm::impl::half );
  }
  inline mm::impl::vec3i<float> sinh( const mm::impl::vec3i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_sub_ps( etox.d, etominusx.d ), mm::impl::half );
  }
  inline mm::impl::vec4i<float> sinh( const mm::impl::vec4i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_sub_ps( etox.d, etominusx.d ), mm::impl::half );
  }

//cosh
  inline mm::impl::vec2i<float> cosh( const mm::impl::vec2i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_add_ps( etox.d, etominusx.d ), mm::impl::half );
  }
  inline mm::impl::vec3i<float> cosh( const mm::impl::vec3i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_add_ps( etox.d, etominusx.d ), mm::impl::half );
  }
  inline mm::impl::vec4i<float> cosh( const mm::impl::vec4i<float>& vec )
  {
    auto etox = pow( mm::impl::e, vec );
    auto etominusx = pow( mm::impl::e, -vec );
    return _mm_mul_ps( _mm_add_ps( etox.d, etominusx.d ), mm::impl::half );
  }

//tanh
  inline mm::impl::vec2i<float> tanh( const mm::impl::vec2i<float>& vec )
  {
    return sinh( vec ) / cosh( vec );
  }
  inline mm::impl::vec3i<float> tanh( const mm::impl::vec3i<float>& vec )
  {
    return sinh( vec ) / cosh( vec );
  }
  inline mm::impl::vec4i<float> tanh( const mm::impl::vec4i<float>& vec )
  {
    return sinh( vec ) / cosh( vec );
  }


//exp
  inline mm::impl::vec2i<float> exp( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_exp_ps( vec.d );
  }
  inline mm::impl::vec3i<float> exp( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_exp_ps( vec.d );
  }
  inline mm::impl::vec4i<float> exp( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_exp_ps( vec.d );
  }

//log
  inline mm::impl::vec2i<float> log( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_log_ps( vec.d );
  }
  inline mm::impl::vec3i<float> log( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_log_ps( vec.d );
  }
  inline mm::impl::vec4i<float> log( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_log_ps( vec.d );
  }

//ceil
  inline mm::impl::vec2i<float> ceil( const mm::impl::vec2i<float>& vec )
  {
    return mm::impl::sse_ceil_ps( vec.d );
  }
  inline mm::impl::vec3i<float> ceil( const mm::impl::vec3i<float>& vec )
  {
    return mm::impl::sse_ceil_ps( vec.d );
  }
  inline mm::impl::vec4i<float> ceil( const mm::impl::vec4i<float>& vec )
  {
    return mm::impl::sse_ceil_ps( vec.d );
  }

//min
  inline mm::impl::vec2i<float> min( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return _mm_min_ps( a.d, b.d );
  }
  inline mm::impl::vec3i<float> min( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return _mm_min_ps( a.d, b.d );
  }
  inline mm::impl::vec4i<float> min( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return _mm_min_ps( a.d, b.d );
  }

//max
  inline mm::impl::vec2i<float> max( const mm::impl::vec2i<float>& a, const mm::impl::vec2i<float>& b )
  {
    return _mm_max_ps( a.d, b.d );
  }
  inline mm::impl::vec3i<float> max( const mm::impl::vec3i<float>& a, const mm::impl::vec3i<float>& b )
  {
    return _mm_max_ps( a.d, b.d );
  }
  inline mm::impl::vec4i<float> max( const mm::impl::vec4i<float>& a, const mm::impl::vec4i<float>& b )
  {
    return _mm_max_ps( a.d, b.d );
  }

  namespace impl
  {
    template<int a, int b, int c, int d>
    const vec2i<float>& vec2i<float>::swizzle<a, b, c, d>::operator/=( const vec2i<float>& vec )
    {
      assert( notEqual( vec, vec2i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *( vec2i<float>* )this;
    }

    template<int a, int b, int c, int d>
    const vec3i<float>& vec3i<float>::swizzle<a, b, c, d>::operator/=( const vec3i<float>& vec )
    {
      assert( notEqual( vec, vec3i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *( vec3i<float>* )this;
    }

    template<int a, int b, int c, int d>
    const vec4i<float>& vec4i<float>::swizzle<a, b, c, d>::operator/=( const vec4i<float>& vec )
    {
      assert( notEqual( vec, vec4i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *( vec4i<float>* )this;
    }

    const vec2i<float>& vec2i<float>::operator/=( const vec2i<float>& vec )
    {
      assert( notEqual( vec, vec2i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *this;
    }

    const vec3i<float>& vec3i<float>::operator/=( const vec3i<float>& vec )
    {
      assert( notEqual( vec, vec3i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *this;
    }

    const vec4i<float>& vec4i<float>::operator/=( const vec4i<float>& vec )
    {
      assert( notEqual( vec, vec4i<float>( 0 ) ) );
      d = _mm_div_ps( d, vec.d );
      return *this;
    }
  }
}

#endif
