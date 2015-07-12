#include "mymath/mymath.h"

#define GLM_FORCE_SSE2
#define GLM_SIMD_ENABLE_XYZW_UNION
#include "glm/glm.hpp"
#include "glm/gtx/simd_mat4.hpp"
#include "glm/gtx/simd_vec4.hpp"

#include <string>
#include <time.h>
#include <chrono>

class timer
{
  std::chrono::time_point<std::chrono::high_resolution_clock> before;

public:
  void restart()
  {
    before = std::chrono::high_resolution_clock::now();
  }

  double get_elapsed_time_seconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::seconds>( after - before ).count();
    return elapsed;
  }

  double get_elapsed_time_milliseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>( after - before ).count();
    return elapsed;
  }

  double get_elapsed_time_microseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>( after - before ).count();
    return elapsed;
  }

  double get_elapsed_time_nanoseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>( after - before ).count();
    return elapsed;
  }

  timer()
  {
    restart();
  }
};

void print_sse_mask( unsigned mask )
{
  using namespace std;

  unsigned w = ( mask >> 6 ) & 3;
  unsigned z = ( mask >> 4 ) & 3;
  unsigned y = ( mask >> 2 ) & 3;
  unsigned x = mask & 3;

  auto helper = []( unsigned m ) -> string
  {
    switch( m )
    {
    case 0:
      return "x";
    case 1:
      return "y";
    case 2:
      return "z";
    case 3:
      return "w";
    }

    return "";
  };

  cout << helper( x ) << helper( y ) << helper( z ) << helper( w ) << endl;
}

template< class t, class u, class v >
void benchmark( u& uu, v& vv, double freq, const t& tt )
{
  using namespace std;

  timer ttt;

  int count = 1e+8;

  ttt.restart();

  for( int c = 0; c < count; ++c )
  {
    tt( uu, vv );
  }

  double action_time = ttt.get_elapsed_time_nanoseconds() / (double)count;
  double cycle_time = 1.0e+9 / freq;

  cout << "Time per action: " << action_time << " nanoseconds" << endl;
  //cout << "Cycle time: " << cycle_time << " nanoseconds" << endl;
  cout << "CPU cycles per action: " << ( action_time / cycle_time ) << " cycles" << endl;
}

void fill_vec_rand( float* f, int l )
{
  for( int c = 0; c < l; ++c )
    *( f + c ) = rand() % 101 / 100.0f;
}

void fill_mat_rand( float* f, int l )
{
  for( int c = 0; c < l; ++c )
    for( int d = 0; d < l; ++d )
      *( f + c * l + d ) = rand() % 101 / 100.0f;
}

std::ostream& operator<<( std::ostream& o, const glm::simdVec4& v )
{
  return o << "( " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " )\n";
}

std::ostream& operator<<( std::ostream& o, const glm::simdMat4& m )
{
  return o << "( " << m[0].x << ", " << m[1].x << ", " << m[2].x << ", " << m[3].x << "\n  "
    << m[0].y << ", " << m[1].y << ", " << m[2].y << ", " << m[3].y << "\n  "
    << m[0].z << ", " << m[1].z << ", " << m[2].z << ", " << m[3].z << "\n  "
    << m[0].w << ", " << m[1].w << ", " << m[2].w << ", " << m[3].w << " )\n";
}

int main( int argc, char** args )
{
  using namespace mymath;
  using namespace std;

  srand( time( 0 ) );

  double freq = 3.4e+9;

  camera<float> c;

  /**/
  //benchmarks
  mat4 m;
  vec4 v;

  fill_vec_rand( &v.x, v.length() );
  fill_mat_rand( &m[0].x, m[0].length() );

  cout << inverse( inverse( m ) ) << m;

  benchmark( m, v, freq, []( mat4& a, vec4& b )
  {
    a = inverse( a );
  } );

  glm::simdMat4 gm;
  glm::simdVec4 gv;

  //fill_vec_rand(&gv.x, 4);
  //fill_mat_rand(&gm[0].x, 4);
  memcpy( &gm, &m, sizeof( mat4 ) );
  memcpy( &gv, &v, sizeof( vec4 ) );

  benchmark( gm, gv, freq, []( glm::simdMat4& a, glm::simdVec4& b )
  {
    glm::detail::sse_inverse_fast_ps( &a[0].Data, &a[0].Data );
  } );

  cout << m << v;
  cout << gm << gv;
  /**/

  return 0;
}
