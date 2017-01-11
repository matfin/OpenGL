//
//  GLParams.cpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "GLParams.hpp"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "Logger.hpp"

using namespace std;

GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
};

const char *names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
};

const char* GLParams::gl_type_to_string(GLenum type) {
    switch(type) {
        case GL_BOOL: return "bool";
        case GL_INT: return "int";
        case GL_FLOAT: return "float";
        case GL_FLOAT_VEC2: return "vec2";
        case GL_FLOAT_VEC3: return "vec3";
        case GL_FLOAT_VEC4: return "vec4";
        case GL_FLOAT_MAT2: return "mat2";
        case GL_FLOAT_MAT3: return "mat3";
        case GL_FLOAT_MAT4: return "mat4";
        case GL_SAMPLER_1D: return "sampler1D";
        case GL_SAMPLER_2D: return "sampler2D";
        case GL_SAMPLER_3D: return "sampler3D";
        case GL_SAMPLER_CUBE: return "samplerCube";
        case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
        default: return "Other";
    }
}

void GLParams::print_verbose(GLuint program) {
    
    printf("Shader program info for %i\n", program);
    
    int params;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    printf("GL_LINK_STATUS: %i\n", params);
    
    glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
    printf("GL_ATTACHED_SHADERS: %i\n", params);
    
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
    printf("GL_ACTIVE_ATTRIBUTES: %i\n", params);
    
    for(GLuint i = 0; i < (GLuint)params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(program, i, max_length, &actual_length, &size, &type, name);
        
        if(size > 1) {
            for(int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetAttribLocation(program, long_name);
                printf("%i) type: %s, name: %s, location:%i\n", i, gl_type_to_string(type), long_name, location);
            }
        }
        else {
            int location = glGetAttribLocation(program, name);
            printf("%i type: %s, name: %s, location: %i\n", i, gl_type_to_string(type), name, location);
        }
    }
    
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
    printf("GL_ACTIVE_UNIFORMS: %i\n", params);
    
    for(GLuint i = 0; i < (GLuint)params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(program, i, max_length, &actual_length, &size, &type, name);
        
        if(size > 1) {
            for(int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetUniformLocation(program, long_name);
                printf("%i) type: %s, name: %s, location: %i\n", i, gl_type_to_string(type), long_name, location);
            }
        }
        else {
            int location = glGetUniformLocation(program, name);
            printf("%i type: %s, name: %s, location: %i\n", i, gl_type_to_string(type), name, location);
        }
    }
    
    print_program_info_log(program);
    
}

void GLParams::print_shader_log(GLuint shader_index) {
    int max_length = 2048;
    int actual_length = 0;
    char log[max_length];
    glGetShaderInfoLog(shader_index, max_length, &actual_length, log);
    printf("Shader info log for GL index %u:\n%s\n", shader_index, log);
}

void GLParams::print_program_info_log(GLuint program) {
    int max_length = 2048;
    int actual_length = 0;
    char log[max_length];
    glGetProgramInfoLog(program, max_length, &actual_length, log);
    printf("Program info log for GL index %u:\n%s", program, log);
}

vector<string> GLParams::getGLParams() const {
    vector<string> t;
    for(int i = 0; i < 10; i++) {
        int v = 0;
        ostringstream os;
        glGetIntegerv(params[i], &v);
        os << names[i] << ": " << v << endl;
        string param_str = os.str();
        t.push_back(param_str);
    }
    return t;
}

void GLParams::logGLParams(vector<string> params) const {
    Logger logger;
    logger.write("OpenGL context parameters:\n");
    for(auto &i : params) {
        logger.write(i.c_str());
    }
}

void GLParams::updateWindowFPSCounter(GLFWwindow *window) {
    static double previous_seconds = glfwGetTime();
    static int frame_count;
    double current_seconds = glfwGetTime();
    double elapsed_seconds = current_seconds - previous_seconds;
    
    if(elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapsed_seconds;
        ostringstream os;
        os << "One - fps: " << fps;
        string out = os.str();
        const char *fps_string = out.c_str();
        glfwSetWindowTitle(window, fps_string);
        frame_count = 0;
    }
    frame_count++;
}

bool GLParams::is_valid(GLuint program) {
    glValidateProgram(program);
    int params;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
    
    printf("Program %i GL_VALIDATE_STATUS: %i\n", program, params);
    if(GL_TRUE != params) {
        print_program_info_log(program);
        return false;
    }
    return true;
}
