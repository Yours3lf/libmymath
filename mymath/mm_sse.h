#ifndef mm_sse_h
#define mm_sse_h

#include "mm_common.h"

namespace mymath
{
  namespace impl
  {
    //the following is heavily based on GLM's implementation
    //https://github.com/Groovounet/glm/tree/master
    //http://gruntthepeon.free.fr/ssemath/

    union ieee754_QNAN
    {
      const float f;
      struct i
      {
        const unsigned int mantissa: 23, exp: 8, sign: 1;
      };

      ieee754_QNAN() : f( 0.0 )/*, mantissa(0x7FFFFF), exp(0xFF), sign(0x0)*/ {}
    };

    static const __m128 abs_mask = _mm_set_ps1( ieee754_QNAN().f );
    static const __m128 one = _mm_set_ps1( 1.0f );
    static const __m128 minus_one = _mm_set_ps1( -1.0f );
    static const __m128 zero = _mm_set_ps1( 0.0f );
    static const __m128 two = _mm_set_ps1( 2.0f );
    static const __m128 three = _mm_set_ps1( 3.0f );
    static const __m128 epi32_sign_mask = _mm_castsi128_ps( _mm_set1_epi32( 0x80000000 ) );
    static const __m128 ps_2pow23 = _mm_set_ps1( 8388608.0f );
    static const __m128 sse_pi = _mm_set_ps1( pi );
    static const __m128 sse_two_pi = _mm_set_ps1( two_pi );
    static const __m128 sse_pi_div_180 = _mm_set_ps1( pi_div_180 );
    static const __m128 sse_inv_pi_div_180 = _mm_set_ps1( inv_pi_div_180 );

    inline __m128 sse_rad_ps( __m128 x )
    {
      return _mm_mul_ps( x, sse_pi_div_180 );
    }

    inline __m128 sse_deg_ps( __m128 x )
    {
      return _mm_mul_ps( x, sse_inv_pi_div_180 );
    }

    inline __m128 sse_abs_ps( __m128 x )
    {
      return _mm_and_ps( abs_mask, x );
    }

    inline __m128 sse_sgn_ps( __m128 x )
    {
      __m128 cmp0 = _mm_cmplt_ps( x, zero );
      __m128 cmp1 = _mm_cmpgt_ps( x, zero );

      __m128 and0 = _mm_and_ps( cmp0, minus_one );
      __m128 and1 = _mm_and_ps( cmp1, one );

      return _mm_or_ps( and0, and1 );
    }

    inline __m128 sse_rnd_ps( __m128 x )
    {
      __m128 and0 = _mm_and_ps( epi32_sign_mask, x );
      __m128 or0 = _mm_or_ps( and0, ps_2pow23 );
      __m128 add0 = _mm_add_ps( x, or0 );
      __m128 sub0 = _mm_sub_ps( add0, or0 );
      return sub0;
    }

    inline __m128 sse_flr_ps( __m128 x )
    {
      __m128 rnd0 = sse_rnd_ps( x );
      __m128 cmp0 = _mm_cmplt_ps( x, rnd0 );
      __m128 and0 = _mm_and_ps( cmp0, one );
      __m128 sub0 = _mm_sub_ps( rnd0, and0 );
      return sub0;
    }

    /*inline __m128 sse_trc_ps( __m128 x )
    {
      //TODO
    }*/

    inline __m128 sse_rde_ps( __m128 x )
    {
      __m128 and0 = _mm_and_ps( epi32_sign_mask, x );
      __m128 or0 = _mm_or_ps( and0, ps_2pow23 );
      __m128 add0 = _mm_add_ps( x, or0 );
      __m128 sub0 = _mm_sub_ps( add0, or0 );
      return sub0;
    }

    inline __m128 sse_ceil_ps( __m128 x )
    {
      __m128 rnd0 = sse_rnd_ps( x );
      __m128 cmp0 = _mm_cmpgt_ps( x, rnd0 );
      __m128 and0 = _mm_and_ps( cmp0, one );
      __m128 add0 = _mm_add_ps( rnd0, and0 );
      return add0;
    }

    inline __m128 sse_frc_ps( __m128 x )
    {
      __m128 flr0 = sse_flr_ps( x );
      __m128 sub0 = _mm_sub_ps( x, flr0 );
      return sub0;
    }

    inline __m128 sse_mod_ps( __m128 x, __m128 y )
    {
      __m128 div0 = _mm_div_ps( x, y );
      __m128 flr0 = sse_flr_ps( div0 );
      __m128 mul0 = _mm_mul_ps( y, flr0 );
      __m128 sub0 = _mm_sub_ps( x, mul0 );
      return sub0;
    }

    /*inline __m128 sse_modf_ps( __m128 x, __m128i& i )
    {
      //TODO
    }*/

    inline __m128 sse_clp_ps( __m128 v, __m128 minv, __m128 maxv )
    {
      __m128 min0 = _mm_min_ps( v, maxv );
      __m128 max0 = _mm_max_ps( min0, minv );
      return max0;
    }

    inline __m128 sse_mix_ps( __m128 v1, __m128 v2, __m128 a )
    {
      __m128 sub0 = _mm_sub_ps( one, a );
      __m128 mul0 = _mm_mul_ps( v1, sub0 );
      __m128 mul1 = _mm_mul_ps( v2, a );
      __m128 add0 = _mm_add_ps( mul0, mul1 );
      return add0;
    }

    inline __m128 sse_stp_ps( __m128 edge, __m128 x )
    {
      __m128 cmp = _mm_cmple_ps( x, edge );

      if( _mm_movemask_ps( cmp ) == 0 )
        return one;
      else
        return zero;
    }

    inline __m128 sse_ssp_ps( __m128 edge0, __m128 edge1, __m128 x )
    {
      __m128 sub0 = _mm_sub_ps( x, edge0 );
      __m128 sub1 = _mm_sub_ps( edge1, edge0 );
      __m128 div0 = _mm_sub_ps( sub0, sub1 );
      __m128 clp0 = sse_clp_ps( div0, zero, one );
      __m128 mul0 = _mm_mul_ps( two, clp0 );
      __m128 sub2 = _mm_sub_ps( three, mul0 );
      __m128 mul1 = _mm_mul_ps( clp0, clp0 );
      __m128 mul2 = _mm_mul_ps( mul1, sub2 );
      return mul2;
    }

    inline __m128 sse_neg_ps( __m128 x )
    {
      return _mm_xor_ps( x, epi32_sign_mask );
    }

    //TODO sse_nan_ps

    //TODO sse_inf_ps
  }
}

#endif
