#ifndef glsl_code_h
#define glsl_code_h

#include "mymath/mymath.h"
using namespace mymath;

namespace glsl
{

  class glsl_code
  {
    public:
      vec4 gl_FragCoord;
      float time; //elapsed time since application start in seconds
      vec2 mouse; //mouse coordiantes [0...1], with y = 1 being the top of the window
      vec2 resolution; //window size in pixels
      vec4 gl_FragColor;

      inline void main();
      glsl_code()
      {
        gl_FragCoord = vec4( 0, 0, 0, 0 );
        time = 0;
        mouse = vec2( 0, 0 );
        resolution = vec2( 0, 0 );
        gl_FragColor = vec4( 0, 0, 0, 1 );
      }
  };

#define time glsl_code::time
#define mouse glsl_code::mouse
#define resolution glsl_code::resolution
#define gl_FragColor glsl_code::gl_FragColor
#define gl_FragCoord glsl_code::gl_FragCoord

#define main glsl_code::main
#include "glsl.h"
#undef main

}
#endif
