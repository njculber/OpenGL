#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../lib/stb_image.h"
#include "../lib/program.h"
#include "../lib/lib.h"
#include "../lib/camera.h"

GLFWwindow *window;
#define screenWidth 640.0f
#define screenHeight 480.0f
Camera camera(glm::vec3(0.0, 0.0, 5.0), glm::vec3(3.0, 0.0, 0.0));

int firstmouse = 1;
float lastX = screenWidth / 2.0;
float lastY = screenHeight / 2.0;
float fov = 45.0f;
int line = 0;
float angle = 0.0f;
int rotating = 1;

neil_geometry cube, cylinder;

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){ 
        camera.processKeyboard(1);
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){ 
        camera.processKeyboard(2);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        camera.processKeyboard(3);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        camera.processKeyboard(4);
    }
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
        angle -= 0.5f;
    }
    if(glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
        angle += 0.5f;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        if(rotating){
            rotating = 0;
            std::cout << "set to 0\n";
        } 
        else {
            rotating = 1;
            std::cout << "set to 1\n";
        }
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        GLint polygonMode;
        glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
        if(polygonMode == GL_LINE)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } 
    
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos){
    (void)window;
    if(firstmouse){
        lastX = xPos;
        lastY = yPos;
        firstmouse = 0;
    }

    float x_offset = xPos - lastX;
    float y_offset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.processMouse(x_offset, y_offset);
}

void scroll_callback(GLFWwindow* window, double xOff, double yOff){
    (void)window; (void)xOff;
    fov -= yOff;
}

void init_cube(neil_geometry *geom, Shader prog){
    glGenVertexArrays(1, &geom->VAO);
    prog.use();

    GLfloat data[] = {
        -0.5f, -0.5f, 0.5f, // front face
         0.5f, -0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
         0.5f,  0.5f, 0.5f,

        -0.5f, -0.5f,  0.5f, // left face
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,

         0.5f, -0.5f,  0.5f, // right face
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f, // back face
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,

        -0.5f,  0.5f,  0.5f, // top face
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, // bottom face
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f
    };
    geom_attr(geom, data, geom->attribute[0], prog.getAttribLoc("aPos"), 3, 4*6);

    GLfloat color[] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0,
        1.0, 1.0, 1.0,

        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0, 
        1.0, 1.0, 1.0
    };
    geom_attr(geom, color, geom->attribute[1], prog.getAttribLoc("myColor"), 3, 8);

    GLfloat tex[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f, 

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f, 

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f, 

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f, 

        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };
    geom_attr(geom, tex, geom->attribute[2], prog.getAttribLoc("texCoordIn"), 2, 4*6);

    prog.setInt("texture1", geom->texture_count);
    geom_texture(&geom->texture[geom->texture_count++], "../images/container.jpg", 0, 0);

    prog.setInt("texture2", geom->texture_count);
    geom_texture(&geom->texture[geom->texture_count++], "../images/awesomeface.png", 1, 1);

    for(int i = 0; i < geom->texture_count; i += 1){
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, geom->texture[i]);
    }

    GLint indices[] = {
        0, 1, 2,
        1, 2, 3, 

        4, 5, 6, 
        5, 6, 7, 

        8, 9, 10, 
        9, 10, 11, 

        12, 13, 14, 
        13, 14, 15, 

        16, 17, 18, 
        17, 18, 19, 

        20, 21, 22, 
        21, 22, 23
    };
    geom_indices(geom, indices, 3, 2*6);
}

