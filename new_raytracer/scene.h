#ifndef scene_h
#define scene_h

#include "globals.h"

#include "aabb.h"
#include "plane.h"
#include "sphere.h"
#include "box.h"
#include "primitive.h"

class scene
{
private:
protected:
public:
  std::vector<primitive*> primitives;
  std::vector<primitive*> lights;
  std::vector< std::list<primitive*> > grid;
  aabb extents;
  vec3 cell_size, inv_cell_size;
  camera<float> cam;
  vec3 pos;
  vec4 wll, wur;

  void build_grid()
  {
    grid.resize( gridsize * gridsize * gridsize );

    vec3 p1( -14, -5, -6 ), p2( 14, 8, 30 );
    float dx = ( p2.x - p1.x ) / gridsize, dx_rcp = 1.0f / dx;
    float dy = ( p2.y - p1.y ) / gridsize, dy_rcp = 1.0f / dy;
    float dz = ( p2.z - p1.z ) / gridsize, dz_rcp = 1.0f / dz;

    extents = aabb( p1, p2 - p1 );

    inv_cell_size = vec3( gridsize ) / extents.size;
    cell_size = extents.size * vec3( 1.0f / gridsize );

    for( std::vector<primitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it )
    {
      if( ( *it )->light )
      {
        lights.push_back( *it );
      }

      aabb bound = ( *it )->get_aabb();

      vec3 bv2 = bound.pos + bound.size;

      int x1 = (int)( ( bound.pos.x - p1.x ) * dx_rcp );
      int x2 = (int)( ( bv2.x - p1.x ) * dx_rcp ) + 1;
      x1 = ( x1 < 0 ) ? 0 : x1;
      x2 = ( x2 > ( gridsize - 1 ) ) ? gridsize - 1 : x2;
      int y1 = (int)( ( bound.pos.y - p1.y ) * dy_rcp );
      int y2 = (int)( ( bv2.y - p1.y ) * dy_rcp ) + 1;
      y1 = ( y1 < 0 ) ? 0 : y1;
      y2 = ( y2 > ( gridsize - 1 ) ) ? gridsize - 1 : y2;
      int z1 = (int)( ( bound.pos.z - p1.z ) * dz_rcp );
      int z2 = (int)( ( bv2.z - p1.z ) * dz_rcp ) + 1;
      z1 = ( z1 < 0 ) ? 0 : z1;
      z2 = ( z2 > ( gridsize - 1 ) ) ? gridsize - 1 : z2;

      for( int x = x1; x < x2; ++x )
      {
        for( int y = y1; y < y2; ++y )
        {
          for( int z = z1; z < z2; ++z )
          {
            int idx = x + y * gridsize + z * gridsize * gridsize;
            vec3 pos( p1.x + x * dx, p1.y + y * dy, p1.z + z * dz );
            aabb cell( pos, vec3( dx, dy, dz ) );

            if( ( *it )->intersect_box( cell ) )
            {
              grid[idx].push_back( *it );
            }
          }
        }
      }
    }
  }

  void update_frame()
  {
    vec3 zaxis = cam.view_dir;
    vec3 up( 0, 1, 0 );
    vec3 xaxis = cross( up, zaxis );
    vec3 yaxis = cross( xaxis, -zaxis );
    mat4 m(
      xaxis.x, yaxis.x, zaxis.x, 0,
      xaxis.y, yaxis.y, zaxis.y, 0,
      xaxis.z, yaxis.z, zaxis.z, 0,
      0, 0, 0, 1
      );
    m = inverse( m );
    m[3].x = cam.pos.x;
    m[3].y = cam.pos.y;
    m[3].z = cam.pos.z;
    pos = ( m * vec4( vec3( cam.pos.xy, -cam.pos.z ), 1 ) ).xyz;
    wll = m * vec4( -4, -3, 0, 1 );
    wur = m * vec4( 4, 3, 0, 1 );
  }

