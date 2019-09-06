#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;

uniform mat4 mvp;
uniform vec3 eye;

void main(){
	gl_Position = mvp * vec4(in_pos, 1.0);
}