//
//  VertexBudfferObjects.cpp
//  OpenGL
//
//  Created by Matt Finucane on 12/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "VertexBufferObjects.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

using namespace std;

/**
 *  Initialise these now so we can 
 *  load them in any function.
 */
ShaderLoader shader_loader_vbo;
GLParams gl_params_vbo;

/**
 *  Prepares a GLFW window
 *
 *  @return     {GLFWwindow*}
 *  @throws     {runtime_error}
 */
GLFWwindow *prepareWindowForVBO() {
    /**
     *  Setting hints for MacOS
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /**
     *  Prepping the window
     */
    GLFWwindow *window = glfwCreateWindow(1080, 810, "VertexBufferObjects", NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw runtime_error("Could not initialise the GLFW window.");
    }
    
    return window;
};

/**
 *  Compile shaders loaded from a file.
 *  
 *  @param      {const char*}   - GLSL source code.
 *  @param      {GLenum}        - GLenum shader type (GL_VERTEX_SHADER/GL_FRAGMENT_SHADER).
 *  @return     {GLuint}        - reference to where the compiled shader is stored.
 */
GLuint createShaderForVBO(const char *source, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    
    int p;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &p);
    if(GL_TRUE != p) {
        gl_params_vbo.print_shader_log(shader);
        return false;
    }
    
    return shader;
}

/**
 *  Function to compile a program from shaders.
 *  
 *  @param      {GLuint}    - reference to the compiled vertex shader.
 *  @param      {GLuint}    - reference to the compile fragment shader.
 */
GLuint compileProgramForVBO(GLuint vertex_shader, GLuint fragment_shader) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    int p;
    glGetProgramiv(program, GL_LINK_STATUS, &p);
    if(GL_TRUE != p) {
        gl_params_vbo.print_program_info_log(program);
        return false;
    }
    
    return program;
}

/**
 *  Listens for keyboard key press events and acts
 *  
 *  @param      {GLFWwindow*}
 *  @return     {void}
 */
void keyListeningLoopForVBO(GLFWwindow *window) {
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, 1);
    }
}

/**
 *  The main draw loop
 *
 *  @param      {GLFWwindow*}
 *  @return     {void}
 */
void drawloopForVBO(GLFWwindow *window) {
    /**
     *  Standard pre-draw tasks
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1080, 810);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /**
     *  Poll for events and swap buffers into the window.
     */
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void x() {
    
    /**
     *  Array of GLfloats for points
     *  and colours.
     */
    GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    GLfloat colours[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    /**
     *  Buffer for points.
     */
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    /**
     *  Buffer for colours.
     */
    GLuint colours_vbo;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colours), colours, GL_STATIC_DRAW);
}

/**
 *  Main execute function
 *  
 *  @param      {void}
 *  @return     {int}
 */
int vertex_buffer_objects_main(void) {
    
    /**
     *  Check to see if we can init GLFW.
     */
    if(!glfwInit()) {
        cout << "Could not initialise GLFW. Exiting." << endl;
        return 1;
    }
    
    try {
        /**
         *  Get the window and set the context to it.
         */
        GLFWwindow *window = prepareWindowForVBO();
        glfwMakeContextCurrent(window);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        while(!glfwWindowShouldClose(window)) {
            drawloopForVBO(window);
            keyListeningLoopForVBO(window);
        }
    }
    catch(exception &e) {
        cout << "Exception in main: " << e.what() << endl;
        return 1;
    }

    return 0;
}