  scene()
  {
    cam.pos = vec3( 0, 0, -5 );
    pos = cam.pos;
    wll = vec4( -4, -3, 0, 1 );
    wur = vec4( 4, 3, 0, 1 );
    //update_frame();

    plane* p = new plane( vec3( 0, 1, 0 ), 3.0f );
    p->mat.diffuse_color = vec3( 0.4f, 0.3f, 0.3f );
    p->mat.reflectivity = 0;
    p->mat.refractivity = 0;
    p->mat.diffuse_coeff = 0.7f;
    p->mat.specular_coeff = 0.5f;
    //p->mat.diffuse_reflectivity = 0.05f;
    //p->mat.tex = new texture( "../textures/brick.png" );
    p->mat.tex = new texture( "../textures/wood.tga" );
    p->mat.uvscale = vec2( 0.05f );
    p->mat.inv_uvscale = vec2( 1.0f / 0.05f );
    p->id = 0;
    primitives.push_back( p );

    sphere* s = new sphere( vec3( 0, 0.5f, 4 ), 2.0f );
    s->mat.diffuse_color = vec3( 0.8f );
    s->mat.reflectivity = 0.05f;
    s->mat.refractivity = 0;
    s->mat.diffuse_coeff = 0.5f;
    s->mat.specular_coeff = 0.8f;
    //s->mat.diffuse_reflectivity = 0.3f;
    //s->mat.tex = new texture( "../textures/rock.png" );
    s->mat.tex = new texture( "../textures/marble.tga" );
    s->mat.uvscale = vec2( 0.8f );
    s->mat.inv_uvscale = vec2( 1.0f / 0.8f );
    s->id = 1;
    primitives.push_back( s );

    s = new sphere( vec3( -5, -0.8f, 7 ), 2 );
    s->mat.diffuse_color = vec3( 0.7f, 0.7f, 1.0f );
    s->mat.reflectivity = 0.2f;
    s->mat.refractivity = 0;
    s->mat.diffuse_coeff = 0.7f;
    //s->mat.diffuse_reflectivity = 0.6f;
    //s->mat.tex = new texture( "../textures/brick.png" );
    s->mat.tex = new texture( "../textures/marble.tga" );
    s->mat.uvscale = vec2( 0.8f );
    s->mat.inv_uvscale = vec2( 1.0f / 0.8f );
    s->id = 2;
    primitives.push_back( s );

    s = new sphere( vec3( 5, -0.8f, 7 ), 2 );
    s->mat.diffuse_color = vec3( 0.8f, 0.8f, 1.0f );
    s->mat.reflectivity = 0.6f;
    s->mat.refractivity = 0;
    s->mat.refraction_index = 1.3f;
    s->mat.diffuse_coeff = 0.4f;
    //s->mat.tex = new texture( "../textures/terrain.png" );
    s->mat.tex = new texture( "../textures/marble.tga" );
    s->mat.uvscale = vec2( 0.8f );
    s->mat.inv_uvscale = vec2( 1.0f / 0.8f );
    s->id = 3;
    primitives.push_back( s );

    box* b = new box( aabb( vec3( -1, 5, 4 ), vec3( 2, 0.1f, 2 ) ) );
    b->set_light();
    b->mat.diffuse_color = vec3( 0.7f );
    primitives.push_back( b );

    b = new box( aabb( vec3( -1, 5, -1 ), vec3( 2, 0.1f, 2 ) ) );
    b->set_light();
    b->mat.diffuse_color = vec3( 0.7f );
    b->id = 4;
    primitives.push_back( b );

    /*s = new sphere( vec3( 4, 4, -4 ), 0.1f );
    s->light = true;
    s->mat.diffuse_color = vec3( 0.6f, 0.6f, 0.7f );
    primitives.push_back( s );

    s = new sphere( vec3( 2, 5, -2 ), 0.1f );
    s->light = true;
    s->mat.diffuse_color = vec3( 0.5f, 0.8f, 0.8f );
    primitives.push_back( s );*/

    p = new plane( vec3( 0, 0, -1 ), 22.4f );
    p->mat.reflectivity = 0;
    p->mat.refractivity = 0;
    p->mat.specular_coeff = 0;
    p->mat.diffuse_coeff = 1;
    p->mat.diffuse_color = vec3( 0.6f, 0.5f, 0.5f );
    //p->mat.tex = new texture( "../textures/terrain.png" );
    p->mat.tex = new texture( "../textures/marble.tga" );
    p->mat.uvscale = vec2( 0.1f );
    p->mat.inv_uvscale = vec2( 1.0f / 0.1f );
    p->id = 5;
    primitives.push_back( p );

    p = new plane( vec3( 1, 0, 0 ), 10.0f );
    p->mat.reflectivity = 0;
    p->mat.refractivity = 0;
    p->mat.specular_coeff = 0;
    p->mat.diffuse_coeff = 1;
    p->mat.diffuse_color = vec3( 0.5f, 0.5f, 0.6f );
    //p->mat.tex = new texture( "../textures/terrain.png" );
    p->mat.tex = new texture( "../textures/marble.tga" );
    p->mat.uvscale = vec2( 0.1f );
    p->mat.inv_uvscale = vec2( 1.0f / 0.1f );
    p->id = 6;
    primitives.push_back( p );

    p = new plane( vec3( -1, 0, 0 ), 10.0f );
    p->mat.reflectivity = 0;
    p->mat.refractivity = 0;
    p->mat.specular_coeff = 0;
    p->mat.diffuse_coeff = 1;
    p->mat.diffuse_color = vec3( 0.5f, 0.5f, 0.6f );
    //p->mat.tex = new texture( "../textures/terrain.png" );
    p->mat.tex = new texture( "../textures/marble.tga" );
    p->mat.uvscale = vec2( 0.1f );
    p->mat.inv_uvscale = vec2( 1.0f / 0.1f );
    p->id = 7;
    primitives.push_back( p );

    p = new plane( vec3( 0, -1, 0 ), 5.2f );
    p->mat.reflectivity = 0;
    p->mat.refractivity = 0;
    p->mat.specular_coeff = 0;
    p->mat.diffuse_coeff = 1;
    p->mat.diffuse_color = vec3( 0.7f );
    //p->mat.tex = new texture( "../textures/wood.tga" );
    p->mat.uvscale = vec2( 0.4f );
    p->mat.inv_uvscale = vec2( 1.0f / 0.4f );
    p->id = 8;
    primitives.push_back( p );

    box* b2 = new box( aabb( vec3( 1.5f, -3, 2.5f ), vec3( 3, 1.5f, 3 ) ) );
    b2->mat.reflectivity = 0.0f;
    b2->mat.refractivity = 0.0f;
    b2->mat.diffuse_coeff = 1.0f;
    b2->mat.diffuse_color = vec3( 0.7f );
    //b2->mat.tex = new texture( "../textures/wood.tga" );
    b2->mat.uvscale = vec2( 0.4f );
    b2->mat.inv_uvscale = vec2( 1.0f / 0.4f );
    b2->id = 9;
    primitives.push_back( b2 );

    build_grid();
  }

  ~scene()
  {
    for( std::vector<primitive*>::iterator it = primitives.begin(); it != primitives.end(); ++it )
    {
      delete *it;
    }
  }
};

static scene the_scene;

#endif
