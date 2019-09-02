#ifndef PROGRAM_H
#define PROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../lib/neil_math.h"

class Shader{
public:
	unsigned int ID;
	Shader(const char *vertexPath, const char *fragmentPath);
	void use();
	void setFloat(const char *, float);
	void setInt(const char *, int);
	void setVec3f(const char *, float, float, float);
	void setVec3f(const char *, glm::vec3);
	void setVec3f(const char *, Vec3);
	void setMat4(const char *, glm::mat4);
	void setMat4(const char *, Mat4);
	GLint getAttribLoc(const char *);
};

#endif
