#ifndef mm_quat_func_h
#define mm_quat_func_h

#include "mm_quat_impl.h"

template<typename ty>
mymath::impl::quati<ty> operator*(const mymath::impl::quati<ty>& p, const mymath::impl::quati<ty>& q)
{
  const mymath::impl::vec3i<ty> pv = p.xyz;
  const ty ps = p.w;
  const mymath::impl::vec3i<ty> qv = q.xyz;
  const ty qs = q.w;

  return mymath::impl::vec4i<ty>(ps * qv + qs * pv + mymath::cross(pv, qv),
      ps * qs - mymath::dot(pv, qv));
}

template<typename ty>
mymath::impl::quati<ty> operator*(const mymath::impl::quati<ty>& p, const ty& num)
{
  return p.value * num;
}

template<typename ty>
mymath::impl::quati<ty> operator/(const mymath::impl::quati<ty>& q, const ty& num)
{
  return q.value / num;
}

template<typename ty>
mymath::impl::quati<ty> operator+(const mymath::impl::quati<ty>& q1, const mymath::impl::quati<ty>& q2)
{
  return q1.value + q2.value;
}

namespace mymath
{
  template<typename ty>
  impl::quati<ty> conjugate(const impl::quati<ty>& q)
  {
    impl::vec4i<t> t = q.value;
    t.xyz = -t.xyz;
    return t;
  }

  template<typename ty>
  impl::quati<ty> inverse(const impl::quati<ty>& q)
  {
    return conjugate(q) / dot_helper(q.value, q.value);
  }

  template<typename ty>
  impl::quati<ty> normalize(const impl::quati<ty>& q)
  {
    return normalize(q.value);
  }

  template<typename ty>
  ty norm(const impl::quati<ty>& q)
  {
    return length(q.value);
  }

  template<typename ty>
  impl::mat3i<ty> mat3_cast(const impl::quati<ty>& q)
  {
    vec4 tmp1 = q.value.yyxx * q.value.yxzz * vec4(2) * vec4(-1, 1, 1, 1);
    vec4 tmp2 = q.value.zzyy * q.value.zwww * vec4(2) * vec4(-1, -1, 1, 1);
    tmp1 = tmp1 + tmp2 + vec4(1, 0, 0, 0);

    vec4 tmp3 = q.value.xxyy * q.value.yxzz * vec4(2) * vec4(1, -1, 1, 1);
    vec4 tmp4 = q.value.zzxx * q.value.wzww * vec4(2) * vec4(1, -1, -1, 1);
    tmp3 = tmp3 + tmp4 + vec4(0, 1, 0, 0);

    vec4 tmp5 = q.value.xyxx * q.value.zzxx * vec4(2) * vec4(1, 1, -1, 1);
    vec4 tmp6 = q.value.yxyy * q.value.wwyy * vec4(2) * vec4(-1, 1, -1, 1);
    tmp5 = tmp5 + tmp6 + vec4( 0, 0, 1, 0 );

    return mat3( tmp1.xyz, tmp3.xyz, tmp5.xyz);
  }

  template<typename ty>
  impl::mat4i<ty> mat4_cast(const impl::quati<ty>& q)
  {
    return impl::mat4i<ty>(mat3_cast<ty>(q));
  }

  ///This function does a linear interpolation
  ///
  template<typename ty>
  impl::quati<ty> mix(const impl::quati<ty>& q1, const impl::quati<ty>& q2, const ty& t)
  {
    return normalize(q1*(1-t)+q2*t);
  }

  template<typename ty>
  impl::quati<ty> slerp(const impl::quati<ty>& q1, const impl::quati<ty>& q2, const ty& t)
  {
    float theta = acos( dot( q1, q2 ) );
    float sintheta = sin( theta );
    float wp = sin( (1 - t) * theta ) / sintheta;
    float wq = sin( t * theta ) / sin( theta );
    return wp * q1 + wq * q2;
  }

  //TODO SLOW
  template<typename ty>
  impl::quati<ty> quat_cast(const impl::mat3i<ty>& m)
  {
    ty trace = m[0][0] + m[1][1] + m[2][2];

    impl::quati<ty> result;

    //If the trace of the matrix is greater than zero, then the result is
    if (trace > 0)
    {
      /* X = ( m21 - m12 ) * S
       * Y = ( m02 - m20 ) * S
       * Z = ( m10 - m01 ) * S
       * our matrices are column-major so the indexing is reversed
       */

      ty s = 0.5 / std::sqrt(trace + 1);
      result.value.w = 0.25 / s;
      result.value.x = (m[1][2] - m[2][1]) * s;
      result.value.y = (m[2][0] - m[0][2]) * s;
      result.value.z = (m[0][1] - m[1][0]) * s;
    }
    else
    {
      if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
      {
        ty s = 2 * std::sqrt(1 + m[0][0] - m[1][1] - m[2][2]);

        result.value.w = (m[1][2] - m[2][1]) / s;
        result.value.x = 0.25 * s;
        result.value.y = (m[1][0] + m[0][1]) / s;
        result.value.z = (m[2][0] + m[0][2]) / s;
      }
      else if (m[1][1] > m[2][2])
      {
        ty s = 2 * std::sqrt(1 + m[1][1] - m[0][0] - m[2][2]);

        result.value.w = (m[2][0] - m[0][2]) / s;
        result.value.x = (m[1][0] + m[0][1]) / s;
        result.value.y = 0.25 * s;
        result.value.z = (m[2][1] + m[1][2]) / s;
      }
      else
      {
        ty s = 2 * std::sqrt(1 + m[2][2] - m[0][0] - m[1][1]);

        result.value.w = (m[0][1] - m[1][0]) / s;
        result.value.x = (m[2][0] + m[0][2]) / s;
        result.value.y = (m[2][1] + m[1][2]) / s;
        result.value.z = 0.25 * s;
      }
    }

    return result;
  }

  template<typename ty>
  impl::quati<ty> quat_cast(const impl::mat4i<ty>& m)
  {
    return quat_cast(impl::mat3i < ty > (m));
  }

  //angle in radians!
  template<typename ty>
  impl::quati<ty> rotate(const impl::quati<ty>& q, const ty& angle, const impl::vec3i<ty>& axis)
  {
    return q * impl::quati<ty>(angle, axis);
  }

  template<typename ty>
  impl::vec3i<ty> rotate_vector(const impl::quati<ty>& q, const impl::vec3i<ty>& v)
  {
    impl::quati<ty> v_quat = impl::quati < ty > (impl::vec4i < ty > (v, 0));

    v_quat = q * v_quat * inverse(q);
    return v_quat.vector();
  }
}

#endif
