#version 330 core
in vec3 vertNormal;
in vec3 fragPos;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 pos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material mat;
uniform Light light;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 eye;

out vec4 FragColor;

void main(){
	vec3 norm = normalize(vertNormal);
	vec3 lightDir = normalize(light.pos - fragPos);

	// ambient calculation
	vec3 ambient = mat.ambient * light.ambient;

	// diffuse calculation
	float diffuseScalar = max(dot(vertNormal, lightDir), 0.0);
	vec3 diffuse = (mat.diffuse * diffuseScalar) * light.diffuse;

	// specular calculation
	vec3 viewDir = normalize(eye - fragPos);
	vec3 reflectVec = reflect(-lightDir, norm);
	float specularScalar = pow(max(dot(viewDir, reflectVec), 0.0), mat.shininess * 128);
	vec3 specular = (mat.specular * specularScalar) * light.specular;

	// final result
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1);
}