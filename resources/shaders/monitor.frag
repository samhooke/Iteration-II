// Trimmed down version of http://glsl.heroku.com/e#11376.0

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main(void)
{
	vec3 col = vec3(0.1,0.3*(.7+sin(gl_FragCoord.y*3.1456+time*1.2)), 0.1);
	gl_FragColor = vec4(col, 1.0);
}
