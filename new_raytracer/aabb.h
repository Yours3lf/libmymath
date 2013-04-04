#ifndef aabb_h
#define aabb_h

#include "globals.h"

class aabb
{
  private:
  protected:
  public:
    vec3 pos, size;

    bool intersect_box( const aabb& box )
    {
      vec3 v2 = box.pos + box.size;
      vec3 v4 = pos + size;

      return v4.x > box.pos.x &&
             pos.x < v2.x &&
             v4.y > box.pos.y &&
             pos.y < v2.y &&
             v4.z > box.pos.z &&
             pos.z < v2.z;
    }

    bool contains( const vec3& p )
    {
      vec3 v2 = pos + size;
      return p.x > ( pos.x - fepsilon ) &&
             p.x < ( v2.x + fepsilon ) &&
             p.y > ( pos.y - fepsilon ) &&
             p.y < ( v2.y + fepsilon ) &&
             p.z > ( pos.z - fepsilon ) &&
             p.z < ( v2.z + fepsilon );
    }

    aabb() {}

    aabb( const vec3& p, const vec3& s )
    {
      pos = p;
      size = s;
    }
};

#endif
