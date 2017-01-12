//
//  Shaders.cpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Shaders.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

using namespace std;

GLParams shaders_gl_params;

/**
 *  This stores a reference to the shapes colour using
 *  r: red
 *  g: green
 *  b: blue
 *  a: alpha
 *  dr: difference red
 *  dg: difference green
 *  db: difference blue
 */
struct ColourStruct {
    float r;
    float g;
    float b;
    float a;
};

/**
 *  This stores a reference to both the VAO and colour.
 */
struct VaoAndColour {
    GLuint vao;
    ColourStruct colour;
    GLenum render_mode;
};

enum Adjustment {
    UP,
    DOWN
};

enum KeyAction {
    ACTION_NONE,
    ACTION_QUIT,
    ACTION_COLOUR_UP,
    ACTION_COLOUR_DOWN,
    ACTION_POSITION_UP,
    ACTION_POSITION_DOWN,
    ACTION_POSITION_LEFT,
    ACTION_POSITION_RIGHT,
};

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
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

void adjustColourWithBounds(float &colour, Adjustment adjustment) {
    switch(adjustment) {
        case UP: {
            if(colour >= 1.0f) colour = 1.0f;
            else colour += 0.05f;
            break;
        }
        case DOWN: {
            if(colour <= 0.0f) colour = 0.0f;
            else colour -= 0.05f;
            break;
        }
    }
}

void drawingLoop(GLFWwindow *window, GLuint program, vector<VaoAndColour> shapes_colours, GLint colour_uniform_location) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 960);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glUseProgram(program);
    
    /**
     *  Loop through the array of VaoAndColour.
     */
    for(auto const &i : shapes_colours) {
        /**
         *  We then create a glIUniform4f (note the 4) to pass in the
         *  uniform location and the colour we want as an
         *  rgba value (0 - 255 = 0.0f to 1.0f).
         *
         *  Note: It's important to call this after glUseProgram
         */
        glUniform4f(
            colour_uniform_location,
            i.colour.r,
            i.colour.g,
            i.colour.b,
            i.colour.a
        );
        glBindVertexArray(i.vao);
        glDrawArrays(i.render_mode, 0, 3);
    }
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void adjustColour(VaoAndColour &i, Adjustment adjustment) {    
    adjustColourWithBounds(i.colour.r, adjustment);
    adjustColourWithBounds(i.colour.g, adjustment);
    adjustColourWithBounds(i.colour.b, adjustment);
}

/**
 *  Takes our window, listens for the key press 
 *  and returns
 */
KeyAction keyListeningLoop(GLFWwindow *window) {
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        return ACTION_QUIT;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
        return ACTION_POSITION_UP;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
        return ACTION_POSITION_DOWN;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
        return ACTION_POSITION_LEFT;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
        return ACTION_POSITION_RIGHT;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
        return ACTION_COLOUR_UP;
    }
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
        return ACTION_COLOUR_DOWN;
    }
    return ACTION_NONE;
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
        
        /**
         *  Create 4 shapes with their accompanying colour.
         */
        vector<VaoAndColour> shapes_colours = {
            VaoAndColour{
                prepareTriangle(-0.5f, 0.5f, 0.8f, 0.8f),
                {1.0f, 0.0f, 0.0f, 0.0f},
                GL_TRIANGLES
            },
            VaoAndColour{
                prepareTriangle(0.5f, 0.5f, 0.8f, 0.8f),
                {0.0f, 1.0f, 0.0f, 0.0f},
                GL_LINE_LOOP
            },
            VaoAndColour{
                prepareTriangle(-0.5f, -0.5f, 0.8f, 0.8f),
                {0.0f, 0.0f, 1.0f, 0.0f},
                GL_TRIANGLE_STRIP
            },
            VaoAndColour{
                prepareTriangle(0.5f, -0.5f, 0.8f, 0.8f),
                {1.0f, 1.0f, 0.0f, 0.0f},
                GL_LINE_LOOP
            }
        };
        
        GLint colour_uniform_location = glGetUniformLocation(program, "inputColour");
        
        while(!glfwWindowShouldClose(window)) {
            
            drawingLoop(window, program, shapes_colours, colour_uniform_location);
            
            switch(keyListeningLoop(window)) {
                case ACTION_QUIT: {
                    glfwSetWindowShouldClose(window, 1);
                    break;
                }
                case ACTION_POSITION_UP: {
                    break;
                }
                case ACTION_POSITION_DOWN: {
                    break;
                }
                case ACTION_POSITION_LEFT: {
                    break;
                }
                case ACTION_POSITION_RIGHT: {
                    break;
                }
                case ACTION_COLOUR_UP: {
                    for(auto &i : shapes_colours) {
                        adjustColour(i, UP);
                    }
                    break;
                }
                case ACTION_COLOUR_DOWN: {
                    for(auto &i : shapes_colours) {
                        adjustColour(i, DOWN);
                    }
                    break;
                }
            }
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
