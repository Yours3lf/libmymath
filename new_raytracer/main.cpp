#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include "globals.h"

#include "GL/glew.h" //the mighty GLEW :)
#include "SFML/Window.hpp"
#if USE_QRNG == 1
#include <gsl/gsl_qrng.h>
#endif
#if COUNT_INTERSECTIONS == 0
#include "tbb/tbb.h"
#endif

#include "scene.h"

#include <string>
#include <sstream>

static sf::Window the_window;
static sf::Event the_event;

static float fps = 1.0f;
static int frames = 0;
static sf::Clock the_clock;
static std::string app_path;
static uvec2 screen( 800, 600 );
static std::vector<vec4> tex;
static float elapsed_time = 0.0f;
static unsigned int current_time = 0;
static bool silent = false;
static bool fullscreen = false;
static bool fast_mode = false;
static std::vector<float> random_cache;

inline int find_nearest( const ray& r, float& dist, primitive*& p )
{
  int result = miss;

  vec3 cb, tmax, tdelta, cell;
  cell = ( r.origin - the_scene.extents.pos ) * the_scene.inv_cell_size;
  int step_x, out_x, x = (int)cell.x;
  int step_y, out_y, y = (int)cell.y;
  int step_z, out_z, z = (int)cell.z;

  if( x < 0 || x >= gridsize || y < 0 || y >= gridsize || z < 0 || z >= gridsize )
  {
    return miss;
  }

  if( r.direction.x > 0 )
  {
    step_x = 1;
    out_x = gridsize;
    cb.x = the_scene.extents.pos.x + ( x + 1 ) * the_scene.cell_size.x;
  }
  else
  {
    step_x = -1;
    out_x = -1;
    cb.x = the_scene.extents.pos.x + x * the_scene.cell_size.x;
  }

  if( r.direction.y > 0 )
  {
    step_y = 1;
    out_y = gridsize;
    cb.y = the_scene.extents.pos.y + ( y + 1 ) * the_scene.cell_size.y;
  }
  else
  {
    step_y = -1;
    out_y = -1;
    cb.y = the_scene.extents.pos.y + y * the_scene.cell_size.y;
  }

  if( r.direction.z > 0 )
  {
    step_z = 1;
    out_z = gridsize;
    cb.z = the_scene.extents.pos.z + ( z + 1 ) * the_scene.cell_size.z;
  }
  else
  {
    step_z = -1;
    out_z = -1;
    cb.z = the_scene.extents.pos.z + z * the_scene.cell_size.z;
  }

  float rxr, ryr, rzr;

  if( r.direction.x != 0 )
  {
    rxr = 1.0f / r.direction.x;
    tmax.x = ( cb.x - r.origin.x ) * rxr;
    tdelta.x = the_scene.cell_size.x * step_x * rxr;
  }
  else
  {
    tmax.x = 1000000;
  }

  if( r.direction.y != 0 )
  {
    ryr = 1.0f / r.direction.y;
    tmax.y = ( cb.y - r.origin.y ) * ryr;
    tdelta.y = the_scene.cell_size.y * step_y * ryr;
  }
  else
  {
    tmax.y = 1000000;
  }

  if( r.direction.z != 0 )
  {
    rzr = 1.0f / r.direction.z;
    tmax.z = ( cb.z - r.origin.z ) * rzr;
    tdelta.z = the_scene.cell_size.z * step_z * rzr;
  }
  else
  {
    tmax.z = 1000000;
  }

  p = 0;

  while( true )
  {
    std::list<primitive*>* ptr = &the_scene.grid[x + ( y << gridshift ) + ( z << ( gridshift * 2 ) )];

    for( std::list<primitive*>::iterator it = ptr->begin(); it != ptr->end(); ++it )
    {
      int res;

      if( ( *it )->ray_id != r.ray_id && ( res = ( *it )->intersect( r, dist ) ) != miss )
      {
        result = res;
        p = *it;

        while( true )
        {
          std::list<primitive*>* ptr2 = &the_scene.grid[x + ( y << gridshift ) + ( z << ( gridshift * 2 ) )];

          for( std::list<primitive*>::iterator it2 = ptr2->begin(); it2 != ptr2->end(); ++it2 )
          {
            int res2;

            if( ( *it2 )->ray_id != r.ray_id && ( res2 = ( *it2 )->intersect( r, dist ) ) != miss )
            {
              result = res2;
              p = *it2;
            }
          }

          if( tmax.x < tmax.y )
          {
            if( tmax.x < tmax.z )
            {
              if( dist < tmax.x )
              {
                break;
              }

              x += step_x;

              if( x == out_x )
              {
                break;
              }

              tmax.x += tdelta.x;
            }
            else
            {
              if( dist < tmax.z )
              {
                break;
              }

              z += step_z;

              if( z == out_z )
              {
                break;
              }

              tmax.z += tdelta.z;
            }
          }
          else
          {
            if( tmax.y < tmax.z )
            {
              if( dist < tmax.y )
              {
                break;
              }

              y += step_y;

              if( y == out_y )
              {
                break;
              }

              tmax.y += tdelta.y;
            }
            else
            {
              if( dist < tmax.z )
              {
                break;
              }

              z += step_z;

              if( z == out_z )
              {
                break;
              }

              tmax.z += tdelta.z;
            }
          }
        }

        return result;
      }
    }

    if( tmax.x < tmax.y )
    {
      if( tmax.x < tmax.z )
      {
        x += step_x;

        if( x == out_x )
        {
          return miss;
        }

        tmax.x += tdelta.x;
      }
      else
      {
        z += step_z;

        if( z == out_z )
        {
          return miss;
        }

        tmax.z += tdelta.z;
      }
    }
    else
    {
      if( tmax.y < tmax.z )
      {
        y += step_y;

        if( y == out_y )
        {
          return miss;
        }

        tmax.y += tdelta.y;
      }
      else
      {
        z += step_z;

        if( z == out_z )
        {
          return miss;
        }

        tmax.z += tdelta.z;
      }
    }
  }

  while( true )
  {
    std::list<primitive*>* ptr2 = &the_scene.grid[x + ( y << gridshift ) + ( z << ( gridshift * 2 ) )];

    for( std::list<primitive*>::iterator it2 = ptr2->begin(); it2 != ptr2->end(); ++it2 )
    {
      int res2;

      if( ( *it2 )->ray_id != r.ray_id && ( res2 = ( *it2 )->intersect( r, dist ) ) != miss )
      {
        result = res2;
        p = *it2;
      }
    }

    if( tmax.x < tmax.y )
    {
      if( tmax.x < tmax.z )
      {
        if( dist < tmax.x )
        {
          break;
        }

        x += step_x;

        if( x == out_x )
        {
          break;
        }

        tmax.x += tdelta.x;
      }
      else
      {
        if( dist < tmax.z )
        {
          break;
        }

        z += step_z;

        if( z == out_z )
        {
          break;
        }

        tmax.z += tdelta.z;
      }
    }
    else
    {
      if( tmax.y < tmax.z )
      {
        if( dist < tmax.y )
        {
          break;
        }

        y += step_y;

        if( y == out_y )
        {
          break;
        }

        tmax.y += tdelta.y;
      }
      else
      {
        if( dist < tmax.z )
        {
          break;
        }

        z += step_z;

        if( z == out_z )
        {
          break;
        }

        tmax.z += tdelta.z;
      }
    }
  }

  return result;
}

