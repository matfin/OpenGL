//
//  CubeTransformDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 13/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//
#include <iostream>
#include "CubeTransformDemo.hpp"
#include "Enumerations.h"

using namespace std;

/**
 *  Constructor for the CubeTransformDemo which initialises
 *  the GLFW window and compiles the shaders to link them and 
 *  create a program.
 *  
 *  @param  {vector<GLfloat>} - a vector of GLfloats for the cube vertices.
 *  @param  {vector<GLfloat>} - a vector of GLfloats for the cube colours.
 */
CubeTransformDemo::CubeTransformDemo(vector<GLfloat> _vertex_floats, vector<GLfloat> _colour_floats)
: vertex_floats(_vertex_floats), colour_floats(_colour_floats) {
    cout << "Construct: CubeTransformDemo." << endl;
    
    try {
        /**
         *  Set up the window.
         */
        setupWindow();
        
        /**
         *  Prepare the program by:
         *  - loading the vertex shader and compiling it.
         *  - loadig the fragment shader and compiling it.
         *  - compiling and linking them to form a program.
         */
        string vertex_shader_str = shader_loader.load("cube_transform_demo.vert");
        string fragment_shader_str = shader_loader.load("cube_transform_demo.frag");
        
        GLuint vertex_shader = compileShader(vertex_shader_str, GL_VERTEX_SHADER);
        GLuint fragment_shader = compileShader(fragment_shader_str, GL_FRAGMENT_SHADER);
        program = linkShaders(vertex_shader, fragment_shader);
        gl_params.print_program_info_log(program);
        
        /**
         *  Finally, we need to set the current adjustment 
         *  matrix (transform, rotate, scale).
         */
    }
    catch(exception &e) {
        cout << e.what() << endl;
    }
}

/**
 *  Destructor for the CubeTransformDemo which terminates
 *  GLFW and does other cleanup tasks.
 */
CubeTransformDemo::~CubeTransformDemo() {
    cout << "Destruct: CubeTransformDemo." << endl;
    delete m;
    window = 0;
    program = 0;
    vertex_floats.clear();
    colour_floats.clear();
    glfwTerminate();
}

/**
 *  Function to initialise glfw and set up a widnow.
 * 
 *  @param  {void}
 *  @return {GLFWwindow*} - The GLFWwindow
 */
bool CubeTransformDemo::setupWindow(void) {
    
    /**
     *  Initialise and check GLFW, which needs to be done
     *  before we attempt to create a window.
     */
    if(!glfwInit()) {
        throw runtime_error("Could not initialise GLFW. Exiting");
        return false;
    }
    
    /**
     *  GLFW window hints needed for MacOS
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /**
     *  Then we create the window.
     */
    window = glfwCreateWindow(1280, 960, "CubeTransformDemo", NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw runtime_error("GLFW failed to initialise a new window. Exiting");
        return false;
    }
    
    /**
     *  Set this window as the current context for GLFW
     */
    glfwMakeContextCurrent(window);
    
    /**
     *  Some stuff needed for perspective and drawing 
     *  items that are in front of other items.
     */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    /**
     *  Set up back face culling so fragments aren't 
     *  shaded for the part of a mesh we cannot see.
     */
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    /**
     *  This is needed to tell OpenGL what the front 
     *  and back of a primative is, given we specify
     *  vertices in a clockwise form.
     */
    glFrontFace(GL_CW);
    
    return true;
};

/**
 *  Function to compile shaders from source
 *
 *  @param  {string} - the shader source code.
 *  @param  {GLenum} - shader type (VERTEX_SHADER/FRAGMENT_SHADER).
 *  @retirn {GLuint} - a reference to the copiled shader.
 */
GLuint CubeTransformDemo::compileShader(string shader_src_str, GLenum shader_type) {
    
    /**
     *  We need to convert the string to a pointer of
     *  an array of chars.
     */
    GLuint shader = glCreateShader(shader_type);
    const char *shader_src = shader_src_str.c_str();
    GLint shader_src_len = shader_src_str.length();
    glShaderSource(shader, 1, &shader_src, &shader_src_len);
    glCompileShader(shader);
    
    /**
     *  Then run a check
     */
    int p;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &p);
    if(GL_TRUE != p){
        cout << "Failed to compile shader with reference: " << shader << endl;
        gl_params.print_shader_log(shader);
        return false;
    }
    
    return shader;
}

/**
 *  Function to compile a GL program from the vertex and fragment shaders.
 * 
 *  @param {GLuint} - a reference to the compiled vertex shader.
 *  @param {GLuint} - a reference to the compiled fragment shader.
 */
GLuint CubeTransformDemo::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    /**
     *  Declare our program and then attach 
     *  the two shaders.
     */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    /** 
     *  Get the shader link status.
     */
    int p;
    glGetProgramiv(program, GL_LINK_STATUS, &p);
    if(GL_TRUE != p) {
        cout << "Failed to link the shaders with reference: " << program << endl;
        gl_params.print_program_info_log(program);
        return false;
    }
    
    return program;
}

