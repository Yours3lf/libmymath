#pragma once

#include "../mm_vec3_impl.h"
#include "../mm_vec4_impl.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED plane : public shape
	{
		typedef impl::vec4i<float> vec4;
		typedef impl::vec3i<float> vec3;
		
		vec4 data; //xyz: point on plane, w: cache -(normal dot point)
		vec3 normal; //normal vector pointing out of the plane
	public:

		vec3 get_point() const
		{
			return data.xyz;
		}

		void set_point( const vec3& p )
		{
			data = vec4( p, data.w );
		}

		float get_minus_n_dot_p() const
		{
			return data.w;
		}

		void set_minus_n_dot_p( float f )
		{
			data = vec4( data.xyz, f );
		}

		vec3 get_normal() const
		{
			return normal;
		}

		void set_normal( const vec3& n )
		{
			normal = n;
		}

		static int get_class_idx()
		{
			static int idx = 3;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		//define a plane by 3 points
		void set_up( const vec3& a, const vec3& b, const vec3& c )
		{
			vec3 tmp1, tmp2;

			tmp1 = a - b;
			tmp2 = c - b;

			normal = normalize( cross( tmp2, tmp1 ) );
			data = vec4( a, -dot( normal, a ) );
		}

		//signed distance
		float distance( const vec3& p )
		{
			return get_minus_n_dot_p() + dot( normal, p );
		}

		//define a plane by a normal and a point
		plane( const vec3& n = vec3( 0 ), const vec3& p = vec3( 0 ) ) : normal( n )
		{
			data = vec4( p, -dot( n, p ) );
		}

		plane( const vec3& a, const vec3& b, const vec3& c )
		{
			set_up( a, b, c );
		}
	};
	
}

