#ifndef LIB_H
#define LIB_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "program.h"

typedef struct Neil_Geometry{
	GLuint VAO, EBO;
	GLint num_vertices;
	GLuint attribute[16];
	GLint texture_count;
	GLuint texture[16];
} neil_geometry;

void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
GLFWwindow* init(float, float);
void framebuffer_size_callback(GLFWwindow*, int, int);
void geom_texture(GLuint *, const char *, int, int);
void geom_attr(neil_geometry *, GLfloat *, GLuint, GLint, GLint, GLint);
void geom_indices(neil_geometry *, GLint *, GLint, GLint);

#endif
