#ifndef mm_vec4i_impl_h
#define mm_vec4i_impl_h

#include "mm_common.h"
#include "mm_vec2_impl.h"
#include "mm_vec3_impl.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class vec4i
    {
      private:
        template< int a, int b, int c, int d >
        class swizzle
        {
          private:
            t v[4];
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const vec4i& operator=( const vec4i& other )
            {
              v[a] = other.x;
              v[b] = other.y;
              v[c] = other.z;
              v[d] = other.w;
              return *( vec4i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const vec4i& operator*=( const vec4i& other )
            {
              v[a] *= other.x;
              v[b] *= other.y;
              v[c] *= other.z;
              v[d] *= other.w;
              return *( vec4i* )this;
            }

            const vec4i& operator/=( const vec4i& other ); //needs notEqual defined elsewhere

            const vec4i& operator+=( const vec4i& other )
            {
              v[a] += other.x;
              v[b] += other.y;
              v[c] += other.z;
              v[d] += other.w;
              return *( vec4i* )this;
            }

            const vec4i& operator-=( const vec4i& other )
            {
              v[a] -= other.x;
              v[b] -= other.y;
              v[c] -= other.z;
              v[d] -= other.w;
              return *( vec4i* )this;
            }

            operator vec4i()
            {
              return vec4i( v[a], v[b], v[c], v[d] );
            }
        };

        template<int a>
        class swizzle<a, a, a, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[a] );
            }
        };

        template<int a, int b>
        class swizzle<b, a, a, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[b], v[a], v[a], v[a] );
            }
        };

        template<int a, int b>
        class swizzle<a, b, a, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[a], v[b], v[a], v[a] );
            }
        };

        template<int a, int b>
        class swizzle<a, a, b, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[a], v[a], v[b], v[a] );
            }
        };

        template<int a, int b>
        class swizzle<a, a, a, b>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[a], v[a], v[a], v[b] );
            }
        };

        template<int a, int b, int c>
        class swizzle<b, c, a, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[b], v[c], v[a], v[a] );
            }
        };

        template<int a, int b, int c>
        class swizzle<b, a, c, a>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[b], v[a], v[c], v[a] );
            }
        };

        template<int a, int b, int c>
        class swizzle<b, a, a, c>
        {
          private:
            t v[4];
          public:
            operator vec4i()
            {
              return vec4i( v[b], v[a], v[a], v[c] );
            }
        };

        //vec3 swizzlers
        template<int a>
        class swizzle < a, a, a, -3 >
        {
          private:
            t v[4];
          public:
            operator vec3i<t>()
            {
              return vec3i<t>( v[a] );
            }
        };

        template<int a, int b>
        class swizzle < b, a, a, -3 >
        {
          private:
            t v[4];
          public:
            operator vec3i<t>()
            {
              return vec3i<t>( v[b], v[a], v[a] );
            }
        };

        template<int a, int b>
        class swizzle < a, b, a, -3 >
        {
          private:
            t v[4];
          public:
            operator vec3i<t>()
            {
              return vec3i<t>( v[a], v[b], v[a] );
            }
        };

        template<int a, int b>
        class swizzle < a, a, b, -3 >
        {
          private:
            t v[4];
          public:
            operator vec3i<t>()
            {
              return vec3i<t>( v[a], v[a], v[b] );
            }
        };

        template<int a, int b, int c> //3 component
        class swizzle < a, b, c, -3 >
        {
          private:
            t v[4];
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const vec3i<t>& operator=( const vec3i<t>& other )
            {
              v[a] = other.x;
              v[b] = other.y;
              v[c] = other.z;
              return *( vec3i<t>* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const vec3i<t>& operator*=( const vec3i<t>& other )
            {
              v[a] *= other.x;
              v[b] *= other.y;
              v[c] *= other.z;
              return *( vec3i<t>* )this;
            }

            const vec3i<t>& operator/=( const vec3i<t>& other )
            {
              assert( other.x != ( t )0 && other.y != ( t )0 && other.z != ( t )0 );
              vec3i<t> tmp( ( t )1 / other.x, ( t )1 / other.y, ( t )1 / other.z );
              v[a] *= tmp.x;
              v[b] *= tmp.y;
              v[c] *= tmp.z;
              return *( vec3i<t>* )this;
            }

            const vec3i<t>& operator+=( const vec3i<t>& other )
            {
              v[a] += other.x;
              v[b] += other.y;
              v[c] += other.z;
              return *( vec3i<t>* )this;
            }

            const vec3i<t>& operator-=( const vec3i<t>& other )
            {
              v[a] -= other.x;
              v[b] -= other.y;
              v[c] -= other.z;
              return *( vec3i<t>* )this;
            }

            operator vec3i<t>()
            {
              return vec3i<t>( v[a], v[b], v[c] );
            }
        };

        //vec2 swizzlers
        template<int a>
        class swizzle < a, a, -2, -3 >
        {
          private:
            t v[4];
          public:
            operator vec2i<t>()
            {
              return vec2i<t>( v[a], v[a] );
            }
        };

        template<int a, int b>
        class swizzle < a, b, -2, -3 >
        {
          private:
            t v[4];
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const vec2i<t>& operator=( const vec2i<t>& other )
            {
              v[a] = other.x;
              v[b] = other.y;
              return *( vec2i<t>* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const vec2i<t>& operator*=( const vec2i<t>& other )
            {
              v[a] *= other.x;
              v[b] *= other.y;
              return *( vec2i<t>* )this;
            }

            const vec2i<t>& operator/=( const vec2i<t>& other )
            {
              assert( other.x != ( t )0 && other.y != ( t )0 );
              vec2i<t> tmp( ( t )1 / other.x, ( t )1 / other.y );
              v[a] *= tmp.x;
              v[b] *= tmp.y;
              return *( vec2i<t>* )this;
            }

            const vec2i<t>& operator+=( const vec2i<t>& other )
            {
              v[a] += other.x;
              v[b] += other.y;
              return *( vec2i<t>* )this;
            }

            const vec2i<t>& operator-=( const vec2i<t>& other )
            {
              v[a] -= other.x;
              v[b] -= other.y;
              return *( vec2i<t>* )this;
            }

            operator vec2i<t>()
            {
              return vec2i<t>( v[a], v[b] );
            }
        };

      protected:

      public:
#pragma GCC diagnostic ignored "-pedantic"
        union
        {
          struct
          {
            t x, y, z, w;
          };

#include "includes/vec4_swizzle_declarations.h"

          t v[4];
        };
#pragma GCC diagnostic pop

        vec4i( const t& a, const t& b, const t& c, const t& d ) : x( a ), y( b ), z( c ), w( d ) {}
        vec4i( const vec3i<t>& vec, const t& num ) : x( vec.x ), y( vec.y ), z( vec.z ), w( num ) {}
        vec4i( const t& num, const vec3i<t>& vec ) : x( num ), y( vec.x ), z( vec.y ), w( vec.z ) {}
        vec4i( const vec2i<t>& a, const vec2i<t>& b ) : x( a.x ), y( a.y ), z( b.x ), w( b.y ) {}
        vec4i( const t& num1, const t& num2, const vec2i<t>& vec ) : x( num1 ), y( num2 ), z( vec.x ), w( vec.y ) {}
        vec4i( const vec2i<t>& vec, const t& num1, const t& num2 ) : x( vec.x ), y( vec.y ), z( num1 ), w( num2 ) {}
        explicit vec4i( const t& num ) : x( num ), y( num ), z( num ), w( num ) {}
        vec4i() : x( 0.0f ), y( 0.0f ), z( 0.0f ), w( 0.0f ) {}

        t& operator[]( const unsigned int& num )
        {
          assert( num >= 0 && num < 4 && this );
          return v[num];
        }

        const t& operator[]( const unsigned int& num ) const
        {
          assert( num >= 0 && num < 4 && this );
          return v[num];
        }

        const vec4i& operator= ( const vec4i& other )
        {
          x = other.x;
          y = other.y;
          z = other.z;
          w = other.w;
          return *this;
        }

        const vec4i& operator*= ( const vec4i& vec )
        {
          x *= vec.x;
          y *= vec.y;
          z *= vec.z;
          w *= vec.w;
          return *this;
        }

        const vec4i& operator/= ( const vec4i& vec ); //needs notEqual defined elsewhere

        const vec4i& operator+= ( const vec4i& vec )
        {
          x += vec.x;
          y += vec.y;
          z += vec.z;
          w += vec.w;
          return *this;
        }

        const vec4i& operator-= ( const vec4i& vec )
        {
          x -= vec.x;
          y -= vec.y;
          z -= vec.z;
          w -= vec.w;
          return *this;
        }

        const vec4i& operator%= ( const vec4i& vec )
        {
          x = ( int )x % ( int )vec.x;
          y = ( int )y % ( int )vec.y;
          z = ( int )z % ( int )vec.z;
          w = ( int )w % ( int )vec.w;
          return *this;
        }

        const vec4i& operator<<= ( const vec4i& vec )
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
        }

        const vec4i& operator&= ( const vec4i& vec )
        {
          x = ( int )x & ( int )vec.x;
          y = ( int )y & ( int )vec.y;
          z = ( int )z & ( int )vec.z;
          w = ( int )w & ( int )vec.w;
          return *this;
        }

        const vec4i& operator^= ( const vec4i& vec )
        {
          x = ( int )x ^( int )vec.x;
          y = ( int )y ^( int )vec.y;
          z = ( int )z ^( int )vec.z;
          w = ( int )w ^( int )vec.w;
          return *this;
        }

        const vec4i& operator|= ( const vec4i& vec )
        {
          x = ( int )x | ( int )vec.x;
          y = ( int )y | ( int )vec.y;
          z = ( int )z | ( int )vec.z;
          w = ( int )w | ( int )vec.w;
          return *this;
        }

        const vec4i operator++ ( int )
        {
          x++;
          y++;
          z++;
          w++;
          return *this;
        }

        const vec4i operator-- ( int )
        {
          x--;
          y--;
          z--;
          w--;
          return *this;
        }

        const unsigned int lenght()
        {
          return 4;
        }
    };
  }
}

#endif
