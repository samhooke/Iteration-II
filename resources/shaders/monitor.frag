// Trimmed down version of http://glsl.heroku.com/e#11376.0

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float alpha;

void main(void) {
	// 3.1456
	//float w = (sin(gl_FragCoord.y*1.0+time*5));
	//vec3 col = vec3(0.1,0.3*(0.7+w), 0.1);
	//gl_FragColor = vec4(col, w);
	
	float w = sin(gl_FragCoord.y/resolution.y * 3.1456) * 0.5;
	vec3 col = vec3(0.2, 0.5 + w, 0.2);
	gl_FragColor = vec4(col, w);
}
