#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>



class utils{


public:
    utils(){}
        
public:

    std::string readShaderSource(const char *filePath);
    GLuint createShaderProgram(const char* filepath1,const char* filepath2);
    


};