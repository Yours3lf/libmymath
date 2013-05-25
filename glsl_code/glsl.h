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
  gl_FragColor = vec4( gl_FragCoord.xy * mouse / resolution, sin( time ) * 0.5 + 0.5, 1 );
}
/**/
