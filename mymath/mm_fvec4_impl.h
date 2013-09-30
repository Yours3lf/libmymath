#ifndef mm_fvec4i_impl_h
#define mm_fvec4i_impl_h

#include "mm_common.h"
#include "mm_fvec2_impl.h"
#include "mm_fvec3_impl.h"

namespace mymath
{
  namespace impl
  {
    template< typename ty >
    class fvec4i
    {
    };

    template<>
    class fvec4i<float>
    {
      private:
        template< int at, int bt, int ct, int dt >
        class swizzle
        {
          private:
            __m128 v;
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const fvec4i& operator=( const fvec4i& other )
            {
              v = _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, dt ) );
              return *( fvec4i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const fvec4i& operator*=( const fvec4i& other )
            {
              v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, dt ) ) );
              return *( fvec4i* )this;
            }

            const fvec4i& operator/=( const fvec4i& other ); //needs notEqual defined elsewhere

            const fvec4i& operator+=( const fvec4i& other )
            {
              v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, dt ) ) );
              return *( fvec4i* )this;
            }

            const fvec4i& operator-=( const fvec4i& other )
            {
              v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, dt ) ) );
              return *( fvec4i* )this;
            }

            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, ct, dt ) ) );
            }
        };

        template<int at>
        class swizzle<at, at, at, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, at, at ) ) );
            }
        };

        template<int at, int bt>
        class swizzle<bt, at, at, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, at, at, at ) ) );
            }
        };

        template<int at, int bt>
        class swizzle<at, bt, at, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, at, at ) ) );
            }
        };

        template<int at, int bt>
        class swizzle<at, at, bt, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, bt, at ) ) );
            }
        };

        template<int at, int bt>
        class swizzle<at, at, at, bt>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, at, bt ) ) );
            }
        };

        template<int at, int bt, int ct>
        class swizzle<bt, ct, at, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, ct, at, at ) ) );
            }
        };

        template<int at, int bt, int ct>
        class swizzle<bt, at, ct, at>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, at, ct, at ) ) );
            }
        };

        template<int at, int bt, int ct>
        class swizzle<bt, at, at, ct>
        {
          private:
            __m128 v;
          public:
            operator fvec4i() const
            {
              return fvec4i( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, at, at, ct ) ) );
            }
        };

        //vec3 swizzlers
        template<int at>
        class swizzle < at, at, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i<float>() const
            {
              return fvec3i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < bt, at, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i<float>() const
            {
              return fvec3i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( bt, at, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < at, bt, at, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i<float>() const
            {
              return fvec3i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, at, 0 ) ) );
            }
        };

        template<int at, int bt>
        class swizzle < at, at, bt, -3 >
        {
          private:
            __m128 v;
          public:
            operator fvec3i<float>() const
            {
              return fvec3i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, at, bt, 0 ) ) );
            }
        };

        template<int at, int bt, int ct> //3 component
        class swizzle < at, bt, ct, -3 >
        {
          private:
            __m128 v;
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const fvec3i<float>& operator=( const fvec3i<float>& other )
            {
              v = _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) );
              return *( fvec3i<float>* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const fvec3i<float>& operator*=( const fvec3i<float>& other )
            {
              v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i<float>* )this;
            }

            const fvec3i<float>& operator/=( const fvec3i<float>& other )
            {
              assert( !impl::is_eq( other.x, ( float )0 ) && !impl::is_eq( other.y, ( float )0 ) && !impl::is_eq( other.z, ( float )0 ) );
              v = _mm_div_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i<float>* )this;
            }

            const fvec3i<float>& operator+=( const fvec3i<float>& other )
            {
              v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i<float>* )this;
            }

            const fvec3i<float>& operator-=( const fvec3i<float>& other )
            {
              v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
              return *( fvec3i<float>* )this;
            }

            operator fvec3i<float>() const
            {
              return fvec3i<float>( _mm_shuffle_ps( v, v, _MM_SHUFFLE( at, bt, ct, 0 ) ) );
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
              assert( other.x != ( float )0 && other.y != ( float )0 );
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
            float x, y, z, w;
          };

          struct
          {
            float r, g, b, a;
          };

          struct
          {
            float s, t, q, p;
          };

