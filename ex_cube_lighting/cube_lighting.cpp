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
#define screenWidth 640.0f
#define screenHeight 480.0f
Camera myCam(Vec3(0.0, 0.0, 5.0), Vec3(0.0, 0.0, 0.0));

int firstmouse = 1;
float lastX = screenWidth / 2.0;
float lastY = screenHeight / 2.0;
float fov = 45.0f;

neil_geometry cube, light_cube;

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){ 
        myCam.processKeyboard(1);
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){ 
        myCam.processKeyboard(2);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        myCam.processKeyboard(3);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        myCam.processKeyboard(4);
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

    myCam.processMouse(x_offset, y_offset);
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

    GLfloat normals[] = {
        0.0, 0.0, 1.0, 
        0.0, 0.0, 1.0, 
        0.0, 0.0, 1.0, 
        0.0, 0.0, 1.0, 

        -1.0, 0.0, 0.0, 
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,

        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,

        0.0, 0.0, -1.0, 
        0.0, 0.0, -1.0, 
        0.0, 0.0, -1.0, 
        0.0, 0.0, -1.0, 

        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,

        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
    };
    geom_attr(geom, normals, geom->attribute[1], prog.getAttribLoc("normal"), 3, 4*6);

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

void init_light_cube(neil_geometry *geom, Shader prog){
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
    geom_attr(geom, data, geom->attribute[0], prog.getAttribLoc("in_pos"), 3, 4*6);

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

    Shader shader("diff_spec.vert", "diff_spec.frag");
    Shader shader2("light.vert", "light.frag");

    init_cube(&cube, shader);
    init_light_cube(&light_cube, shader2);

    shader.use();
    shader.setVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3f("light.diffuse", 0.5f, 0.5f, 0.5f);
    shader.setVec3f("light.specular", 1.0f, 1.0f, 1.0f);

    // obsidian material
    shader.setVec3f("mat.ambient", 0.05375f, 0.5f, 0.06625f);
    shader.setVec3f("mat.diffuse", 0.028275f, 0.17, 0.22525f);
    shader.setVec3f("mat.specular", 0.1732741f, 0.0328634f, 0.346435f);
    shader.setFloat("mat.shininess", 0.2f);
    /*
        For more materials, visit:
        http://devernay.free.fr/cours/opengl/materials.html
    */

    /***************************************************************************
    *                                 DISPLAY                                  *
    ****************************************************************************/

    glEnable(GL_DEPTH_TEST); 

    while(!glfwWindowShouldClose(window)){
        // render
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // input
        processInput(window);

        Mat4 model;
        Mat4 view = myCam.getView();
        Mat4 proj = perspective(fov, screenWidth/screenHeight, 0.1, 100.0f);
        Mat4 mvp;

        // draw color cube
        shader.use();
        Vec3 lightPos(2.6f, 1.9f, 5.2f);
        shader.setVec3f("light.pos", lightPos);
        shader.setVec3f("eye", myCam.position);
        glBindVertexArray(cube.VAO);

        model.toIdentity();
        model = rotate(model, glfwGetTime(), Vec3(2.0,1.3,1.8));
        model = translate(model, Vec3(0.0, 0.0, -1.4));
        mvp = proj * view * model;
        shader.setMat4("model", model);
        shader.setMat4("mvp", mvp);
        glDrawElements(GL_TRIANGLES, cube.num_vertices, GL_UNSIGNED_INT, 0);


        // draw light
        shader2.use();
        Mat4 model1(1.0f);
        model1 = translate(model1, lightPos);
        model1 = scale(model1, Vec3(0.2f, 0.2f, 0.2f));

        mvp = proj * view * model1;
        shader2.setMat4("mvp", mvp);
        glBindVertexArray(light_cube.VAO);
        glDrawElements(GL_TRIANGLES, light_cube.num_vertices, GL_UNSIGNED_INT, 0);

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
