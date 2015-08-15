#pragma once

#include "mm_aabb.h"
#include "mm_dispatcher.h"
#include "mm_frustum.h"
#include "mm_plane.h"
#include "mm_point.h"
#include "mm_ray.h"
#include "mm_shape.h"
#include "mm_sphere.h"
#include "mm_triangle.h"

#include <vector>

#ifndef FLT_MAX
#define FLT_MAX 3.402823466e+38
#endif

#define INVALID (FLT_MAX)

//haxx
#ifdef _WIN32
#undef FAR
#endif

namespace mymath
{
	namespace inner
	{
		//only tells if the sphere is on the right side of the plane!
		static bool is_on_right_side_sp(shape* aa, shape* bb)
		{
			auto a = static_cast<sphere*>(aa);
			auto b = static_cast<plane*>(bb);

			float dist = b->distance(a->get_center());
			//dist + radius == how far is the sphere from the plane (usable when we want to do lod using the near plane)

			return dist >= -a->get_radius();
		}

		static bool is_on_right_side_ps(shape* aa, shape* bb)
		{
			return is_on_right_side_sp(bb, aa);
		}

		//only tells if the sphere is on the right side of the plane!
		static bool is_on_right_side_ap(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<plane*>(bb);

			return b->distance(a->get_pos_vertex(b->get_normal())) >= 0;
		}

		static bool is_on_right_side_pa(shape* aa, shape* bb)
		{
			return is_on_right_side_ap(bb, aa);
		}

		static bool is_intersecting_ss(shape* aa, shape* bb)
		{
			auto a = static_cast<sphere*>(aa);
			auto b = static_cast<sphere*>(bb);

			impl::vec3i<float> diff = a->get_center() - b->get_center();
			float dist = mm::dot(diff, diff);

			float rad_sum = b->get_radius() + a->get_radius();

			return dist <= rad_sum * rad_sum; //squared distance check
		}

		//checks if a sphere intersects a plane
		static bool is_intersecting_sp(shape* aa, shape* bb)
		{
			auto a = static_cast<sphere*>(aa);
			auto b = static_cast<plane*>(bb);

			float dist = b->distance(a->get_center());

			return std::abs(dist) <= a->get_radius();
		}

		static bool is_intersecting_ps(shape* aa, shape* bb)
		{
			return is_intersecting_sp(bb, aa);
		}

		static bool is_intersecting_pp(shape* aa, shape* bb)
		{
			auto a = static_cast<plane*>(aa);
			auto b = static_cast<plane*>(bb);

			impl::vec3i<float> vector = mm::cross(a->get_normal(), b->get_normal());

			//if the cross product yields a null vector
			//then the angle is either 0 or 180
			//that is the two normals are parallel
			// sin(alpha) = 0
			// ==> |a| * |b| * sin(alpha) = 0
			return !mm::all(mm::equal(vector, impl::vec3i<float>(0)));
		}

		static bool is_intersecting_aa(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<aabb*>(bb);

			impl::vec3i<float> t = b->get_pos() - a->get_pos();

			impl::vec3i<float> aextent = a->get_extents();
			impl::vec3i<float> bextent = b->get_extents();

			impl::vec3i<float> abs_t = abs(t);
			impl::vec3i<float> a_plus_b = aextent + bextent;

			return mm::all(mm::lessThanEqual(abs_t, a_plus_b));
		}

		static bool is_intersecting_as(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<sphere*>(bb);

			//square distance check between spheres and aabbs
			impl::vec3i<float> vec = b->get_center() - mm::clamp(a->get_pos() + (b->get_center() - a->get_pos()), a->min, a->max);

			float sqlength = mm::dot(vec, vec);

			return sqlength <= b->get_radius() * b->get_radius();
		}

		static bool is_intersecting_sa(shape* aa, shape* bb)
		{
			return is_intersecting_as(bb, aa);
		}

		static bool is_intersecting_ap(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<plane*>(bb);

			impl::vec3i<float> p = a->get_pos_vertex(b->get_normal());
			impl::vec3i<float> n = a->get_neg_vertex(b->get_normal());

			float dist_p = b->distance(p);
			float dist_n = b->distance(n);

			return !((dist_n > 0 && dist_p > 0) ||
				(dist_n < 0 && dist_p < 0));
		}

		static bool is_intersecting_pa(shape* aa, shape* bb)
		{
			return is_intersecting_ap(bb, aa);
		}

		static bool is_intersecting_fs(shape* aa, shape* bb)
		{
			auto a = static_cast<frustum*>(aa);

			for (int c = 0; c < 6; ++c)
			{
				if (!is_on_right_side_ps(&a->planes[c], bb))
					return false;
			}

			return true;
		}

		static bool is_intersecting_sf(shape* aa, shape* bb)
		{
			return is_intersecting_fs(bb, aa);
		}

