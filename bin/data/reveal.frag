
#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D depthTexture;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;


varying vec2        v_texcoord;

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(){
    
    vec3 texColor = texture2D(depthTexture, v_texcoord).rgb;
    
    if (texColor.r > 0.4) {
        float scale = texColor.r;
        scale = map(scale, 0.4, 1.0, 0.5, 1.0);

        gl_FragColor = vec4(scale, scale, scale, 1.0);
    }
    else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
}
