#ifndef ray_h
#define ray_h

#include "globals.h"

class ray
{
private:
protected:
public:
  vec3 origin, direction;
  int ray_id;

  ray()
  {
  }

  ray( const vec3& o, const vec3& d, int id )
  {
    origin = o;
    direction = d;
    ray_id = id;
  }
};

#endif
