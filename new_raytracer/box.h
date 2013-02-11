#ifndef box_h
#define box_h

#include "globals.h"

#include "primitive.h"

class box : public primitive
{
  private:
  protected:
  public:
    aabb bb;
    std::vector<float> grid;

    int intersect( const ray& r, float& d )
    {
      ray_id = r.ray_id;

      float dist[6];
      vec3 ip[6];
      bool result = false;

      for( int c = 0; c < 6; ++c )
      {
        dist[c] = -1;
      }

      vec3 v2 = bb.pos + bb.size;

      if( r.direction.x )
      {
        float rc = 1.0f / r.direction.x;
        dist[0] = ( bb.pos.x - r.origin.x ) * rc;
        dist[3] = ( v2.x - r.origin.x ) * rc;
      }

      if( r.direction.y )
      {
        float rc = 1.0f / r.direction.y;
        dist[1] = ( bb.pos.y - r.origin.y ) * rc;
        dist[4] = ( v2.y - r.origin.y ) * rc;
      }

      if( r.direction.z )
      {
        float rc = 1.0f / r.direction.z;
        dist[2] = ( bb.pos.z - r.origin.z ) * rc;
        dist[5] = ( v2.z - r.origin.z ) * rc;
      }

      for( int c = 0; c < 6; ++c )
      {
        if( dist[c] > 0 )
        {
          ip[c] = r.origin + vec3( dist[c] ) * r.direction;

          if( ip[c].x > bb.pos.x - fepsilon &&
              ip[c].x < v2.x + fepsilon &&
              ip[c].y > bb.pos.y - fepsilon &&
              ip[c].y < v2.y + fepsilon &&
              ip[c].z > bb.pos.z - fepsilon &&
              ip[c].z < v2.z + fepsilon )
          {
            if( dist[c] < d )
            {
              d = dist[c];
              result = hit;
            }
          }
        }
      }

      return result;
    }

    bool intersect_box( const aabb& b )
    {
      return bb.intersect_box( b );
    }

    vec3 get_normal( const vec3& pos )
    {
      float dist[6];
      dist[0] = std::abs( bb.size.x - bb.pos.z );
      dist[1] = std::abs( 2 * bb.size.x - bb.pos.x );
      dist[2] = std::abs( bb.size.y - bb.pos.y );
      dist[3] = std::abs( 2 * bb.size.y - bb.pos.y );
      dist[4] = std::abs( bb.size.z - bb.pos.z );
      dist[5] = std::abs( 2 * bb.size.z - bb.pos.z );

      int best = 0;
      float bdist = dist[0];

      for( int c = 1; c < 6; ++c )
      {
        if( dist[c] < bdist )
        {
          bdist = dist[c];
          best = c;
        }
      }

      switch( best )
      {
        case 0:
          {
            return vec3( -1, 0, 0 );
          }
        case 1:
          {
            return vec3( 1, 0, 0 );
          }
        case 2:
          {
            return vec3( 0, -1, 0 );
          }
        case 3:
          {
            return vec3( 0, 1, 0 );
          }
        case 4:
          {
            return vec3( 0, 0, -1 );
          }
        default:
          {
            return vec3( 0, 0, 1 );
          }
      }
    }

    void set_light()
    {
      light = true;

      if( grid.size() == 0 )
      {
        grid.resize( 32 );
        grid[ 0] = 1;
        grid[ 1] = 2;
        grid[ 2] = 3;
        grid[ 3] = 3;
        grid[ 4] = 2;
        grid[ 5] = 0;
        grid[ 6] = 0;
        grid[ 7] = 1;
        grid[ 8] = 2;
        grid[ 9] = 3;
        grid[10] = 0;
        grid[11] = 3;
        grid[12] = 0;
        grid[13] = 0;
        grid[14] = 2;
        grid[15] = 2;
        grid[16] = 3;
        grid[17] = 1;
        grid[18] = 1;
        grid[19] = 3;
        grid[20] = 1;
        grid[21] = 0;
        grid[22] = 3;
        grid[23] = 2;
        grid[24] = 2;
        grid[25] = 1;
        grid[26] = 3;
        grid[27] = 0;
        grid[28] = 1;
        grid[29] = 1;
        grid[30] = 0;
        grid[31] = 2;

        for( int c = 0; c < 16; ++c )
        {
          grid[c * 2] = grid[c * 2] * bb.size.x / 4 + bb.pos.x;
          grid[c * 2 + 1] = grid[c * 2 + 1] * bb.size.z / 4 + bb.pos.z;
        }
      }
    }

    bool contains( const vec3& p )
    {
      return bb.contains( p );
    }

    aabb get_aabb()
    {
      return bb;
    }

    box() {}
    
    box( const aabb& b )
    {
      bb = b;
    }
};

#endif