		static bool is_intersecting_fa(shape* aa, shape* bb)
		{
			auto a = static_cast<frustum*>(aa);
			auto b = static_cast<aabb*>(bb);

			for (int c = 0; c < 6; ++c)
			{
				if (!bb->is_on_right_side(&a->planes[c]))
					return false;
			}

			return true;
		}

		static bool is_intersecting_af(shape* aa, shape* bb)
		{
			return is_intersecting_fa(bb, aa);
		}

		//is a inside b?
		static bool is_inside_sa(shape* aa, shape* bb)
		{
			auto a = static_cast<sphere*>(aa);
			auto b = static_cast<aabb*>(bb);

			impl::vec3i<float> spheremax = a->get_center() + a->get_radius();
			impl::vec3i<float> spheremin = a->get_center() - a->get_radius();

			return (mm::all(mm::lessThanEqual(spheremax, b->max)) && mm::all(mm::greaterThanEqual(spheremin, b->min)));
		}

		//is a inside b?
		static bool is_inside_as(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<sphere*>(bb);

			impl::vec3i<float> minvec = a->min - b->get_center();
			impl::vec3i<float> maxvec = a->max - b->get_center();
			float sqrmaxlength = mm::dot(maxvec, maxvec);
			float sqrminlength = mm::dot(minvec, minvec);
			float sqrradius = b->get_radius() * b->get_radius();

			return (sqrmaxlength <= sqrradius && sqrminlength <= sqrradius);
		}

		//is a inside b?
		static bool is_inside_aa(shape* aa, shape* bb)
		{
			auto a = static_cast<aabb*>(aa);
			auto b = static_cast<aabb*>(bb);

			return (mm::all(mm::greaterThanEqual(a->min, b->min)) && mm::all(mm::lessThanEqual(a->max, b->max)));
		}

		//is a inside b?
		static bool is_inside_ss(shape* aa, shape* bb)
		{
			auto a = static_cast<sphere*>(aa);
			auto b = static_cast<sphere*>(bb);

			impl::vec3i<float> spheredist = b->get_center() - a->get_center();

			return (mm::dot(spheredist, spheredist) <= b->get_radius() * b->get_radius());
		}

		static bool is_intersecting_rt(shape* aa, shape* bb)
		{
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<triangle*>(bb);

			impl::vec3i<float> e = b->k - b->m;
			impl::vec3i<float> f = b->l - b->m;

			impl::vec3i<float> g = a->origin - b->m;

			//apply barycentric triangle math
			float t = 1.0f / mm::dot(mm::cross(a->direction, f), e);
			impl::vec3i<float> tkl = t * impl::vec3i<float>(mm::dot(mm::cross(g, e), f),
				mm::dot(mm::cross(a->direction, f), g),
				mm::dot(mm::cross(g, e), a->direction));

			//barycentric coordinate check
			//if between 0...1 the point is inside
			return tkl.y > 0 && tkl.z > 0 && (tkl.y + tkl.z) < 1;
		}

		static mm::vec2 intersect_rt(shape* aa, shape* bb)
		{
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<triangle*>(bb);

			//klm
			//TODO http://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
		}

		static bool is_intersecting_tr(shape* aa, shape* bb)
		{
			return is_intersecting_rt(bb, aa);
		}

		static impl::vec2i<float> intersect_tr(shape* aa, shape* bb)
		{
			return intersect_rt(bb, aa);
		}

		static bool is_intersecting_rs(shape* aa, shape* bb)
		{
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<sphere*>(bb);

			impl::vec3i<float> diff = b->get_center() - a->origin;
			float dist = mm::dot(diff, diff) - (b->get_radius() * b->get_radius());

			if (dist <= 0)
				return true;

			float dist2 = mm::dot(a->direction, diff);

			if (dist2 >= 0)
				return false;

			return (dist2 * dist2 - dist) >= 0;
		}

		static impl::vec2i<float> intersect_rs(shape* aa, shape* bb)
		{ //we assume ray dir is a unit vector
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<sphere*>(bb);

			impl::vec3i<float> x = a->origin - b->get_center();

			float bbb = mm::dot(a->direction, x) * 2;
			float ccc = mm::dot(x, x) - b->get_radius() * b->get_radius();

			float sqr = bbb * bbb - 4 * ccc;

			if (sqr > 0)
			{
				float root = std::sqrt(sqr);
				float inv_2a = 0.5f;

				float t1 = (-bbb - root) * inv_2a;
				float t2 = (-bbb + root) * inv_2a;

				if (t1 < 0)
				{
					if (t2 < 0)
					{
						return INVALID;
					}
					else
					{
						return impl::vec2i<float>(t2, t1);
					}
				}
				else
				{
					return impl::vec2i<float>(t1, t2);
				}
			}

			return INVALID;
		}

		static bool is_intersecting_sr(shape* aa, shape* bb)
		{
			return is_intersecting_rs(bb, aa);
		}

