//
//  GLUtilities.hpp
//  OpenGL
//
//  Created by Matt Finucane on 09/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef GLUtilities_hpp
#define GLUtilities_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Matrix.hpp"

class GLUtilities {
public:
    static GLFWwindow* setupWindow(const int gl_viewport_w, const int gl_viewport_h, const char *title);
    static GLuint compileShader(const std::string shader_src_str, GLenum type);
    static GLuint linkShaders(const GLuint vertex_shader, const GLuint fragment_shader);
    static GLint programReady(const GLuint program);
    static void applyProjectionMatrix(const int gl_viewport_w, const int gl_viewport_h, const float fov, const GLuint program, const char *uniform_location_name);
    static Matrix<GLfloat> calculateProjectionMatrix(const int gl_viewport_w, const int gl_viewport_h, const float fov);
};

#endif /* GLUtilities_hpp */
