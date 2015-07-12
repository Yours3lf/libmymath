#ifndef material_h
#define material_h

#include "globals.h"

#include "texture.h"

class material
{
private:
protected:
public:
  vec3 diffuse_color;
  float reflectivity, refractivity, diffuse_coeff, specular_coeff, refraction_index, diffuse_reflectivity;
  texture* tex;
  vec2 uvscale, inv_uvscale;

  material()
  {
    diffuse_color = vec3( 0.2f );
    reflectivity = 0;
    diffuse_coeff = 0.2f;
    specular_coeff = 0.8f;
    refraction_index = 1.5f;
    diffuse_reflectivity = 0;
    uvscale = vec2( 1 );
    inv_uvscale = vec2( 1 );
    tex = 0;
  }

  ~material()
  {
    if( tex )
    {
      delete tex;
    }
  }
};

#endif