inline vec3 raytrace( const ray& r, int depth, float r_index, float& dist, int& curr_id, float samples, float scale )
{
  if( depth > trace_depth )
  {
    return vec3( 0 );
  }

  dist = 1000000.0f;
  int type = miss;
  primitive* p = 0;

  if( ( type = find_nearest( r, dist, p ) ) == miss )
  {
    return vec3( 0 );
  }

  if( p->light )
  {
    return p->mat.diffuse_color;
  }

  //point of intersection
  vec3 point = r.origin + r.direction * vec3( dist );

  vec3 result;

  vec3 n = p->get_normal( point );

#if GAMMA_CORRECTION == 1
  vec3 color = pow( p->get_color( point ), vec3( 2.2f ) );
#else
  vec3 color = p->get_color( point );
#endif

  if( p->mat.diffuse_coeff > 0.0f )
  {
    for( std::vector<primitive*>::iterator it = the_scene.lights.begin(); it != the_scene.lights.end(); ++it )
    {
      float shade = 1;
      primitive* p2 = 0;
      vec3 l;

      if( ( *it )->type == primitive::SPHERE )
      {
        shade = 1.0f;

        l = ( (sphere*)( *it ) )->center - point;
        float dist2 = length( l );
        l *= vec3( 1.0f / dist2 );

        if( !fast_mode )
        {
          find_nearest( ray( point + l * epsilon, l, ++curr_id ), dist2, p2 );

          if( p2 != *it )
          {
            shade = 0;
          }
        }
      }
      else if( ( *it )->type == primitive::BOX )
      {
        shade = 0;
        box* b = (box*)* it;

        l = normalize( ( b->bb.pos + vec3( 0.5 ) * b->bb.size ) - point );

        if( !fast_mode )
        {
          float deltax = b->bb.size.x * 0.25f;
          float deltay = b->bb.size.z * 0.25f;

          float seed = ( random_cache.size() / 2 ) * ( (float)rand() / RAND_MAX ) * 2.0f;

          float dirx = random_cache[seed];
          float diry = random_cache[seed + 1];

          for( int c = 0; c < samples; ++c )
          {
            vec3 lp( b->grid[( c & 15 ) << 1] + dirx * deltax, b->bb.pos.y, b->grid[( ( c & 15 ) << 1 ) + 1] + diry * deltay );
            dirx = random_cache[random_cache.size() * dirx];
            diry = random_cache[random_cache.size() * diry];
            vec3 dir = lp - point;
            float dist2 = length( dir );
            dir *= vec3( 1.0f / dist2 );

            if( find_nearest( ray( point + dir * epsilon, dir, ++curr_id ), dist2, p2 ) )
            {
              if( p2 == *it )
              {
                shade += scale;
              }
            }
          }
        }
      }

      if( fast_mode )
      {
        shade = 1;
      }

      if( shade > 0.0f )
      {
        float n_dot_l = dot( n, l );

        if( n_dot_l > 0.0f )
        {
          result += vec3( shade * p->mat.diffuse_coeff * n_dot_l ) * ( *it )->mat.diffuse_color * color;

          if( p->mat.specular_coeff > 0.0f && !fast_mode )
          {
            vec3 v = r.direction;
            vec3 re = reflect( l, n );
            float v_dot_r = dot( v, re );

            if( v_dot_r > 0.0f )
            {
              const float spec_pow = 20;
              result += vec3( spec_pow * shade * std::pow( v_dot_r, spec_pow ) * p->mat.specular_coeff ) * ( *it )->mat.diffuse_color;
            }
          }
        }
      }
    }
  }

  if( depth < trace_depth && !fast_mode )
  {
    if( p->mat.reflectivity > 0.0f )
    {
      vec3 re = reflect( r.direction, n );

      if( p->mat.diffuse_reflectivity > 0.0f && depth < 2 )
      {
        vec3 re1( re.z, re.y, -re.x );
        vec3 re2 = cross( re, re1 );

        float seed = ( random_cache.size() / 2 ) * ( (float)rand() / RAND_MAX ) * 2.0f;

        float dirx = random_cache[seed];
        float diry = random_cache[seed + 1];

        for( int c = 0; c < samples; ++c )
        {
          float xoffs = dirx * p->mat.diffuse_reflectivity;
          float yoffs = diry * p->mat.diffuse_reflectivity;
          dirx = random_cache[random_cache.size() * dirx];
          diry = random_cache[random_cache.size() * diry];

          while( xoffs * xoffs + yoffs * yoffs > p->mat.diffuse_reflectivity * p->mat.diffuse_reflectivity )
          {
            xoffs = dirx * p->mat.diffuse_reflectivity;
            yoffs = diry * p->mat.diffuse_reflectivity;
            dirx = random_cache[random_cache.size() * dirx];
            diry = random_cache[random_cache.size() * diry];
          }

          vec3 rp = normalize( re + re1 * vec3( xoffs ) + re2 * vec3( yoffs * p->mat.diffuse_reflectivity ) );
          float rdist;
          result += color * vec3( p->mat.reflectivity * scale ) * raytrace( ray( point + rp * epsilon, rp, ++curr_id ), depth + 1, r_index, rdist, curr_id, samples * 0.25f, scale * 4 );
        }
      }
      else
      {
        float rdist;
        result += color * vec3( p->mat.reflectivity ) * raytrace( ray( point + re * epsilon, re, ++curr_id ), depth + 1, r_index, rdist, curr_id, samples * 0.5f, scale * 2 );
      }
    }

    if( p->mat.refractivity > 0.0f )
    {
      float rn = r_index / p->mat.refraction_index;
      n *= vec3( type );
      vec3 t = refract( r.direction, n, vec3( rn ) );
      float rdist;
      vec3 rcolor = raytrace( ray( point + t * epsilon, t, ++curr_id ), depth + 1, p->mat.refraction_index, rdist, curr_id, samples * 0.5f, scale * 2 );
      result += exp( p->mat.diffuse_color * vec3( 0.15f * -rdist ) ) * rcolor;
    }
  }

  return result;
}

