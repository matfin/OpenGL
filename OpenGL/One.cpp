//
//  One.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "One.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

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
     *  When done, terminate.
     */
    glfwTerminate();
    return 0;
}
