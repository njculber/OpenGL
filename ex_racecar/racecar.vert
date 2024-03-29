#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 myColor;
layout (location = 2) in vec2 texCoordIn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec2 texCoord;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vertexColor = myColor;
	texCoord = texCoordIn;
}