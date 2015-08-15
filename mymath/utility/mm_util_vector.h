#pragma once

#include "../mm_common.h" 
#include "../mm_vec4_impl.h"
#include "../mm_vec3_impl.h"
#include "../mm_vec2_impl.h"
#include "../mm_vec_func.h"

#include <string>

namespace mymath
{
  using namespace impl;

  MYMATH_INLINE float aabb_to_point_distance_squared( const vec3i<float>& min, const vec3i<float>& max, const vec3i<float>& point )
  {
    vec3i<float> mindiff = point - min;
    vec3i<float> maxdiff = point - max;
    mindiff *= mindiff;
    maxdiff *= maxdiff;

    float dist_sqr = 0;
    for( int c = 0; c < 3; ++c )
    {
      if( point[c] < min[c] )
      {
        dist_sqr += mindiff[c];
      }
      else if( point[c] > max[c] )
      {
        dist_sqr += maxdiff[c];
      }
    }

    return dist_sqr;
  }

  MYMATH_INLINE vec3i<float> rotate_vector_by_angle_axis( const vec3i<float>& v, float angle, const vec3i<float>& axis )
  {
    assert( !impl::is_eq( length( axis ), 0 ) ); 
    float a = angle; 
    float s = std::sin( a );
    float c = std::cos( a );
    vec3i<float> av = normalize( axis );
    float xx = av.x * av.x;
    float yy = av.y * av.y;
    float zz = av.z * av.z;
    float xy = av.x * av.y;
    float yz = av.y * av.z;
    float zx = av.z * av.x;
    float xs = av.x * s;
    float ys = av.y * s;
    float zs = av.z * s;
    float oc = 1 - c;
    return vec3i<float>( 
      ( oc * xx + c ) * v.x + ( oc * xy - zs ) * v.y + ( oc * zx + ys ) * v.z,
      ( oc * xy + zs ) * v.x + ( oc * yy + c ) * v.y + ( oc * yz - xs ) * v.z,
      ( oc * zx - ys ) * v.x + ( oc * yz + xs ) * v.y + ( oc * zz + c ) * v.z );
  }

  MYMATH_INLINE bool are_points_near( const vec3i<float>& a, const vec3i<float>& b, float dist )
  {
    vec3i<float> diff = a - b;
    return dot( diff, diff ) < ( dist * dist );
  }

  MYMATH_INLINE float point_to_plane_dist( const vec3i<float>& point, const vec3i<float>& plane_point, const vec3i<float>& plane_normal )
  {
    return dot( (point - plane_point), plane_normal );
  }

  MYMATH_INLINE vec3i<float> project_point_onto_plane( const vec3i<float>& point, const vec3i<float>& plane_base, const vec3i<float>& plane_normal )
  {
    return point - point_to_plane_dist( point, plane_base, plane_normal ) * plane_normal;
  }

  MYMATH_INLINE vec3i<float> project_vector_onto_normal( const vec3i<float>& v, const vec3i<float>& normal )
  {
    return normal * dot( v, normal );
  }

  MYMATH_INLINE vec3i<float> project_vector_onto_plane( const vec3i<float>& v, const vec3i<float>& plane_normal )
  {
    return v - project_vector_onto_normal( v, plane_normal );
  }

  MYMATH_INLINE bool are_normals_nearly_parallel( const vec3i<float>& normal_a, const vec3i<float>& normal_b, float cosine_threshold )
  {
    float cos_normals = dot( normal_a, normal_b );
    return std::abs( cos_normals ) >= cosine_threshold;
  }

  //parallel and point in the same dir
  MYMATH_INLINE bool are_normals_nearly_coincident( const vec3i<float>& normal_a, const vec3i<float>& normal_b, float cosine_threshold )
  {
    float cos_normals = dot( normal_a, normal_b );
    return cos_normals >= cosine_threshold;
  }

  MYMATH_INLINE bool are_normals_nearly_perpendicular( const vec3i<float>& normal_a, const vec3i<float>& normal_b, float cosine_threshold )
  {
    float cos_normals = dot( normal_a, normal_b );
    return std::abs( cos_normals ) <= cosine_threshold;
  }

  MYMATH_INLINE bool are_planes_nearly_coplanar( const vec3i<float>& plane_base_a, const vec3i<float>& plane_normal_a, const vec3i<float>& plane_base_b, const vec3i<float>& plane_normal_b, float threshold )
  {
    if( !are_normals_nearly_parallel( plane_normal_a, plane_normal_b, threshold ) ) return false;
    else if( point_to_plane_dist( plane_base_b, plane_base_a, plane_normal_a ) > 0.1f ) return false;

    return true;
  }

  //returns triple product of three vectors: a dot (b cross c)
  MYMATH_INLINE float triple_product( const vec3i<float>& a, const vec3i<float>& b, const vec3i<float>& c )
  {
    return dot( a, cross( b, c ) );
  }

  MYMATH_INLINE bool are_all_components_equal( const vec3i<float>& v )
  {
    return is_eq( v.x, v.y ) && is_eq( v.x, v.z ) && is_eq( v.y, v.z );
  }

