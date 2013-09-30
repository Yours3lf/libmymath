#ifndef mm_fvec3_impl_h
#define mm_fvec3_impl_h

#include "mm_common.h"
#include "mm_fvec2_impl.h"

namespace mymath
{
  namespace impl
  {
    template< typename ty >
    class fvec3i
    {
    };

    template<>
    class fvec3i<float>
    {
      private:
        template< int at, int bt, int ct, int dt >
        class swizzle
        {
          private:
            __m128 v;
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const fvec3i& operator=( const fvec3i& other )
            {
              v = _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) );
              return *( fvec3i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const fvec3i& operator*=( const fvec3i& other )
            {
              v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i* )this;
            }

            const fvec3i& operator/=( const fvec3i& other ); //needs notEqual, defined elsewhere

            const fvec3i& operator+=( const fvec3i& other )
            {
              v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i* )this;
            }

            const fvec3i& operator-=( const fvec3i& other )
            {
              v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i* )this;
            }

            operator fvec3i() const
            {
              return fvec3i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
            }
        };

        template<int at>
        class swizzle < at, at, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i() const
            {
              return fvec3i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < bt, at, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i() const
            {
              return fvec3i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, at, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < at, bt, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i() const
            {
              return fvec3i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < at, at, bt, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i() const
            {
              return fvec3i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, bt, 0 ) ) );
            }
        };

        //vec2 swizzlers
        template<int at>
        class swizzle < at, at, -2, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec2i<float>() const
            {
              return fvec2i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, 0, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < at, bt, -2, -3 >
        {
          private:
            __m128 v;
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const fvec2i<float>& operator=( const fvec2i<float>& other )
            {
              v = _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) );
              return *( fvec2i<float>* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const fvec2i<float>& operator*=( const fvec2i<float>& other )
            {
              v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i<float>* )this;
            }

            const fvec2i<float>& operator/=( const fvec2i<float>& other )
            {
              assert( !impl::is_eq( other.x, ( float )0 ) && !impl::is_eq( other.y, ( float )0 ) );
              v = _mm_div_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i<float>* )this;
            }

            const fvec2i<float>& operator+=( const fvec2i<float>& other )
            {
              v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i<float>* )this;
            }

            const fvec2i<float>& operator-=( const fvec2i<float>& other )
            {
              v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
              return *( fvec2i<float>* )this;
            }

            operator fvec2i<float>() const
            {
              return fvec2i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, 0, 0 ) ) );
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
            float x, y, z;
          };

          struct
          {
            float r, g, b;
          };

          struct
          {
            float s, t, q;
          };

#include "includes/vec3_swizzle_declarations.h"

          struct
          {
            float v[3];
          };

          __m128 d;
        };
#ifndef _WIN32
#pragma GCC diagnostic pop
#endif

        fvec3i( const float& at, const float& bt, const float& ct ) : x( at ), y( bt ), z( ct ) {}
        fvec3i( const fvec2i<float>& vec, const float& num ) : x( vec.x ), y( vec.y ), z( num ) {}
        fvec3i( const float& num, const fvec2i<float>& vec ) : x( num ), y( vec.x ), z( vec.y ) {}
#if MYMATH_STRICT_GLSL == 1
        explicit
#endif
        fvec3i( const float& num ) : x( num ), y( num ), z( num ) {}
        fvec3i( const __m128& num ) : d( num ) {}
        fvec3i() : x( 0 ), y( 0 ), z( 0 ) {}

        float& operator[]( const unsigned int& num )
        {
          assert( num < 3 && this );
          return v[num];
        }

        const float& operator[]( const unsigned int& num ) const
        {
          assert( num < 3 && this );
          return v[num];
        }

        const fvec3i& operator= ( const fvec3i& other )
        {
          d = other.d;
          return *this;
        }

        const fvec3i& operator*= ( const fvec3i& vec )
        {
          d = _mm_mul_ps( d, vec.d );
          return *this;
        }

        const fvec3i& operator/= ( const fvec3i& vec ); //needs notEqual defined elsewhere

        const fvec3i& operator+= ( const fvec3i& vec )
        {
          d = _mm_add_ps( d, vec.d );
          return *this;
        }

        const fvec3i& operator-= ( const fvec3i& vec )
        {
          d = _mm_sub_ps( d, vec.d );
          return *this;
        }

        const fvec3i& operator%= ( const fvec3i& vec )
        {
          d = sse_mod_ps( d, vec.d );
          return *this;
        }

        //TODO
        /*const fvec3i& operator<<= ( const fvec3i& vec )
        {
          x = ( int )x << ( int )vec.x;
          y = ( int )y << ( int )vec.y;
          z = ( int )z << ( int )vec.z;
          return *this;
        }

        const fvec3i& operator>>= ( const fvec3i& vec )
        {
          x = ( int )x >> ( int )vec.x;
          y = ( int )y >> ( int )vec.y;
          z = ( int )z >> ( int )vec.z;
          return *this;
        }*/

        const fvec3i& operator&= ( const fvec3i& vec )
        {
          d = _mm_and_ps( d, vec.d );
          return *this;
        }

        const fvec3i& operator^= ( const fvec3i& vec )
        {
          d = _mm_xor_ps( d, vec.d );
          return *this;
        }

        const fvec3i& operator|= ( const fvec3i& vec )
        {
          d = _mm_or_ps( d, vec.d );
          return *this;
        }

        const fvec3i operator++ () //pre
        {
          d = _mm_add_ps( d, impl::one );
          return *this;
        }

        const fvec3i operator++ ( impl::post )
        {
          fvec3i tmp = *this;
          ++( *this );
          return tmp;
        }

        const fvec3i operator-- () //pre
        {
          d = _mm_sub_ps( d, impl::one );
          return *this;
        }

        const fvec3i operator-- ( impl::post )
        {
          fvec3i tmp = *this;
          --( *this );
          return tmp;
        }

        const unsigned int length() const
        {
          return 3;
        }
    };
  }
}

#endif
