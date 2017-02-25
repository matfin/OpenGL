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
#include "Quaternion.hpp"
#include "Camera.hpp"

#define gl_viewport_w 1280
#define gl_viewport_h 960

using namespace std;

QuaternionDemo::QuaternionDemo() {
}

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
    glViewport(0, 0, gl_viewport_w, gl_viewport_h);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(GL_TRUE == GLUtilities::programReady(program)) {
        for(auto &mesh: meshes) {
            mesh.applyIdentityMatrix(program);
            glBindVertexArray(mesh.getVao());
            glDrawArrays(drawing_method, 0, mesh.pointsSize());
        }
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void QuaternionDemo::keyActionListener(void) {
    
    if(!window) {
        return;
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, 1);
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_LEFT)) {
    }
    
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_RIGHT)) {
    }

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
        window = GLUtilities::setupWindow(gl_viewport_w, gl_viewport_h, "Quaternion Demo");
    }
    catch(exception &e) {
        cout << e.what();
        return -1;
    }
    
    /**
     *  Prepare the mesh buffers for all meshes
     */
    prepareMeshes();
    
    /**
     *  Load the vertex and fragment shaders, compile them,
     *  link them and then assign them to the program member
     *  variable so we can use it.
     */
    createProgram();
    glUseProgram(program);
    
    if(GLUtilities::programReady(program)) {
        
        /**
         *  Once the program is ready we need to do the following:
         *
         *  -   apply the projection matrix to the world.
         *  -   assign a program to the camera which will also apply the cameras
         *      Quaternion view matrix to the world.
         */
        Camera::applyProgram(program);
        Camera::moveTo(0.0f, 0.0f, 15.0f);
        cout << Camera::repr() << endl;
        
        GLUtilities::applyProjectionMatrix(gl_viewport_w, gl_viewport_h, fov, program, "projection");
    }
    
    while(!glfwWindowShouldClose(window)) {
        drawLoop();
        keyActionListener();
    }
    
    return 0;
}

int QuaternionDemo::run() {
    return getInstance().start();
}
