#pragma once

#include "../mm_common.h"
#include "../mm_mat4_impl.h"
#include "../mm_vec3_impl.h"
#include "../mm_vec4_impl.h"
#include "mm_shape.h"
#include "mm_sphere.h"
#include "mm_util_matrix.h"
#include "mm_util_transform.h"

namespace mymath
{
	class MM_16_BYTE_ALIGNED aabb : public shape
	{
		typedef impl::vec4i<float> vec4;
		typedef impl::vec3i<float> vec3;
		typedef impl::mat4i<float> mat4;
	public:
		vec3 min, max; //minimum/maximum apex of the aabb

		vec3 get_extents() const
		{
			return abs( max - min ) * 0.5;
		}

		vec3 get_pos() const
		{
			return min + get_extents();
		}

		static int get_class_idx()
		{
			static int idx = 4;
			return idx;
		}

		int get_class_index() const
		{
			return get_class_idx();
		}

		float surface_area()
		{
			vec3 delta = max - min;
			return 2 * (delta.x * delta.y + delta.y * delta.z + delta.x * delta.z);
		}

		float volume()
		{
			vec3 delta = max - min;
			return delta.x * delta.y * delta.z;
		}

		//returns the axis on which the aabb is the biggest
		int dominating_axis()
		{
			vec3 diag = max - min;
			
			if( diag.x > diag.y && diag.x > diag.z )
			return 0; //x axis
			else if( diag.y > diag.z )
			return 1; //y axis
			else
			return 2; //z axis
		}

		//return relative to the min (0) and max (1)
		//where a point is in the aabb
		vec3 offset( const vec3& p )
		{
			vec3 mindiff = p - min;
			vec3 minmaxdiff = max - min;
			return mindiff / minmaxdiff;
		}

		sphere bounding_sphere()
		{
			sphere s;
			s.set_center( (min + max) * 0.5f );
			s.set_radius( distance( s.get_center(), max ) );
			return s;
		}

		static aabb transform(const aabb& ab, const mat4& transformation)
		{
			aabb tmp;
			static std::vector< vec3 > v;
			v.clear();
			ab.get_points( v );
			
			for( auto& c : v )
			{
			tmp.expand( transform_position( vec4( c, 1 ), transformation ).xyx );
			}

			return tmp;
		}

		//fills v with the 8 points of the aabb
		void get_points( std::vector<vec3>& v ) const
		{
			v.push_back( vec3( min.x, min.y, min.z ) );
			v.push_back( vec3( min.x, min.y, max.z ) );
			v.push_back( vec3( min.x, max.y, min.z ) );
			v.push_back( vec3( min.x, max.y, max.z ) );
			v.push_back( vec3( max.x, min.y, min.z ) );
			v.push_back( vec3( max.x, min.y, max.z ) );
			v.push_back( vec3( max.x, max.y, min.z ) );
			v.push_back( vec3( max.x, max.y, max.z ) );
		}

		//returns the vertices of the triangles of the aabb in counter clockwise order
		void get_triangles( std::vector<vec3>& v ) const
		{
			//left
			v.push_back( vec3( min.x, max.yz ) );
			v.push_back( vec3( min.x, max.y, min.z ) );
			v.push_back( vec3( min.xyz ) );

			v.push_back( vec3( min.xyz ) );
			v.push_back( vec3( min.xy, max.z ) );
			v.push_back( vec3( min.x, max.yz ) );

			//front
			v.push_back( vec3( min.xy, max.z ) );
			v.push_back( vec3( max.x, min.y, max.z ) );
			v.push_back( vec3( max.xyz ) );

			v.push_back( vec3( max.xyz ) );
			v.push_back( vec3( min.x, max.yz ) );
			v.push_back( vec3( min.xy, max.z ) );

			//right
			v.push_back( vec3( max.xy, min.z ) );
			v.push_back( vec3( max.xyz ) );
			v.push_back( vec3( max.x, min.y, max.z ) );

			v.push_back( vec3( max.x, min.y, max.z ) );
			v.push_back( vec3( max.x, min.yz ) );
			v.push_back( vec3( max.xy, min.z ) );

			//back
			v.push_back( vec3( max.xy, min.z ) );
			v.push_back( vec3( max.x, min.yz ) );
			v.push_back( vec3( min.xyz ) );

			v.push_back( vec3( min.xyz ) );
			v.push_back( vec3( min.x, max.y, min.z ) );
			v.push_back( vec3( max.xy, min.z ) );

			//top
			v.push_back( vec3( min.x, max.y, min.z ) );
			v.push_back( vec3( min.x, max.yz ) );
			v.push_back( vec3( max.xyz ) );

			v.push_back( vec3( max.xyz ) );
			v.push_back( vec3( max.xy, min.z ) );
			v.push_back( vec3( min.x, max.y, min.z ) );

			//bottom
			v.push_back( vec3( max.x, min.y, max.z ) );
			v.push_back( vec3( min.xy, max.z ) );
			v.push_back( vec3( min.xyz ) );

			v.push_back( vec3( min.xyz ) );
			v.push_back( vec3( max.x, min.yz ) );
			v.push_back( vec3( max.x, min.y, max.z ) );
		}

		vec3 get_pos_vertex( const vec3& n ) const
		{
			vec3 res = min;

			if( n.x >= 0 )
			res.x = max.x;

			if( n.y >= 0 )
			res.y = max.y;

			if( n.z >= 0 )
			res.z = max.z;

			return res;
		}

		void expand( const vec3& p )
		{
			min = mymath::min( min, p );
			max = mymath::max( max, p );
		}

		vec3 get_neg_vertex( const vec3& n ) const
		{
			vec3 res = max;

			if( n.x >= 0 )
			res.x = min.x;

			if( n.y >= 0 )
			res.y = min.y;

			if( n.z >= 0 )
			res.z = min.z;

			return res;
		}

		void reset_minmax()
		{
			min = vec3( FLT_MAX );
			max = vec3( -FLT_MAX );
		}

		aabb()
		{
			reset_minmax();
		}

		aabb( const vec3& p, const vec3& e )
		{
			min = p - e;
			max = p + e;
		}
	};
}
