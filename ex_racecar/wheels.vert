#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 eye;

out vec3 vertexColor;

void main(){
	gl_Position = projection * view * model * vec4(in_pos, 1.0);
	vertexColor = in_color;
}