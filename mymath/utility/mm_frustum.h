#pragma once

#include "../mm_camera.h"
#include "../mm_vec3_impl.h"
#include "../mm_vec4_impl.h"
#include "../mm_mat4_impl.h"
#include "mm_shape.h"
#include "mm_plane.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED frustum : public shape
	{
		typedef impl::vec4i<float> vec4;

	public:
		plane planes[6];
		vec4 points[8];

		enum which_plane
		{
			PLANE_TOP = 0, PLANE_BOTTOM, PLANE_LEFT, PLANE_RIGHT, PLANE_NEAR, PLANE_FAR
		};

		enum which_point
		{
			NTL = 0, NTR, NBL, NBR, FTL, FTR, FBL, FBR
		};

		static int get_class_idx()
		{
			static int idx = 5;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		frustum()
		{}

		void set_up( const camera<float>& cam, const impl::mat4i<float>& inv_viewproj )
		{
			std::vector<vec4> tmp_points;
			tmp_points.reserve(8);

			get_frustum_corners( tmp_points, inv_viewproj );
			memcpy( &points[0].x, &tmp_points[0].x, tmp_points.size() * sizeof(vec4) );

			planes[PLANE_TOP].set_up( points[NTR].xyz, points[NTL].xyz, points[FTL].xyz );
			planes[PLANE_BOTTOM].set_up( points[NBL].xyz, points[NBR].xyz, points[FBR].xyz );
			planes[PLANE_LEFT].set_up( points[NTL].xyz, points[NBL].xyz, points[FBL].xyz );
			planes[PLANE_RIGHT].set_up( points[NBR].xyz, points[NTR].xyz, points[FBR].xyz );
			planes[PLANE_NEAR].set_up( points[NTL].xyz, points[NTR].xyz, points[NBR].xyz );
			planes[PLANE_FAR].set_up( points[FTR].xyz, points[FTL].xyz, points[FBL].xyz );
		}

		void get_vertices( std::vector<vec4>& v ) const
		{
			//top
			v.push_back( points[NTL] );
			v.push_back( points[NTR] );
			v.push_back( points[FTR] );

			v.push_back( points[NTL] );
			v.push_back( points[FTR] );
			v.push_back( points[FTL] );

			//bottom
			v.push_back( points[NBL] );
			v.push_back( points[FBL] );
			v.push_back( points[FBR] );

			v.push_back( points[NBL] );
			v.push_back( points[FBR] );
			v.push_back( points[NBR] );

			//left
			v.push_back( points[NTL] );
			v.push_back( points[FTL] );
			v.push_back( points[NBL] );

			v.push_back( points[NBL] );
			v.push_back( points[FTL] );
			v.push_back( points[FBL] );

			//right
			v.push_back( points[NTR] );
			v.push_back( points[NBR] );
			v.push_back( points[FTR] );

			v.push_back( points[NBR] );
			v.push_back( points[FBR] );
			v.push_back( points[FTR] );

			//near
			v.push_back( points[NBL] );
			v.push_back( points[NTR] );
			v.push_back( points[NTL] );

			v.push_back( points[NBL] );
			v.push_back( points[NBR] );
			v.push_back( points[NTR] );

			//far
			v.push_back( points[FTL] );
			v.push_back( points[FTR] );
			v.push_back( points[FBR] );

			v.push_back( points[FTR] );
			v.push_back( points[FBR] );
			v.push_back( points[FBL] );
		}
	};
}