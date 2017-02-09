//
//  GLParams.hpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef GLParams_hpp
#define GLParams_hpp

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

class GLParams {
public:
    static std::vector<std::string> getGLParams();
    static const char *gl_type_to_string(GLenum type);
    static void logGLParams(std::vector<std::string> params);
    static void updateWindowFPSCounter(GLFWwindow *window);
    static void print_verbose(GLuint program);
    static void print_shader_log(GLuint shader_index);
    static void print_program_info_log(GLuint program);
    static bool is_valid(GLuint program);
};

#endif /* GLParams_hpp */
