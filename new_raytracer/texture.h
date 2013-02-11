#ifndef texture_h
#define texture_h

#include "globals.h"

#include "SFML/Graphics/Image.hpp"

class texture
{
  private:
  protected:
  public:
    std::vector<vec3> data;
    unsigned int w, h;

    vec3 get_texel( const vec2& uv )
    {
      if( data.size() == 0 )
      {
        return vec3( 1 );
      }

      float fu = ( uv.x + 1000.5f ) * w;
      float fv = ( 1.0f - uv.y + 1000.0f ) * w;
      int u1 = ( ( int )fu ) % w;
      int v1 = ( ( int )fv ) % h;
      int u2 = ( u1 + 1 ) % w;
      int v2 = ( v1 + 1 ) % h;

      float fracu = fu - floorf( fu );
      float fracv = fv - floorf( fv );

      float w1 = ( 1 - fracu ) * ( 1 - fracv );
      float w2 = ( fracu * ( 1 - fracv ) );
      float w3 = ( 1 - fracu ) * fracv;
      float w4 = fracu * fracv;

      vec3 c1 = data[u1 + v1 * w];
      vec3 c2 = data[u2 + v1 * w];
      vec3 c3 = data[u1 + v2 * w];
      vec3 c4 = data[u2 + v2 * w];

      return c1 * vec3( w1 ) + c2 * vec3( w2 ) + c3 * vec3( w3 ) + c4 * vec3( w4 );
    }

    texture( std::vector<vec3> t, unsigned int wi, unsigned int he )
    {
      data = t;
      w = wi;
      h = he;
    }

    texture( std::string filename )
    {
      sf::Image im;
      im.loadFromFile( filename );

      w = im.getSize().x;
      h = im.getSize().y;

      data.resize( w * h );

      for( unsigned int c = 0; c < data.size(); ++c )
      {
        data[c].x = im.getPixelsPtr()[c * 4 + 0] / 255.0f;
        data[c].y = im.getPixelsPtr()[c * 4 + 1] / 255.0f;
        data[c].z = im.getPixelsPtr()[c * 4 + 2] / 255.0f;
      }
    }

    texture()
    {
      w = 0;
      h = 0;
    }
};

#endif
