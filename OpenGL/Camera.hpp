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

enum RotationAxis {
    AXIS_X,
    AXIS_Y,
    AXIS_Z
};

class Camera {

private:
    Camera();
    ~Camera() {};
    Camera(Camera const &);
    void operator=(Camera const &);
    static Camera& getInstance();
    
    GLuint program;
    Matrices m;
    
    int gl_viewport_h;
    int gl_viewport_w;
    float fov = 67.0f * one_deg_in_rad;
    
    float cam_pos_x = 0.0f;
    float cam_pos_y = 0.0f;
    float cam_pos_z = 5.0f;
    
    float cam_pitch = 0.0f;
    float cam_yaw = 0.0f;
    float cam_roll = 0.0f;
    
    float cam_pitch_speed = 0.1f;
    float cam_yaw_speed = 0.1f;
    float cam_roll_speed = 0.1f;
    float cam_move_speed = 0.1f;
    float cam_heading = 0.0f;
    
    Matrix<float> fwd_mat4;
    Matrix<float> rgt_mat4;
    Matrix<float> up_mat4;
    Matrix<float> rotation_mat4;
    Matrix<float> quaternion_mat4;
    Matrix<float> _calculateProjectionMatrix(void);
    
    void _applyProgram(GLuint _progam);
    void _updateTranslation(void);
    void _updateViewportSize(const int _gl_viewport_w, const int gl_viewport_h);
    void _applyProjection(const char *uniform_location_name);
    void _updateViewQuaternionOnAxis(RotationAxis axis);
    void _applyView(void);
    
    void _pitch(CameraRotation rotation);
    void _yaw(CameraRotation rotation);
    void _roll(CameraRotation rotation);
    void _move(CameraMovement movement);
    
    void _pitchTo(float deg);
    void _yawTo(float deg);
    void _rollTo(float deg);
    void _moveTo(float _x, float _y, float _z);
    
    void _reset(void);
    
    std::string _repr(void);
    
public:
    
    static void applyProgram(GLuint _program) {
        getInstance()._applyProgram(_program);
    }
    
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
    
    static void updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
        getInstance()._updateViewportSize(_gl_viewport_w, _gl_viewport_h);
    }
    
    static void reset(void) {
        getInstance()._reset();
    }
    
    static std::string repr(void) {
        return getInstance()._repr();
    }
};

#endif /* Camera_hpp */
