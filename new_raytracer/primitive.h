#ifndef primitive_h
#define primitive_h

#include "globals.h"

#include "material.h"
#include "ray.h"
#include "aabb.h"

class primitive
{
  private:
  protected:
  public:
    enum prim_type
    {
      BOX, PLANE, SPHERE
    };

    bool light;
    material mat;
    int ray_id;
    prim_type type;
    int id;

    virtual int intersect( const ray& r, float& dist ) = 0;
    virtual bool intersect_box( const aabb& box ) = 0;
    virtual vec3 get_normal( const vec3& pos ) = 0;
    virtual aabb get_aabb() = 0;
    virtual vec3 get_color( const vec3& )
    {
      return mat.diffuse_color;
    }

    primitive()
    {
      light = false;
      ray_id = -1;
      id = -1;
    }
};

#endif
