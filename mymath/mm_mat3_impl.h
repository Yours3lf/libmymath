#ifndef mm_mat3_impl_h
#define mm_mat3_impl_h

#include "mm_vec3_impl.h"
#include "mm_vec_func.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class mat3i
    {
      private:
        /*
         * matrix layout:
         * m[0].x m[1].x m[2].x
         * m[0].y m[1].y m[2].y
         * m[0].z m[1].z m[2].z
         */
        vec3i<t> m[3];

      protected:

      public:
        // 1 column vector per row
        mat3i( const t& m0, const t& m1, const t& m2,
               const t& m3, const t& m4, const t& m5,
               const t& m6, const t& m7, const t& m8 )
        {
          m[0].x = m0;
          m[0].y = m1;
          m[0].z = m2;
          m[1].x = m3;
          m[1].y = m4;
          m[1].z = m5;
          m[2].x = m6;
          m[2].y = m7;
          m[2].z = m8;
        }

        // 1 column per vector
        mat3i( const vec3i<t>& a, const vec3i<t>& b, const vec3i<t>& c )
        {
          m[0] = a;
          m[1] = b;
          m[2] = c;
        }

        explicit mat3i( const t& num )
        {
          m[0].x = num;
          m[0].y = 0;
          m[0].z = 0;
          m[1].x = 0;
          m[1].y = num;
          m[1].z = 0;
          m[2].x = 0;
          m[2].y = 0;
          m[2].z = num;
        }

        mat3i()
        {
          m[0].x = 1;
          m[0].y = 0;
          m[0].z = 0;
          m[1].x = 0;
          m[1].y = 1;
          m[1].z = 0;
          m[2].x = 0;
          m[2].y = 0;
          m[2].z = 1;
        }

        vec3i<t>& operator[]( const unsigned int& num )
        {
          assert( ( num >= 0 ) && ( num < 3 ) );
          return m[num];
        }

        const vec3i<t>& operator[]( const unsigned int& num ) const
        {
          assert( ( num >= 0 ) && ( num < 3 ) );
          return m[num];
        }

        const mat3i& operator*= ( const mat3i& mat )
        {
          vec3i<t> r0( m[0].x, m[1].x, m[2].x );
          vec3i<t> r1( m[0].y, m[1].y, m[2].y );
          vec3i<t> r2( m[0].z, m[1].z, m[2].z );

          vec3i<t> c0 = mat[0];
          vec3i<t> c1 = mat[1];
          vec3i<t> c2 = mat[2];

          m[0].x = dot( r0, c0 );
          m[0].y = dot( r1, c0 );
          m[0].z = dot( r2, c0 );

          m[1].x = dot( r0, c1 );
          m[1].y = dot( r1, c1 );
          m[1].z = dot( r2, c1 );

          m[2].x = dot( r0, c2 );
          m[2].y = dot( r1, c2 );
          m[2].z = dot( r2, c2 );
          return *this;
        }

        const mat3i& operator*= ( const t& num )
        {
          m[0] *= num;
          m[1] *= num;
          m[2] *= num;
          return *this;
        }

        const mat3i& operator++ () //pre
        {
          ++m[0];
          ++m[1];
          ++m[2];
          return *this;
        }

        const mat3i& operator++ ( impl::post )
        {
          mat3i tmp = ( *this );
          ++( *this );
          return tmp;
        }

        const mat3i& operator-- () //pre
        {
          --m[0];
          --m[1];
          --m[2];
          return *this;
        }

        const mat3i& operator-- ( impl::post )
        {
          mat3i tmp = ( *this );
          --( *this );
          return tmp;
        }
    };
  }
}

#endif
