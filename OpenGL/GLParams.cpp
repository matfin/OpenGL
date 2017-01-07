//
//  GLParams.cpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "GLParams.hpp"
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>
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
