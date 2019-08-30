#include "lib.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    (void)window;
    glViewport(0, 0, width, height);
}

void geom_attr(neil_geometry *geom, GLfloat *data, GLuint vbo, GLint loc, GLint components, GLint verts){

    glBindVertexArray(geom->VAO);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (components * verts), data, GL_STATIC_DRAW);
    glVertexAttribPointer(loc, components, GL_FLOAT, GL_FALSE, components * sizeof(float), (void*)0);
    glEnableVertexAttribArray(loc);
}

void geom_indices(neil_geometry *geom, GLint *data, GLint components, GLint edges){
	glBindVertexArray(geom->VAO);
	glGenBuffers(1, &geom->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geom->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * (components * edges), data, GL_STATIC_DRAW);
    geom->num_vertices = components * edges;
}

/*****************************************************************************************
*                                 TEXTURE                                                *
*   TEXTURE WRAPPING                                                                     *
*        - GL_REPEAT: Repeats texture image                                              *
*        - GL_MIRRORED_REPEAT: Same as above, but mirrors with each repeat               *
*        - GL_CLAMP_TO_EDGE: Clamps coordinates between 0 & 1                            *
*        - GL_CLAMP_TO_BORDER: Coordinates outside range are given border color          *
*                                                                                        *
*                                                                                        *
*   TEXTURE FILTERING:                                                                   *
*        - GL_NEAREST: (a.k.a Nearest Neighbor) Selects pixel which center is closest    *
*                    to texture coordinate.                                              *
*        - GL_LINEAR: (a.k.a (bi)Linear Filtering) Takes an interpolated value from the  *
*                    texture coordinates neighboring texels.                             *
*                                                                                        *
******************************************************************************************/

void geom_texture(GLuint *texture, const char * file, GLenum internalFormat, GLenum format, int flipped){
    GLuint tex = 0;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flipped);
    unsigned char *data;
    GLenum type = GL_RGB;
    if(type == format) data = stbi_load(file, &width, &height, &nrChannels, 0);
    else data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb_alpha);

    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Error loading " << file << " texture\n";
    }
    stbi_image_free(data);
    *texture = tex;
}

GLFWwindow* init(float width, float height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create OpenGL window\n";
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        //Problem: glewInit failed, something is seriously wrong. 
        fprintf(stderr, "Error with GLEW: %s\n", glewGetErrorString(err));
        return NULL;
    }
    
    return window;
}


