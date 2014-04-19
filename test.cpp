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
    double elapsed = std::chrono::duration_cast<std::chrono::seconds>(after - before).count();
    return elapsed;
  }

  double get_elapsed_time_milliseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
    return elapsed;
  }

  double get_elapsed_time_microseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
    return elapsed;
  }

  double get_elapsed_time_nanoseconds()
  {
    auto after = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
    return elapsed;
  }

  timer()
  {
    restart();
  }
};

void print_sse_mask(unsigned mask)
{
  using namespace std;

  unsigned w = (mask >> 6) & 3;
  unsigned z = (mask >> 4) & 3;
  unsigned y = (mask >> 2) & 3;
  unsigned x = mask & 3;

  auto helper = [](unsigned m) -> string
  {
    switch(m)
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

  cout << helper(x) << helper(y) << helper(z) << helper(w) << endl;
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
  cout << "CPU cycles per action: " << (action_time / cycle_time) << " cycles" << endl;
}

void fill_vec_rand( float* f, int l )
{
  for( int c = 0; c < l; ++c )
    *(f + c) = rand() % 101 / 100.0f; 
}

void fill_mat_rand( float* f, int l )
{
  for( int c = 0; c < l; ++c )
    for( int d = 0; d < l; ++d )
      *(f + c * l + d) = rand() % 101 / 100.0f;
}

std::ostream& operator<<( std::ostream& o, glm::simdVec4 v )
{
  return o << "( " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << " )\n";
}

std::ostream& operator<<( std::ostream& o, glm::simdMat4 m )
{
  return o      << "( " << m[0].x << ", " << m[1].x << ", " << m[2].x << ", " << m[3].x << "\n  "
         /*__________*/ << m[0].y << ", " << m[1].y << ", " << m[2].y << ", " << m[3].y << "\n  "
         /*__________*/ << m[0].z << ", " << m[1].z << ", " << m[2].z << ", " << m[3].z << "\n  "
         /*__________*/ << m[0].w << ", " << m[1].w << ", " << m[2].w << ", " << m[3].w << " )\n";
}

int main( int argc, char** args )
{
  using namespace mymath;
  using namespace std;

  srand(time(0));

  double freq = 2.66e+9;

  /**
  //benchmarks
  mat4 m;
  vec4 v;

  fill_vec_rand(&v.x, v.length());
  fill_mat_rand(&m[0].x, m[0].length());

  benchmark( m, v, freq, []( mat4& a, vec4& b )
  {
    b = determinant_helper( a );
  } );

  glm::simdMat4 gm;
  glm::simdVec4 gv;

  fill_vec_rand(&gv.x, 4);
  fill_mat_rand(&gm[0].x, 4);

  benchmark( gm, gv, freq, []( glm::simdMat4& a, glm::simdVec4& b )
  {
    b = glm::detail::sse_det_ps( &a[0].Data );
  } );

  cout << m << v;
  cout << gm << gv;
  /**/

  /*
   * vec2 tests
   */

  cout << vec2( 1, 2 )
       << vec2( 1 )
       << vec2();

  vec2 a;
  a[0] = 1;

  a *= vec2(2);
  a /= vec2(2);

  a += vec2(2);
  a -= vec2(2);

  a = vec2(4);
  a %= vec2(3);

  a &= vec2(2);
  a ^= vec2(2);

  a |= vec2(2);

  ++a;
  a++;

  --a;
  a--;

  cout << a.length() << endl;

  a.xy = vec2();
  a.xy = a.yx;

  a.xy *= vec2();
  a.xy *= a.xy;

  a = vec2(1, 2);
  a.xy /= vec2(2, 2).xy;
  cout << a;

  a.xy += a.xy;
  a.xy -= a.xy;

  a = vec2(1);
  cout << a.xx
       << a.xxx
       << a.yxx
       << a.xyx
       << a.xxy
       << a.xxxx
       << a.yxxx
       << a.xyxx
       << a.xxyx
       << a.yyxx;

  cout << endl;

  /*
   * vec3 tests
   */

  cout << vec3(1, 2, 3)
       << vec3(vec2(1, 2), 3)
       << vec3(1, vec2(2, 3))
       << vec3(1)
       << vec3();

  vec3 aa;
  aa[0] = 1;

  aa *= vec3();
  aa /= vec3(1);
  aa += vec3();
  aa -= vec3();
  aa %= vec3();
  aa &= vec3();
  aa ^= vec3();
  aa |= vec3();
  ++aa;
  aa++;
  --aa;
  aa--;
  cout << aa.length() << endl;

  aa.xyz = aa.xyz;
  aa.xyz *= aa.xyz;
  aa.xyz /= vec3(1).xyz;
  aa.xyz += aa.xyz;
  aa.xyz -= aa.xyz;

  aa = vec3(1);
  cout << aa.xxx
       << aa.yxx
       << aa.xyx
       << aa.xxy
       << aa.xx;

  aa.xy = aa.xy;
  aa.xy *= aa.xy;
  aa.xy /= vec2(1).xy;
  aa.xy += aa.xy;
  aa.xy -= aa.xy;

  aa = vec3(1);
  cout << aa.xxxx
       << aa.yxxx
       << aa.xyxx
       << aa.xxyx
       << aa.xxxy
       << aa.xxyy
       << aa.xyyx
       << aa.xyzz
       << aa.xxyz
       << aa.xyzx
       << aa.xyzy
       << aa.xyyz;

  /*
   * vec4 tests
   */

  cout << vec4(1, 2, 3, 4)
       << vec4(vec3(1, 2, 3), 4)
       << vec4(1, vec3(2, 3, 4))
       << vec4(vec2(1, 2), vec2(3, 4))
       << vec4(vec2(1, 2), 3, 4)
       << vec4(1, vec2(2, 3), 4)
       << vec4(1, 2, vec2(3, 4))
       << vec4(1)
       << vec4();

  vec4 aaa;
  aaa[0] = 1;

  aaa *= vec4();
  aaa /= vec4();
  aaa += vec4();
  aaa -= vec4();
  aaa %= vec4();
  aaa &= vec4();
  aaa ^= vec4();
  aaa |= vec4();
  ++aaa;
  aaa++;
  --aaa;
  aaa--;

  cout << aaa.length() << endl;

  aaa.xwyz = aaa.ywzx;
  aaa.xwyz *= aaa.xwzy;
  aaa.xywz /= aaa.xzwy;
  aaa.xyzw += aaa.xywz;
  aaa.xyzw -= aaa.xyzw;

  cout << aaa.xxxx
       << aaa.yxxx
       << aaa.xyxx
       << aaa.xxyx
       << aaa.xxxy
       << aaa.xyzz
       << aaa.xzyz
       << aaa.xyyz
       << aaa.xxx
       << aaa.yxx
       << aaa.xyx
       << aaa.xxy
       << aaa.xyz;

  aaa.xyz = aaa.xzy;
  aaa.xyz *= aaa.zyx;
  aaa.xyz /= aaa.xzy;
  aaa.xyz += aaa.xyz;
  aaa.xyz -= aaa.xyz;

  cout << aaa.xx;

  aaa.xy = aaa.yx;
  aaa.xy *= aaa.zy;
  aaa.xy /= aaa.zy;
  aaa.xy += aaa.zy;
  aaa.xy -= aaa.zy;

  new vec2;
  new vec3;
  new vec4;
  new mat2;
  new mat3;
  new mat4;

  return 0;
}