/*
 * GLSL main function
 */
inline vec4 fragment_program( const vec2& coord, const float& time, int& curr_id )
{
  vec2 screen_size( screen.x, screen.y );
  //float aspect = screen_size.x / screen_size.y;

  vec2 uv = coord / screen_size;

  //the ray to shoot
  ray r;

  //camera origin
  r.origin = the_scene.pos;

  r.direction = normalize( vec3( mix( the_scene.wll.xy, the_scene.wur.xy, uv ), 0 ) - r.origin );

  r.ray_id = ++curr_id;

  if( !the_scene.extents.contains( r.origin ) )
  {
    float bdist = 10000;

    box b( the_scene.extents );

    if( b.intersect( r, bdist ) )
    {
      r.origin += vec3( bdist + epsilon ) * r.direction;
    }
  }

  float rdist;

  vec3 color = raytrace( r, 1, 1, rdist, curr_id, num_samples, 1.0f / num_samples );

  return vec4( color, 1 );
}

/*
 *  C++ code starts here
 */

inline void write_tex( const vec4& val, const uvec2& coord )
{
  unsigned int c = coord.y * screen.x + coord.x;
  assert( tex.size() > 0 && c < screen.x * screen.y );

#if GAMMA_CORRECTION == 1
  tex[c] = pow( val, vec4( 1.0f / 2.2f ) );
#else
  tex[c] = val;
#endif
}

