#ifdef GL_ES
precision mediump float;
#endif

uniform mat4 normalMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform float u_time;

attribute vec4 position;

//in vec4 normal;

//out vec3 v_normal;

void main(){
    //v_normal = normal.xyz; //normalize((normalMatrix * vec4(normal.xyz, 0.0)).xyz);
    
    vec3 pos = vec3(position);
    pos.z *= sin(u_time);
    gl_Position = modelViewProjectionMatrix * vec4(pos.xyz, 1.0);
}
