#ifndef mm_mat4_impl_h
#define mm_mat4_impl_h

#include "mm_vec4_impl.h"
#include "mm_vec_func.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class MM_GPU_ALIGNED mat4i
    {
      private:
        /*
         * matrix layout:
         * m[0].x m[1].x m[2].x m[3].x
         * m[0].y m[1].y m[2].y m[3].y
         * m[0].z m[1].z m[2].z m[3].z
         * m[0].w m[1].w m[2].w m[3].w
         */
        vec4i<t> m[4];

      protected:

      public:
        // 1 column vector per row
        mat4i( const t& m0, const t& m1, const t& m2,  const t& m3,
               const t& m4, const t& m5, const t& m6,  const t& m7,
               const t& m8, const t& m9, const t& m10, const t& m11,
               const t& m12, const t& m13, const t& m14, const t& m15 )
        {
          m[0] = vec4i<t>( m0, m1, m2, m3 );
          m[1] = vec4i<t>( m4, m5, m6, m7 );
          m[2] = vec4i<t>( m8, m9, m10, m11 );
          m[3] = vec4i<t>( m12, m13, m14, m15 );
        }

        // 1 column per vector
        mat4i( const vec4i<t>& a, const vec4i<t>& b, const vec4i<t>& c, const vec4i<t>& d )
        {
          m[0] = a;
          m[1] = b;
          m[2] = c;
          m[3] = d;
        }

        explicit mat4i( const t& num )
        {
          m[0] = vec4i<t>( num, 0, 0, 0 );
          m[1] = vec4i<t>( 0, num, 0, 0 );
          m[2] = vec4i<t>( 0, 0, num, 0 );
          m[3] = vec4i<t>( 0, 0, 0, num );
        }

        mat4i()
        {
          m[0] = vec4i<t>( 1, 0, 0, 0 );
          m[1] = vec4i<t>( 0, 1, 0, 0 );
          m[2] = vec4i<t>( 0, 0, 1, 0 );
          m[3] = vec4i<t>( 0, 0, 0, 1 );
        }

        vec4i<t>& operator[]( const unsigned int& num )
        {
          assert( num < 4 );
          return m[num];
        }

        vec4i<t> const& operator[]( const unsigned int& num ) const
        {
          assert( num < 4 );
          return m[num];
        }

        const mat4i& operator*= ( const mat4i& mat )
        {
          vec4i<t> tmp1 = m[0];
          vec4i<t> tmp2 = m[1];
          vec4i<t> tmp3 = m[2];
          vec4i<t> tmp4 = m[3];

          m[0] = tmp1 * mat[0].xxxx + tmp2 * mat[0].yyyy + tmp3 * mat[0].zzzz + tmp4 * mat[0].wwww;
          m[1] = tmp1 * mat[1].xxxx + tmp2 * mat[1].yyyy + tmp3 * mat[1].zzzz + tmp4 * mat[1].wwww;
          m[2] = tmp1 * mat[2].xxxx + tmp2 * mat[2].yyyy + tmp3 * mat[2].zzzz + tmp4 * mat[2].wwww;
          m[3] = tmp1 * mat[3].xxxx + tmp2 * mat[3].yyyy + tmp3 * mat[3].zzzz + tmp4 * mat[3].wwww;

          return *this;
        }

        const mat4i& operator*= ( const t& num )
        {
          m[0] *= num;
          m[1] *= num;
          m[2] *= num;
          m[3] *= num;
          return *this;
        }

        const mat4i& operator++ () //pre
        {
          ++m[0];
          ++m[1];
          ++m[2];
          ++m[3];
          return *this;
        }

        mat4i operator++ ( impl::post )
        {
          mat4i tmp = ( *this );
          ++( *this );
          return tmp;
        }

        const mat4i& operator-- () //pre
        {
          --m[0];
          --m[1];
          --m[2];
          --m[3];
          return *this;
        }

        mat4i operator-- ( impl::post )
        {
          mat4i tmp = ( *this );
          --( *this );
          return tmp;
        }
    };
  }
}

#endif

