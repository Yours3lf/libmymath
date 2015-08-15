#pragma once

#include "../mm_camera.h"
#include "../mm_vec3_impl.h"
#include "../mm_vec4_impl.h"
#include "../mm_mat4_impl.h"

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
			TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR
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
		{
		}

		void set_up( const camera<float>& cam, const frame<float>& f )
		{
			std::vector<vec4> tmp_points;
			tmp_points.reserve(8);

			get_frustum_corners( tmp_points, mymath::inverse( f.projection_matrix * cam.get_matrix() ) );
			memcpy( &points[0].x, &tmp_points[0].x, tmp_points.size() * sizeof(vec4) );

			planes[TOP].set_up( ntr, ntl, ftl );
			planes[BOTTOM].set_up( nbl, nbr, fbr );
			planes[LEFT].set_up( ntl, nbl, fbl );
			planes[RIGHT].set_up( nbr, ntr, fbr );
			planes[NEAR].set_up( ntl, ntr, nbr );
			planes[FAR].set_up( ftr, ftl, fbl );
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