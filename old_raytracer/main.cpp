#include "GL/glew.h" //the mighty GLEW :)
#include "SFML/Window.hpp"

#include "mymath/mymath.h"
#include <string>
#include <sstream>

using namespace mymath;
using namespace std;

/*
 * Global variables
 */

sf::Window the_window;
sf::Event the_event;

float fps = 1.0f;
int frames = 0;
sf::Clock the_clock;
std::string app_path;
uvec2 screen( 800, 600 );
vec4* tex = 0;
float elapsed_time = 0.0f;
unsigned int current_time = 0;
unsigned int num_threads = 16;
bool silent = false;
bool fullscreen = false;

/*
 * GLSL code starts here
 */

inline float int_sphere( const vec3& o, const vec3& d, const vec4& sphere )
{
  //a sphere centered at the origin has the equation |xyz| = r
  //that is |xyz|^2 = r^2
  //xyz = o + t * d, therefore |o|^2 + t^2 + 2<o, d>t - r^2 = 0
  //just think of the simple sphere equation learned in high school
  vec4 s = sphere;
  vec3 oc = o - s.xyz;
  //vec3 oc = o - sphere.xyz;
  float b = 2.0f * dot( oc, d );
  float c = dot( oc, oc ) - s.w * s.w;
  float h = b * b - 4.0f * c;

  if( h < 0.0f ) return -1.0f;

  float t = ( -b - sqrt( h ) ) / 2.0f;
  return t;
}

inline vec3 nor_sphere( const vec3& pos, const vec4& sphere )
{
  vec4 s = sphere;
  return normalize( pos - s.xyz ) / vec3( s.w );
}

inline float int_plane( const vec3& o, const vec3& d )
{
  //equation of a plane, y = 0 = o.y + t * d.y
  return -o.y / d.y;
}

inline vec3 nor_plane( const vec3& pos )
{
  return vec3( 0, 1, 0 );
}

vec4 sph1( 0, 1, 0, 1 );

inline vec2 intersect( const vec3& o, const vec3& d )
{
  float id = -1.0f;
  float res_t = 1000.0f;
  float tsphere = int_sphere( o, d, sph1 ); //intersect with sphere
  float tplane = int_plane( o, d ); //intersect with plane

  if( tsphere > 0.0f )
  {
    id = 1.0f;
    res_t = tsphere;
  }

  if( tplane > 0.0f && tplane < res_t )
  {
    id = 2.0f;
    res_t = tplane;
  }

  return vec2( id, res_t );
}

inline vec4 fragment_program( const vec2& coord, const float& time )
{
  /*
   * Start GLSL code here
   */
  vec2 screen_size( screen.x, screen.y );
  float aspect = screen_size.x / screen_size.y;

  vec3 light = normalize( vec3( 0.5773f ) );

  vec2 uv = coord / screen_size;

  sph1.x = cos( time ) * 2.0f;
  sph1.z = sin( time );

  //generate a ray with origin o and direction d
  vec3 o = vec3( 0.0f, 0.5f, 3.0f );
  vec3 d = normalize( vec3( ( vec2( -1 ) + vec2( 2 ) * uv ) * vec2( aspect, 1.0f ), -1 ) );

  vec2 res_int = intersect( o, d );

  vec3 col = vec3( 0 );

  if( res_int.x > 0.5f && res_int.x < 1.5f )
  {
    //if hit something, draw white
    vec3 pos = o + vec3( res_int.y ) * d;
    vec3 nor = nor_sphere( pos, sph1 );
    //float dif = clamp( dot( nor, light ), 0.0f, 1.0f );
    float dif = dot( nor, light );

    if( dif > 0.0f )
    {
      col = vec3( 0.9f, 0.8f, 0.6f ) * vec3( dif );
    }

    float ao = 0.5f + 0.5f * nor.y;
    col += vec3( 0.1f, 0.2f, 0.4f );
    col *= vec3( ao );
  }
  else if( res_int.x > 1.5f )
  {
    vec3 pos = o + vec3( res_int.y ) * d;

    float amb = smoothstep( vec2( 0.0f ), vec2( 2.0f * sph1.w ), vec2( length( pos.xz - sph1.xz ) ) ).x;
    col = vec3( amb * 0.7f );
  }

  return vec4( col, 1 );
}

/*
 *  C++ code starts here
 */

inline void write_tex( const vec4& val, const uvec2& coord )
{
  unsigned int c = coord.y * screen.x + coord.x;
  assert( tex != 0 && c < screen.x * screen.y );
  tex[c] = val;
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

inline void thread_func( const uvec2& startend )
{
  uvec2 coord;

  for( coord.y = 0; coord.y < screen.y; coord.y++ )
  {
    for( coord.x = startend.x; coord.x < startend.y; coord.x++ )
    {
      write_tex( fragment_program( vec2( coord.x, coord.y ), elapsed_time ), coord );
    }
  }
}

int main( int argc, char* args[] )
{
  //parse command line arguments
  for( int i = 1; i < argc; i++ )
  {
    /* We will iterate over argv[] to get the parameters stored inside.
     * Note that we're starting on 1 because we don't need to know the
     * path of the program, which is stored in argv[0]
     */
    std::stringstream ss;
    ss << args[i];

    if( ss.str() == "--threads" )
    {
      // We know the next argument *should* be the num of threads:
      num_threads = atoi( args[i + 1] );

      if( num_threads == 0 )
      {
        num_threads = 1;
      }

      std::cout << "Using: " << num_threads << " threads.\n";
    }
    else if( ss.str() == "--screenx" )
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
                "based on: http://www.youtube.com/watch?v=9g8CdctxmeU\n"
                "Usage: --threads num //use [num] number of threads\n"
                "       --silent      //don't display FPS info in the terminal\n"
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

  /*
   * Initialize OpenGL context
   */

  tex = new vec4[screen.x * screen.y];

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
          }
        default:
          break;
      }
    }

    //memset( tex, 0, screen.x * screen.y ); //clear screen

    if( num_threads > 1 )
    {
      std::vector<sf::Thread*> threads;

      for( unsigned int c = 0; c < num_threads; c++ )
      {
        float amount = screen.x / ( float )num_threads;
        unsigned int end = amount * ( c + 1 );

        if( end > screen.x )
        {
          end = screen.x;
        }

        threads.push_back( new sf::Thread( &thread_func, uvec2( amount * c, end ) ) );
        threads[c]->launch();
      }

      for( unsigned int c = 0; c < num_threads; c++ )
      {
        threads[c]->wait();
      }
    }
    else
    {
      thread_func( uvec2( 0, screen.x ) );
    }

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

    elapsed_time = radians( ( float )the_clock.getElapsedTime().asMilliseconds() * 0.05f );

    if( the_clock.getElapsedTime().asMilliseconds() - current_time > 1000.0f && !silent )
    {
      int timepassed = the_clock.getElapsedTime().asMilliseconds() - current_time;
      fps = 1000.0f / ( ( float ) timepassed / ( float ) frames );
      std::cout << "FPS: " << fps << " Time: " << ( float ) timepassed / ( float ) frames << "\n";
      frames = 0;
      current_time = the_clock.getElapsedTime().asMilliseconds();
    }
  }

  return 0;
}

