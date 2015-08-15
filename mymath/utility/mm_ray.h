#pragma once

#include "../mm_vec3_impl.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED ray : public shape
	{
		typedef impl::vec3i<float> vec3;
	public:
		//define a ray by origin and direction
		vec3 origin, direction;

		static int get_class_idx()
		{
			static int idx = 0;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		ray( const vec3& o = vec3( 0 ), const vec3& d = vec3( 0, 0, -1 ) ) : origin( o ), direction( d )
		{
		}
	};
}
