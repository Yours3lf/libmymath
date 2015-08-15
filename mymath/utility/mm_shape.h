#pragma once

#include "mm_dispatcher.h"
#include "../mm_vec2_impl.h"

namespace mymath
{
	//generic abstract shape class
	//needed so that any shape can intersect any other shape
	class shape
	{
		typedef impl::vec4i<float> vec4;
		typedef impl::vec3i<float> vec3;
		typedef impl::vec2i<float> vec2;

		static dispatcher<shape*, shape*, bool> _is_on_right_side;
		static dispatcher<shape*, shape*, bool> _is_inside;
		static dispatcher<shape*, shape*, bool> _is_intersecting;
		static dispatcher<shape*, shape*, vec2> _intersect;
		static bool is_setup;
		public:
		static void set_up_intersection();

		bool is_on_right_side( shape* s )
		{
			assert( is_setup );
			return _is_on_right_side.go( this, s );
		}

		bool is_inside( shape* s )
		{
			assert( is_setup );
			return _is_inside.go( this, s );
		}

		//x: min, y: max intersection
		vec2 intersect( shape* s )
		{
			assert( is_setup );
			return _intersect.go( this, s );
		}

		bool is_intersecting( shape* s )
		{
			assert( is_setup );
			return _is_intersecting.go( this, s );
		}

		virtual int get_class_index() const = 0;
	};

	dispatcher<shape*, shape*, bool> shape::_is_on_right_side;
	dispatcher<shape*, shape*, bool> shape::_is_inside;
	dispatcher<shape*, shape*, bool> shape::_is_intersecting;
	dispatcher<shape*, shape*, vec2 > shape::_intersect;
	bool shape::is_setup = false;
}
