#ifndef mm_vec2_impl_h
#define mm_vec2_impl_h

#include "mm_common.h"

namespace mymath
{
  namespace impl
  {
    template< typename t >
    class vec2i
    {
      private:
        template< int a, int b, int c, int d >
        class swizzle
        {
          private:
            t v[2];
          public:
            //For cases like swizzle = vec2 and swizzle = swizzle
            const vec2i& operator=( const vec2i& other )
            {
              v[a] = other.x;
              v[b] = other.y;
              return *( vec2i* )this;
            }

            //For cases like swizzle *= vec2 and swizzle *= swizzle
            const vec2i& operator*=( const vec2i& other )
            {
              v[a] *= other.x;
              v[b] *= other.y;
              return *( vec2i* )this;
            }

            const vec2i& operator/=( const vec2i& other ); //needs notEqual, defined elsewhere

            const vec2i& operator+=( const vec2i& other )
            {
              v[a] += other.x;
              v[b] += other.y;
              return *( vec2i* )this;
            }

            const vec2i& operator-=( const vec2i& other )
            {
              v[a] -= other.x;
              v[b] -= other.y;
              return *( vec2i* )this;
            }

            operator vec2i()
            {
              return vec2i( v[a], v[b] );
            }
        };

        template<int a>
        class swizzle < a, a, -2, -3 >
        {
          private:
            t v[2];
          public:
            operator vec2i()
            {
              return vec2i( v[a] );
            }
        };

      protected:

      public:
#pragma GCC diagnostic ignored "-pedantic"
        union
        {
          struct
          {
            t x, y;
          };

#include "includes/vec2_swizzle_declarations.h"

          t v[2];
        };
#pragma GCC diagnostic pop

        vec2i( const t& a, const t& b ) : x( a ), y( b ) {}
        explicit vec2i( const t& num ) : x( num ), y( num ) {}
        vec2i() : x( 0 ), y( 0 ) {}

        t& operator[]( const unsigned int& num ) //read-write
        {
          assert( num >= 0 && num < 2 && this );
          return v[num];
        }

        const t& operator[]( const unsigned int& num ) const //read only, constant ref
        {
          assert( num >= 0 && num < 2 && this );
          return v[num];
        }

        const vec2i& operator= ( const vec2i& other )
        {
          x = other.x;
          y = other.y;
          return *this;
        }

        const vec2i& operator*= ( const vec2i& vec )
        {
          x *= vec.x;
          y *= vec.y;
          return *this;
        }

        const vec2i& operator/= ( const vec2i& vec ); //needs notEqual defined elsewhere

        const vec2i& operator+= ( const vec2i& vec )
        {
          x += vec.x;
          y += vec.y;
          return *this;
        }

        const vec2i& operator-= ( const vec2i& vec )
        {
          x -= vec.x;
          y -= vec.y;
          return *this;
        }

        const vec2i& operator%= ( const vec2i& vec )
        {
          x = ( int )x % ( int )vec.x;
          y = ( int )y % ( int )vec.y;
          return *this;
        }

        const vec2i& operator<<= ( const vec2i& vec )
        {
          x = ( int )x << ( int )vec.x;
          y = ( int )y << ( int )vec.y;
          return *this;
        }

        const vec2i& operator>>= ( const vec2i& vec )
        {
          x = ( int )x >> ( int )vec.x;
          y = ( int )y >> ( int )vec.y;
          return *this;
        }

        const vec2i& operator&= ( const vec2i& vec )
        {
          x = ( int )x & ( int )vec.x;
          y = ( int )y & ( int )vec.y;
          return *this;
        }

        const vec2i& operator^= ( const vec2i& vec )
        {
          x = ( int )x ^( int )vec.x;
          y = ( int )y ^( int )vec.y;
          return *this;
        }

        const vec2i& operator|= ( const vec2i& vec )
        {
          x = ( int )x | ( int )vec.x;
          y = ( int )y | ( int )vec.y;
          return *this;
        }

        const vec2i operator++ ( int )
        {
          x++;
          y++;
          return *this;
        }

        const vec2i operator-- ( int )
        {
          x--;
          y--;
          return *this;
        }

        const unsigned int length()
        {
          return 2;
        }
    };
  }
}

#endif