		static impl::vec2i<float> intersect_sr(shape* aa, shape* bb)
		{
			return intersect_rs(bb, aa);
		}

		static bool is_intersecting_ra(shape* aa, shape* bb)
		{
			aabb* ab = static_cast<aabb*>(bb);
			ray* r = static_cast<ray*>(aa);
			impl::vec3i<float> invR;

			// compute intersection of ray with all six bbox planes
#ifdef _DEBUG
			//in debug mode, pay attention to asserts
			for (int c = 0; c < 3; ++c)
			{
				if (mm::impl::is_eq(r->direction[c], 0))
				{
					invR[c] = FLT_MAX;
				}
				else
				{
					invR[c] = 1.0f / r->direction[c];
				}
			}
#else
			//in release mode we dgaf about div by zero
			invR = 1.0f / r->direction;
#endif

			impl::vec3i<float> tbot = invR * (ab->min - r->origin);
			impl::vec3i<float> ttop = invR * (ab->max - r->origin);

			// re-order intersections to find smallest and largest on each axis
			impl::vec3i<float> tmin = mm::min(ttop, tbot);
			impl::vec3i<float> tmax = mm::max(ttop, tbot);

			// find the largest tmin and the smallest tmax
			float largest_tmin = mm::max(mm::max(tmin.x, tmin.y), mm::max(tmin.x, tmin.z));
			float smallest_tmax = mm::min(mm::min(tmax.x, tmax.y), mm::min(tmax.x, tmax.z));

			return smallest_tmax > largest_tmin;
		}

		static impl::vec2i<float> intersect_ra(shape* aa, shape* bb)
		{
			aabb* ab = static_cast<aabb*>(bb);
			ray* r = static_cast<ray*>(aa);
			impl::vec3i<float> invR;

			// compute intersection of ray with all six bbox planes
#ifdef _DEBUG
			//in debug mode, pay attention to asserts
			for (int c = 0; c < 3; ++c)
			{
				if (mm::impl::is_eq(r->direction[c], 0))
				{
					invR[c] = FLT_MAX;
				}
				else
				{
					invR[c] = 1.0f / r->direction[c];
				}
			}
#else
			//in release mode we dgaf about div by zero
			invR = 1.0f / r->direction;
#endif

			impl::vec3i<float> tbot = invR * (ab->min - r->origin);
			impl::vec3i<float> ttop = invR * (ab->max - r->origin);

			// re-order intersections to find smallest and largest on each axis
			impl::vec3i<float> tmin = mm::min(ttop, tbot);
			impl::vec3i<float> tmax = mm::max(ttop, tbot);

			// find the largest tmin and the smallest tmax
			float largest_tmin = mm::max(mm::max(tmin.x, tmin.y), mm::max(tmin.x, tmin.z));
			float smallest_tmax = mm::min(mm::min(tmax.x, tmax.y), mm::min(tmax.x, tmax.z));

			return smallest_tmax > largest_tmin ? (largest_tmin >= 0 ? impl::vec2i<float>(largest_tmin, smallest_tmax) : impl::vec2i<float>(smallest_tmax, largest_tmin)) : INVALID;
		}

		static bool is_intersecting_ar(shape* aa, shape* bb)
		{
			return is_intersecting_ra(bb, aa);
		}

		static impl::vec2i<float> intersect_ar(shape* aa, shape* bb)
		{
			return intersect_ra(bb, aa);
		}

		static bool is_intersecting_rp(shape* aa, shape* bb)
		{
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<plane*>(bb);

			float denom = mm::dot(a->direction, b->get_normal());

			if (!mm::impl::is_eq(denom, 0.0f))
			{
				float t = mm::dot(b->get_point() - a->origin, b->get_normal());
				float tmp = t * denom;

				if (tmp > 0.0f)
				{
					return true;
				}
			}

			return false;
		}

		static impl::vec2i<float> intersect_rp(shape* aa, shape* bb)
		{
			auto a = static_cast<ray*>(aa);
			auto b = static_cast<plane*>(bb);

			float denom = mm::dot(a->direction, b->get_normal());

			if (!mm::impl::is_eq(denom, 0.0f))
			{
				float t = mm::dot(b->get_point() - a->origin, b->get_normal());
				float tmp = t * denom;

				if (tmp > 0.0f)
				{
					return t / denom;
				}
			}

			return INVALID;
		}

		static bool is_intersecting_pr(shape* aa, shape* bb)
		{
			return is_intersecting_rp(bb, aa);
		}

		static impl::vec2i<float> intersect_pr(shape* aa, shape* bb)
		{
			return intersect_rp(bb, aa);
		}

		static bool is_inside_poa(shape* aa, shape* bb)
		{
			auto a = static_cast<point*>(aa);
			auto b = static_cast<aabb*>(bb);

			return mm::all(mm::lessThanEqual(a->pos, b->max)) && mm::all(mm::greaterThanEqual(a->pos, b->min));
		}
	}
}
