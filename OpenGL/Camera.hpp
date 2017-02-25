//
//  Camera.hpp
//  OpenGL
//
//  Created by Matt Finucane on 24/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include "Matrices.hpp"

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

enum CameraMovement {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
};

enum CameraRotation {
    ROT_UP,
    ROT_DOWN,
    ROT_LEFT,
    ROT_RIGHT
};

class Camera {

private:
    Camera();
    ~Camera() {};
    Camera(Camera const &);
    void operator=(Camera const &);
    
    GLuint program;
    Matrices m;
    
    float cam_pos_x = 0.0f;
    float cam_pos_y = 0.0f;
    float cam_pos_z = 0.0f;
    
    float cam_pitch = 0.0f;
    float cam_yaw = 0.0f;
    float cam_roll = 0.0f;
    
    float cam_pitch_speed = 2.0f;
    float cam_yaw_speed = 2.0f;
    float cam_roll_speed = 2.0f;
    float cam_move_speed = 0.1f;
    
    float fov = 67.0f * one_deg_in_rad;
    
    void applyViewQuaternion(void);
    void applyViewEuler(void);
    
    void _pitch(CameraRotation rotation);
    void _yaw(CameraRotation rotation);
    void _roll(CameraRotation rotation);
    void _move(CameraMovement movement);
    
    void _pitchTo(float deg);
    void _yawTo(float deg);
    void _rollTo(float deg);
    void _moveTo(float _x, float _y, float _z);
    
    std::string _repr(void);
    
public:
    static Camera& getInstance();
    static Camera& getInstance(GLuint _program);
    
    static void pitch(CameraRotation rotation) {
        getInstance()._pitch(rotation);
    }
    
    static void yaw(CameraRotation rotation) {
        getInstance()._yaw(rotation);
    }
    
    static void roll(CameraRotation rotation) {
        getInstance()._roll(rotation);
    }
    
    static void move(CameraMovement movement) {
        getInstance()._move(movement);
    }
    
    static void pitchTo(float deg) {
        getInstance()._pitchTo(deg);
    }
    
    static void yawTo(float deg) {
        getInstance()._yawTo(deg);
    }
    
    static void rollTo(float deg) {
        getInstance()._rollTo(deg);
    }
    
    static void moveTo(float _x, float _y, float _z) {
        getInstance()._moveTo(_x, _y, _z);
    }
    
    static std::string repr(void) {
        return getInstance()._repr();
    }
};

#endif /* Camera_hpp */
