#pragma once

#include "../mm_vec4_impl.h"
#include "../mm_vec3_impl.h"
#include "../mm_mat2_impl.h"
#include "../mm_mat3_impl.h"
#include "../mm_mat4_impl.h"

namespace mymath
{
	//transforms a position vector by a matrix
	//it also ensures that the last coordinate of the vector will always be one
	//ie. the vector returned will not be in homogenous coordinates
	template< class t >
	MYMATH_INLINE impl::vec4i<t> transform_position(const impl::vec4i<t>& vector, const impl::mat4i<t>& transformation)
	{
		impl::vec4i<t> tmp = transformation * vector;
		if (!impl::is_eq(tmp[tmp.length() - 1], 1.0f)) tmp /= tmp[tmp.length() - 1];
		return tmp;
	}

	//translates a position vector by an other vector
	template< class t >
	MYMATH_INLINE impl::vec4i<t> transform_position(const impl::vec4i<t>& vector, const impl::vec3i<t>& translation)
	{
		return vector + impl::vec4i<t>(transformation, 0);
	}

	//TODO unit test
	//transforms a point by a quaternion (rotation)
	//last coordinate of vector is desired to be one
	template< class t >
	MYMATH_INLINE impl::vec4i<t> transform_position(const impl::vec4i<t>& vector, const impl::quati<t>& rotation)
	{
		assert(is_eq(vector.w, 1));
		return rotate_vector(rotation, vector.xyz);
	}

	//TODO unit test
	//scales a point from origo
	//scaling a point means to change the distance of that point from origo by a factor of "scale"
	//scaling all the points of an object by scale is equivalent to scaling the object by scale.
	//last coordinate of vector is desired to be one
	template< class t >
	MYMATH_INLINE impl::vec4i<t> transform_position(const impl::vec4i<t>& vector, const t& scalar)
	{
		assert(is_eq(vector.w, 1));
		return vector*scalar;
	}

	//transforms a direction vector by a matrix
	//the last coordinate is desired to be zero (the vector represents a direction)
	template< class t >
	MYMATH_INLINE impl::vec4i<t> transform_direction(const impl::vec4i<t>& vector, const impl::mat4i<t>& transformation)
	{
		assert(is_eq(vector.w, 0));
		return transformation * vector;
	}

	//TODO unit test
	//transforms a normal vector by the inverse transpose of a transformation matrix
	//the matrix is assumed to contain the inverse transpose of the transformation
	MYMATH_INLINE impl::vec3i<float> transform_direction(const impl::vec3i<float>& normal, const impl::mat4i<float>& inverse_transpose_transformation)
	{
		return impl::mat3i<float>(inverse_transpose_transformation) * normal;
	}

	//computes the following transformation
	//1) apply a
	//2) apply b
	//takes the transformations themseves as parameters
	template< class t >
	MYMATH_INLINE impl::mat4i<t> concat_transformations(const impl::mat4i<t>& a, const impl::mat4i<t>& b)
	{
		return b * a;
	}

	//TODO unit test
	//computes the following transformation
	//1) apply a
	//2) apply b
	//takes the transformations themseves as parameters
	template< class t >
	MYMATH_INLINE impl::quati<t> concat_transformations(const impl::quati<t>& a, const impl::quati<t>& b)
	{
		return a * b;
	}

	//computes the inverse of the following transformation
	//1) apply a
	//2) apply b
	//takes the inverse of the transformations as parameters
	template< class t >
	MYMATH_INLINE impl::mat4i<t> inv_concat_transformations(const impl::mat4i<t>& inv_a, const impl::mat4i<t>& inv_b)
	{
		return inv_a * inv_b;
	}

	//TODO unit test
	//computes the inverse of the following transformation
	//1) apply a
	//2) apply b
	//takes the inverse of the transformations as parameters
	template< class t >
	MYMATH_INLINE impl::mat4i<t> inv_concat_transformations(const impl::quati<t>& inv_a, const impl::quati<t>& inv_b)
	{
		return inv_b * inv_a;
	}
}