inline void draw_quad()
{
  glBegin( GL_QUADS );
  glTexCoord2f( 0, 0 );
  glVertex2f( 0, 0 );
  glTexCoord2f( 1, 0 );
  glVertex2f( 1, 0 );
  glTexCoord2f( 1, 1 );
  glVertex2f( 1, 1 );
  glTexCoord2f( 0, 1 );
  glVertex2f( 0, 1 );
  glEnd();
}

inline void thread_func( const uvec4& startend )
{
  uvec2 coord;
  int curr_id = 0;

  for( coord.y = startend.z; coord.y < startend.w; coord.y++ )
  {
    for( coord.x = startend.x; coord.x < startend.y; coord.x++ )
    {
      write_tex( fragment_program( vec2( coord.x, coord.y ), elapsed_time, curr_id ), coord );
    }
  }
}

int main( int argc, char* args[] )
{
  //parse command line arguments
  for( int i = 1; i < argc; ++i )
  {
    /* We will iterate over args[] to get the parameters stored inside.
     * Note that we're starting on 1 because we don't need to know the
     * path of the program, which is stored in args[0]
     */
    std::stringstream ss;
    ss << args[i];

    if( ss.str() == "--screenx" )
    {
      screen.x = atoi( args[i + 1] );

      if( screen.x == 0 )
      {
        screen.x = 1280;
      }
    }
    else if( ss.str() == "--screeny" )
    {
      screen.y = atoi( args[i + 1] );

      if( screen.y == 0 )
      {
        screen.y = 720;
      }
    }
    else if( ss.str() == "--fullscreen" )
    {
      fullscreen = true;
    }
    else if( ss.str() == "--help" )
    {
      std::cout << "libmymath raytracer, written by Tamas Marton.\n"
        "based on: http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_1_Introduction.shtml\n"
        "Usage: --silent      //don't display FPS info in the terminal\n"
        "       --screenx num //set screen width (default:1280)\n"
        "       --screeny num //set screen height (default:720)\n"
        "       --fullscreen  //set fullscreen, windowed by default\n"
        "       --help        //display this information\n";
      return 0;
    }
    else if( ss.str() == "--silent" )
    {
      silent = true;
    }
  }

#if COUNT_INTERSECTIONS == 1
  std::cout << "Counting intersections, running on 1 thread.\n";
#endif

  /*
   * Initialize OpenGL context
   */

  tex.resize( screen.x * screen.y );

  if( fullscreen )
  {
    the_window.create( sf::VideoMode( screen.x, screen.y, 32 ), "libmymath raytracer", sf::Style::Fullscreen );
  }
  else
  {
    the_window.create( sf::VideoMode( screen.x, screen.y, 32 ), "libmymath raytracer", sf::Style::Default );
  }

  if( !the_window.isOpen() )
  {
    std::cerr << "Couldn't initialize SFML.\n";
    the_window.close();
    exit( 1 );
  }

  //the_window.setVerticalSyncEnabled( true );

  GLenum glew_error = glewInit();

  if( glew_error != GLEW_OK )
  {
    std::cerr << "Error initializing GLEW: " << glewGetErrorString( glew_error ) << "\n";
    the_window.close();
    exit( 1 );
  }

  if( !GLEW_VERSION_1_1 )
  {
    std::cerr << "Error: OpenGL 1.1 is required\n";
    the_window.close();
    exit( 1 );
  }

  GLuint gltex;

  glGenTextures( 1, &gltex );
  glBindTexture( GL_TEXTURE_2D, gltex );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, screen.x, screen.y, 0, GL_RGBA, GL_FLOAT, 0 );

  /*
   * MAIN LOOP
   */

  the_clock.restart();

  glViewport( 0, 0, screen.x, screen.y );
  glMatrixMode( GL_PROJECTION );
  //x_min:0, x_max:1, y_min:0, y_max:1, z_min:0, z_max:-1
  mat4 ortho_matrix = ortographic( 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f );
  glLoadMatrixf( &ortho_matrix[0][0] );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glEnable( GL_TEXTURE_2D );

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_2D, gltex );

  //this basically divides the screen into 256 small parts
  std::vector<uvec4> startends;
  const unsigned int w = 16;
  const unsigned int h = 16;
  startends.resize( w * h );

  for( unsigned int x = 0; x < w; ++x )
  {
    for( unsigned int y = 0; y < h; ++y )
    {
      startends[x * h + y] = uvec4( ( screen.x / (float)w ) * x, ( screen.x / (float)w ) * ( x + 1 ), ( screen.y / (float)h ) * y, ( screen.y / (float)h ) * ( y + 1 ) );
    }
  }

  srand( time( 0 ) );

