#ifndef mm_vec3_impl_h
#define mm_vec3_impl_h

#include "mm_common.h"
#include "mm_vec2_impl.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class vec3i
    {
      private:
        template< int a, int b, int c, int d >
        class swizzle
        {
          private:
            t v[3];
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const vec3i& operator=( const vec3i& other )
            {
              v[a] = other.x;
              v[b] = other.y;
              v[c] = other.z;
              return *( vec3i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const vec3i& operator*=( const vec3i& other )
            {
              v[a] *= other.x;
              v[b] *= other.y;
              v[c] *= other.z;
              return *( vec3i* )this;
            }

            const vec3i& operator/=( const vec3i& other ); //needs notEqual, defined elsewhere

            const vec3i& operator+=( const vec3i& other )
            {
              v[a] += other.x;
              v[b] += other.y;
              v[c] += other.z;
              return *( vec3i* )this;
            }

            const vec3i& operator-=( const vec3i& other )
            {
              v[a] -= other.x;
              v[b] -= other.y;
              v[c] -= other.z;
              return *( vec3i* )this;
            }

            operator vec3i()
            {
              return vec3i( v[a], v[b], v[c] );
            }
        };

        template<int a>
        class swizzle < a, a, a, -3 >
        {
          private:
            t v[3];
          public:
            operator vec3i()
            {
              return vec3i( v[a] );
            }
        };

        template<int a, int b>
        class swizzle < b, a, a, -3 >
        {
          private:
            t v[3];
          public:
            operator vec3i()
            {
              return vec3i( v[b], v[a], v[a] );
            }
        };

        template<int a, int b>
        class swizzle < a, b, a, -3 >
        {
          private:
            t v[3];
          public:
            operator vec3i()
            {
              return vec3i( v[a], v[b], v[a] );
            }
        };

        template<int a, int b>
        class swizzle < a, a, b, -3 >
        {
          private:
            t v[3];
          public:
            operator vec3i()
            {
              return vec3i( v[a], v[a], v[b] );
            }
        };

        //vec2 swizzlers
        template<int a>
        class swizzle < a, a, -2, -3 >
        {
          private:
            t v[3];
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
            t v[3];
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
            t x, y, z;
          };

#include "includes/vec3_swizzle_declarations.h"

          t v[3];
        };
#pragma GCC diagnostic pop

        vec3i( const t& a, const t& b, const t& c ) : x( a ), y( b ), z( c ) {}
        vec3i( const vec2i<t>& vec, const t& num ) : x( vec.x ), y( vec.y ), z( num ) {}
        vec3i( const t& num, const vec2i<t>& vec ) : x( num ), y( vec.x ), z( vec.y ) {}
        explicit vec3i( const t& num ) : x( num ), y( num ), z( num ) {}
        vec3i() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

        t& operator[]( const unsigned int& num )
        {
          assert( num >= 0 && num < 3 && this );
          return v[num];
        }

        const t& operator[]( const unsigned int& num ) const
        {
          assert( num >= 0 && num < 3 && this );
          return v[num];
        }

        const vec3i& operator= ( const vec3i& other )
        {
          x = other.x;
          y = other.y;
          z = other.z;
          return *this;
        }

        const vec3i& operator*= ( const vec3i& vec )
        {
          x *= vec.x;
          y *= vec.y;
          z *= vec.z;
          return *this;
        }

        const vec3i& operator/= ( const vec3i& vec ); //needs notEqual defined elsewhere

        const vec3i& operator+= ( const vec3i& vec )
        {
          x += vec.x;
          y += vec.y;
          z += vec.z;
          return *this;
        }

        const vec3i& operator-= ( const vec3i& vec )
        {
          x -= vec.x;
          y -= vec.y;
          z -= vec.z;
          return *this;
        }

        const vec3i& operator%= ( const vec3i& vec )
        {
          x = ( int )x % ( int )vec.x;
          y = ( int )y % ( int )vec.y;
          z = ( int )z % ( int )vec.z;
          return *this;
        }

        const vec3i& operator<<= ( const vec3i& vec )
        {
          x = ( int )x << ( int )vec.x;
          y = ( int )y << ( int )vec.y;
          z = ( int )z << ( int )vec.z;
          return *this;
        }

        const vec3i& operator>>= ( const vec3i& vec )
        {
          x = ( int )x >> ( int )vec.x;
          y = ( int )y >> ( int )vec.y;
          z = ( int )z >> ( int )vec.z;
          return *this;
        }

        const vec3i& operator&= ( const vec3i& vec )
        {
          x = ( int )x & ( int )vec.x;
          y = ( int )y & ( int )vec.y;
          z = ( int )z & ( int )vec.z;
          return *this;
        }

        const vec3i& operator^= ( const vec3i& vec )
        {
          x = ( int )x ^( int )vec.x;
          y = ( int )y ^( int )vec.y;
          z = ( int )z ^( int )vec.z;
          return *this;
        }

        const vec3i& operator|= ( const vec3i& vec )
        {
          x = ( int )x | ( int )vec.x;
          y = ( int )y | ( int )vec.y;
          z = ( int )z | ( int )vec.z;
          return *this;
        }

        const vec3i operator++ ( int )
        {
          x++;
          y++;
          z++;
          return *this;
        }

        const vec3i operator-- ( int )
        {
          x--;
          y--;
          z--;
          return *this;
        }

        const unsigned int length()
        {
          return 3;
        }
    };
  }
}

#endif
