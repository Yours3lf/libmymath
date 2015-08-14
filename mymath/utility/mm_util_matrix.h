#pragma once

#include "../mm_mat2_impl.h"
#include "../mm_mat3_impl.h"
#include "../mm_mat4_impl.h"

namespace mymath
{
	//TODO unit test
	//this function transforms a position vector by a matrix
	//it also ensures that the last coordinate of the vector will always be one
	//ie. the vector returned will not be in homogenous coordinates
	template< class t, class u >
	MYMATH_INLINE t transform_position( const t& vector, const u& transformation)
	{
		t tmp = transformation * vector;
		if( !impl::is_eq(tmp[tmp.length()-1], 1.0f) ) tmp /= tmp[tmp.length()-1];
		return tmp;
	}

	//TODO unit test
	//this function transforms a direction vector by a matrix
	//it also ensures that the last coordinate of the vector will always be one
	//because the last coordinate is implicitly zero (the vector represents a direction)
	template< class t, class u >
	MYMATH_INLINE t transform_direction( const t& vector, const u& transformation )
	{
		t tmp = transformation * vector;
		return tmp;
	}

	//TODO unit test
	//this function transforms a normal vector by the inverse transpose of a transformation matrix
	//the matrix is assumed to contain the inverse transpose of the transformation
	MYMATH_INLINE impl::vec3i<float> transform_direction( const impl::vec3i<float>& normal, const impl::mat4i<float>& inverse_transpose_transformation )
	{
		return impl::mat3i<float>(inverse_transpose_transformation) * normal;
	}

	//TODO unit test
	//computes the following transformation
	//1) apply a
	//2) apply b
	template< class t >
	MYMATH_INLINE t concat_transformations( const t& a, const t& b )
	{
		return b * a;
	}

	//TODO unit test
	//computes the inverse of the following transformation
	//1) apply a
	//2) apply b
	template< class t >
	MYMATH_INLINE t inv_concat_transformations( const t& inv_a, const t& inv_b )
	{
		return inv_a * inv_b;
	}

	//TODO unit test
	//returns true if the transformation changes the handedness of the coordinate system
	MYMATH_INLINE bool swaps_handedness( const impl::mat4i<float>& transformation )
	{
		return determinant( impl::mat3i<float>(transformation) ) < 0;
	}

	//TODO test
	template< typename t >
	impl::mat4i<t> arbitrary_basis_matrix( const impl::mat4i<t>& x, const impl::mat4i<t>& y, const impl::mat4i<t>& z, const impl::mat4i<t>& origin )
	{
		return impl::mat4i<t> (
			x.x, x.y, x.z, 0,
			y.x, y.y, y.z, 0,
			z.x, z.y, z.z, 0,
			origin.x, origin.y, origin.z, 1
			);
	}
}
