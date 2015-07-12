#ifndef mm_vec2_impl_h
#define mm_vec2_impl_h

#include "mm_common.h"

namespace mymath
{
  namespace impl
  {
    template< typename ty >
    class MM_16_BYTE_ALIGNED vec2i
    {
    private:
      template< int at, int bt, int ct, int dt >
      class swizzle
      {
      private:
        struct
        {
          ty v[2];
          ty _dummy[2];
        };
      public:
        //For cases like swizzle = vec2 and swizzle = swizzle
        const vec2i& operator=( const vec2i& other )
        {
          v[at] = other.x;
          v[bt] = other.y;
          return *( vec2i* )this;
        }

        //For cases like swizzle *= vec2 and swizzle *= swizzle
        const vec2i& operator*=( const vec2i& other )
        {
          v[at] *= other.x;
          v[bt] *= other.y;
          return *( vec2i* )this;
        }

        const vec2i& operator/=( const vec2i& other ); //needs notEqual, defined elsewhere

        const vec2i& operator+=( const vec2i& other )
        {
          v[at] += other.x;
          v[bt] += other.y;
          return *( vec2i* )this;
        }

        const vec2i& operator-=( const vec2i& other )
        {
          v[at] -= other.x;
          v[bt] -= other.y;
          return *( vec2i* )this;
        }

        operator vec2i() const
        {
          return vec2i( v[at], v[bt] );
        }
      };

      template<int at>
      class swizzle < at, at, -2, -3 >
      {
      private:
        struct
        {
          ty v[2];
          ty _dummy[2];
        };
      public:
        operator vec2i() const
        {
          return vec2i( v[at] );
        }
      };

    protected:

    public:
#ifdef __GNUC__  //g++
#pragma GCC diagnostic ignored "-pedantic"
#endif
      union
      {
        struct
        {
          ty x, y;
          ty _dummy[2];
        };

        struct
        {
          ty r, g;
          ty _dummy2[2];
        };

        struct
        {
          ty s, t;
          ty _dummy3[2];
        };

#include "includes/vec2_swizzle_declarations.h"

        struct
        {
          ty v[2];
          ty _dummy4[2];
        };
      };
#ifdef __GNUC__  //g++
#pragma GCC diagnostic pop
#endif

      vec2i( const ty& at, const ty& bt ) : x( at ), y( bt )
      {
      }
#if MYMATH_STRICT_GLSL == 1
      explicit
#endif
        vec2i( const ty& num ) : x( num ), y( num )
      {
      }
      //vec2i() : x( 0 ), y( 0 ) {}
      vec2i()
      {
      }
      vec2i( const vec2i<int>& v )
      {
        x = v.x; y = v.y;
      }
      vec2i( const vec2i<unsigned>& v )
      {
        x = v.x; y = v.y;
      }

      vec2i( std::initializer_list<ty> list )
      {
        assert( list.size() == 2 );

        x = *( list.begin() + 0 );
        y = *( list.begin() + 1 );
      }

      ty& operator[]( const unsigned int& num ) //read-write
      {
        assert( num < 2 && this );
        return v[num];
      }

      const ty& operator[]( const unsigned int& num ) const //read only, constant ref
      {
        assert( num < 2 && this );
        return v[num];
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

      const vec2i<int>& operator%= ( const vec2i<int>& vec )
      {
        x = x % vec.x;
        y = y % vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator%= ( const vec2i<unsigned>& vec )
      {
        x = x % vec.x;
        y = y % vec.y;
        return *this;
      }

      const vec2i<int>& operator<<= ( const vec2i<int>& vec )
      {
        x = x << vec.x;
        y = y << vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator<<= ( const vec2i<unsigned>& vec )
      {
        x = x << vec.x;
        y = y << vec.y;
        return *this;
      }

      const vec2i<int>& operator>>= ( const vec2i<int>& vec )
      {
        x = x >> vec.x;
        y = y >> vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator>>= ( const vec2i<unsigned>& vec )
      {
        x = x >> vec.x;
        y = y >> vec.y;
        return *this;
      }

      const vec2i<int>& operator&= ( const vec2i<int>& vec )
      {
        x = x & vec.x;
        y = y & vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator&= ( const vec2i<unsigned>& vec )
      {
        x = x & vec.x;
        y = y & vec.y;
        return *this;
      }

      const vec2i<int>& operator^= ( const vec2i<int>& vec )
      {
        x = x ^vec.x;
        y = y ^vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator^= ( const vec2i<unsigned>& vec )
      {
        x = x ^vec.x;
        y = y ^vec.y;
        return *this;
      }

      const vec2i<int>& operator|= ( const vec2i<int>& vec )
      {
        x = x | vec.x;
        y = y | vec.y;
        return *this;
      }

      const vec2i<unsigned>& operator|= ( const vec2i<unsigned>& vec )
      {
        x = x | vec.x;
        y = y | vec.y;
        return *this;
      }

      const vec2i operator++ ( ) //pre
      {
        ++x;
        ++y;
        return *this;
      }

      const vec2i operator++ ( impl::post )
      {
        vec2i tmp = *this;
        ++( *this );
        return tmp;
      }

      const vec2i operator-- ( ) //pre
      {
        --x;
        --y;
        return *this;
      }

      const vec2i operator-- ( impl::post )
      {
        vec2i tmp = *this;
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
