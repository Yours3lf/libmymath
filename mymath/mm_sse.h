#ifndef mm_sse_h
#define mm_sse_h

#include "mm_common.h"

namespace mymath
{
  namespace impl
  {
    //the following is heavily based on GLM's implementation
    //mit licence
    //https://github.com/Groovounet/glm/tree/master

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
    static const __m128 e = _mm_set_ps1( 2.7182818284590452353602874713526624977572470936999595f );
    static const __m128 ee = _mm_mul_ps( e, e );
    static const __m128 half = _mm_set_ps1( 0.5f );
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
    static const __m128i min_norm_pos = _mm_set1_epi32( 0x00800000 );
    static const __m128i mant_mask = _mm_set1_epi32( 0x7f800000 );
    static const __m128i inv_mant_mask = _mm_set1_epi32( ~0x7f800000 );
    static const __m128 sign_mask = _mm_castsi128_ps( _mm_set1_epi32( ( int )0x80000000 ) );
    static const __m128 inv_sign_mask = _mm_castsi128_ps( _mm_set1_epi32( ~0x80000000 ) );
    static const __m128i one_i32 = _mm_set1_epi32( 1 );
    static const __m128i inv_one_i32 = _mm_set1_epi32( ~1 );
    static const __m128i two_i32 = _mm_set1_epi32( 2 );
    static const __m128i four_i32 = _mm_set1_epi32( 4 );
    static const __m128i sevenf = _mm_set1_epi32( 0x7f );
    static const __m128 sqrthf = _mm_set_ps1( 0.707106781186547524f );
    static const __m128 log_p0 = _mm_set_ps1( 7.0376836292E-2f );
    static const __m128 log_p1 = _mm_set_ps1( - 1.1514610310E-1f );
    static const __m128 log_p2 = _mm_set_ps1( 1.1676998740E-1f );
    static const __m128 log_p3 = _mm_set_ps1( - 1.2420140846E-1f );
    static const __m128 log_p4 = _mm_set_ps1( + 1.4249322787E-1f );
    static const __m128 log_p5 = _mm_set_ps1( - 1.6668057665E-1f );
    static const __m128 log_p6 = _mm_set_ps1( + 2.0000714765E-1f );
    static const __m128 log_p7 = _mm_set_ps1( - 2.4999993993E-1f );
    static const __m128 log_p8 = _mm_set_ps1( + 3.3333331174E-1f );
    static const __m128 log_q1 = _mm_set_ps1( -2.12194440e-4f );
    static const __m128 log_q2 = _mm_set_ps1( 0.693359375f );
    static const __m128 exp_hi = _mm_set_ps1( 88.3762626647949f );
    static const __m128 exp_lo = _mm_set_ps1( -88.3762626647949f );
    static const __m128 log2ef = _mm_set_ps1( 1.44269504088896341f );
    static const __m128 expc1 = _mm_set_ps1( 0.693359375f );
    static const __m128 expc2 = _mm_set_ps1( -2.12194440e-4f );
    static const __m128 exp_p0 = _mm_set_ps1( 1.9875691500E-4f );
    static const __m128 exp_p1 = _mm_set_ps1( 1.3981999507E-3f );
    static const __m128 exp_p2 = _mm_set_ps1( 8.3334519073E-3f );
    static const __m128 exp_p3 = _mm_set_ps1( 4.1665795894E-2f );
    static const __m128 exp_p4 = _mm_set_ps1( 1.6666665459E-1f );
    static const __m128 exp_p5 = _mm_set_ps1( 5.0000001201E-1f );
    static const __m128 dp1 = _mm_set_ps1( -0.78515625f );
    static const __m128 dp2 = _mm_set_ps1( -2.4187564849853515625e-4f );
    static const __m128 dp3 = _mm_set_ps1( -3.77489497744594108e-8f );
    static const __m128 sincof_p0 = _mm_set_ps1( -1.9515295891E-4f );
    static const __m128 sincof_p1 = _mm_set_ps1( 8.3321608736E-3f );
    static const __m128 sincof_p2 = _mm_set_ps1( -1.6666654611E-1f );
    static const __m128 coscof_p0 = _mm_set_ps1( 2.443315711809948E-005f );
    static const __m128 coscof_p1 = _mm_set_ps1( -1.388731625493765E-003f );
    static const __m128 coscof_p2 = _mm_set_ps1( 4.166664568298827E-002f );
    static const __m128 four_per_pi = _mm_set_ps1( 1.27323954473516f );
    static const __m128 asinf_p0 = _mm_set_ps1( 4.2163199048E-2f );
    static const __m128 asinf_p1 = _mm_set_ps1( 2.4181311049E-2f );
    static const __m128 asinf_p2 = _mm_set_ps1( 4.5470025998E-2f );
    static const __m128 asinf_p3 = _mm_set_ps1( 7.4953002686E-2f );
    static const __m128 asinf_p4 = _mm_set_ps1( 1.6666752422E-1f );
    static const __m128 asinf_p5 = _mm_set_ps1( 1.0E-4f );
    static const __m128 two_per_pi = _mm_set_ps1( 0.63661977236758134308f );
    static const __m128 atanf_p0 = _mm_set_ps1( 8.05374449538e-2f );
    static const __m128 atanf_p1 = _mm_set_ps1( -1.38776856032e-1f );
    static const __m128 atanf_p2 = _mm_set_ps1( 1.99777106478e-1f );
    static const __m128 atanf_p3 = _mm_set_ps1( -3.33329491539e-1f );
    static const __m128 t3pi08 = _mm_set_ps1( 2.414213562373095f );
    static const __m128 tpi08 = _mm_set_ps1( 0.4142135623730950f );


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