/**
 *  Function to return a VAO to the cube mesh.
 *
 *  @param  {const vector<GLfloat>} - Vector of GLfloats for the vertices.
 *  @param  {const vector<GLfloat>} - Vector of GLfloats for the colours.
 *  @return {GLuint} - a reference to the VAO for the mesh
 */
GLuint CubeTransformDemo::prepareMesh(const vector<GLfloat> points, const vector<GLfloat> colours) {
    
    /**
     *  Preparing the VBO for points.
     *  Note: we are passing in a pointer to the first 
     *  element of the vector which is the same as a 
     *  pointer to the first element of a c style array.
     */
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
    
    /**
     *  Now we do the same for colours.
     */
    GLuint colours_vbo;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(float), &colours[0], GL_STATIC_DRAW);
    
    /**
     *  Now we need to set up the VAO.
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    /**
     *  Then we bind the buffers for the points and colours
     *  and set the vertex attribute pointers.
     */
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    /**
     *  Then we enable the vertex attribute arrays, a call
     *  then needs to me made because they are disabled by
     *  default. We pass in the first arguments we used when
     *  used the glVertexAttribPointer() function.
     */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    return vao;
}

void CubeTransformDemo::drawLoop(GLuint vao) {
    /**
     *  Standard GL setup for each frame draw.
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 960);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    /**
     *  Ensure the program is ready and if it is, we can draw.
     */
    int program_ready;
    glGetProgramiv(program, GL_LINK_STATUS, &program_ready);
    
    if(GL_TRUE == program_ready) {
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertex_floats.size() / 3);
    }
    
    /**
     *  Poll for events and swap buffers into the window.
     */
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void CubeTransformDemo::applyMatrices(void) {
    
    int rot_x_matrix_loc = glGetUniformLocation(program, "rot_x_matrix");
    int rot_y_matrix_loc = glGetUniformLocation(program, "rot_y_matrix");
    int rot_z_matrix_loc = glGetUniformLocation(program, "rot_z_matrix");
    int scale_matrix_loc = glGetUniformLocation(program, "scale_matrix");
    int translate_matrix_loc = glGetUniformLocation(program, "translate_matrix");
    
    if(
       GL_TRUE != rot_x_matrix_loc ||
       GL_TRUE != rot_y_matrix_loc ||
       GL_TRUE != rot_z_matrix_loc ||
       GL_TRUE != scale_matrix_loc ||
       GL_TRUE != translate_matrix_loc
    ) {
//        glUniformMatrix4fv(rot_x_matrix_loc, 1, GL_FALSE, m->getMatrixUnwound(ROTATION_X));
//        glUniformMatrix4fv(rot_y_matrix_loc, 1, GL_FALSE, m->getMatrixUnwound(ROTATION_Y));
//        glUniformMatrix4fv(rot_z_matrix_loc, 1, GL_FALSE, m->getMatrixUnwound(ROTATION_Z));
//        glUniformMatrix4fv(translate_matrix_loc, 1, GL_FALSE, m->getMatrixUnwound(TRANSLATION));
//        glUniformMatrix4fv(scale_matrix_loc, 1, GL_FALSE, m->getMatrixUnwound(SCALING));
    }
    else {
        cout << "Matrix location could not be determined in the shaders. Exiting.";
    }
}

/**
 *  This function strobes for key presses and carries 
 *  out actions when these happen.
 *  
 *  @param  {void}
 *  @return {void}
 */
void CubeTransformDemo::keyActionListener(void) {
    
    /**
     *  Exit if we don't have a window.
     */
    if(!window) return;
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        /**
         *  This will initiate the close of the 
         *  GLFWWindow object and terminate the 
         *  while loop that is running.
         */
        glfwSetWindowShouldClose(window, 1);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
//        m->translateX(LEFT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
//        m->translateX(RIGHT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
//        m->translateY(UP);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
//        m->translateY(DOWN);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
//        m->rotateX(UP);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
//        m->rotateX(DOWN);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
//        m->rotateY(LEFT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
//        m->rotateY(RIGHT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_Q)) {
//        m->rotateZ(LEFT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_E)) {
//        m->rotateZ(RIGHT);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_EQUAL)) {
//        m->scale(LARGER);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_MINUS)) {
//        m->scale(SMALLER);
    }
}

int CubeTransformDemo::run(void) {
    
    /**
     *  Prepare the mesh to be drawn.
     */
    GLuint mesh_vao = prepareMesh(vertex_floats, colour_floats);
    
    /**
     *  Use the program we have compiled.
     */
    glUseProgram(program);
    
    /**
     *  While GLFW determines that the window 
     *  should remain open, run these three 
     *  functions. 
     *
     *  Note: The keyActionListener() function 
     *  will kill the window when the ESC key
     *  is pressed and the while condition will
     *  no longer evaluate to true.
     */
    while(!glfwWindowShouldClose(window)) {
        applyMatrices();
        drawLoop(mesh_vao);
        keyActionListener();
    }
    return 0;
}
