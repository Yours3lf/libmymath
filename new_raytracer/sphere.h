#ifndef sphere_h
#define sphere_h

#include "globals.h"

#include "primitive.h"

class sphere : public primitive
{
  private:
  protected:
  public:
    vec3 center;
    float radius, square_radius, inv_radius;
    vec3 vn, ve, vc;

    vec3 get_normal( const vec3& pos )
    {
      //get the vector from the center to the point on the sphere
      //divide by radius to normalize
      return ( pos - center ) * vec3( inv_radius );
    }

    int intersect( const ray& r, float& dist )
    {
#if COUNT_INTERSECTIONS == 1
      ++intersections;
#endif
      //get vector from center to ray origin
      vec3 v = r.origin - center;
      //get the angle between the ray direction and the vector to the sphere center
      //negate is needed, because it is in opposite direction
      float b = -dot( v, r.direction );
      //b squared - v's length squared + radius squared
      float det = b * b - dot( v, v ) + square_radius;

      if( det > 0 )
      {
        det = std::sqrt( det );
        float i1 = b - det;
        float i2 = b + det;

        if( i2 > 0 )
        {
          if( i1 < 0 )
          {
            if( i2 < dist )
            {
              dist = i2;
              return inside;
            }
          }
          else
          {
            if( i1 < dist )
            {
              dist = i1;
              return hit;
            }
          }
        }
      }

      return miss;
    }

    bool intersect_box( const aabb& box )
    {
      float dmin = 0;
      vec3 v2 = box.pos + box.size;

      if( center.x < box.pos.x )
      {
        dmin += ( center.x - box.pos.x ) * ( center.x - box.pos.x );
      }
      else if( center.x > v2.x )
      {
        dmin += ( center.x - v2.x ) * ( center.x - v2.x );
      }

      if( center.y < box.pos.y )
      {
        dmin += ( center.y - box.pos.y ) * ( center.y - box.pos.y );
      }
      else if( center.y > v2.y )
      {
        dmin += ( center.y - v2.y ) * ( center.y - v2.y );
      }

      if( center.z < box.pos.z )
      {
        dmin += ( center.z - box.pos.z ) * ( center.z - box.pos.z );
      }
      else if( center.z > v2.z )
      {
        dmin += ( center.z - v2.z ) * ( center.z - v2.z );
      }

      return ( dmin <= square_radius );
    }

    aabb get_aabb()
    {
      return aabb( center - vec3( radius ), vec3( radius * 2 ) );
    }

    vec3 get_color( const vec3& p )
    {
      vec3 result;

      if( !mat.tex )
      {
        result = mat.diffuse_color;
      }
      else
      {
        vec3 vp = ( p - center ) * vec3( inv_radius );
        float phi = std::acos( -dot( vp, vn ) );
        vec2 uv;
        uv.y = phi * mat.inv_uvscale.y * ( 1.0f / pi );
        float theta = std::acos( dot( ve, vp ) / std::sin( phi ) ) * ( 2.0f / pi );

        if( dot( vc, vp ) >= 0 )
        {
          uv.x = ( 1.0f - theta ) * mat.inv_uvscale.x;
        }
        else
        {
          uv.x = theta * mat.inv_uvscale.x;
        }

        result = mat.tex->get_texel( uv ) * mat.diffuse_color;
      }

      return result;
    }

    sphere()
    {
      type = SPHERE;
    }

    sphere( const vec3& c, float r )
    {
      type = SPHERE;
      center = c;
      radius = r;
      square_radius = r * r;
      inv_radius = 1.0f / r;
      vn = vec3( 0, 1, 0 );
      ve = vec3( 1, 0, 0 );
      vc = cross( vn, ve );
    }
};

#endif