    //clamp
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

    //the following is heavily based on the "sse_mathfun" library
    //zlib licence
    //http://gruntthepeon.free.fr/ssemath/

    inline __m128 sse_log_ps( __m128 x )
    {
      __m128i emm0;

      __m128 invalid_mask = _mm_cmple_ps( x, _mm_setzero_ps() );

      x = _mm_max_ps( x, _mm_castsi128_ps(min_norm_pos) ); /* cut off denormalized stuff */

      emm0 = _mm_srli_epi32( _mm_castps_si128( x ), 23 );
      /* keep only the fractional part */
      x = _mm_and_ps( x, _mm_castsi128_ps(inv_mant_mask) );
      x = _mm_or_ps( x, half );

      emm0 = _mm_sub_epi32( emm0, sevenf );
      __m128 e = _mm_cvtepi32_ps( emm0 );

      e = _mm_add_ps( e, one );

      /* part2:
        if( x < SQRTHF ) {
          e -= 1;
          x = x + x - 1.0;
        } else { x = x - 1.0; }
      */
      __m128 mask = _mm_cmplt_ps( x, sqrthf );
      __m128 tmp = _mm_and_ps( x, mask );
      x = _mm_sub_ps( x, one );
      e = _mm_sub_ps( e, _mm_and_ps( one, mask ) );
      x = _mm_add_ps( x, tmp );


      __m128 z = _mm_mul_ps( x, x );

      __m128 y = log_p0;
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p1 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p2 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p3 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p4 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p5 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p6 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p7 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, log_p8 );
      y = _mm_mul_ps( y, x );

      y = _mm_mul_ps( y, z );


      tmp = _mm_mul_ps( e, log_q1 );
      y = _mm_add_ps( y, tmp );


      tmp = _mm_mul_ps( z, half );
      y = _mm_sub_ps( y, tmp );

      tmp = _mm_mul_ps( e, log_q2 );
      x = _mm_add_ps( x, y );
      x = _mm_add_ps( x, tmp );
      x = _mm_or_ps( x, invalid_mask ); // negative arg will be NAN
      return x;
    }

