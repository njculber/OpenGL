#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 myColor;
layout (location = 2) in vec2 texCoordIn;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 mvp;

out vec3 vertNormal;
out vec3 fragPos;

void main(){
	/*
		MODEL MATRIX:       object ----> world
		VIEW MATRIX:        world  ----> eye
        PROJECTION MATRIX:  eye    ----> clip-space
	*/
    gl_Position = mvp * vec4(aPos, 1.0);
	vertNormal = mat3(transpose(inverse(model))) * normal;
	fragPos = vec3(model * vec4(aPos, 1.0f));
}