#include "includes/vec4_swizzle_declarations.h"

          struct
          {
            float v[4];
          };

          __m128 d;
        };
#ifndef _WIN32
#pragma GCC diagnostic pop
#endif

        fvec4i( const float& at, const float& bt, const float& ct, const float& dt ) : x( at ), y( bt ), z( ct ), w( dt ) {}
        fvec4i( const fvec3i<float>& vec, const float& num ) : x( vec.x ), y( vec.y ), z( vec.z ), w( num ) {}
        fvec4i( const float& num, const fvec3i<float>& vec ) : x( num ), y( vec.x ), z( vec.y ), w( vec.z ) {}
        fvec4i( const fvec2i<float>& at, const fvec2i<float>& bt ) : x( at.x ), y( at.y ), z( bt.x ), w( bt.y ) {}
        fvec4i( const float& num1, const float& num2, const fvec2i<float>& vec ) : x( num1 ), y( num2 ), z( vec.x ), w( vec.y ) {}
        fvec4i( const fvec2i<float>& vec, const float& num1, const float& num2 ) : x( vec.x ), y( vec.y ), z( num1 ), w( num2 ) {}
#if MYMATH_STRICT_GLSL == 1
        explicit
#endif
        fvec4i( const float& num ) : x( num ), y( num ), z( num ), w( num ) {}
        fvec4i( const __m128& num ) : d( num ) {}
        fvec4i() : x( 0 ), y( 0 ), z( 0 ), w( 0 ) {}

        float& operator[]( const unsigned int& num )
        {
          assert( num < 4 && this );
          return v[num];
        }

        const float& operator[]( const unsigned int& num ) const
        {
          assert( num < 4 && this );
          return v[num];
        }

        const fvec4i& operator= ( const fvec4i& other )
        {
          d = other.d;
          return *this;
        }

        const fvec4i& operator*= ( const fvec4i& vec )
        {
          d = _mm_mul_ps( d, vec.d );
          return *this;
        }

        const fvec4i& operator/= ( const fvec4i& vec ); //needs notEqual defined elsewhere

        const fvec4i& operator+= ( const fvec4i& vec )
        {
          d = _mm_add_ps( d, vec.d );
          return *this;
        }

        const fvec4i& operator-= ( const fvec4i& vec )
        {
          d = _mm_sub_ps( d, vec.d );
          return *this;
        }

        const fvec4i& operator%= ( const fvec4i& vec )
        {
          d = sse_mod_ps( d, vec.d );
          return *this;
        }

        //TODO
        /*const vec4i& operator<<= ( const vec4i& vec )
        {
          x = ( int )x << ( int )vec.x;
          y = ( int )y << ( int )vec.y;
          z = ( int )z << ( int )vec.z;
          w = ( int )w << ( int )vec.w;
          return *this;
        }

        const vec4i& operator>>= ( const vec4i& vec )
        {
          x = ( int )x >> ( int )vec.x;
          y = ( int )y >> ( int )vec.y;
          z = ( int )z >> ( int )vec.z;
          w = ( int )w >> ( int )vec.w;
          return *this;
        }*/

        const fvec4i& operator&= ( const fvec4i& vec )
        {
          d = _mm_and_ps( d, vec.d );
          return *this;
        }

        const fvec4i& operator^= ( const fvec4i& vec )
        {
          d = _mm_xor_ps( d, vec.d );
          return *this;
        }

        const fvec4i& operator|= ( const fvec4i& vec )
        {
          d = _mm_or_ps( d, vec.d );
          return *this;
        }

        const fvec4i operator++ () //pre
        {
          d = _mm_add_ps( d, impl::one );
          return *this;
        }

        const fvec4i operator++ ( impl::post )
        {
          fvec4i tmp = *this;
          ++( *this );
          return tmp;
        }

        const fvec4i operator-- () //pre
        {
          d = _mm_sub_ps( d, impl::one );
          return *this;
        }

        const fvec4i operator-- ( impl::post )
        {
          fvec4i tmp = *this;
          --( *this );
          return tmp;
        }

        const unsigned int lenght() const
        {
          return 4;
        }
    };
  }
}

#endif

