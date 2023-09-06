varying vec4 oNormal;
varying vec4 oPosition;

// ----------------------------------------------------------------------------
// Pseudo random noise function
float hash(vec3 p)
{
  p = fract(p*0.3183099+.1);
  p *= 17.0;
  return fract(p.x*p.y*p.z*(p.x+p.y+p.z));
}

float noise(in vec3 x)
{
  vec3 i = floor(x);
  vec3 f = fract(x);
  f = f*f*(3.0-2.0*f);
	
  return mix(mix(mix(hash(i+vec3(0,0,0)), 
		     hash(i+vec3(1,0,0)),f.x),
		 mix(hash(i+vec3(0,1,0)), 
		     hash(i+vec3(1,1,0)),f.x),f.y),
	     mix(mix(hash(i+vec3(0,0,1)), 
		     hash(i+vec3(1,0,1)),f.x),
		 mix(hash(i+vec3(0,1,1)), 
		     hash(i+vec3(1,1,1)),f.x),f.y),f.z);
}

vec3 noisemap(in vec3 p) {
  vec3 q = 16.0*p;
  float fx = 0.25000*noise(q);
  q = q*2.0; 
  float fy = fx + 0.12500*noise(q);
  q = q*2.0; 
  float fz = fy + 0.06250*noise(q);
  q = q*2.0;
  return p+vec3(fx,fy,fz);
}
// ----------------------------------------------------------------------------


// Volonoi---------------

vec2 dispHash(int i, int j){
     float x = float(i);
     float y = float(j);

     for(int i=0; i<2; ++i){
        x = mod(87.0*x + 23.0*y, 257.0);
	y = mod(87.0*x + 23.0*y, 1009.0);
     }

     return vec2(x/257.0, y/1009.0);
}

vec3 colHash(int i, int j){
     float r = float(i);
     float g = float(j);
     float b = float(i+j);

     for(int i=0; i<2; ++i){
       r = mod(87.0*r + 23.0*g + 125.0*b, 257.0);
       g = mod(87.0*r + 23.0*g + 125.0*b, 1009.0);
       b = mod(87.0*r + 23.0*g + 125.0*b, 21001.0);
     }
     return vec3(r/257.0, g/1009.0, b/21001.0);
}

vec3 vor2d(vec2 pos){
     float step = 10.0;

     int xi = int(floor(pos.x/step));
     int yj = int(floor(pos.y/step));
     
     ivec2 nearest;
     float min_dist = 1e5;

     for(int i = xi-1; i <= xi+1; ++i){
     	 for(int j=yj-1; j<=yj+1; j++){
	    vec2 disp = dispHash(i,j);
	    vec2 seed = vec2(
	    (float(i)+disp.x)*step,
	    (float(j)+disp.y)*step);
	    float dist = length(pos-seed);
	    if(dist < min_dist){
	       min_dist = dist;
	       nearest = ivec2(i,j);
	    }
	 }
     }
     // color of the cell
     vec3 col = colHash(nearest.x, nearest.y);
     return col;
}

// ---------------------------

void main(){
  // light position in eye space
  vec4 light2 = vec4(10.0, 5.0, 1.0, 1.0);

  // vertex in eye space
  vec4 V = oPosition;

  // vertex to light direction
  vec4 L = normalize(light2 - V);

  // normal in eye space
  vec4 N = oNormal;

  // apply a (pseudo-random) perturbation to the normal
  N.xyz = noisemap(N.xyz);
  N.w = 0.0;
  N = normalize(N);

  // material
  vec4 amb = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 diff = vec4(1.4, 0.7, 0.6, 1.0);
  vec4 spec = vec4(1.0, 1.0, 1.0, 1.0);
  float shiny = 16.0;
  
  // light color
  vec4 lcol = vec4(1.0, 1.0, 1.0, 1.0);

  // Phong shading model
  //
  // reflected light vector:
  vec4 R = reflect(-L, N);
  vec4 View = normalize(-V);

  // lighting
  float ndl = clamp(dot(N, L), 0.0, 1.0);
  float vdr = pow(clamp(dot(View, R), 0.0, 1.0), shiny);

  vec4 lin = vec4(0.0);
  lin += amb * lcol;
  lin += ndl * diff * lcol;
  lin += vdr * spec * lcol;

  //Voronoi
  //vec2 uv = 0.5 * (1.0 + fragCoord); 
  //vec2 pos = uv * 100.0;
  vec2 pos = gl_FragCoord.xy;
  vec3 col = vor2d(pos);
  gl_FragColor = vec4(col,1.0);
}