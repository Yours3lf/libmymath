#ifndef mm_fvec4_impl_h
#define mm_fvec4_impl_h

#include "mm_common.h"
#include "mm_fvec2_impl.h"
#include "mm_fvec3_impl.h"

#include "mm_vec4_impl.h"

namespace mymath
{
  namespace impl
  {
    template<>
    class vec4i < float >
    {
    private:
      template< int at, int bt, int ct, int dt >
      class swizzle
      {
      private:
        __m128 v;
      public:
#ifndef MYMATH_FAST_COMPILE
        //For cases like swizzle = vec2 and swizzle = swizzle
        const vec4i& operator=( const vec4i& other )
        {
          v = _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, dt ) );
          return *( vec4i* )this;
        }

        //For cases like swizzle *= vec2 and swizzle *= swizzle
        const vec4i& operator*=( const vec4i& other )
        {
          v = _mm_mul_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, dt ) ) );
          return *( vec4i* )this;
        }

        const vec4i& operator/=( const vec4i& other ) //needs notEqual defined elsewhere
        {
          assert( !is_eq(other.x, 0) && !is_eq(other.y, 0) && !is_eq(other.z, 0) && !is_eq(other.w, 0) );
          vec4i<float>* tmp = (vec4i<float>*)this;
          tmp->d = _mm_div_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, dt ) ) );
          return *( vec4i<float>* )this;
        }

        const vec4i& operator+=( const vec4i& other )
        {
          v = _mm_add_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, dt ) ) );
          return *( vec4i* )this;
        }

        const vec4i& operator-=( const vec4i& other )
        {
          v = _mm_sub_ps( v, _mm_shuffle_ps( other.d, other.d, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, dt ) ) );
          return *( vec4i* )this;
        }
#endif

        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, ct, dt ) ) );
        }
      };

      template<int at>
      class swizzle < at, at, at, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, at, at ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < bt, at, at, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, at, at, at ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, bt, at, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, at, at ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, at, bt, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, bt, at ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, at, at, bt >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, at, bt ) ) );
        }
      };

      template<int at, int bt, int ct>
      class swizzle < bt, ct, at, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, ct, at, at ) ) );
        }
      };

      template<int at, int bt, int ct>
      class swizzle < bt, at, ct, at >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, at, ct, at ) ) );
        }
      };

      template<int at, int bt, int ct>
      class swizzle < bt, at, at, ct >
      {
      private:
        __m128 v;
      public:
        operator vec4i() const
        {
          return vec4i( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, at, at, ct ) ) );
        }
      };

      //vec3 swizzlers
      template<int at>
      class swizzle < at, at, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i<float>() const
        {
          return vec3i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < bt, at, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i<float>() const
        {
          return vec3i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( bt, at, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, bt, at, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i<float>() const
        {
          return vec3i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, at, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, at, bt, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec3i<float>() const
        {
          return vec3i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, bt, 0 ) ) );
        }
      };

      template<int at, int bt, int ct> //3 component
      class swizzle < at, bt, ct, -3 >
      {
      private:
        __m128 v;
      public:
#ifndef MYMATH_FAST_COMPILE
        //For cases like swizzle = vec2 and swizzle = swizzle
        const vec3i<float>& operator=( const vec3i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, v, MYMATH_SHUFFLE( 0, 1, 6-at-bt-ct, 6-at-bt-ct ) );
          __m128 m = _mm_shuffle_ps( other.d, v, MYMATH_SHUFFLE( 2, 3, 6-at-bt-ct, 6-at-bt-ct ) );
          l = _mm_shuffle_ps( l, m, MYMATH_SHUFFLE(0, 1, 0, 2) );
          v = _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 6 - at - bt - ct ) );
          return *( vec3i<float>* )this;
        }

        //For cases like swizzle *= vec2 and swizzle *= swizzle
        const vec3i<float>& operator*=( const vec3i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, 6-at-bt-ct, 6-at-bt-ct ) );
          __m128 m = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 2, 3, 6-at-bt-ct, 6-at-bt-ct ) );
          l = _mm_shuffle_ps( l, m, MYMATH_SHUFFLE(0, 1, 0, 2) );
          v = _mm_mul_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 6 - at - bt - ct ) ) );
          return *( vec3i<float>* )this;
        }

        const vec3i<float>& operator/=( const vec3i<float>& other )
        {
          assert( !impl::is_eq( other.x, ( float )0 ) && !impl::is_eq( other.y, ( float )0 ) && !impl::is_eq( other.z, ( float )0 ) );
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, 6-at-bt-ct, 6-at-bt-ct ) );
          __m128 m = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 2, 3, 6-at-bt-ct, 6-at-bt-ct ) );
          l = _mm_shuffle_ps( l, m, MYMATH_SHUFFLE(0, 1, 0, 2) );
          v = _mm_div_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 6 - at - bt - ct ) ) );
          return *( vec3i<float>* )this;
        }

        const vec3i<float>& operator+=( const vec3i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, 6-at-bt-ct, 6-at-bt-ct ) );
          __m128 m = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 2, 3, 6-at-bt-ct, 6-at-bt-ct ) );
          l = _mm_shuffle_ps( l, m, MYMATH_SHUFFLE(0, 1, 0, 2) );
          v = _mm_add_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 6 - at - bt - ct ) ) );
          return *( vec3i<float>* )this;
        }

        const vec3i<float>& operator-=( const vec3i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, 6-at-bt-ct, 6-at-bt-ct ) );
          __m128 m = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 2, 3, 6-at-bt-ct, 6-at-bt-ct ) );
          l = _mm_shuffle_ps( l, m, MYMATH_SHUFFLE(0, 1, 0, 2) );
          v = _mm_sub_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, ct, 6 - at - bt - ct ) ) );
          return *( vec3i<float>* )this;
        }

