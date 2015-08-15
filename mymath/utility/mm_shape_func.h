#include "mm_shape.h"

namespace mymath
{
	void shape::set_up_intersection()
	{
		const int num_shapes = 7;

		//order doesnt matter
		_is_on_right_side.set_elements( num_shapes );
		_is_on_right_side.add<sphere, plane>( inner::is_on_right_side_sp );
		_is_on_right_side.add<aabb, plane>( inner::is_on_right_side_ap );
		_is_on_right_side.add<plane, sphere>( inner::is_on_right_side_ps );
		_is_on_right_side.add<plane, aabb>( inner::is_on_right_side_pa );

		/////////////
		_is_intersecting.set_elements( num_shapes );
		_is_intersecting.add<aabb, aabb>( inner::is_intersecting_aa );
		_is_intersecting.add<aabb, sphere>( inner::is_intersecting_as );
		_is_intersecting.add<aabb, ray>( inner::is_intersecting_ar );
		_is_intersecting.add<aabb, frustum>( inner::is_intersecting_af );
		_is_intersecting.add<aabb, plane>( inner::is_intersecting_ap );

		_is_intersecting.add<plane, aabb>( inner::is_intersecting_pa );
		_is_intersecting.add<plane, sphere>( inner::is_intersecting_ps );
		_is_intersecting.add<plane, ray>( inner::is_intersecting_pr );
		_is_intersecting.add<plane, plane>( inner::is_intersecting_pp );

		_is_intersecting.add<sphere, aabb>( inner::is_intersecting_sa );
		_is_intersecting.add<sphere, sphere>( inner::is_intersecting_ss );
		_is_intersecting.add<sphere, ray>( inner::is_intersecting_sr );
		_is_intersecting.add<sphere, frustum>( inner::is_intersecting_sf );
		_is_intersecting.add<sphere, plane>( inner::is_intersecting_sp );

		_is_intersecting.add<frustum, aabb>( inner::is_intersecting_fa );
		_is_intersecting.add<frustum, sphere>( inner::is_intersecting_fs );
		//_is_intersecting.add<frustum, frustum>( inner::is_intersecting_ff ); //TODO

		_is_intersecting.add<ray, aabb>( inner::is_intersecting_ra );
		_is_intersecting.add<ray, sphere>( inner::is_intersecting_rs );
		_is_intersecting.add<ray, triangle>( inner::is_intersecting_rt );
		_is_intersecting.add<ray, plane>( inner::is_intersecting_rp );

		_is_intersecting.add<triangle, ray>( inner::is_intersecting_tr );

		//order matters
		_is_inside.set_elements( num_shapes );
		_is_inside.add<aabb, aabb>( inner::is_inside_aa );
		_is_inside.add<aabb, sphere>( inner::is_inside_as );
		_is_inside.add<sphere, aabb>( inner::is_inside_sa );
		_is_inside.add<sphere, sphere>( inner::is_inside_ss );
		_is_inside.add<point, aabb>( inner::is_inside_poa );

		_intersect.set_elements( num_shapes  );
		_intersect.add<aabb, ray>( inner::intersect_ar );
		_intersect.add<ray, aabb>( inner::intersect_ra );
		_intersect.add<plane, ray>( inner::intersect_pr );
		_intersect.add<ray, plane>( inner::intersect_rp );
		_intersect.add<sphere, ray>( inner::intersect_sr );
		_intersect.add<ray, sphere>( inner::intersect_rs );
		//_intersect.add<triangle, ray>( inner::intersect_tr ); //TODO
		//_intersect.add<triangle, ray>( inner::intersect_rt );

		//usage
		//is_on_the_right_side.go(new aabb(), new sphere());

		is_setup = true;
	}
}
