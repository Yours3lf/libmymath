#ifndef plane_h
#define plane_h

#include "globals.h"

#include "primitive.h"

class plane : public primitive
{
  private:
  protected:
  public:
    vec3 normal;
    float point;
    vec3 uaxis, vaxis;

    vec3 get_normal( const vec3& pos )
    {
      return normal;
    }

    int intersect( const ray& r, float& dist )
    {
#if COUNT_INTERSECTIONS == 1
      ++intersections;
#endif
      float d = dot( normal, r.direction );

      if( d != 0.0f )
      {
        float dist2 = -( dot( normal, r.origin ) + point ) / d;

        if( dist2 > 0 )
        {
          if( dist2 < dist )
          {
            dist = dist2;
            return hit;
          }
        }
      }

      return miss;
    }

    bool intersect_box( const aabb& box )
    {
      vec3 v[2];
      v[0] = box.pos, v[1] = box.pos + box.size;

      int side1 = 0, side2 = 0;

      for( int c = 0; c < 8; ++c )
      {
        vec3 p( v[c & 1].x, v[( c >> 1 ) & 1].y, v[( c >> 2 ) & 1].z );

        if( ( dot( p, normal ) + point ) < 0 )
        {
          ++side1;
        }
        else
        {
          ++side2;
        }
      }

      if( side1 == 0 || side2 == 0 )
      {
        return false;
      }
      else
      {
        return true;
      }
    }

    vec3 get_color( const vec3& p )
    {
      vec3 result;

      if( mat.tex )
      {
        vec2 uv;
        uv.x = dot( p, uaxis ) * mat.uvscale.x;
        uv.y = dot( p, vaxis ) * mat.uvscale.y;
        result = mat.tex->get_texel( uv ) * mat.diffuse_color;
      }
      else
      {
        result = mat.diffuse_color;
      }

      return result;
    }

    aabb get_aabb()
    {
      return aabb( vec3( -10000 ), vec3( 20000 ) );
    }

    plane()
    {
      type = PLANE;
    }

    plane( const vec3& n, float p )
    {
      type = PLANE;
      normal = n;
      point = p;
      uaxis = vec3( n.y, n.z, -n.x );
      vaxis = cross( uaxis, n );
    }
};

#endif
