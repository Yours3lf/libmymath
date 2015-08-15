#pragma once

#include "../mm_mat2_impl.h"
#include "../mm_mat3_impl.h"
#include "../mm_mat4_impl.h"

namespace mymath
{
	#define MYMATH_UNPROJECT_FUNC(t) \
	MYMATH_INLINE impl::vec3i<t> unproject( const impl::vec3i<t>& ndc_pos, const impl::mat4i<t>& inv_mvp ) \
	{ \
		impl::vec4i<t> obj_space = inv_mvp * impl::vec4i<t>( ndc_pos, 1 ); \
		return obj_space.xyz / obj_space.w; \
	}

	#define MYMATH_CREATEROTATION_FUNC(t) \
	MYMATH_INLINE impl::mat4i<t> create_rotation( const t& angle, const impl::vec3i<t>& vec ) \
	{ \
		assert( !impl::is_eq( length( vec ), (t)0 ) ); \
		t a = angle; \
		t s = std::sin( a ); \
		t c = std::cos( a ); \
		impl::vec3i<t> v = normalize( vec ); \
		t xx = v.x * v.x; \
		t yy = v.y * v.y; \
		t zz = v.z * v.z; \
		t xy = v.x * v.y; \
		t yz = v.y * v.z; \
		t zx = v.z * v.x; \
		t xs = v.x * s; \
		t ys = v.y * s; \
		t zs = v.z * s; \
		t oc = ( t )1 - c; \
		return impl::mat4i<t>( oc * xx + c, oc * xy + zs, oc * zx - ys, 0, \
								oc * xy - zs, oc * yy + c, oc * yz + xs, 0, \
								oc * zx + ys, oc * yz - xs, oc * zz + c, 0, \
								0, 0, 0, 1 ); \
	}

	#define MYMATH_CREATESCALE_FUNC(t) \
	MYMATH_INLINE impl::mat4i<t> create_scale( const impl::vec3i<t>& vec ) \
	{ return impl::mat4i<t>( vec.x, 0, 0, 0, \
							0, vec.y, 0, 0, \
							0, 0, vec.z, 0, \
							0, 0, 0, 1); }

	#define MYMATH_CREATETRANSLATION_FUNC(t) \
	MYMATH_INLINE impl::mat4i<t> create_translation( const impl::vec3i<t>& vec ) \
	{ return impl::mat4i<t>( 1, 0, 0, 0, \
							0, 1, 0, 0, \
							0, 0, 1, 0, \
							vec.x, vec.y, vec.z, 1 ); }

	MYMATH_UNPROJECT_FUNC(float)
	MYMATH_CREATEROTATION_FUNC(float)
	MYMATH_CREATESCALE_FUNC(float)
	MYMATH_CREATETRANSLATION_FUNC(float)

	template< typename t >
	MYMATH_INLINE impl::mat4i<t> perspective(const t& fovy, const t& aspect, const t& near, const t& far)
	{
		t top = near * std::tan(fovy * (t)0.5);
		t bottom = -top;
		t left = bottom * aspect;
		t right = -left;
		impl::mat4i<t> r = mat4::identity;
		r[0].x = ((t)2 * near) / (right - left);
		r[1].y = ((t)2 * near) / (top - bottom);
		r[2].x = (right + left) / (right - left);
		r[2].y = (top + bottom) / (top - bottom);
		r[2].z = -(far + near) / (far - near);
		r[2].w = -(t)1;
		r[3].z = -((t)2 * far * near) / (far - near);
		r[3].w = (t)0;
		return r;
	}

	template< typename t >
	MYMATH_INLINE impl::mat4i<t> ortographic(const t& left, const t& right, const t& bottom, const t& top, const t& near, const t& far)
	{
		impl::mat4i<t> r = mat4::identity;
		r[0].x = (t)2 / (right - left);
		r[1].y = (t)2 / (top - bottom);
		r[2].z = -(t)2 / (far - near);
		r[3].x = -((right + left) / (right - left));
		r[3].y = -((top + bottom) / (top - bottom));
		r[3].z = -((far + near) / (far - near));
		r[3].w = (t)1;
		return r;
	}

	//this function transforms a position vector by a matrix
	//it also ensures that the last coordinate of the vector will always be one
	//ie. the vector returned will not be in homogenous coordinates
	template< class t, class u >
	MYMATH_INLINE t transform_position(const t& vector, const u& transformation)
	{
		t tmp = transformation * vector;
		if (!impl::is_eq(tmp[tmp.length() - 1], 1.0f)) tmp /= tmp[tmp.length() - 1];
		return tmp;
	}

	//this function transforms a direction vector by a matrix
	//it also ensures that the last coordinate of the vector will always be one
	//because the last coordinate is implicitly zero (the vector represents a direction)
	template< class t, class u >
	MYMATH_INLINE t transform_direction(const t& vector, const u& transformation)
	{
		t tmp = transformation * vector;
		return tmp;
	}

	//TODO unit test
	//this function transforms a normal vector by the inverse transpose of a transformation matrix
	//the matrix is assumed to contain the inverse transpose of the transformation
	MYMATH_INLINE impl::vec3i<float> transform_direction(const impl::vec3i<float>& normal, const impl::mat4i<float>& inverse_transpose_transformation)
	{
		return impl::mat3i<float>(inverse_transpose_transformation) * normal;
	}

	//computes the following transformation
	//1) apply a
	//2) apply b
	template< class t >
	MYMATH_INLINE t concat_transformations(const t& a, const t& b)
	{
		return b * a;
	}

	//computes the inverse of the following transformation
	//1) apply a
	//2) apply b
	template< class t >
	MYMATH_INLINE t inv_concat_transformations(const t& inv_a, const t& inv_b)
	{
		return inv_a * inv_b;
	}

	//returns true if the transformation changes the handedness of the coordinate system
	MYMATH_INLINE bool swaps_handedness(const impl::mat4i<float>& transformation)
	{
		return determinant(impl::mat3i<float>(transformation)) < 0;
	}

	template< typename t >
	impl::mat4i<t> arbitrary_basis_matrix(const impl::vec3i<t>& x, const impl::vec3i<t>& y, const impl::vec3i<t>& z, const impl::vec3i<t>& origin = impl::vec3i<t>(0, 0, 0))
	{
		return impl::mat4i<t>(
			x.x, x.y, x.z, 0,
			y.x, y.y, y.z, 0,
			z.x, z.y, z.z, 0,
			origin.x, origin.y, origin.z, 1
			);
	}
}
