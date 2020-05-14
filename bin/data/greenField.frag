#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;


//in vec3 v_normal;

void main(){
    
    //float intensity = max(dot(v_normal.xyz, vec3(0.f, 0.5f, .5f)), 0.0);
    
    vec2 coord = gl_FragCoord.xy;
    vec3 color = vec3(0.0);
    //color.r = intensity;

    gl_FragColor = vec4(color, 1.0);
}
