
const float tau = 6.28318530717958647692;



uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

float PHI = 1.61803398874989484820459;  // Φ = Golden Ratio

float gold_noise(in vec2 xy, in float seed){
       return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}
vec4 GoldenNoise(vec2 uv) {
    return vec4(gold_noise(uv, sin(u_time * 0.01) * 834), 0, 0, 0);
}

// Gamma correction
#define GAMMA (2.2)

vec3 ToLinear( in vec3 col )
{
    // simulate a monitor, converting colour values into light values
    return pow( col, vec3(GAMMA) );
}

vec3 ToGamma( in vec3 col )
{
    // convert back into colour values, so the correct light will come out of the monitor
    return pow( col, vec3(1.0/GAMMA) );
}

vec4 Noise( in ivec2 x )
{
    return GoldenNoise((vec2(x)+0.5)/256.0);
}



vec4 Rand( in int x )
{
    vec2 uv;
    uv.x = (float(x)+0.5)/256.0;
    uv.y = (floor(uv.x)+0.5)/256.0;
    return GoldenNoise(uv);
}





float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

varying vec2        v_texcoord;

void main(){
    vec3 ray;
    ray.xy = 2.0*((v_texcoord.xy * u_resolution.xy)-u_resolution.xy*.5)/u_resolution.x;
    ray.z = 1.0;

    float offset = u_time*.5;
    float speed2 = u_time * 0.01;
    float speed = speed2 + 2.0;// + sin(iTime) * (1.8 * random(v_texcoord.xy));
    offset += offset*1.0;
    offset *= 1.0;
    
    
    vec3 col = vec3(0);
    
    vec3 stp = ray/max(abs(ray.x),abs(ray.y));
    
    vec3 pos = 2.0*stp+.5;
    for ( int i=0; i < 20; i++ )
    {
        float z = random(ivec2(pos.xy));
        z = fract(z-offset);
        float d = 50.0*z-pos.z;
        float w = pow(max(0.0,1.0-8.0*length(fract(pos.xy)-.5)),2.0);
        vec3 c = max(vec3(0),vec3(1.0-abs(d+speed2*10.0)/speed,1.0-abs(d)/speed,1.0-abs(d-speed2*10.0)/speed));
        col += 1.5*(1.0-z)*c*w;
        pos += stp;
    }
    
    gl_FragColor = vec4(ToGamma(col),1.0);
}
