//
//  CameraPerspectiveDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "CameraPerspectiveDemo.hpp"

using namespace std;

CameraPerspectiveDemo::CameraPerspectiveDemo(const std::vector<GLfloat> _vertex_floats, const std::vector<GLfloat> _colour_floats) : vertex_floats(_vertex_floats), colour_floats(_colour_floats) {
    cout << "Construct: CameraPerspectiveDemo" << endl;
    m = new Matrices();
}

CameraPerspectiveDemo::~CameraPerspectiveDemo() {
    delete(m);
}

void CameraPerspectiveDemo::prepare() const {
    
}

bool CameraPerspectiveDemo::setupWindow(void) {
    return 1;
}

GLuint CameraPerspectiveDemo::compileShader(const string *shader_src_str, GLenum type) const {
    return 1;
}

GLuint CameraPerspectiveDemo::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    return 1;
}

GLuint CameraPerspectiveDemo::prepareMesh(const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) const {
    return 1;
}

void CameraPerspectiveDemo::drawLoop(const vector<GLuint> *meshes) const {
    
}

void CameraPerspectiveDemo::applyMatrices(void) const {}

void CameraPerspectiveDemo::keyActionListener(void) const {}

int CameraPerspectiveDemo::run(void) const {
    return 0;
}
