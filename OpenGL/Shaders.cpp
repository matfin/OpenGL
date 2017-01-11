//
//  Shaders.cpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Shaders.hpp"
#include <iostream>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

using namespace std;

GLParams shaders_gl_params;

GLFWwindow *prepareWindow() {
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
    GLFWwindow *window = glfwCreateWindow(1280, 960, "Shaders", NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw runtime_error("Could not initialise the GLFW window.");
    }
    
    return window;
}

/**
 *  @param {float} pos_x  - the x coordinate for the center point
 *  @param {float} pos_y  - the y coordinate for the center point
 *  @param {float} width  - the width
 *  @param {float} height - the height
 */
GLuint prepareTriangle(const float pos_x, const float pos_y, const float width, const float height) {
    /**
     *  Setting up the array of vertices.
     */
    float points[] = {
        pos_x, pos_y + (height / 2), 0.0f,
        pos_x + (width / 2), pos_y - (height / 2), 0.0f,
        pos_x - (width / 2), pos_y - (height / 2), 0.0f
    };
    
    /**
     *  Setting up the Vertex Buffer Ojbect (VBO)
     */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    /**
     *  Setting up the Vertex Attribute Object (VAO)
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    return vao;
}

GLuint prepareSquare(const float pos_x, const float pos_y, const float width, const float height) {
    return 0;
}

GLuint createShader(const char *source, const GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    /**
     *  Some shader compile error checking
     */
    int params;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params) {
        fprintf(stderr, "Error: GL Shader index %i did not compile.\n", shader);
        shaders_gl_params.print_shader_log(shader);
        return false;
    }
    return shader;
}

bool validateGLProgram() {
    return true;
}

GLuint linkProgram(const GLuint vert, const GLuint frag) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    
    /**
     *  Some program link error checking
     */
    int params;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if(GL_TRUE != params) {
        fprintf(stderr, "Error: could not link the program at GL index %u\n", program);
        shaders_gl_params.print_program_info_log(program);
        return false;
    }
    
    /**
     *  Delete the shaders when they are no longer needed.
     */
    glDeleteShader(vert);
    glDeleteShader(frag);
    
    return program;
}

static float _r = 0.0f;
static float _g = 0.0f;
static float _b = 0.0f;
static float _diff = 0.0005f;

void drawingLoop(GLFWwindow *window, GLuint program, GLuint vao, GLint colour_uniform_location) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 960);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program);
    
    /**
     *  We then create a glIUniform4f (note the 4) to pass in the
     *  uniform location and then thencolour we want as an
     *  rgba value (0 - 255 = 0.0f to 1.0f).
     *
     *  Note: It's important to call these two after glUseProgram
     */
    glUniform4f(colour_uniform_location, _r, _g, _b, 1.0f);
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glfwPollEvents();
    glfwSwapBuffers(window);
    
    if(_r >= 1.0f) {
        _diff = -0.0005f;
    }
    else if(_r <= 0.0f) {
        _diff = 0.0005f;
    }
    
    _r += _diff;
    _g += _diff;
    _b += _diff;
}

int shaders_main(void) {
    
    GLFWwindow *window;
    
    if(!glfwInit()) {
        cout << "Unable to initialise GLFW. Exiting";
        return 1;
    }
    
    try {
        window = prepareWindow();
        glfwMakeContextCurrent(window);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        ShaderLoader loader;
        string vertex_shader_str = loader.load("shaders.vert");
        string fragment_shader_str = loader.load("shaders.frag");
        
        const char *vert_shader_src = vertex_shader_str.c_str();
        const char *frag_shader_src = fragment_shader_str.c_str();
        
        GLuint vert_shader = createShader(vert_shader_src, GL_VERTEX_SHADER);
        GLuint frag_shader = createShader(frag_shader_src, GL_FRAGMENT_SHADER);
        GLuint program = linkProgram(vert_shader, frag_shader);
        GLuint vao = prepareTriangle(0.0f, 0.0f, 1.0f, 1.5f);
        
        GLint colour_uniform_location = glGetUniformLocation(program, "inputColour");
        
        while(!glfwWindowShouldClose(window)) {
            drawingLoop(window, program, vao, colour_uniform_location);
        }
    }
    catch(exception &e) {
        cout << "Error: " << e.what() << endl;
        glfwTerminate();
    }
    
    /**
     *  Exit when done.
     */
    glfwTerminate();
    return 0;
}
