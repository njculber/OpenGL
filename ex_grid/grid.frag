#version 330 core
in vec2 tex_coord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
	// FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	FragColor = texture(texture2, tex_coord);
}