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
#include <math.h>
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
 *  Assigns two VBO (Vertex Buffer Objects) 
 *  to a single VAO (Vertex Array Object) which
 *  will then be returned. 
 *  This creates a simple triangle with two buffers.
 */
GLuint prepareTriangleItem(const GLfloat *points, const GLfloat *colours) {
    
    /**
     *  Buffer for points.
     */
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(points), points, GL_STATIC_DRAW);
    
    /**
     *  Buffer for colours.
     */
    GLuint colours_vbo;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(colours), colours, GL_STATIC_DRAW);
    
    /**
     *  Setting up the vao.
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    /**
     *  We bind the buffer of type GL_ARRAY_BUFFER
     *  for the points_vbo which was taken care of above.
     *  
     *  We then call glVertexAttribPointer with the params:
     *
     *  - first we set the index number to 0.
     *  - we then specify the number of components per generic vertex attribute (3 in this case for x, y, z).
     *  - we specify the data type of each component of the array, in this case GL_FLOAT.
     *  - defines whether fixed point values should be normalised, false in this case so GL_FALSE.
     *  - stride specifies the byte offset between consecutive vertex attributes, set to 0 in this case.
     *  - pointer specfies the offset of the first component of the first generic vertex attribute, 0 in this case.
     */
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    /**
     *  We now need to set up the vertex attribute pointers to point 
     *  to what we created above. In this case that will be 0 for the 
     *  points and 1 for the colours.
     */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    return vao;
}

void applyTransformationMatrix(const GLuint program, const float move_x) {
    /**
     *  Declare a matrix via an array of floats.
     *  This will move the triangle 0.5 units to
     *  the right.
     *  Note: This takes the form column-major
     */
    float matrix[] = {
        1.0f, 0.0f, 0.0f, 0.0f, // first column
        0.0f, 1.0f, 0.0f, 0.0f, // second column
        0.0f, 0.0f, 1.0f, 0.0f, // third column
        (0.0f + move_x), 0.0f, 0.0f, 1.0f  // fourth column
    };
    
    /**
     *  Find the reference to the "matrix" variable 
     *  inside the compiled GL Program.
     *  Then apply the above array of floats to it 
     *  so we can pass that value in.
     */
    int matrix_location = glGetUniformLocation(program, "matrix");
    
    if(GL_TRUE != matrix_location) {
        glUniformMatrix4fv(matrix_location, 1, GL_FALSE, matrix);
    }
    else {
        cout << "Matrix transformation could not be applied." << endl;
    }
}

/**
 *  The main draw loop
 *
 *  @param      {GLFWwindow*}   - the window
 *  @param      {GLuint*}       - the shader program
 *  @return     {void}
 */
void drawloopForVBO(GLFWwindow *window, GLuint program, GLuint vao) {
    /**
     *  Standard pre-draw tasks
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1080, 810);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /**
     *  Check the program is ready
     */
    int ready;
    glGetProgramiv(program, GL_LINK_STATUS, &ready);
    
    if(GL_TRUE == ready) {
        /**
         *  Then prepare and draw the VAO we passed in
         */
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
    /**
     *  Poll for events and swap buffers into the window.
     */
    glfwPollEvents();
    glfwSwapBuffers(window);
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
        
        /**
         *  Other setup: TODO explain.
         */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        /**
         *  Exploring back face culling
         */
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
        
        /**
         *  Let's grab the shaders and compile them in to a program,
         *  printing the program details along the way.
         */
        string vertex_shader_string = shader_loader_vbo.load("vertex_buffer_objects.vert");
        string fragment_shader_string = shader_loader_vbo.load("vertex_buffer_objects.frag");
        const char *vertex_shader_source = vertex_shader_string.c_str();
        const char *fragment_shader_source = fragment_shader_string.c_str();
        
        GLuint vertex_shader = createShaderForVBO(vertex_shader_source, GL_VERTEX_SHADER);
        GLuint fragment_shader = createShaderForVBO(fragment_shader_source, GL_FRAGMENT_SHADER);
        GLuint program = compileProgramForVBO(vertex_shader, fragment_shader);
        
        gl_params_vbo.print_verbose(program);
        
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
         *  Then we create a reference to our VAO
         */
        GLuint vao = prepareTriangleItem(points, colours);
        
        /**
         *  Make a call to use the program
         */
        glUseProgram(program);
        
        /**
         *  To be used for animating the transformation matrix.
         */
        float speed = 0.3f;
        float last_x_position = 0.0f;
        float move_x = 0.0f;
        
        while(!glfwWindowShouldClose(window)) {
            
            static double previous_seconds = glfwGetTime();
            double current_seconds = glfwGetTime();
            double elapsed_seconds = current_seconds - previous_seconds;
            previous_seconds = current_seconds;
            float t = fabs(last_x_position);
            
            if(t >= 0.5f) {
                speed = -speed;
            }
            
            move_x = (elapsed_seconds * speed) + last_x_position;
            last_x_position = move_x;
            
            /**
             *  Then make a call to one of our functions to
             *  set the matrix (floats).
             */
            applyTransformationMatrix(program, move_x);

            /**
             *  Then draw and poll for key presses.
             */
            drawloopForVBO(window, program, vao);
            keyListeningLoopForVBO(window);
        }
    }
    catch(exception &e) {
        cout << "Exception in main: " << e.what() << endl;
        return 1;
    }

    return 0;
}
