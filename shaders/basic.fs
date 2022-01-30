#version 130 

varying vec4 v_color;
varying vec2 v_textCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;


void main(void){

    vec4 u_texColor = texture2D(u_texture, v_textCoord);
    gl_FragColor  = u_texColor * u_color;
}