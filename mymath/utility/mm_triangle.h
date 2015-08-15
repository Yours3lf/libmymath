#pragma once

#include "../mm_vec3_impl.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED triangle : public shape
	{
		typedef impl::vec4i<float> vec4;
		typedef impl::vec3i<float> vec3;
		
	public:
		//define a triangle by three points
		vec3 k, l, m;

		static int get_class_idx()
		{
			static int idx = 1;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		triangle( const vec3& kk = vec3( 0 ), const vec3& ll = vec3( 0 ), const vec3& mm = vec3( 0 ) ) : k( kk ), l( ll ), m( mm )
		{
		}
	};
}
