//
//  CubeTransformDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 13/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//
#include <iostream>
#include <cmath>
#include "CubeTransformDemo.hpp"

using namespace std;

CubeTransformDemo::CubeTransformDemo(vector<float> _vertex_floats) {
    cout << "Creating: Cube Transform Demo." << endl;
}

CubeTransformDemo::~CubeTransformDemo() {
    cout << "Destroying: Cube Transform Demo." << endl;
}

bool CubeTransformDemo::setupWindow(void) const {
    return 1;
};

GLuint CubeTransformDemo::compileShader(const string shader_source, GLenum shader_type) {
    return 1;
}

GLuint CubeTransformDemo::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    return 1;
}

GLuint CubeTransformDemo::prepareCubeMesh(const vector<GLfloat> points, const vector<GLfloat> colours) {
    return 1;
}

void CubeTransformDemo::drawLoop(GLFWwindow *window, const GLuint program, const GLuint vao) {
    
}

void CubeTransformDemo::rotateX(float rotation) {
    
}

void CubeTransformDemo::rotateY(float rotation) {
    
}

void CubeTransformDemo::rotateZ(float rotation) {
    
}

void CubeTransformDemo::translateX(float translation) {
    
}

void CubeTransformDemo::translateY(float translation) {
    
}

void CubeTransformDemo::translateZ(float translation) {
    
}

void CubeTransformDemo::scale(float scale) {
    
}

int run() {
    return 0;
}