    inline __m128 sse_exp_ps( __m128 x )
    {
      __m128 tmp = _mm_setzero_ps(), fx;
      __m128i emm0;

      x = _mm_min_ps( x, exp_hi );
      x = _mm_max_ps( x, exp_lo );

      /* express exp(x) as exp(g + n*log(2)) */
      fx = _mm_mul_ps( x, log2ef );
      fx = _mm_add_ps( fx, half );

      /* how to perform a floorf with SSE: just below */
      emm0 = _mm_cvttps_epi32( fx );
      tmp  = _mm_cvtepi32_ps( emm0 );
      /* if greater, substract 1 */
      __m128 mask = _mm_cmpgt_ps( tmp, fx );
      mask = _mm_and_ps( mask, one );
      fx = _mm_sub_ps( tmp, mask );

      tmp = _mm_mul_ps( fx, expc1 );
      __m128 z = _mm_mul_ps( fx, expc2 );
      x = _mm_sub_ps( x, tmp );
      x = _mm_sub_ps( x, z );

      z = _mm_mul_ps( x, x );

      __m128 y = exp_p0;
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, exp_p1 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, exp_p2 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, exp_p3 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, exp_p4 );
      y = _mm_mul_ps( y, x );
      y = _mm_add_ps( y, exp_p5 );
      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, x );
      y = _mm_add_ps( y, one );

      /* build 2^n */
      emm0 = _mm_cvttps_epi32( fx );
      emm0 = _mm_add_epi32( emm0, sevenf );
      emm0 = _mm_slli_epi32( emm0, 23 );
      __m128 pow2n = _mm_castsi128_ps( emm0 );
      y = _mm_mul_ps( y, pow2n );
      return y;
    }

    __m128 sse_sin_ps( __m128 x ) // any x
    {
      __m128 xmm1, xmm2 = _mm_setzero_ps(), xmm3, sign_bit, y;

      __m128i emm0, emm2;
      sign_bit = x;
      /* take the absolute value */
      x = _mm_and_ps( x, ( __m128 )inv_sign_mask );
      /* extract the sign bit (upper one) */
      sign_bit = _mm_and_ps( sign_bit, ( __m128 )sign_mask );

      /* scale by 4/Pi */
      y = _mm_mul_ps( x, four_per_pi );

      /* store the integer part of y in mm0 */
      emm2 = _mm_cvttps_epi32( y );
      /* j=(j+1) & (~1) (see the cephes sources) */
      emm2 = _mm_add_epi32( emm2, one_i32 );
      emm2 = _mm_and_si128( emm2, inv_one_i32 );
      y = _mm_cvtepi32_ps( emm2 );

      /* get the swap sign flag */
      emm0 = _mm_and_si128( emm2, four_i32 );
      emm0 = _mm_slli_epi32( emm0, 29 );
      /* get the polynom selection mask
         there is one polynom for 0 <= x <= Pi/4
         and another one for Pi/4<x<=Pi/2

         Both branches will be computed.
      */
      emm2 = _mm_and_si128( emm2, two_i32 );
      emm2 = _mm_cmpeq_epi32( emm2, _mm_setzero_si128() );

      __m128 swap_sign_bit = _mm_castsi128_ps( emm0 );
      __m128 poly_mask = _mm_castsi128_ps( emm2 );
      sign_bit = _mm_xor_ps( sign_bit, swap_sign_bit );

      /* The magic pass: "Extended precision modular arithmetic"
         x = ((x - y * DP1) - y * DP2) - y * DP3; */
      xmm1 = dp1;
      xmm2 = dp2;
      xmm3 = dp3;
      xmm1 = _mm_mul_ps( y, xmm1 );
      xmm2 = _mm_mul_ps( y, xmm2 );
      xmm3 = _mm_mul_ps( y, xmm3 );
      x = _mm_add_ps( x, xmm1 );
      x = _mm_add_ps( x, xmm2 );
      x = _mm_add_ps( x, xmm3 );

      /* Evaluate the first polynom  (0 <= x <= Pi/4) */
      y = coscof_p0;
      __m128 z = _mm_mul_ps( x, x );

      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p1 );
      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p2 );
      y = _mm_mul_ps( y, z );
      y = _mm_mul_ps( y, z );
      __m128 tmp = _mm_mul_ps( z, half );
      y = _mm_sub_ps( y, tmp );
      y = _mm_add_ps( y, one );

      /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

      __m128 y2 = sincof_p0;
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p1 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p2 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_mul_ps( y2, x );
      y2 = _mm_add_ps( y2, x );

      /* select the correct result from the two polynoms */
      xmm3 = poly_mask;
      y2 = _mm_and_ps( xmm3, y2 ); //, xmm3);
      y = _mm_andnot_ps( xmm3, y );
      y = _mm_add_ps( y, y2 );
      /* update the sign */
      y = _mm_xor_ps( y, sign_bit );
      return y;
    }

    /* almost the same as sin_ps */
    __m128 sse_cos_ps( __m128 x ) // any x
    {
      __m128 xmm1, xmm2 = _mm_setzero_ps(), xmm3, y;
      __m128i emm0, emm2;
      /* take the absolute value */
      x = _mm_and_ps( x, ( __m128 )inv_sign_mask );

      /* scale by 4/Pi */
      y = _mm_mul_ps( x, four_per_pi );

      /* store the integer part of y in mm0 */
      emm2 = _mm_cvttps_epi32( y );
      /* j=(j+1) & (~1) (see the cephes sources) */
      emm2 = _mm_add_epi32( emm2, one_i32 );
      emm2 = _mm_and_si128( emm2, inv_one_i32 );
      y = _mm_cvtepi32_ps( emm2 );

      emm2 = _mm_sub_epi32( emm2, two_i32 );

      /* get the swap sign flag */
      emm0 = _mm_andnot_si128( emm2, four_i32 );
      emm0 = _mm_slli_epi32( emm0, 29 );
      /* get the polynom selection mask */
      emm2 = _mm_and_si128( emm2, two_i32 );
      emm2 = _mm_cmpeq_epi32( emm2, _mm_setzero_si128() );

      __m128 sign_bit = _mm_castsi128_ps( emm0 );
      __m128 poly_mask = _mm_castsi128_ps( emm2 );

      /* The magic pass: "Extended precision modular arithmetic"
         x = ((x - y * DP1) - y * DP2) - y * DP3; */
      xmm1 = dp1;
      xmm2 = dp2;
      xmm3 = dp3;
      xmm1 = _mm_mul_ps( y, xmm1 );
      xmm2 = _mm_mul_ps( y, xmm2 );
      xmm3 = _mm_mul_ps( y, xmm3 );
      x = _mm_add_ps( x, xmm1 );
      x = _mm_add_ps( x, xmm2 );
      x = _mm_add_ps( x, xmm3 );

      /* Evaluate the first polynom  (0 <= x <= Pi/4) */
      y = coscof_p0;
      __m128 z = _mm_mul_ps( x, x );

      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p1 );
      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p2 );
      y = _mm_mul_ps( y, z );
      y = _mm_mul_ps( y, z );
      __m128 tmp = _mm_mul_ps( z, half );
      y = _mm_sub_ps( y, tmp );
      y = _mm_add_ps( y, one );

      /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

      __m128 y2 = sincof_p0;
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p1 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p2 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_mul_ps( y2, x );
      y2 = _mm_add_ps( y2, x );

      /* select the correct result from the two polynoms */
      xmm3 = poly_mask;
      y2 = _mm_and_ps( xmm3, y2 ); //, xmm3);
      y = _mm_andnot_ps( xmm3, y );
      y = _mm_add_ps( y, y2 );
      /* update the sign */
      y = _mm_xor_ps( y, sign_bit );

      return y;
    }

    /* since sin_ps and cos_ps are almost identical, sincos_ps could replace both of them..
       it is almost as fast, and gives you a free cosine with your sine */
    void sse_sincos_ps( __m128 x, __m128* s, __m128* c )
    {
      __m128 xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
      __m128i emm0, emm2, emm4;
      sign_bit_sin = x;
      /* take the absolute value */
      x = _mm_and_ps( x, ( __m128 )inv_sign_mask );
      /* extract the sign bit (upper one) */
      sign_bit_sin = _mm_and_ps( sign_bit_sin, ( __m128 )sign_mask );

      /* scale by 4/Pi */
      y = _mm_mul_ps( x, four_per_pi );

      /* store the integer part of y in emm2 */
      emm2 = _mm_cvttps_epi32( y );

      /* j=(j+1) & (~1) (see the cephes sources) */
      emm2 = _mm_add_epi32( emm2, one_i32 );
      emm2 = _mm_and_si128( emm2, inv_one_i32 );
      y = _mm_cvtepi32_ps( emm2 );

      emm4 = emm2;

      /* get the swap sign flag for the sine */
      emm0 = _mm_and_si128( emm2, four_i32 );
      emm0 = _mm_slli_epi32( emm0, 29 );
      __m128 swap_sign_bit_sin = _mm_castsi128_ps( emm0 );

      /* get the polynom selection mask for the sine*/
      emm2 = _mm_and_si128( emm2, two_i32 );
      emm2 = _mm_cmpeq_epi32( emm2, _mm_setzero_si128() );
      __m128 poly_mask = _mm_castsi128_ps( emm2 );

      /* The magic pass: "Extended precision modular arithmetic"
         x = ((x - y * DP1) - y * DP2) - y * DP3; */
      xmm1 = dp1;
      xmm2 = dp2;
      xmm3 = dp3;
      xmm1 = _mm_mul_ps( y, xmm1 );
      xmm2 = _mm_mul_ps( y, xmm2 );
      xmm3 = _mm_mul_ps( y, xmm3 );
      x = _mm_add_ps( x, xmm1 );
      x = _mm_add_ps( x, xmm2 );
      x = _mm_add_ps( x, xmm3 );

      emm4 = _mm_sub_epi32( emm4, two_i32 );
      emm4 = _mm_andnot_si128( emm4, four_i32 );
      emm4 = _mm_slli_epi32( emm4, 29 );
      __m128 sign_bit_cos = _mm_castsi128_ps( emm4 );

      sign_bit_sin = _mm_xor_ps( sign_bit_sin, swap_sign_bit_sin );


      /* Evaluate the first polynom  (0 <= x <= Pi/4) */
      __m128 z = _mm_mul_ps( x, x );
      y = coscof_p0;

      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p1 );
      y = _mm_mul_ps( y, z );
      y = _mm_add_ps( y, coscof_p2 );
      y = _mm_mul_ps( y, z );
      y = _mm_mul_ps( y, z );
      __m128 tmp = _mm_mul_ps( z, half );
      y = _mm_sub_ps( y, tmp );
      y = _mm_add_ps( y, one );

      /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

      __m128 y2 = sincof_p0;
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p1 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_add_ps( y2, sincof_p2 );
      y2 = _mm_mul_ps( y2, z );
      y2 = _mm_mul_ps( y2, x );
      y2 = _mm_add_ps( y2, x );

      /* select the correct result from the two polynoms */
      xmm3 = poly_mask;
      __m128 ysin2 = _mm_and_ps( xmm3, y2 );
      __m128 ysin1 = _mm_andnot_ps( xmm3, y );
      y2 = _mm_sub_ps( y2, ysin2 );
      y = _mm_sub_ps( y, ysin1 );

      xmm1 = _mm_add_ps( ysin1, ysin2 );
      xmm2 = _mm_add_ps( y, y2 );

      /* update the sign */
      *s = _mm_xor_ps( xmm1, sign_bit_sin );
      *c = _mm_xor_ps( xmm2, sign_bit_cos );
    }

    //the rest is my implementation

    inline __m128 sse_asinh_ps( __m128 x )
    {
      //log (x+sqrt(1+x2))
      __m128 sqr = _mm_mul_ps( x, x );
      sqr = _mm_add_ps( sqr, one );
      sqr = _mm_sqrt_ps( sqr );
      sqr = _mm_add_ps( sqr, x );
      return sse_log_ps( sqr );
    }

    inline __m128 sse_acosh_ps( __m128 x )
    {
      //2 log (sqrt((x+1)/2) + sqrt((x-1)/2))
      __m128 plusone = _mm_add_ps( x, one );
      __m128 minusone = _mm_sub_ps( x, one );
      plusone = _mm_mul_ps( plusone, half );
      minusone = _mm_mul_ps( minusone, half );
      plusone = _mm_sqrt_ps( plusone );
      minusone = _mm_sqrt_ps( minusone );
      __m128 sum = _mm_add_ps( plusone, minusone );
      __m128 thelog = sse_log_ps( sum );
      return _mm_mul_ps( thelog, two );
    }

    inline __m128 sse_atanh_ps( __m128 x )
    {
      //(log (1+x) - log (1-x))/2
      __m128 plusone = _mm_add_ps( x, one );
      __m128 minusone = _mm_sub_ps( x, one );
      plusone = sse_log_ps( plusone );
      minusone = sse_log_ps( minusone );
      minusone = _mm_mul_ps( minusone, half );
      return _mm_sub_ps( plusone, minusone );
    }

    inline __m128 sse_exp2_ps( __m128 x )
    {
      //e*e*x
      return _mm_mul_ps( ee, x );
    }

    inline __m128 sse_log2_ps( __m128 x )
    {
      static const __m128 logtwo = sse_log_ps( two );
      return _mm_div_ps( sse_log_ps( x ), logtwo );
    }

    inline __m128 sse_inversesqrt_ps( __m128 x )
    {
      return _mm_rsqrt_ps( x );
    }

    inline __m128 sse_sign_ps( __m128 x )
    {
      //return (T(0) < val) - (val < T(0));
      __m128 left = _mm_cmplt_ps( zero, x );
      __m128 right = _mm_cmplt_ps( x, zero );
      return _mm_sub_ps( left, right );
    }

    inline __m128 sse_sqrt_ps( __m128 x )
    {
      return _mm_sqrt_ps( x );
    }

    inline __m128 sse_fma_ps( __m128 a, __m128 b, __m128 c )
    {
      //fma instruction could be used here, but only recent processors support it
      //so hopefully the compiler will notice this
      return _mm_add_ps( _mm_mul_ps( a, b ), c );
    }

    inline __m128 sse_acos_ps( __m128 x )
    {
      __m128 neg = _mm_cmplt_ps( x, zero );
      x = sse_abs_ps( x );
      static __m128 acos_p0 = _mm_set1_ps( -0.0187293f );
      static __m128 acos_p1 = _mm_set1_ps( 0.0742610f );
      static __m128 acos_p2 = _mm_set1_ps( 0.2121144f );
      static __m128 acos_p3 = _mm_set1_ps( 1.5707288f );

      __m128 ret = acos_p0;
      ret = _mm_mul_ps( ret, x );
      ret = _mm_add_ps( ret, acos_p1 );
      ret = _mm_mul_ps( ret, x );
      ret = _mm_sub_ps( ret, acos_p2 );
      ret = _mm_mul_ps( ret, x );
      ret = _mm_add_ps( ret, acos_p3 );
      __m128 ox = _mm_sqrt_ps( _mm_sub_ps( one, x ) );
      ret = _mm_mul_ps( ret, ox );
      __m128 twonegret = _mm_mul_ps( two, neg );
      twonegret = _mm_mul_ps( twonegret, ret );
      ret = _mm_sub_ps( ret, twonegret );
      __m128 negpi = _mm_mul_ps( neg, sse_pi );
      return _mm_add_ps( negpi, ret );
    }

    //the following is taken from:
    //https://github.com/LiraNuna/glsl-sse2/blob/master/source/vec4.h

