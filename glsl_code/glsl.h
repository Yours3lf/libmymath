/**
 * Write GLSL code here
 *
 * Built-ins:
 * float time; //elapsed time since application start in seconds
 * vec2 mouse; //mouse coordiantes [0...1], with y = 1 being the top of the window
 * vec2 resolution; //window size in pixels
 * vec4 gl_FragColor;
 * vec4 gl_FragCoord;
 */

/**/
void main()
{
  vec2 msperr = mouse / resolution;
  msperr *= gl_FragCoord.xy;
  gl_FragColor.xy = msperr;
  gl_FragColor.z = sin( time ) * 0.5 + 0.5;
  gl_FragColor.w = 1;
}
/**/
