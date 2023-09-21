#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 2


float cameraX,cameraY,cameraZ;
float cubeLocX,cubeLocY,cubeLocZ,pryLocX,pryLocY,pryLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Allocating varibles that will be used in display()

GLuint mvLoc,projLoc,tfLoc;
int width,height;
float aspect;
float timeFactor;
glm::mat4 pMat,vMat,mMat,mvMat;

void setupVertices(){
    float cubePositions[108] = {
    -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,+
    1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
};
// Pyramid with 18 vertices, 6 triangles
    float pyramidPositions[54]={
        -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // front face
        1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // right face
        1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // back face
        -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // left face
        -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, // base – left front
         1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f // base – right back
    };

    glGenVertexArrays(numVAOs,vao); // At least one VAO
    glBindVertexArray(vao[0]); // make VAO 0 as active buffer
    glGenBuffers(numVBOs,vbo); // we need at least two VBOs for two objects

    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]); // For the vertex of cube
    glBufferData(GL_ARRAY_BUFFER,sizeof(cubePositions),cubePositions,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(pyramidPositions),pyramidPositions,GL_STATIC_DRAW);
}

void init(GLFWwindow* window){
    //const char* file1 = "cubeVertexShader.glsl";
    //const char* file2 = "cubeFragShader.glsl";
    renderingProgram = utils::createShaderProgram("cubeVertexShader.glsl","cubeFragShader.glsl");
    cameraX = 0.0f;cameraY=0.0f;cameraZ = 8.0f;
    cubeLocX=0.0f;cubeLocY=-2.0f;cubeLocZ=0.0f;
    pryLocX=0.0f,pryLocY=2.0f,pryLocZ=3.0f;
    setupVertices();
}

void display(GLFWwindow* window,double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram); // to load the linked program in the GPU hardware, just load

    mvLoc = glGetUniformLocation(renderingProgram,"mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram,"proj_matrix");

    //build the perspective matrix
    glfwGetFramebufferSize(window,&width,&height);
    aspect = (float) width/(float) height;
    pMat = glm::perspective(1.0472f,aspect,0.1f,1000.0f);

    vMat = glm::translate(glm::mat4(1.0f),glm::vec3(-cameraX,-cameraY,-cameraZ));
    mMat = glm::translate(glm::mat4(1.0f),glm::vec3(cubeLocX,cubeLocY,cubeLocZ));

    mvMat = vMat*mMat;
    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER,vbo[0]); //Make VBO[0] active
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0); // based on layout 0 in vert shader, enabling it to take the input attribute

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36); 
    // Now render the Pyramid in the Scene
    
    // Now Render the Pyramid 
    mMat = glm::translate(glm::mat4(1.0f),glm::vec3(pryLocX,pryLocY,pryLocZ));
    mvMat = vMat*mMat;
    glUniformMatrix4fv(mvLoc,1,GL_FALSE,glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc,1,GL_FALSE,glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER,vbo[1]);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES,0,18);
}   


int main(void) { // main() is unchanged from before
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter 4 - program 1", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    
    glfwSwapInterval(1);
    
    init(window);
    
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
exit(EXIT_SUCCESS);
}