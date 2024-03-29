#version 330 core
in vec3 vertexColor;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	vec2 coord = texCoord;
	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}