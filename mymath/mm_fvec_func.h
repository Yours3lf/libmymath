#ifndef mm_vec_func_h
#define mm_vec_func_h

#include "mm_common.h"

namespace mymath
{
  inline bool equal( const impl::fvec2i<float>& a, const impl::fvec2i<float>& b )
  {
    impl::fvec2i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y;
  }
  inline bool equal( const impl::fvec3i<float>& a, const impl::fvec3i<float>& b )
  {
    impl::fvec3i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y && c.z;
  }
  inline bool equal( const impl::fvec4i<float>& a, const impl::fvec4i<float>& b )
  {
    impl::fvec4i<float> c = _mm_cmpeq_ps( a.d, b.d );
    return c.x && c.y && c.z && c.w;
  }

  inline bool notEqual( const impl::fvec2i<float>& a, const impl::fvec2i<float>& b )
  {
    return !equal( a, b );
  }
  inline bool notEqual( const impl::fvec3i<float>& a, const impl::fvec3i<float>& b )
  {
    return !equal( a, b );
  }
  inline bool notEqual( const impl::fvec4i<float>& a, const impl::fvec4i<float>& b )
  {
    return !equal( a, b );
  }
}

//mul
inline mm::impl::fvec2i<float> operator*( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator*( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator*( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_mul_ps( a.d, b.d );
}

//div
inline mm::impl::fvec2i<float> operator/( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

inline mm::impl::fvec3i<float> operator/( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) && !mm::impl::is_eq( b.z, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

inline mm::impl::fvec4i<float> operator/( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  assert( !mm::impl::is_eq( b.x, ( float )0 ) && !mm::impl::is_eq( b.y, ( float )0 ) && !mm::impl::is_eq( b.z, ( float )0 ) && !mm::impl::is_eq( b.w, ( float )0 ) );
  return _mm_div_ps( a.d, b.d );
}

//add
inline mm::impl::fvec2i<float> operator+( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator+( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator+( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_add_ps( a.d, b.d );
}

//sub
inline mm::impl::fvec2i<float> operator-( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator-( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator-( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_sub_ps( a.d, b.d );
}

//mod
inline mm::impl::fvec2i<float> operator%( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return sse_mod_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator%( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return sse_mod_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator%( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return sse_mod_ps( a.d, b.d );
}

//TODO shift left
//TODO shift right

//and
inline mm::impl::fvec2i<float> operator&( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator&( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator&( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_and_ps( a.d, b.d );
}

//xor
inline mm::impl::fvec2i<float> operator^( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator^( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator^( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_xor_ps( a.d, b.d );
}

//or
inline mm::impl::fvec2i<float> operator|( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator|( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator|( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return _mm_or_ps( a.d, b.d );
}

//negate
inline mm::impl::fvec2i<float> operator|( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  return sse_neg_ps( a.d, b.d );
}
inline mm::impl::fvec3i<float> operator|( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  return sse_neg_ps( a.d, b.d );
}
inline mm::impl::fvec4i<float> operator|( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  return sse_neg_ps( a.d, b.d );
}

//cout
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::fvec2i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << " )\n";
}
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::fvec3i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n";
}
inline std::ostream& operator<< ( std::ostream& output, const mm::impl::fvec4i<float>& vec )
{
  return output << "( " << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << " )\n";
}

//less
inline bool lessThan( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmplt_ps( a.d, b.d );
  return v.x && v.y;
}
inline bool lessThan( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmplt_ps( a.d, b.d );
  return v.x && v.y && v.z;
}
inline bool lessThan( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmplt_ps( a.d, b.d );
  return v.x && v.y && v.z && v.w;
}

//greater
inline bool lessThan( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpgt_ps( a.d, b.d );
  return v.x && v.y;
}
inline bool lessThan( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpgt_ps( a.d, b.d );
  return v.x && v.y && v.z;
}
inline bool lessThan( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpgt_ps( a.d, b.d );
  return v.x && v.y && v.z && v.w;
}

//less or equal
inline bool lessThan( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmple_ps( a.d, b.d );
  return v.x && v.y;
}
inline bool lessThan( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmple_ps( a.d, b.d );
  return v.x && v.y && v.z;
}
inline bool lessThan( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmple_ps( a.d, b.d );
  return v.x && v.y && v.z && v.w;
}

//greater or equal
inline bool lessThan( const mm::impl::fvec2i<float>& a, const mm::impl::fvec2i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpge_ps( a.d, b.d );
  return v.x && v.y;
}
inline bool lessThan( const mm::impl::fvec3i<float>& a, const mm::impl::fvec3i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpge_ps( a.d, b.d );
  return v.x && v.y && v.z;
}
inline bool lessThan( const mm::impl::fvec4i<float>& a, const mm::impl::fvec4i<float>& b )
{
  mm::impl::fvec2i<float> v = _mm_cmpge_ps( a.d, b.d );
  return v.x && v.y && v.z && v.w;
}

//radians
inline mm::impl::fvec2i<float> radians( const mm::impl::fvec2i<float>& vec )
{
  return sse_rad_ps( vec.d );
}
inline mm::impl::fvec3i<float> radians( const mm::impl::fvec3i<float>& vec )
{
  return sse_rad_ps( vec.d );
}
inline mm::impl::fvec4i<float> radians( const mm::impl::fvec4i<float>& vec )
{
  return sse_rad_ps( vec.d );
}

//degrees
inline mm::impl::fvec2i<float> degrees( const mm::impl::fvec2i<float>& vec )
{
  return sse_deg_ps( vec.d );
}
inline mm::impl::fvec3i<float> degrees( const mm::impl::fvec3i<float>& vec )
{
  return sse_deg_ps( vec.d );
}
inline mm::impl::fvec4i<float> degrees( const mm::impl::fvec4i<float>& vec )
{
  return sse_deg_ps( vec.d );
}

//TODO to be cont'd

#endif
