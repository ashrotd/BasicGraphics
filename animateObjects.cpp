#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

float x = 0.0f;
float inc = 0.01f;

#define numVAOs 1
GLuint renderingProgram; //GLuint means unsigned integer
GLuint vao[numVAOs];

string readShaderSource(const char *filePath){
    string content;
    ifstream fileStream(filePath,ios::in);
    string line="";

    while(!fileStream.eof()){
        getline(fileStream,line);
        content.append(line+"\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram() {
    
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); 
    //Generates Vertex shader empty object and returns an integer ID
    // That ID is stored in vShader and fShader 
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    string vertShaderStr = readShaderSource("vertShader.glsl");
    string fragShaderStr = readShaderSource("fragShader.glsl");

    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();
    

    //This process loades the GLSL code from string to empty shader
    //object.
    
    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    //After loading, it compiles the code
    glCompileShader(vShader);
    glCompileShader(fShader);

    // A program object saves ID that points to it
    GLuint vfProgram = glCreateProgram();

    // Attaches each of the shader to the program
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    //Requests the GLSL compiles ensure that they are compatible
    glLinkProgram(vfProgram);
    return vfProgram;
}
void init(GLFWwindow* window) {
    renderingProgram = createShaderProgram();

    // These lines deals with buffers required to pass
    // OpenGL need at least one Vertex array object which
    // Organizes the buffers
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
}
void display(GLFWwindow* window, double currentTime) {
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // loads the program containing two compiled shaders
    // into OpenGL pipeline state (onto GPU!)
    glUseProgram(renderingProgram); // It doesn't run shaders
        // But loads onto the hardware.

    x += inc;
    if(x>1.0f){   // move the triangle along x axis
    // switch to moving the triangle to the left
        inc=-0.01f; 
    }
    if(x<-1.0f){
        inc = 0.01f;
    }
    
    GLuint offsetLoc = glGetUniformLocation(renderingProgram,"offset"); //get pointer to offset from vertex shader
    
    glProgramUniform1f(renderingProgram,offsetLoc,x); //Send value x to offset
    //glPointSize(300.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Initiates pipeline processing
    // Primitive is a GL_Point, only one point to display
}
int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Checking version 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    GLFWwindow* window = glfwCreateWindow(600, 600, "Chapter2 - program1", NULL, NULL);
    
    glfwMakeContextCurrent(window); //Means Render Graphics in this window, not others
    
    if (glewInit() != GLEW_OK) { 
        exit(EXIT_FAILURE); }
    
    glfwSwapInterval(1);
    
    init(window);
    
    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);  // Puts from back buffer to front buffer
        // Swapping the front buffers and back buffers
        //In double-buffering graphics systems like OpenGL, rendering is done to a back buffer
        // while the front buffer is displayed.
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}