#if USE_QRNG == 1
  gsl_qrng* q = gsl_qrng_alloc( gsl_qrng_halton, 2 );
#endif

  random_cache.resize( 10000 * 2 );

  for( unsigned int c = 0; c < random_cache.size() / 2; c++ )
  {
    double v[2];
#if USE_QRNG == 1
    gsl_qrng_get( q, v );
    random_cache[c * 2] = v[0];
    random_cache[c * 2 + 1] = v[1];
#else
    v[0] = (float)rand() / (float)RAND_MAX;
    v[1] = (float)rand() / (float)RAND_MAX;
    random_cache[c * 2] = v[0];
    random_cache[c * 2 + 1] = v[1];
#endif
  }

#if USE_QRNG == 1
  gsl_qrng_free( q );
#endif

#if COUNT_INTERSECTIONS == 0
  //initialize thread building blocks
  tbb::task_scheduler_init();
#endif

  while( true )
  {
    /*
     * Handle events
     */

    while( the_window.pollEvent( the_event ) )
    {
      switch( the_event.type )
      {
      case sf::Event::Closed:
      {
        the_window.close();
        exit( 0 );
      }
      case sf::Event::KeyPressed:
      {
        if( the_event.key.code == sf::Keyboard::Escape )
        {
          the_window.close();
          exit( 0 );
        }

        if( the_event.key.code == sf::Keyboard::Space )
        {
          fast_mode = !fast_mode;

          if( fast_mode )
          {
            num_samples = 16;
            trace_depth = 4;
          }
          else
          {
            num_samples = 64;
            trace_depth = 8;
          }
        }

        if( the_event.key.code == sf::Keyboard::Tab )
        {
          sf::Image im;
          im.create( screen.x, screen.y );

          for( unsigned int x = 0; x < screen.x; ++x )
          {
            for( unsigned int y = 0; y < screen.y; ++y )
            {
              vec4 val = clamp( tex[y * screen.x + x], vec4( 0 ), vec4( 1 ) ) * vec4( 255 );
              im.setPixel( x, y, sf::Color( val.x, val.y, val.z, val.w ) );
            }
          }

          im.saveToFile( "screenshot.png" );

          std::cout << "Screenshot saved." << std::endl;
        }

        /*
        if( the_event.key.code == sf::Keyboard::Left )
        {
        the_scene.cam.rotate_y( radians( 5.0f ) );
        the_scene.update_frame();
        }

        if( the_event.key.code == sf::Keyboard::Right )
        {
        the_scene.cam.rotate_y( radians( -5.0f ) );
        the_scene.update_frame();
        }

        if( the_event.key.code == sf::Keyboard::Up )
        {
        the_scene.cam.move_forward( 0.5f );
        the_scene.update_frame();
        }

        if( the_event.key.code == sf::Keyboard::Down )
        {
        the_scene.cam.move_forward( -0.5f );
        the_scene.update_frame();
        }*/
      }
      default:
        break;
      }
    }

    std::cout << mm::ortographic( -1, 1, -1, 1, -100, 100 );

    //memset( tex, 0, screen.x * screen.y ); //clear screen

#if COUNT_INTERSECTIONS == 1
    thread_func( uvec4( 0, screen.x, 0, screen.y ) );
#else
    //intel thread building blocks for the rescue!
    tbb::parallel_for( tbb::blocked_range<size_t>( 0, (size_t)startends.size() ),
      [=]( const tbb::blocked_range<size_t>& r )
    {
      for( size_t i = r.begin(); i != r.end(); ++i )
        thread_func( startends[i] );
    }
    );
#endif

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, screen.x, screen.y, 0, GL_RGBA, GL_FLOAT, &tex[0][0] );

    /*
     * DRAW RESULT
     */

    draw_quad();

    /*
     * Show the result
     */

    the_window.display();

    frames++;

    elapsed_time = radians( (float)the_clock.getElapsedTime().asMilliseconds() * 0.05f );

    if( the_clock.getElapsedTime().asMilliseconds() - current_time > 1000.0f && !silent )
    {
#if COUNT_INTERSECTIONS == 1
      std::cout << "Number of intersections: " << intersections / frames << std::endl;
      std::cout << "Per pixel: " << ( intersections / frames ) / ( screen.x * screen.y ) << std::endl;
      intersections = 0;
#endif

      int timepassed = the_clock.getElapsedTime().asMilliseconds() - current_time;
      fps = 1000.0f / ( (float)timepassed / (float)frames );
      std::cout << "FPS: " << fps << " Time: " << (float)timepassed / (float)frames << std::endl;
      frames = 0;
      current_time = the_clock.getElapsedTime().asMilliseconds();
    }
  }

  return 0;
}


