#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// uniform sampler2D texture1;
uniform sampler2D texture2;

out vec2 tex_coord;

void main(){
	float height = texture(texture2, in_tex).r * 0.2;
	vec3 pos = vec3(in_pos.x, 1.0 + height, in_pos.z);
	pos.x = -pos.x;
	gl_Position = projection * view * model * vec4(pos, 1.0);
	tex_coord = in_tex;
}