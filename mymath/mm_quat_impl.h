#ifndef mm_quat_impl_h
#define mm_quat_impl_h

//class declaration only
namespace mymath
{
  namespace impl
  {
	template<typename ty>
	class quati;
  }
}

#include "mm_vec3_impl.h"
#include "mm_vec4_impl.h"
#include "mm_vec_func.h"

#include "mm_mat3_impl.h"
#include "mm_mat4_impl.h"

#include <cmath>
#include <math.h>

//TODO replace scalar operations w/ vector
namespace mymath
{
  namespace impl
  {
	template<typename ty>
	class quati
	{
	  typedef vec4i<ty> type_vec4;
	  typedef vec3i<ty> type_vec3;

	public:

	  //value=(qv, qs) where qv is a 3d vector and qs is a scalar
	  //value.xyz is the vector and value.w is the scalar part
	  type_vec4 value;

	  quati():value(0, 0, 0, 1){} //no rotation
	  quati(const type_vec4& vec) : value(vec){}
	  quati(const type_vec3& vector, const ty& scalar) : value(vector, scalar){}
	  
    quati(const mat3i<ty>& m)
	  {
		  value = quat_cast(m).value;
	  }

	  quati(const mat4i<ty>& m)
	  {
		  value = quat_cast(m).value;
	  }

	  quati(const ty& angle, const type_vec3& axis)
	  {
      float a = angle * 0.5;
      float s, c;
      sincosf(a, &s, &c);
      value = type_vec4(normalize(axis) * s, c);
    }

	  //Grassman product
	  const quati& operator*=(const quati& other)
	  {
		  const type_vec3&	pv = value.xyz;
		  const ty&			ps = value.w;
		  const type_vec3&	qv = other.xyz;
		  const ty&			qs = other.w;

		  *this = type_vec4(type_vec3(ps * qv + qs * pv + cross(pv, qv)),
			ps * qs - dot(pv, qv));

		  return *this;
	  }
	};
  }
}

#endif /* mm_quat_impl_h */
