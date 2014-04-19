#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#endif

#include "GL/glew.h" //the mighty GLEW :)
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <string>
#include <sstream>

#define USE_TBB 1
#define ONETHREAD 0 //if no TBB, use this to run only one thread
#define SAVE_SCREENSHOT 0
#define USE_SUPERSAMPLING 0
#define DISPLAYINFO 1

#if USE_SUPERSAMPLING == 1
#define SS 2
#else
#define SS 1
#endif

#define FRAMERATE_LIMIT 0

#if USE_TBB == 1
#include "tbb/tbb.h"
#endif

using namespace std;

#include "glsl_code.h"

/*
 * Global variables
 */

sf::Window the_window;
sf::Event the_event;

float fps = 1.0f;
int frames = 0;
sf::Clock the_clock;
uvec2 screen( 1280, 720 );
vec4* tex = 0;
float elapsed_time = 0.0f;
unsigned int current_time = 0;
unsigned int num_threads = 16;
bool silent = false;
bool fullscreen = false;
vec2 mouse_coords;

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

inline void thread_func( const uvec4& startend )
{
  uvec2 coord;
  glsl::glsl_code glsl;
  glsl.resolution = vec2( screen.x, screen.y );
  glsl.mouse = mouse_coords;
  glsl.time = elapsed_time;

  for( coord.y = startend.z; coord.y < startend.w; coord.y++ )
  {
    for( coord.x = startend.x; coord.x < startend.y; coord.x++ )
    {
      glsl.gl_FragCoord = vec4( coord.x, coord.y, 0, 0 );
      glsl.main();
      write_tex( glsl.gl_FragColor, coord );
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
      std::cout << "GLSL in c++, written by Tamas Marton.\n"
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

  screen *= SS;

  /*
   * Initialize OpenGL context
   */

  tex = new vec4[screen.x * screen.y];

  the_window.create( sf::VideoMode( screen.x / SS, screen.y / SS, 32 ), "GLSL in c++", fullscreen ? sf::Style::Fullscreen : sf::Style::Default );

  if( !the_window.isOpen() )
  {
    std::cerr << "Couldn't initialize SFML.\n";
    the_window.close();
    exit( 1 );
  }

#if FRAMERATE_LIMIT == 1
  the_window.setFramerateLimit( 30 );
  the_window.setVerticalSyncEnabled( true );
#endif

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

  glViewport( 0, 0, screen.x / SS, screen.y / SS );
  glMatrixMode( GL_PROJECTION );
  //x_min:0, x_max:1, y_min:0, y_max:1, z_min:0, z_max:-1
  mat4 ortho_matrix = ortographic( 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f );
  glLoadMatrixf( &ortho_matrix[0][0] );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glEnable( GL_TEXTURE_2D );

  glActiveTexture( GL_TEXTURE0 );
  glBindTexture( GL_TEXTURE_2D, gltex );

#if USE_TBB == 1
  //this basically divides the screen into 256 small parts
  std::vector<uvec4> startends;
  const unsigned int w = 16;
  const unsigned int h = 16;
  startends.resize( w * h );

  for( unsigned int x = 0; x < w; ++x )
  {
    for( unsigned int y = 0; y < h; ++y )
    {
      startends[x * h + y] = uvec4( ( screen.x / ( float )w ) * x, ( screen.x / ( float )w ) * ( x + 1 ), ( screen.y / ( float )h ) * y, ( screen.y / ( float )h ) * ( y + 1 ) );
    }
  }

  //initialize thread building blocks
  tbb::task_scheduler_init();
#endif

#if SAVE_SCREENSHOT == 1
  std::stringstream ss;
  int frame_count = 0;
  unsigned char* pixels = new unsigned char[screen.x / SS * screen.y / SS * 4];
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
          }
        case sf::Event::MouseMoved:
          {
            mouse_coords.x = the_event.mouseMove.x / ( float )screen.x;
            mouse_coords.y = 1.0f - the_event.mouseMove.y / ( float )screen.y;
          }
        default:
          break;
      }
    }

    //memset( tex, 0, screen.x * screen.y ); //clear screen

#if USE_TBB == 1
    //intel thread building blocks for the rescue!
    tbb::parallel_for( tbb::blocked_range<size_t>( 0, ( size_t )startends.size() ),
                       [ & ]( const tbb::blocked_range<size_t>& r )
    {
      for( size_t i = r.begin(); i != r.end(); ++i )
        thread_func( startends[i] );
    }
                     );
#else

#if ONETHREAD == 0

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

        threads.push_back( new sf::Thread( &thread_func, uvec4( amount * c, end, 0, screen.y ) ) );
        threads[c]->launch();
      }

      for( unsigned int c = 0; c < num_threads; c++ )
      {
        threads[c]->wait();
      }
    }
    else
    {
      thread_func( uvec4( 0, screen.x, 0, screen.y ) );
    }

#else
    thread_func( uvec4( 0, screen.x, 0, screen.y ) );
#endif

#endif

    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, screen.x, screen.y, GL_RGBA, GL_FLOAT, &tex[0][0] );

    /*
     * DRAW RESULT
     */

    draw_quad();

    /*
     * Show the result
     */

    the_window.display();

#if SAVE_SCREENSHOT == 1
    glFinish();
    sf::Image im;
    glReadPixels( 0, 0, screen.x / SS, screen.y / SS, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
    glFinish();
    im.create( screen.x / SS, screen.y / SS, pixels );
    im.flipVertically();
    ss << "screenshot" << frame_count++ << ".png";
    im.saveToFile( ss.str() );
    ss.str( "" );
#endif

#if DISPLAYINFO == 1
    frames++;

    elapsed_time += 1 / 30.0f;

    if( the_clock.getElapsedTime().asMilliseconds() - current_time > 1000.0f && !silent )
    {
      int timepassed = the_clock.getElapsedTime().asMilliseconds() - current_time;
      fps = 1000.0f / ( ( float ) timepassed / ( float ) frames );
      std::cout << "FPS: " << fps << " Time: " << ( float ) timepassed / ( float ) frames << "\n";
      frames = 0;
      current_time = the_clock.getElapsedTime().asMilliseconds();
    }

#endif
  }

#if SAVE_SCREENSHOT == 1
  delete [] pixels;
#endif

  return 0;
}


