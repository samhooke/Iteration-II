// Fractal section from: http://glsl.heroku.com/e#8791.0
// which was inspired by: http://www.fractalforums.com/new-theories-and-research/very-simple-formula-for-fractal-patterns/

// Uncomment to use the (intensive, weird, distracting) fractal shader
// #define USE_FRACTAL

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
#ifdef USE_FRACTAL
uniform vec2 mouse;
#endif
uniform vec2 resolution;
uniform float alpha;

#define N 5
void main(void) {
	// Oval glow
	vec2 position = ( gl_FragCoord.xy / resolution.xy ) - vec2(0.5, 0.5);
	float distance = position[0]*position[0]+position[1]*position[1];
#ifdef USE_FRACTAL
	float glow = (0.7 - (distance / 0.8)) / 2.0;
#else
    float glow = (0.7 - (distance / 0.8)) / 0.5;
#endif // USE_FRACTAL
	glow = max(glow, 0.0);

	// Scanlines
	float scanline = mod(gl_FragCoord.y * 1.23 + time * 0.04, 4.0) < 2.0 ? 0.0 : 2.0;
	
#ifdef USE_FRACTAL
	// Fractal
	vec2 v = (gl_FragCoord.xy - resolution/2.0) / min(resolution.y, resolution.x) * 20.0;

	float rsum = 0.0;
	float pi2 = 3.1415926535 * 2.0;
	float C = cos(mouse.x * pi2 / 2. + pi2 / 4.);
	float S = sin(mouse.x * pi2 / 2. + pi2 / 4.);
	vec2 shift = vec2( 0.0, 1.0 );
	float zoom = (mouse.y*1.0 + 1.0);
	
	for (int i = 0; i < N; i++){
		float rr = v.x * v.x + v.y * v.y;
		if (rr > 1.0){
			rr = 1.0 / rr;
			v.x = v.x * rr;
			v.y = v.y * rr;
		}
		rsum *= 0.99;
		rsum += rr;
		
		v += 0.05 * sin(atan(v.y + mouse.y, v.x + mouse.x) * 2.0);
		v = vec2(C * v.x - S * v.y, S * v.x + C * v.y) * zoom + shift;
	}
	
	float col = rsum;

	// Combined the three effects
	float frac = sin(col);
#else
    float frac = 0.0;
#endif // USE_FRACTAL
    
	gl_FragColor = vec4(0, max(min(frac * 0.5,1.0),0.0) * glow + glow * 0.2, 0, alpha) * scanline;
}