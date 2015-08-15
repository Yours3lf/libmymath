#pragma once

#include "../mm_vec3_impl.h"
#include "../mm_vec4_impl.h"
#include "mm_shape.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED sphere : public shape
	{
		typedef impl::vec4i<float> vec4;
		typedef impl::vec3i<float> vec3;
		
		//define a sphere by a center (xyz) and a radius (w)
		vec4 data;
	public:

		void set_center( const vec3& c )
		{
			data = vec4( c, data.w );
		}

		vec3 get_center() const
		{
			return data.xyz;
		}

		void set_radius( float r )
		{
			data = vec4( data.xyz, r );
		}

		float get_radius() const
		{
			return data.w;
		}

		static int get_class_idx()
		{
			static int idx = 2;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		sphere( const vec3& c = vec3( 0 ), float r = float() ) : data( c, r )
		{
		}
	};
}