#endif
        operator vec3i<float>() const
        {
          return vec3i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, ct, 0 ) ) );
        }
      };

      //vec2 swizzlers
      template<int at>
      class swizzle < at, at, -2, -3 >
      {
      private:
        __m128 v;
      public:
        operator vec2i<float>() const
        {
          return vec2i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, at, 0, 0 ) ) );
        }
      };

      template<int at, int bt>
      class swizzle < at, bt, -2, -3 > //2 component
      {
      private:
        __m128 v;
      public:
#ifndef MYMATH_FAST_COMPILE
#define MM_SECOND_COMPONENT() ( 6-at-bt > 3 ? 3 : 6-at-bt )
#define MM_FIRST_COMPONENT() ( 6-at-bt-MM_SECOND_COMPONENT() )

        static_assert( MM_FIRST_COMPONENT() < 4 && MM_FIRST_COMPONENT() > -1, "first component must be in range" );
        static_assert( MM_SECOND_COMPONENT() < 4 && MM_SECOND_COMPONENT() > -1, "second component must be in range" );
        static_assert( MM_FIRST_COMPONENT() < MM_SECOND_COMPONENT(), "first must be smaller" );

        //For cases like swizzle = vec2 and swizzle = swizzle
        const vec2i<float>& operator=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, v, MYMATH_SHUFFLE( 0, 1, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          v = _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          return *( vec2i<float>* )this;
        }

        //For cases like swizzle *= vec2 and swizzle *= swizzle
        const vec2i<float>& operator*=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          v = _mm_mul_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator/=( const vec2i<float>& other )
        {
          assert( other.x != ( float )0 && other.y != ( float )0 );
          __m128 l = _mm_shuffle_ps( other.d, impl::one, MYMATH_SHUFFLE( 0, 1, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          v = _mm_div_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator+=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          v = _mm_add_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) ) );
          return *( vec2i<float>* )this;
        }

        const vec2i<float>& operator-=( const vec2i<float>& other )
        {
          __m128 l = _mm_shuffle_ps( other.d, impl::zero, MYMATH_SHUFFLE( 0, 1, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) );
          v = _mm_sub_ps( v, _mm_shuffle_ps( l, l, MM_SHUFFLE_SWIZZLE_HELPER( at, bt, MM_FIRST_COMPONENT(), MM_SECOND_COMPONENT() ) ) );
          return *( vec2i<float>* )this;
        }

