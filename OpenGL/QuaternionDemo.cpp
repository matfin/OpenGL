//
//  QuaternionDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 10/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "QuaternionDemo.hpp"
#include <iostream>
#include <string>
#include "GLUtilities.hpp"
#include "GLParams.hpp"
#include "ShaderLoader.hpp"

using namespace std;

QuaternionDemo& QuaternionDemo::getInstance() {
    static QuaternionDemo instance;
    return instance;
}

void QuaternionDemo::createProgram(void) {
    string vertex_shader_str = ShaderLoader::load("quaternion_demo.vert");
    string fragment_shader_str = ShaderLoader::load("quaternion_demo.frag");
    
    GLuint vertex_shader = GLUtilities::compileShader(vertex_shader_str, GL_VERTEX_SHADER);
    GLuint fragment_shader = GLUtilities::compileShader(fragment_shader_str, GL_FRAGMENT_SHADER);
    
    program = GLUtilities::linkShaders(vertex_shader, fragment_shader);
    GLParams::print_program_info_log(program);
}

void QuaternionDemo::prepareMeshes(void) {
    for(auto &mesh: meshes) {
        mesh.prepareBuffers();
    }
}

void QuaternionDemo::drawLoop(void) {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 960);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(GL_TRUE == GLUtilities::programReady(program)) {
        for(auto &mesh: meshes) {
            mesh.applyMatrices(program);
            glBindVertexArray(mesh.getVao());
            glDrawArrays(drawing_method, 0, mesh.pointsSize());
        }
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void QuaternionDemo::addMesh(Mesh mesh, const Position position, const Rotation rotation) {
    mesh.getMatrices()->rotateTo(ROTATE_X, rotation.rx);
    mesh.getMatrices()->rotateTo(ROTATE_Y, rotation.ry);
    mesh.getMatrices()->rotateTo(ROTATE_Z, rotation.rz);
    
    mesh.getMatrices()->translateTo(TRANSLATE_X, position.px);
    mesh.getMatrices()->translateTo(TRANSLATE_Y, position.py);
    mesh.getMatrices()->translateTo(TRANSLATE_Z, position.pz);
    
    getInstance().meshes.push_back(mesh);
}

int QuaternionDemo::start() {
    
    try {
        window = GLUtilities::setupWindow(1280, 960, "Quaternion Demo");
    }
    catch(exception &e) {
        cout << e.what();
        return -1;
    }
    
    /**
     *  Load the vertex and fragment shaders, compile them,
     *  link them and then assign them to the program member
     *  variable so we can use it.
     */
    createProgram();
    glUseProgram(program);
    
    /**
     *  Prepare the mesh buffers for all meshes
     */
    prepareMeshes();
    
    while(!glfwWindowShouldClose(window)) {
        drawLoop();
    }
    
    return 0;
}

int QuaternionDemo::run() {
    return getInstance().start();
}
