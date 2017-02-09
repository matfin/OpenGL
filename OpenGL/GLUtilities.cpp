//
//  GLUtilities.cpp
//  OpenGL
//
//  Created by Matt Finucane on 09/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <iostream>
#include "GLUtilities.hpp"
#include "GLParams.hpp"

using namespace std;

GLFWwindow* GLUtilities::setupWindow(const int gl_viewport_w, const int gl_viewport_h, const char *title) {
    
    GLFWwindow *window;
    
    if(!glfwInit()) {
        throw runtime_error("Could not initialise the GLFW window.");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(gl_viewport_w, gl_viewport_h, title, NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw runtime_error("GLFW failed to create a window.");
    }
    
    glfwMakeContextCurrent(window);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    return window;
}

GLuint GLUtilities::compileShader(const string shader_src_str, GLenum type) {
    
    GLuint shader = glCreateShader(type);
    
    const char *shader_src = shader_src_str.c_str();
    GLint shader_src_len = shader_src_str.length();
    
    glShaderSource(shader, 1, &shader_src, &shader_src_len);
    glCompileShader(shader);
    
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(GL_TRUE != status) {
        cout << "Failed to compile the shader with reference: " << shader << endl;
//        gl_params.print_shader_log(shader);
        return false;
    }
    
    return shader;
}

GLuint GLUtilities::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    
    GLuint program = glCreateProgram();
    
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    if(GL_TRUE != programReady(program)) {
        cout << "Failed to link the program with reference: " << program << endl;
//        gl_params.print_program_info_log(program);
    }
    
    return program;
}

GLint GLUtilities::programReady(const GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    return status;
}
