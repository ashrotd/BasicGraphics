#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 1
GLuint renderingProgram; //GLuint means unsigned integer
GLuint vao[numVAOs];
GLuint createShaderProgram() {
    const char *vshaderSource =
    "#version 410 \n"
    "void main(void) \n"
    "{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }"; //Coordinates in 3D
    
    //Rasterization process transfers this coordinates to pixel Locations(fragments)

    const char *fshaderSource =
    "#version 410 \n"
    "out vec4 color; \n" // Color is an output
    "void main(void) \n"
    "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";
    
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER); 
    //Generates Vertex shader empty object and returns an integer ID
    // That ID is stored in vShader and fShader 
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    //This process loades the GLSL code from string to empty shader
    //object.
    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

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
    // loads the program containing two compiled shaders
    // into OpenGL pipeline state (onto GPU!)
    glUseProgram(renderingProgram); // It doesn't run shaders
    // But loads onto the hardware.

    glPointSize(300.0f);
    glDrawArrays(GL_POINTS, 0, 1); // Initiates pipeline processing
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