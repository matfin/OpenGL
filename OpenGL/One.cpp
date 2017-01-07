//
//  One.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "One.hpp"
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include "ShaderLoader.hpp"
#include "Logger.hpp"
#include "GLParams.hpp"

using namespace std;

Logger logger;
GLParams glparams;
const int w_width = 1280;
const int w_height = 960;

/**
 *  GLFW error callback function
 */
void glfw_error_callback(int error, const char *description) {
    logger.write_err("GLFW Error code: %i, message: %s", error, description);
}

/**
 *  This function returns a VAO for a line strip so that 
 *  this can be used in the draw function.
 */
GLuint setupLineStrip(const float *points) {
    /**
     *  Setting up the VBO.
     */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(float), points, GL_STATIC_DRAW);
    
    /**
     *  Setting up the VAO
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    return vao;
}

/**
 *  This function also tees up a VAO for drawing a triangle.
 */
GLuint setupTriangle(const float *points) {
    /**
     *  Setting up the VBO.
     */
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    /**
     *  Setting up the VAO
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    return vao;
}

/**
 *  Takes a VAO and draws it using a shader_program.
 */
void drawItem(const GLuint vao, const int gl_which, const int items, const GLuint shader_program) {
    /**
     *  Use the shader program, bind the vertex array and then draw.
     */
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(gl_which, 0, items);
    /**
     *  Then clear the vertex array.
     */
    glBindVertexArray(0);
}

/**
 *  Setting up a window and context and priming video mode.
 */
GLFWwindow* setupWindowAndContext(bool fullscreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *vmode = glfwGetVideoMode(monitor);
    GLFWwindow *window;
    
    if(fullscreen) {
        window = glfwCreateWindow(vmode->width, vmode->height , "One", monitor, NULL);
    }
    else {
        window = glfwCreateWindow(w_width, w_height , "One", NULL, NULL);
    }
    
    return window;
}

int one_main(void) {
    
    /**
     *  Set the error callback
     */
    glfwSetErrorCallback(glfw_error_callback);
    
    /**
     *  Check to see if we can initialise GLFW.
     */
    if(!glfwInit()) {
        logger.write_err("Unable to initialise GLFW.");
        return -1;
    }
    
    /**
     *  These are needed for MacOS.
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /**
     *  Create the window and prime the video mode using 
     *  the function declared to do this above.
     */
    GLFWwindow *window = setupWindowAndContext(false);
    
    if(!window) {
        cout << "Unable to create a GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    /**
     *  Get the version info.
     */
    logger.write("Starting GLFW\n%s\n", glfwGetVersionString());
    
    /**
     *  Get the OpenGL Context params using GLFW and then log them.
     */
    vector<string> gl_params = glparams.getGLParams();
    glparams.logGLParams(gl_params);
    
//    const GLubyte *renderer = glGetString(GL_RENDERER);
//    const GLubyte *version = glGetString(GL_VERSION);
//    cout << "Renderer: " << renderer << endl;
//    cout << "Version: " << version << endl;
    
    /**
     *  Instruct GL to draw a pixel if it is closer to the viewer.
     */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    
    /**
     *  This is everything that goes in between.
     *  ----------------------------------------
     *
     *  Points needed to make a basic triangle.
     *  Each float represent the x, y and z coordinates
     *  of a point. These are the coordinates for a 
     *  three point triangle.
     */
    float points_triangle_one[] = {
        -0.5f, 1.0f, 0.0f,   // starting at the top
        0.0f, 0.0f, 0.0f,  // moving clockwise next
        -1.0f, 0.0f, 0.0f  // finishing up triangle.
    };
    float points_triangle_two[] = {
        -0.5f, 0.0f, 0.0f,   // starting at the top
        0.0f, -1.0f, 0.0f,  // moving clockwise next
        -1.0f, -1.0f, 0.0f  // finishing up triangle.
    };
    /**
     *  Creating a square with two triangles.
     */
    float points_square_one[] = {
        1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    float points_square_two[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    
    /**
     *  Triangle strip points.
     */
    float line_points[] = {
        0.5f, -0.125f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.5f, -0.125f, 0.0f
    };
    
    /**
     *  Setting up our shapes using the functions above.
     */
    GLuint vao_triangle_one = setupTriangle(points_triangle_one);
    GLuint vao_triangle_two = setupTriangle(points_triangle_two);
    GLuint vao_square_one = setupTriangle(points_square_one);
    GLuint vao_square_two = setupTriangle(points_square_two);
    GLuint vao_line_strip = setupLineStrip(line_points);
    
    /**
     *  Colours (r,g,b,a)
     */
    float colours[] = {
        0.5f, 0.0f, 0.5f, 1.0f
    };
    
    /**
     *  Now we need to load the shaders starting.
     */
    ShaderLoader loader;
    const string vertex_shader_str = loader.load("one_vs.glsl");
    const string fragment_shader_str = loader.load("one_fs.glsl");
    const string fragment_shader_alt_str = loader.load("one_fs_alt.glsl");
    const char *vertex_shader = vertex_shader_str.c_str();
    const char *fragment_shader = fragment_shader_str.c_str();
    const char *fragment_shader_alt = fragment_shader_alt_str.c_str();
    
    /**
     *  Compiling the vertex shader first:
     *      - call glCreateShader to tee up a new shader.
     *      - set the source of the vertex shader - passed by reference.
     *      - then compile.
     */
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    
    /**
     *  Then we move on to the fragment shader:
     */
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    
    /**
     *  Creating the alernative fragment shader
     */
    GLuint fs_alt = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_alt, 1, &fragment_shader_alt, NULL);
    glCompileShader(fs_alt);
    
    /**
     *  Now we need to compile the shaders into a single 
     *  program that can be executed on the GPU.
     *  
     *      - shader_program will be teed up
     *      - we attach the two compiled shaders. 
     *        In this case, vs and fs are now pointing
     *        to the compiled shaders.
     *      - we then link the compiled programs.
     *
     */
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);
    
    GLuint shader_program_alt = glCreateProgram();
    glAttachShader(shader_program_alt, vs);
    glAttachShader(shader_program_alt, fs_alt);
    glLinkProgram(shader_program_alt);
    
    /**
     *  To draw, we keep the GLFW window open until it 
     *  should close, to ve met by some condition later.
     */
    while(!glfwWindowShouldClose(window)) {
        
        /**
         *  Logging fps to the window title.
         */
        glparams.updateWindowFPSCounter(window);
        
        /**
         *  Clear the drawing surface.
         */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /**
         *  Setting the GL Viewport
         */
        glViewport(0, 0, w_width, w_height);
        
        /**
         *  Set the background colour
         */
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        /**
         *  Draw the line strip and triangles
         */
        drawItem(vao_line_strip, GL_LINE_STRIP, 5, shader_program);
        drawItem(vao_triangle_one, GL_TRIANGLES, 3, shader_program);
        drawItem(vao_triangle_two, GL_TRIANGLES, 3, shader_program_alt);
        drawItem(vao_square_one, GL_TRIANGLES, 3, shader_program);
        drawItem(vao_square_two, GL_TRIANGLES, 3, shader_program);
        
        /**
         *  Poll for input handling.
         */
        glfwPollEvents();
        
        /**
         *  Place what was drawn/painted into the window.
         */
        glfwSwapBuffers(window);
        
        /**
         *  Break out on press of 'ESC'
         */
        if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
    }
    
    /**
     *  ---------------------------------------
     *  When done, terminate.
     */
    glfwTerminate();
    return 0;
}
