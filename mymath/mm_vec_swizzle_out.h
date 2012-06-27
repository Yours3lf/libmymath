#ifndef mm_vec_swizzle_out_h
#define mm_vec_swizzle_out_h

#include "mm_common.h"
#include "mm_vec2_impl.h"
#include "mm_vec3_impl.h"
#include "mm_vec4_impl.h"

namespace mymath
{
  namespace impl
  {
    //vec3 swizzlers for vec2
    template<typename t>
    template<int a>
    class vec2i<t>::swizzle < a, a, a, -3 >
    {
      private:
        t v[2];
      public:
        operator vec3i<t>()
        {
          return vec3i<t>( v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle < b, a, a, -3 >
    {
      private:
        t v[2];
      public:
        operator vec3i<t>()
        {
          return vec3i<t>( v[b], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle < a, b, a, -3 >
    {
      private:
        t v[2];
      public:
        operator vec3i<t>()
        {
          return vec3i<t>( v[a], v[b], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle < a, a, b, -3 >
    {
      private:
        t v[2];
      public:
        operator vec3i<t>()
        {
          return vec3i<t>( v[a], v[a], v[b] );
        }
    };

    //vec4 swizzlers for vec2
    template<typename t>
    template<int a>
    class vec2i<t>::swizzle<a, a, a, a>
    {
      private:
        t v[2];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle<b, a, a, a>
    {
      private:
        t v[2];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[b], v[a], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle<a, b, a, a>
    {
      private:
        t v[2];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[b], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle<a, a, b, a>
    {
      private:
        t v[2];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[a], v[b], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec2i<t>::swizzle<a, a, a, b>
    {
      private:
        t v[2];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[a], v[a], v[b] );
        }
    };

    //vec4 swizzlers for vec3
    template<typename t>
    template<int a>
    class vec3i<t>::swizzle<a, a, a, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec3i<t>::swizzle<b, a, a, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[b], v[a], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec3i<t>::swizzle<a, b, a, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[b], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec3i<t>::swizzle<a, a, b, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[a], v[b], v[a] );
        }
    };

    template<typename t>
    template<int a, int b>
    class vec3i<t>::swizzle<a, a, a, b>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[a], v[a], v[a], v[b] );
        }
    };

    template<typename t>
    template<int a, int b, int c>
    class vec3i<t>::swizzle<b, c, a, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[b], v[c], v[a], v[a] );
        }
    };

    template<typename t>
    template<int a, int b, int c>
    class vec3i<t>::swizzle<b, a, c, a>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[b], v[a], v[c], v[a] );
        }
    };

    template<typename t>
    template<int a, int b, int c>
    class vec3i<t>::swizzle<b, a, a, c>
    {
      private:
        t v[3];
      public:
        operator vec4i<t>()
        {
          return vec4i<t>( v[b], v[a], v[a], v[c] );
        }
    };
  }
}

#endif
