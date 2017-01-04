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
    float points[] = {
        0.0f, 0.5f, 0.0f,   // starting at the top
        0.5f, -0.5f, 0.0f,  // moving clockwise next
        -0.5f, -0.5f, 0.0f  // finishing up
    };
    
    /**
     *  We need to copy these points into the video card
     *  memory in a unit called a VBO (vertex buffer object).
     *  
     *  We will set this up now.
     *      - we set the initial value of the vbo to be 0.
     *      - we generate buffers passing in the vbp by reference.
     *      - we call glBindBuffer with an enum for array buffer.
     *        and specify that it is an array.
     *      - we then buffer the data, setting the buffer size to be 
     *        the size of the hardcoded array times the size of a float,
     *        while passing in the float array of points, finishing off
     *        with an enum called GL_STATIC_DRAW.
     *
     *
     */
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
    
    /**
     *  Since most meshes will have an array of VBOs,
     *  we will use something called a VAO (vertex array object).
     *  This will make it easier to map all the vertex buffers 
     *  like the one above without too much overhead.
     *  
     *  We will set this up now and then use it when we want to 
     *  draw.
     *      - we create an initial value of vao set to 0.
     *      - we call to generate vertex arrays passing in vao by reference.
     *      - we bind the vertex arrays passing in vao by value.
     *      - we enable the vertex attrib array.
     *      - we call glBindBuffer again with vbo.
     *      - glertexAttribPointer will take 0 as the first parameter,
     *        means that we define the layout for attribute number 0.
     *        Using 3 means we are dealing with vec3, meaning we are 
     *        using three floats of type GL_FLOAT for a point.
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
    const string vertex_shader_str = loader.load("one.vertex");
    const string fragment_shader_str = loader.load("one.fragment");
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