#define _mm_shufd(xmm, mask) _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(xmm), mask))

    inline __m128 sse_trunc_ps( __m128 x )
    {
      //return (d>0) ? floor(d) : ceil(d)
      __m128 m = _mm_cmpunord_ps( x, _mm_cmpge_ps( _mm_andnot_ps( _mm_set1_ps( -0.0f ), x ),
                                  _mm_set1_ps( 8388608.0f ) ) );
      return _mm_or_ps( _mm_andnot_ps( m, _mm_cvtepi32_ps( _mm_cvttps_epi32( x ) ) ), _mm_and_ps( m, x ) );
    }

    inline __m128 sse_round_ps( __m128 x )
    {
      __m128 m = _mm_cmpunord_ps( x,
                                  _mm_cmpge_ps( _mm_andnot_ps( _mm_set1_ps( -0.0f ), x ),
                                      _mm_set1_ps( 8388608.0f ) ) );
      return _mm_or_ps( _mm_andnot_ps( m, _mm_cvtepi32_ps(
                                         _mm_cvtps_epi32( x ) ) ), _mm_and_ps( m, x ) );
    }

    inline __m128 sse_floor_ps( __m128 x )
    {
      __m128 m = _mm_cmpunord_ps( x,
                                  _mm_cmpge_ps( _mm_andnot_ps( _mm_set1_ps( -0.0f ), x ),
                                      _mm_set1_ps( 8388608.0f ) ) );
      return _mm_or_ps( _mm_andnot_ps( m, _mm_cvtepi32_ps( _mm_cvtps_epi32(
                                         _mm_sub_ps( x, _mm_set1_ps( 0.5f ) ) ) ) ),
                        _mm_and_ps( m, x ) );
    }

    inline __m128 sse_fract_ps( __m128 x )
    {
      return _mm_sub_ps( x, sse_floor_ps( x ) );
    }

    inline __m128 sse_step_ps( __m128 a, __m128 b )
    {
      return _mm_and_ps( _mm_cmple_ps( a, b ), _mm_set1_ps( 1.0f ) );
    }

    inline __m128 sse_smoothstep_ps( __m128 a, __m128 b, __m128 c )
    {
      __m128 cc = _mm_max_ps( _mm_min_ps( _mm_div_ps( _mm_sub_ps( c, a ),
                                          _mm_sub_ps( b, a ) ), _mm_set1_ps( 1.f ) ),
                              _mm_setzero_ps() );
      return _mm_mul_ps( _mm_mul_ps( cc, cc ),
                         _mm_sub_ps( _mm_set1_ps( 3.0f ), _mm_add_ps( cc, cc ) ) );
    }

    inline float sse_dot_ps( __m128 a, __m128 b )
    {
      __m128 l = _mm_mul_ps( a, b );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      return _mm_cvtss_f32( _mm_add_ss( l, _mm_shufd( l, 0x11 ) ) );
    }

    inline float sse_length_ps( __m128 x )
    {
      __m128 l = _mm_mul_ps( x, x );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      return _mm_cvtss_f32( _mm_sqrt_ss( _mm_add_ss( l,
                                         _mm_shufd( l, 0x11 ) ) ) );
    }

    inline float sse_distance_ps( __m128 a, __m128 b )
    {
      __m128 l = _mm_sub_ps( a, b );
      l = _mm_mul_ps( l, l );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      return _mm_cvtss_f32( _mm_sqrt_ss( _mm_add_ss( l,
                                         _mm_shufd( l, 0x11 ) ) ) );
    }

    inline __m128 sse_normalize_ps( __m128 x )
    {
      __m128 l = _mm_mul_ps( x, x );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      return _mm_div_ps( x, _mm_sqrt_ps( _mm_add_ps( l,
                                         _mm_shufd( l, 0x11 ) ) ) );
    }

    inline __m128 sse_reflect_ps( __m128 a, __m128 b )
    {
      __m128 l = _mm_mul_ps( b, a );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      l = _mm_add_ps( l, _mm_shufd( l, 0x11 ) );
      return _mm_sub_ps( a, _mm_mul_ps( _mm_add_ps( l, l ), b ) );
    }

    inline __m128 sse_refract_ps( __m128 a, __m128 b, __m128 c )
    {
      __m128 o = _mm_set1_ps( 1.0f );
      __m128 e = c;
      __m128 d = _mm_mul_ps( b, a );
      d = _mm_add_ps( d, _mm_shufd( d, 0x4E ) );
      d = _mm_add_ps( d, _mm_shufd( d, 0x11 ) );
      __m128 k = _mm_sub_ps( o, _mm_mul_ps( _mm_mul_ps( e, e ),
                                            _mm_sub_ps( o, _mm_mul_ps( d, d ) ) ) );
      return _mm_and_ps( _mm_cmpnlt_ps( k, _mm_setzero_ps() ),
                         _mm_mul_ps( _mm_mul_ps( e, _mm_sub_ps( a,
                                     _mm_mul_ps( _mm_mul_ps( e, d ), _mm_sqrt_ps( k ) ) ) ),
                                     b ) );
    }

    inline __m128 sse_faceforward_ps( __m128 a, __m128 b, __m128 c )
    {
      __m128 l = _mm_mul_ps( c, b );
      l = _mm_add_ps( l, _mm_shufd( l, 0x4E ) );
      return _mm_xor_ps( _mm_and_ps( _mm_cmpnlt_ps(
                                       _mm_add_ps( l, _mm_shufd( l, 0x11 ) ),
                                       _mm_setzero_ps() ), _mm_set1_ps( -0.f ) ), a );
    }

    inline __m128 sse_cross_ps( __m128 a, __m128 b )
    {
      //return vec3( a.y * b.z - b.y * a.z, -( a.x * b.z ) + b.x * a.z, a.x * b.y - b.x * a.y );
      return _mm_sub_ps(
               _mm_mul_ps( _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 0, 2, 1 ) ), _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 1, 0, 2 ) ) ),
               _mm_mul_ps( _mm_shuffle_ps( a, a, _MM_SHUFFLE( 3, 1, 0, 2 ) ), _mm_shuffle_ps( b, b, _MM_SHUFFLE( 3, 0, 2, 1 ) ) )
             );
    }

    //the following is taken from here:
    //zlib licence
    //https://github.com/raedwulf/gmath/blob/master

    inline __m128 sse_asin_ps( __m128 x )
    {
      __m128 xmm0, xmm1, xmm2;
      __m128 flag;
      __m128 z, z0;
      __m128 sign_bit;

      sign_bit = x;
      /* take the absolute value */
      x = _mm_and_ps( x, inv_sign_mask );
      /* extract the sign bit (upper one) */
      sign_bit = _mm_and_ps( sign_bit, sign_mask );

      flag = _mm_cmpgt_ps( x, half );
      xmm0 = _mm_mul_ps( half, _mm_sub_ps( one, x ) );
      //xmm2 = _mm_rcp_ps(_mm_rsqrt_ps(xmm0));
      //xmm2 = _mm_sqrt_ps(xmm0);
      xmm2 = sse_sqrt_ps( xmm0 );
      x = _mm_or_ps( _mm_and_ps( flag, xmm2 ), _mm_andnot_ps( flag, x ) );
      z0 = _mm_or_ps( _mm_and_ps( flag, xmm0 ), _mm_andnot_ps( flag, _mm_mul_ps( x, x ) ) );

      z = _mm_mul_ps( z0, asinf_p0 );
      z = _mm_add_ps( z, asinf_p1 );
      z = _mm_mul_ps( z, z0 );
      z = _mm_add_ps( z, asinf_p2 );
      z = _mm_mul_ps( z, z0 );
      z = _mm_add_ps( z, asinf_p3 );
      z = _mm_mul_ps( z, z0 );
      z = _mm_add_ps( z, asinf_p4 );
      z = _mm_mul_ps( z, z0 );
      z = _mm_mul_ps( z, x );
      z = _mm_add_ps( z, x );

      xmm1 = _mm_sub_ps( two_per_pi, _mm_add_ps( z, z ) );
      z = _mm_or_ps( _mm_and_ps( flag, xmm1 ), _mm_andnot_ps( flag, z ) );

      return _mm_or_ps( sign_bit, z );
    }

    inline __m128 rcp_ps( __m128 x )
    {
      __m128 r = _mm_rcp_ps( x );
      r = _mm_sub_ps( _mm_add_ps( r, r ), _mm_mul_ps( _mm_mul_ps( r, x ), r ) );
      return r;
    }

    inline __m128 sse_atan_ps( __m128 x )
    {
      __m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5;
      __m128 y, z;
      __m128 sign_bit;

      sign_bit = x;
      /* take the absolute value */
      x = _mm_and_ps( x, inv_sign_mask );
      /* extract the sign bit (upper one) */
      sign_bit = _mm_and_ps( sign_bit, sign_mask );

      /* range reduction */
      xmm0 = _mm_cmpgt_ps( x, t3pi08 );
      xmm4 = _mm_cmpgt_ps( x, tpi08 );
      xmm1 = _mm_andnot_ps( xmm0, xmm4 );
      y = _mm_and_ps( xmm0, two_per_pi );
      y = _mm_or_ps( y, _mm_and_ps( xmm1, four_per_pi ) );
      xmm5 = _mm_and_ps( xmm0, _mm_xor_ps( sign_mask, rcp_ps( x ) ) );
      xmm2 = _mm_sub_ps( x, one );
      xmm3 = _mm_add_ps( x, one );
      xmm5 = _mm_or_ps( xmm5, _mm_and_ps( xmm1, _mm_mul_ps( xmm2, rcp_ps( xmm3 ) ) ) );
      x = _mm_or_ps( _mm_andnot_ps( xmm4, x ), xmm5 );
      z = _mm_mul_ps( x, x );

      xmm0 = _mm_mul_ps( atanf_p0, z );
      xmm1 = _mm_add_ps( atanf_p1, xmm0 );
      xmm0 = _mm_mul_ps( xmm1, z );
      xmm1 = _mm_add_ps( atanf_p2, xmm0 );
      xmm0 = _mm_mul_ps( xmm1, z );
      xmm1 = _mm_add_ps( atanf_p3, xmm0 );
      xmm0 = _mm_mul_ps( xmm1, z );
      xmm0 = _mm_mul_ps( xmm0, x );
      xmm0 = _mm_add_ps( xmm0, x );
      y = _mm_add_ps( y, xmm0 );

      return _mm_xor_ps( sign_bit, y );
    }
  }
}

#endif