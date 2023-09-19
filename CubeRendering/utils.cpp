#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <iostream>

#include "utils.h"


utils::utils(){}

GLuint utils:: createShaderProgram(const char* filepath1,const char* filepath2){

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderStr = readShaderSource(filepath1);
    std::string fragShaderStr = readShaderSource(filepath2);

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    glShaderSource(vshader,1,&vertShaderSrc,NULL);
    glShaderSource(fshader,1,&fragShaderSrc,NULL);

    glCompileShader(vshader);
    glCompileShader(fshader);

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram,vshader);
    glAttachShader(vfProgram,fshader);

    glLinkProgram(vfProgram);
    return vfProgram;
}

std::string utils::readShaderSource(const char* filepath){
    std::string content;
    std::ifstream fileStream(filepath,std::ios::in);
    std::string line="";

    while(!fileStream.eof()){
        getline(fileStream,line);
        content.append(line+"\n");
    }
    fileStream.close();
    return content;
}

    

    
