//
//  CameraPerspectiveDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef CameraPerspectiveDemo_hpp
#define CameraPerspectiveDemo_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <cmath>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"
#include "Matrices.hpp"

class CameraPerspectiveDemo {
private:
    GLuint *program;
    GLFWwindow *window;

    std::vector<GLfloat> vertex_floats;
    std::vector<GLfloat> colour_floats;
    std::vector<GLuint> vertex_array_objects;
    
    ShaderLoader shader_loader;
    GLParams gl_params;
    Matrices *m;
    
    void prepare(void) const;
    bool setupWindow(void);
    GLuint compileShader(const std::string *shader_src_str, GLenum type) const;
    GLuint linkShaders(const GLuint vertex_shader, const GLuint fragment_shader);
    GLuint prepareMesh(const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) const;
    
    void drawLoop(const std::vector<GLuint> *meshes) const;
    void applyMatrices(void) const;
    void keyActionListener(void) const;
    
public:
    CameraPerspectiveDemo(const std::vector<GLfloat> _vertex_floats, const std::vector<GLfloat> _colour_floats);
    ~CameraPerspectiveDemo();
    int run(void) const;
};

#endif /* CameraPerspectiveDemo_hpp */
