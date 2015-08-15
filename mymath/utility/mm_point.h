#pragma once

#include "../mm_vec3_impl.h"
#include "mm_shape.h"

namespace mymath
{

	class MM_16_BYTE_ALIGNED point : public shape
	{
		typedef impl::vec3i<float> vec3;
	public:
		vec3 pos;

		static int get_class_idx( )
		{
			static int idx = 0;
			return idx;
		}

		int get_class_index( ) const
		{
			return get_class_idx( );
		}

		point( const vec3& p ) : pos(p) {}
	};

}