  MYMATH_INLINE float get_max_component( const vec3i<float>& v )
  {
    return max( v.x, max( v.y, v.z ) );
  }

  MYMATH_INLINE float get_abs_max_component( const vec3i<float>& v )
  {
    vec3i<float> tmp = abs( v );
    return max( tmp.x, max( tmp.y, tmp.z ) );
  }

  MYMATH_INLINE float get_min_component( const vec3i<float>& v )
  {
    return min( v.x, min( v.y, v.z ) );
  }

  MYMATH_INLINE float get_abs_min_component( const vec3i<float>& v )
  {
    vec3i<float> tmp = abs( v );
    return min( tmp.x, min( tmp.y, tmp.z ) );
  }

  MYMATH_INLINE bool is_normalized( const vec3i<float>& v )
  {
    return std::abs( 1.0f - length_squared( v ) ) < 0.01f;
  }

  MYMATH_INLINE void get_direction_length( const vec3i<float>& v, vec3i<float>& dir, float& len )
  {
    len = length( v );
    if( len > epsilon )
    {
      dir = v * (1 / len);
    }
    else
    {
      dir = vec3i<float>(0);
    }
  }

  //project v's xy based on z
  MYMATH_INLINE vec3i<float> projection( const vec3i<float>& v )
  {
    return vec3i<float>( v.xy, 1 ) * ( 1.0f / v.z );
  }

  MYMATH_INLINE vec3i<float> snap_to_grid( const vec3i<float>& v, float grid )
  {
    if( is_eq( grid, 0 ) ) return v;

    return floor((v + 0.5f * grid) / grid) * grid;
  }

  MYMATH_INLINE vec3i<float> restrict_to_cube( const vec3i<float>& v, float half_side )
  {
    return clamp( v, -half_side, half_side );
  }

  MYMATH_INLINE vec3i<float> restrict_vector_length( const vec3i<float>& v, float min, float max )
  {
    float size = length( v );
    vec3i<float> vec_dir = v * (1.0f / size);

    size = clamp( size, min, max );

    return vec_dir * size;
  }

  MYMATH_INLINE vec3i<float> add_and_restrict_to_cube( const vec3i<float>& a, const vec3i<float>& b, float half_side )
  {
    return restrict_to_cube( a + b, half_side );
  }

  MYMATH_INLINE bool is_vector_nearly_uniform( const vec3i<float>& v, float threshold )
  {
    return std::abs(v.x - v.y) < threshold && std::abs(v.y - v.z) < threshold;
  }

  MYMATH_INLINE vec3i<float> mirror_vector_by_normal( const vec3i<float>& v, const vec3i<float>& n )
  {
    return v - n * ( 2.0f * dot( v, n ) );
  }

  MYMATH_INLINE vec3i<float> project_vector_onto_vector( const vec3i<float>& a, const vec3i<float>& b )
  {
    return (b * (dot( a, b ) / dot( b, b )));
  }

  template< class t >
  MYMATH_INLINE std::string to_string( const vec2i<t>& v )
  {
    return "( " + std::to_string(v.x) + ", " + std::to_string(v.y) + " )";
  }

  template< class t >
  MYMATH_INLINE std::string to_string( const vec3i<t>& v )
  {
    return "( " + std::to_string( v.x ) + ", " + std::to_string( v.y ) + ", " + std::to_string( v.z ) + " )";
  }

  template< class t >
  MYMATH_INLINE std::string to_string( const vec4i<t>& v )
  {
    return "( " + std::to_string( v.x ) + ", " + std::to_string( v.y ) + ", " + std::to_string( v.z ) + ", " + std::to_string( v.w ) + " )";
  }

  template< class t >
  MYMATH_INLINE std::ostream& operator<< ( std::ostream& output, const mm::impl::vec2i<t>& vec )
  {
    return output << to_string( vec ) << std::endl;
  }

  template< class t >
  MYMATH_INLINE std::ostream& operator<< ( std::ostream& output, const mm::impl::vec3i<t>& vec )
  {
    return output << to_string( vec ) << std::endl;
  }

  template< class t >
  MYMATH_INLINE std::ostream& operator<< ( std::ostream& output, const mm::impl::vec4i<t>& vec )
  {
    return output << to_string( vec ) << std::endl;
  }

  MYMATH_INLINE vec2i<float> convert_normal_to_spherical_coordinates( const vec3i<float>& n )
  {
    float theta = std::acos( n.z / length( n ) );
    float phi = std::atan2( n.y, n.x );
    return vec2i<float>( theta, phi );
  }

  MYMATH_INLINE float get_heading_angle( const vec3i<float>& v )
  {
    //project onto z plane
    vec3i<float> plane_dir = v;
    plane_dir.z = 0;
    plane_dir = normalize( plane_dir );

    float angle = std::acos(plane_dir.x);

    if( plane_dir.y < 0.0f )
    {
      angle *= -1.0f;
    }

    return angle;
  }
}