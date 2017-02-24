//
//  QuaternionDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 10/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef QuaternionDemo_hpp
#define QuaternionDemo_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Structs.h"
#include "Mesh.hpp" 

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

class QuaternionDemo {

private:
    QuaternionDemo();
    ~QuaternionDemo() {};
    QuaternionDemo(QuaternionDemo const &);
    void operator=(QuaternionDemo const &);
    
    GLuint program;
    GLFWwindow *window;
    GLenum drawing_method = GL_TRIANGLES;
    
    float fov = 67.0f * one_deg_in_rad;
    
    Position cam_pos;
    
    float cam_pitch = 0.0f;
    float cam_roll = 0.0f;
    float cam_yaw = 0.0f;
    
    float cam_pitch_speed = 2.0f;
    float cam_yaw_speed = 2.0f;
    float cam_roll_speed = 2.0f;
    
    std::vector<Mesh> meshes;
    
    void createProgram(void);
    void prepareMeshes(void);
    void applyQuaternion(void);
    void drawLoop(void);
    void keyActionListener(void);
    int start(void);

public:
    static QuaternionDemo& getInstance();
    static void addMesh(Mesh mesh, const Position position, const Rotation rotation);
    static int run(void);
};

#endif /* QuaternionDemo_hpp */