#endif
        operator vec2i<float>() const
        {
          return vec2i<float>( _mm_shuffle_ps( v, v, MYMATH_SHUFFLE( at, bt, 0, 0 ) ) );
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
#ifdef __GNUC__  //g++
#pragma GCC diagnostic pop
#endif

      vec4i( const float& at, const float& bt, const float& ct, const float& dt ) : x( at ), y( bt ), z( ct ), w( dt )
      {
      }
      vec4i( const vec3i<float>& vec, const float& num )
      {
        *this = vec.xyzz; w = num;
      }
      vec4i( const float& num, const vec3i<float>& vec )
      {
        *this = vec.xxyz; x = num;
      }
      vec4i( const vec2i<float>& vec, const float& num1, const float& num2 )
      {
        *this = vec.xyyy; z = num1; w = num2;
      }
      vec4i( const float& num1, const vec2i<float>& vec, const float& num2 )
      {
        *this = vec.xxyy; x = num1; w = num2;
      }
      vec4i( const float& num1, const float& num2, const vec2i<float>& vec )
      {
        *this = vec.xxxy; x = num1; y = num2;
      }
      vec4i( const vec2i<float>& at, const vec2i<float>& bt )
      {
        d = _mm_shuffle_ps( at.d, bt.d, MYMATH_SHUFFLE( 0, 1, 0, 1 ) );
      }
#if MYMATH_STRICT_GLSL == 1
      explicit
#endif
        vec4i( const float& num )
      {
        d = _mm_set1_ps( num );
      }
      vec4i( const __m128& num ) : d( num )
      {
      }
      //vec4i() { d = impl::zero; }
      vec4i()
      {
      }
      vec4i( const vec4i<int>& v )
      {
        x = v.x; y = v.y; z = v.z; w = v.w;
      }
      vec4i( const vec4i<unsigned>& v )
      {
        x = v.x; y = v.y; z = v.z; w = v.w;
      }

      vec4i( std::initializer_list<float> list )
      {
        assert( list.size() == 4 );

        x = *( list.begin() + 0 );
        y = *( list.begin() + 1 );
        z = *( list.begin() + 2 );
        w = *( list.begin() + 3 );
      }

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

      const vec4i& operator*= ( const vec4i& vec )
      {
        d = _mm_mul_ps( d, vec.d );
        return *this;
      }

      const vec4i& operator/= ( const vec4i& vec ) //needs notEqual defined elsewhere
      {
        assert( !is_eq( vec.x, 0 ) && !is_eq( vec.y, 0 ) && !is_eq( vec.z, 0 ) && !is_eq( vec.w, 0 ) );
        vec4i<float>* tmp = ( vec4i<float>* )this;
        tmp->d = _mm_div_ps( tmp->d, vec.d );
        return *this;
      }

      const vec4i& operator+= ( const vec4i& vec )
      {
        d = _mm_add_ps( d, vec.d );
        return *this;
      }

      const vec4i& operator-= ( const vec4i& vec )
      {
        d = _mm_sub_ps( d, vec.d );
        return *this;
      }

      const vec4i operator++ ( ) //pre
      {
        d = _mm_add_ps( d, impl::one );
        return *this;
      }

      const vec4i operator++ ( impl::post )
      {
        vec4i tmp = *this;
        ++( *this );
        return tmp;
      }

      const vec4i operator-- ( ) //pre
      {
        d = _mm_sub_ps( d, impl::one );
        return *this;
      }

      const vec4i operator-- ( impl::post )
      {
        vec4i tmp = *this;
        --( *this );
        return tmp;
      }

      const unsigned int length() const
      {
        return 4;
      }
    };
  }
}

#endif
