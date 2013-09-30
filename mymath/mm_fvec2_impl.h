#ifndef mm_fvec2_impl_h
#define mm_fvec2_impl_h

#include "mm_common.h"
#include "mm_sse.h"

namespace mymath
{
  namespace impl
  {
    template< typename ty >
    class fvec2i
    {
    };

    template<>
    class fvec2i<float>
    {
      private:
        template< int at, int bt, int ct, int dt >
        class swizzle
        {
          private:
            __m128 v;
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const fvec2i& operator=( const fvec2i& other )
            {
              v = _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) );
              return *( fvec2i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const fvec2i& operator*=( const fvec2i& other )
            {
              v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i* )this;
            }

            const fvec2i& operator/=( const fvec2i& other ); //needs notEqual, defined elsewhere

            const fvec2i& operator+=( const fvec2i& other )
            {
              v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i* )this;
            }

            const fvec2i& operator-=( const fvec2i& other )
            {
              v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i* )this;
            }

            operator fvec2i() const
            {
              return fvec2i( _mm_shuffle_ps( d, d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
            }
        };

        template<int at>
        class swizzle < at, at, -2, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec2i() const
            {
              return fvec2i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, 0, 0 ) ) );
            }
        };

      protected:

      public:
#ifndef _WIN32
#pragma GCC diagnostic ignored "-pedantic"
#endif
        union
        {
          struct
          {
            float x, y;
          };

          struct
          {
            float r, g;
          };

          struct
          {
            float s, t;
          };

#include "includes/vec2_swizzle_declarations.h"

          struct
          {
            float v[2];
          };

          __m128 d;
        };
#ifndef _WIN32
#pragma GCC diagnostic pop
#endif

        fvec2i( const float& at, const float& bt ) : x( at ), y( bt ) {}
#if MYMATH_STRICT_GLSL == 1
        explicit
#endif
        fvec2i( const float& num ) : x( num ), y( num ) {}
        fvec2i( const __m128& num ) : d( num ) {}
        fvec2i() : x( 0 ), y( 0 ) {}

        float& operator[]( const unsigned int& num ) //read-write
        {
          assert( num < 2 && this );
          return v[num];
        }

        const float& operator[]( const unsigned int& num ) const //read only, constant ref
        {
          assert( num < 2 && this );
          return v[num];
        }

        const fvec2i& operator= ( const fvec2i& other )
        {
          d = other.d;
          return *this;
        }

        const fvec2i& operator*= ( const fvec2i& vec )
        {
          d = _mm_mul_ps( d, vec.d );
          return *this;
        }

        const fvec2i& operator/= ( const fvec2i& vec ); //needs notEqual defined elsewhere

        const fvec2i& operator+= ( const fvec2i& vec )
        {
          d = _mm_add_ps( d, vec.d );
          return *this;
        }

        const fvec2i& operator-= ( const fvec2i& vec )
        {
          d = _mm_sub_ps( d, vec.d );
          return *this;
        }

        const fvec2i& operator%= ( const fvec2i& vec )
        {
          d = sse_mod_ps( d, vec.d );
          return *this;
        }

        //TODO
        /*const fvec2i& operator<<= ( const fvec2i& vec )
        {
          x = ( int )x << ( int )vec.x;
          y = ( int )y << ( int )vec.y;
          return *this;
        }

        const fvec2i& operator>>= ( const fvec2i& vec )
        {
          x = ( int )x >> ( int )vec.x;
          y = ( int )y >> ( int )vec.y;
          return *this;
        }*/

        const fvec2i& operator&= ( const fvec2i& vec )
        {
          d = _mm_and_ps( d, vec.d );
          return *this;
        }

        const fvec2i& operator^= ( const fvec2i& vec )
        {
          d = _mm_xor_ps( d, vec.d );
          return *this;
        }

        const fvec2i& operator|= ( const fvec2i& vec )
        {
          d = _mm_or_ps( d, vec.d );
          return *this;
        }

        const fvec2i operator++ () //pre
        {
          d = _mm_add_ps( d, impl::one );
          return *this;
        }

        const fvec2i operator++ ( impl::post )
        {
          fvec2i tmp = *this;
          ++( *this );
          return tmp;
        }

        const fvec2i operator-- () //pre
        {
          d = _mm_sub_ps( d, impl::one );
          return *this;
        }

        const fvec2i operator-- ( impl::post )
        {
          fvec2i tmp = *this;
          --( *this );
          return tmp;
        }

        const unsigned int length() const
        {
          return 2;
        }
    };
  }
}

#endif
