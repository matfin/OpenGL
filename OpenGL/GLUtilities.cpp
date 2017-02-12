//
//  GLUtilities.cpp
//  OpenGL
//
//  Created by Matt Finucane on 09/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "GLUtilities.hpp"
#include "GLParams.hpp"

using namespace std;

/**
 *  This is where we need to set the window up
 *  and tee up GLFW. We need to do this first
 *  before we do anything else.
 */
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

/**
 *  This function will compile a shader (vertex/fragment) and
 *  return the reference as a GLuint, so it can be attached
 *  to a program for linking.
 */
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
        GLParams::print_shader_log(shader);
        return false;
    }
    
    return shader;
}

/**
 *  This takes in the reference to two shaders that have been compiled and
 *  returns a reference to the linked program.
 */
GLuint GLUtilities::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    
    GLuint program = glCreateProgram();
    
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    if(GL_TRUE != programReady(program)) {
        cout << "Failed to link the program with reference: " << program << endl;
        GLParams::print_program_info_log(program);
    }
    
    return program;
}

/**
 *  Checks to see if the program is ready by
 *  checking its GL_LINK_STATUS
 */
GLint GLUtilities::programReady(const GLuint program) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    return status;
}

/**
 *  Apply a projection matrix to a program
 */
void GLUtilities::applyProjectionMatrix(const int gl_viewport_w, const int gl_viewport_h, const float fov, const GLuint program, const char *uniform_location_name) {
    /**
     *  This sets up the Projection Matrix.
     *
     *  These are part of the mathematical formula
     *  needed to calculate the correct projection
     *  to make the scene look more realistic.
     *
     *  This sets up the camera frustrum, the part of
     *  the scene that the camera covers and is therefore
     *  visible.
     */
    float near = 0.1f;
    float far = 100.0f;
    float aspect = (float)gl_viewport_w / (float)gl_viewport_h;
    float range = tan(fov * 0.5f) * near;
    
    float Sx = (2.0f * near) / ((range * aspect) + (range * aspect));
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2.0f * far * near) / (far - near);
    
    /**
     *  With the above calculations completed, we can then put
     *  this projection matrix together.
     */
    Matrix<float> projection_matrix({
        Row<float>({Sx, 0.0f, 0.0f, 0.0f}),
        Row<float>({0.0f, Sy, 0.0f, 0.0f}),
        Row<float>({0.0f, 0.0f, Sz, -1.0f}),
        Row<float>({0.0f, 0.0f, Pz, 0.0f})
    });
    
    /**
     *  We then unwind them from a Matrix to a vector of float values which
     *  we can then send through to the program, targeting the variable
     *  in the compiled shader program "projection" and sending the values through.
     */
    vector<float> projection_matrix_unwound = projection_matrix.unwind();
    GLuint projection_loc = glGetUniformLocation(program, uniform_location_name);
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection_matrix_unwound[0]);
}

Matrix<GLfloat> GLUtilities::calculateProjectionMatrix(const int gl_viewport_w, const int gl_viewport_h, const float fov) {
    float near = 0.1f;
    float far = 100.0f;
    float aspect = (float)gl_viewport_w / (float)gl_viewport_h;
    float range = tan(fov * 0.5f) * near;
    
    float Sx = (2.0f * near) / ((range * aspect) + (range * aspect));
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2.0f * far * near) / (far - near);
    
    Matrix<float> projection_matrix({
        Row<float>({Sx, 0.0f, 0.0f, 0.0f}),
        Row<float>({0.0f, Sy, 0.0f, 0.0f}),
        Row<float>({0.0f, 0.0f, Sz, -1.0f}),
        Row<float>({0.0f, 0.0f, Pz, 0.0f})
    });
    
    return projection_matrix;
}
