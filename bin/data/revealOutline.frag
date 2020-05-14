

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359

#define SAMPLES 64
#define WIDTH 5.0
#define COLOR vec4(1.0,1.0,1.0,1.0)
#define NUM_FRAMES 6.0

#define HASHSCALE 0.1031

float hash(float p)
{
    vec3 p3  = fract(vec3(p) * HASHSCALE);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

float fade(float t) { return t*t*t*(t*(6.*t-15.)+10.); }

float grad(float hash, float p)
{
    int i = int(1e4*hash);
    return (i & 1) == 0 ? p : -p;
}

float perlinNoise1D(float p)
{
    float pi = floor(p), pf = p - pi, w = fade(pf);
    return mix(grad(hash(pi), pf), grad(hash(pi + 1.0), pf - 1.0), w) * 2.0;
}

uniform sampler2D revealTexture;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

varying vec2        v_texcoord;


float normpdf(in float x, in float sigma)
{
    return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

vec4 blurSample(vec2 uv) {
    vec3 c = texture(revealTexture, uv).rgb;
    //declare stuff
    const int mSize = 11;
    const int kSize = (mSize-1)/2;
    float kernel[mSize];
    vec3 final_colour = vec3(0.0);
    
    //create the 1-D kernel
    float sigma = 7.0;
    float Z = 0.0;
    for (int j = 0; j <= kSize; ++j)
    {
        kernel[kSize+j] = kernel[kSize-j] = normpdf(float(j), sigma);
    }
    
    //get the normalization factor (as the gaussian has been clamped)
    for (int j = 0; j < mSize; ++j)
    {
        Z += kernel[j];
    }
    
    vec2 pixels = 1. / u_resolution;
    //read out the texels
    for (int i=-kSize; i <= kSize; ++i)
    {
        for (int j=-kSize; j <= kSize; ++j)
        {
            final_colour += kernel[kSize+j]*kernel[kSize+i]*texture(revealTexture, (uv + vec2(float(i),float(j)) * pixels)).rgb;

        }
    }
    
    
    return vec4(final_colour/(Z*Z), 1.0);
}

void main(){
    
    float currentAlpha = blurSample(v_texcoord ).r;
    
    if (currentAlpha < 0.5) {
        //OUTLINE
        float outlineAlpha = 0.0;
        float angle = 0.0;
        for( int i=0; i<SAMPLES; i++ ){
            angle += 1.0/(float(SAMPLES)/2.0) * PI;
            float w = WIDTH + sin(u_time * 15.0) * 4.0;
            vec2 testPoint = vec2( (w/u_resolution.x)*cos(angle), (w/u_resolution.y)*sin(angle) );
            testPoint = clamp( v_texcoord + testPoint, vec2(0, 0), u_resolution.xy );
            float sampledAlpha = texture( revealTexture,  testPoint ).r;
            outlineAlpha = max( outlineAlpha, sampledAlpha );
        }
        gl_FragColor = mix( vec4(0.0), COLOR, outlineAlpha * (0.5 + random(v_texcoord * 0.005) * 0.5) );
    }
    else {
        gl_FragColor = vec4(.0, 0.0, 0.0, 0.0);
    }
    
}
