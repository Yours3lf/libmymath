#ifndef mm_quat_impl_h
#define mm_quat_impl_h

#include "mm_vec3_impl.h"
#include "mm_vec4_impl.h"
#include "mm_vec_func.h"

#include "mm_mat3_impl.h"
#include "mm_mat4_impl.h"

#include <cmath>

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
	  quati(const type_vec4& vec):value(vec){}
	  quati(const type_vec3& vec):value(vec, 0){}

	  quati(const ty& angle, const type_vec3& axis) :
		  value(normalize(axis) * std::sin(angle / 2), std::cos(angle / 2))
	  {}

	  type_vec3 vector() const
	  {
		return value.xyz;
	  }
	  const ty& scalar() const
	  {
		return value.w;
	  }

	  //Grassman product
	  const quati& operator*=(const quati& other)
	  {
		const type_vec3&	pv = this->vector();
		const ty&			ps = this->scalar();
		const type_vec3&	qv = other.vector();
		const ty&			qs = other.scalar();

		*this = type_vec4(type_vec3(ps * qv + qs * pv + cross(pv, qv)),
			ps * qs - dot(pv, qv));

		return *this;
	  }
	};
  }
}

#endif /* mm_quat_impl_h */
