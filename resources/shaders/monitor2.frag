#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.xy ) - vec2(0.5, 0.5);
	float distance = position[0]*position[0]+position[1]*position[1];
	float color = (0.5 - (distance / 0.6)) / 2.0;

	float scanline = mod(gl_FragCoord.y, 4.0) < 2.0 ? 0.7 : 1.0;
	gl_FragColor = vec4(0, color, 0, 1.0 ) * scanline;
}