void init_cylinder(neil_geometry *geom, Shader prog){
    glGenVertexArrays(1, &geom->VAO);
    prog.use();

    GLfloat cyl_verts[] = {
        // bottom portion
        0.0, -0.5, 0.0,

      -0.25, -0.5, -0.5, // BL

       0.25, -0.5, -0.5, // BR

       0.5, -0.5, 0.0, // R

       0.25, -0.5, 0.5, // TR

       -0.25, -0.5, 0.5, // TL

       -0.5, -0.5, 0.0, // L

       // top portion
       0.0, 0.5, 0.0,

      -0.25, 0.5, -0.5, // BL

       0.25, 0.5, -0.5, // BR

       0.5, 0.5, 0.0, // R

       0.25, 0.5, 0.5, // TR

       -0.25, 0.5, 0.5, // TL

       -0.5, 0.5, 0.0 // L
    };
    geom_attr(geom, cyl_verts, geom->attribute[0], prog.getAttribLoc("in_pos"), 3, 3*7);

    GLfloat color[] = {
        1.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 
        0.0, 0.0, 1.0
    };
    geom_attr(geom, color, geom->attribute[1], prog.getAttribLoc("in_color"), 3, 3);

    GLint indices[] = {
        0, 1, 2, // top
        0, 2, 3, 
        0, 3, 4, 
        0, 4, 5, 
        0, 5, 6, 
        0, 6, 1, 

        7, 8, 9, // bottom
        7, 9, 10, 
        7, 10, 11, 
        7, 11, 12, 
        7, 12, 13, 
        7, 13, 8, 

        1, 2, 9, // Front face
        1, 8, 9,

        2, 3, 10, // FR face 
        2, 9, 10, 

        3, 4, 11, // BR face
        3, 10, 11, 

        4, 5, 12, // Back face
        4, 11, 12, 

        5, 6, 13, // BL face
        5, 12, 13, 

        6, 1, 8, // FL face
        6, 13, 8

    };
    geom_indices(geom, indices, 3, (7*2) + (2*6));
}

int main(){
    /***************************************************************************
    *                                INITIALIZE                                *
    ****************************************************************************/

    if( !(window = init(screenWidth, screenHeight)) ){
        std::cout << "Error initializing\n";
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader("racecar.vert", "racecar.frag");
    Shader shader2("wheels.vert", "wheels.frag");

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

    init_cube(&cube, shader);
    init_cylinder(&cylinder, shader2);

    /***************************************************************************
    *                                 DISPLAY                                  *
    ****************************************************************************/

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input
        processInput(window);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getView();
        glm::mat4 projection = glm::perspective(glm::radians(fov), 
                                    screenWidth/screenHeight, 
                                    0.1f, 
                                    100.0f);

        // model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 70.0f, glm::vec3(0.2, 1.0, 0.3));
        // model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));

        // model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
        shader.use();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glBindVertexArray(cube.VAO);
        glDrawElements(GL_TRIANGLES, cube.num_vertices, GL_UNSIGNED_INT, 0);

        model = glm::translate(model, glm::vec3(1.0, 0.0, 0.0));
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, cube.num_vertices, GL_UNSIGNED_INT, 0);

        model = glm::translate(model, glm::vec3(-2.0, 0.0, 0.0));
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, cube.num_vertices, GL_UNSIGNED_INT, 0);

        model = glm::translate(model, glm::vec3(1.0, 1.0, 0.0));
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, cube.num_vertices, GL_UNSIGNED_INT, 0);

        
        shader2.use();
        shader2.setMat4("view", view);
        shader2.setMat4("projection", projection);

        // front wheels
        model = glm::mat4(1.0f);
        // model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
        model = glm::translate(model, glm::vec3(-1.0, -0.4, 0.6));
        model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 60.0f * rotating, glm::vec3(0.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(0.7, 0.25, 0.7));
        shader2.setMat4("model", model);
        glBindVertexArray(cylinder.VAO);
        glDrawElements(GL_TRIANGLES, cylinder.num_vertices, GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0, -0.4, -0.6));
        model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 60.0f * rotating, glm::vec3(0.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(0.7, 0.25, 0.7));
        shader2.setMat4("model", model);
        glBindVertexArray(cylinder.VAO);
        glDrawElements(GL_TRIANGLES, cylinder.num_vertices, GL_UNSIGNED_INT, 0);

        // back wheels
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0, -0.4, 0.6));

        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 60.0f * rotating, glm::vec3(0.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(0.7, 0.25, 0.7));
        shader2.setMat4("model", model);
        glBindVertexArray(cylinder.VAO);
        glDrawElements(GL_TRIANGLES, cylinder.num_vertices, GL_UNSIGNED_INT, 0);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0, -0.4, -0.6));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 60.0f * rotating, glm::vec3(0.0, 0.0, 1.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        model = glm::scale(model, glm::vec3(0.7, 0.25, 0.7));
        shader2.setMat4("model", model);
        glBindVertexArray(cylinder.VAO);
        glDrawElements(GL_TRIANGLES, cylinder.num_vertices, GL_UNSIGNED_INT, 0);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO_vertices);
    // glDeleteBuffers(1, &VBO_colors);
    // glDeleteBuffers(1, &VBO_texture);
    // glDeleteBuffers(1, &EBO);
    
    glfwTerminate();
    return 0;
}
