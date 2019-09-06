#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../lib/stb_image.h"
#include "../lib/program.h"
#include "../lib/lib.h"
#include "../lib/camera.h"
#include "../lib/neil_math.h"

GLFWwindow *window;
#define screenWidth 1920.0f
#define screenHeight 1080.0f
Camera camera(Vec3(0.0, 0.0, 5.0), Vec3(3.0, 0.0, 0.0));

int firstmouse = 1;
float lastX = screenWidth / 2.0;
float lastY = screenHeight / 2.0;
float fov = 45.0f;

neil_geometry grid;

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

void init_grid(neil_geometry *geom, Shader prog){
    glGenVertexArrays(1, &geom->VAO);
    prog.use();

    const int rows = 400;
    const int cols = 400;
    float squareSize = 0.001f;
    int arrIndex;

    // set up vertices
    GLfloat data[rows*cols*3];
    for(int i = 0; i < rows; i += 1){
        for (int j = 0; j < cols; j += 1){
            arrIndex = (i*cols*3) + (j*3);
            data[arrIndex] = (GLfloat)j * squareSize;
            data[arrIndex+1] = 0.0;
            data[arrIndex+2] = -(GLfloat)i * squareSize;
        }
    }
    geom_attr(geom, data, geom->attribute[0], prog.getAttribLoc("in_pos"), 3, rows*cols);

    // set up indices
    GLint indices[3 * (rows-1) * (cols-1)];
    for(int i = 0; i < rows-1; i += 1){
        for(int j = 0; j < cols-1; j += 1){
            arrIndex = (i*6*(cols-1)) + j*6;
            int bottomCorner = (i * cols) + j;
            int topRightCorner = ((i+1) * cols) + 1 + j;

            indices[arrIndex] = bottomCorner;
            indices[arrIndex+1] = topRightCorner - cols;
            indices[arrIndex+2] = topRightCorner;
            indices[arrIndex+3] = bottomCorner;
            indices[arrIndex+4] = topRightCorner - 1;
            indices[arrIndex+5] = topRightCorner;
        }
    }
    geom_indices(geom, indices, 3, 2*(rows-1)*(cols-1));
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

    Shader shader("triangle.vert", "triangle.frag");
    init_grid(&grid, shader);

    /***************************************************************************
    *                                 DISPLAY                                  *
    ****************************************************************************/

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        // render
        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input
        processInput(window);

        Mat4 model(1.0f);
        Mat4 view = camera.getView();
        Mat4 projection = perspective(fov, 
                                    screenWidth/screenHeight, 
                                    0.1f, 
                                    100.0f);
        // draw
        shader.use();
        shader.setMat4("mvp", projection * view * model);

        glBindVertexArray(grid.VAO);
        glDrawElements(GL_TRIANGLES, grid.num_vertices, GL_UNSIGNED_INT, 0);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
