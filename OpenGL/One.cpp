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
#include "ShaderLoader.hpp"

using namespace std;

int one_main(void) {
    
    /**
     *  Check to see if we can initialise GLFW.
     */
    if(!glfwInit()) {
        cout << "Unable to initialise GLFW3." << endl;
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
     *  Create the window, check it worked and then assign as context.
     */
    GLFWwindow *window = glfwCreateWindow(640, 480, "One", NULL, NULL);
    
    if(!window) {
        cout << "Unable to create a GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    /**
     *  Get the version info.
     */
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    cout << "Renderer: " << renderer << endl;
    cout << "Version: " << version << endl;
    
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
        0.0f, 0.5f, 0.0f,   // starting at the top
        0.5f, -0.5f, 0.0f,  // moving clockwise next
        -0.5f, -0.5f, 0.0f  // finishing up triangle.
    };
    float points_triangle_two[] = {
        0.0f, 0.0f, 0.0f,   // starting at the top
        0.5f, -1.0f, 0.0f,  // moving clockwise next
        -0.5f, -1.0f, 0.0f  // finishing up triangle.
    };
    
    /**
     *  Colours (r,g,b,a)
     */
    float colours[] = {
        0.5f, 0.0f, 0.5f, 1.0f
    };
    
    /**
     *  We need to copy these points into the video card
     *  memory in a unit called a VBO (vertex buffer object).
     *  
     *  First, we create a VBO so we can tee up an empty buffer,
     *  doing this with the glGenBuffers function by passing in 
     *  a reference to vbo.
     *
     *  The glBindBuffer function will then set this as the current
     *  buffer in the OpenGL state.
     *
     *  We then fill that buffer with vertices by passing in the points,
     *  setting the size of the buffer and stating GL_STATIC_DRAW.
     *  
     *  Note: the points variable passed in is the address of the 
     *  first value.
     *
     */
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points_triangle_one, GL_STATIC_DRAW);
    
    GLuint vbo_two = 0;
    glGenBuffers(1, &vbo_two);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_two);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points_triangle_two, GL_STATIC_DRAW);
    
    /**
     *  Next, we will use a VAO (vertex array object) which is used 
     *  to track references to one or more VBOs. It stores the memory
     *  layout for each of these. We have one of these for each mesh
     *  and then use it when we want to draw.
     *
     *  Here wr are generating a new VAO with an unsigned integer so 
     *  we can identify it later.By binding it, we are bringing it 
     *  into the focus of the OpenGL state.
     *
     *  This allows us to enable the first attribute which is 0. When using 
     *  a single vertex buffer, we know it will be at location 0.
     *
     *  The glVertexAttribPointer function defines the layout of our first 
     *  vertex buffer; "0" means define the layout for attribute number 0.
     *  
     *  Secondly, we pass in 3 as an int which means it should read every
     *  3n ints to make the vertex. The shader takes in a vec3 variable and 
     *  the floats in the points array are seemingly converted to GL_FLOATs.
     */
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    /**
     *  Now we need to load the shaders starting.
     */
    ShaderLoader loader;
    const string vertex_shader_str = loader.load("one_vs.glsl");
    const string fragment_shader_str = loader.load("one_fs.glsl");
    const char *vertex_shader = vertex_shader_str.c_str();
    const char *fragment_shader = fragment_shader_str.c_str();
    
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
    
    /**
     *  To draw, we keep the GLFW window open until it 
     *  should close, to ve met by some condition later.
     */
    while(!glfwWindowShouldClose(window)) {
        /**
         *  Clear the drawing surface.
         */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /**
         *  Use the program that we built from the compiled
         *  shaders.
         */
        glUseProgram(shader_program);
        
        /**
         *  Passing in the VAO and binding with the points
         *  we declared earlier and draw them.
         */
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        /**
         *  Poll for input handling.
         */
        glfwPollEvents();
        
        /**
         *  Place what was drawn/painted into the window.
         */
        glfwSwapBuffers(window);
    }
    
    /**
     *  ---------------------------------------
     *  When done, terminate.
     */
    glfwTerminate();
    return 0;
}
