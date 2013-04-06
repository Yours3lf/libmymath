#ifndef mm_mat2_impl_h
#define mm_mat2_impl_h

#include "mm_vec2_impl.h"
#include "mm_vec_func.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class mat2i
    {
      private:
        /*
         * matrix layout:
         * m[0].x m[1].x
         * m[0].y m[1].y
         */
        impl::vec2i<t> m[2];

      protected:

      public:
        // 1 column vector per row
        mat2i( const t& m0, const t& m1,
               const t& m2, const t& m3 )
        {
          m[0].x = m0;
          m[0].y = m1;
          m[1].x = m2;
          m[1].y = m3;
        }

        // 1 column per vector
        mat2i( const vec2i<t>& a, const vec2i<t>& b )
        {
          m[0] = a;
          m[1] = b;
        }

        explicit mat2i( const t& num )
        {
          m[0].x = num;
          m[0].y = 0;
          m[1].x = 0;
          m[1].y = num;
        }

        mat2i()
        {
          m[0].x = 1;
          m[0].y = 0;
          m[1].x = 0;
          m[1].y = 1;
        }

        vec2i<t>& operator[]( const unsigned int& num )
        {
          assert( ( num >= 0 ) && ( num < 2 ) );
          return m[num];
        }

        const vec2i<t>& operator[]( const unsigned int& num ) const
        {
          assert( ( num >= 0 ) && ( num < 2 ) );
          return m[num];
        }

        const mat2i& operator*= ( const mat2i& mat )
        {
          vec2i<t> r0( m[0].x, m[1].x );
          vec2i<t> r1( m[0].y, m[1].y );

          vec2i<t> c0 = mat[0];
          vec2i<t> c1 = mat[1];

          m[0].x = dot( r0, c0 );
          m[0].y = dot( r1, c0 );

          m[1].x = dot( r0, c1 );
          m[1].y = dot( r1, c1 );
          return *this;
        }

        const mat2i& operator*= ( const t& num )
        {
          m[0] *= num;
          m[1] *= num;
          return *this;
        }

        const mat2i& operator++ () //pre
        {
          ++m[0];
          ++m[1];
          return *this;
        }

        const mat2i& operator++ ( impl::post )
        {
          mat2i tmp = *this;
          ++( *this );
          return tmp;
        }

        const mat2i& operator-- () //pre
        {
          --m[0];
          --m[1];
          return *this;
        }

        const mat2i& operator-- ( impl::post )
        {
          mat2i tmp = *this;
          --( *this );
          return tmp;
        }

    };
  }
}

#endif
