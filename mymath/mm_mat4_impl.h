#ifndef mm_mat4_impl_h
#define mm_mat4_impl_h

#include "mm_vec4_impl.h"
#include "mm_vec_func.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class mat4i
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
          m[0].x = m0;
          m[0].y = m1;
          m[0].z = m2;
          m[0].w = m3;
          m[1].x = m4;
          m[1].y = m5;
          m[1].z = m6;
          m[1].w = m7;
          m[2].x = m8;
          m[2].y = m9;
          m[2].z = m10;
          m[2].w = m11;
          m[3].x = m12;
          m[3].y = m13;
          m[3].z = m14;
          m[3].w = m15;
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
          m[0].x = num;
          m[0].y = 0;
          m[0].z = 0;
          m[0].w = 0;
          m[1].x = 0;
          m[1].y = num;
          m[1].z = 0;
          m[1].w = 0;
          m[2].x = 0;
          m[2].y = 0;
          m[2].z = num;
          m[2].w = 0;
          m[3].x = 0;
          m[3].y = 0;
          m[3].z = 0;
          m[3].w = num;
        }

        mat4i()
        {
          m[0].x = 1;
          m[0].y = 0;
          m[0].z = 0;
          m[0].w = 0;
          m[1].x = 0;
          m[1].y = 1;
          m[1].z = 0;
          m[1].w = 0;
          m[2].x = 0;
          m[2].y = 0;
          m[2].z = 1;
          m[2].w = 0;
          m[3].x = 0;
          m[3].y = 0;
          m[3].z = 0;
          m[3].w = 1;
        }

        vec4i<t>& operator[]( const unsigned int& num )
        {
          assert( ( num >= 0 ) && ( num < 4 ) );
          return m[num];
        }

        vec4i<t> const& operator[]( const unsigned int& num ) const
        {
          assert( ( num >= 0 ) && ( num < 4 ) );
          return m[num];
        }

        const mat4i& operator*= ( const mat4i& mat )
        {
          vec4i<t> r0( m[0].x, m[1].x, m[2].x, m[3].x );
          vec4i<t> r1( m[0].y, m[1].y, m[2].y, m[3].y );
          vec4i<t> r2( m[0].z, m[1].z, m[2].z, m[3].z );
          vec4i<t> r3( m[0].w, m[1].w, m[2].w, m[3].w );

          vec4i<t> c0 = mat[0];
          vec4i<t> c1 = mat[1];
          vec4i<t> c2 = mat[2];
          vec4i<t> c3 = mat[3];

          m[0].x = dot( r0, c0 );
          m[0].y = dot( r1, c0 );
          m[0].z = dot( r2, c0 );
          m[0].w = dot( r3, c0 );

          m[1].x = dot( r0, c1 );
          m[1].y = dot( r1, c1 );
          m[1].z = dot( r2, c1 );
          m[1].w = dot( r3, c1 );

          m[2].x = dot( r0, c2 );
          m[2].y = dot( r1, c2 );
          m[2].z = dot( r2, c2 );
          m[2].w = dot( r3, c2 );

          m[3].x = dot( r0, c3 );
          m[3].y = dot( r1, c3 );
          m[3].z = dot( r2, c3 );
          m[3].w = dot( r3, c3 );
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

        const mat4i& operator++ ( impl::post )
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

        const mat4i& operator-- ( impl::post )
        {
          mat4i tmp = ( *this );
          --( *this );
          return tmp;
        }
    };
  }
}

#endif
