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
    std::vector<std::string> getGLParams() const;
    const char *gl_type_to_string(GLenum type);
    void logGLParams(std::vector<std::string> params) const;
    void updateWindowFPSCounter(GLFWwindow *window);
    void print_verbose(GLuint program);
    void print_shader_log(GLuint shader_index);
    void print_program_info_log(GLuint program);
    bool is_valid(GLuint program);
};

#endif /* GLParams_hpp */
