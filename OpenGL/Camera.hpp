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

enum CameraOrientation {
    PITCH_UP,
    PITCH_DOWN,
    YAW_LEFT,
    YAW_RIGHT,
    ROLL_LEFT,
    ROLL_RIGHT
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
    
    float cam_pitch_speed = 0.4f;
    float cam_yaw_speed = 0.4f;
    float cam_roll_speed = 0.4f;
    float cam_move_speed = 0.4f;
    float cam_heading = 0.0f;
    
    Matrix<float> fwd;
    Matrix<float> rgt;
    Matrix<float> up;
    
    Matrix<float> rotation_mat4;
    Matrix<float> quaternion;
    
    Matrix<float> _calculateProjectionMatrix(void);
    
    void _applyProgram(GLuint _progam);
    void _updateTranslation(void);
    void _updateViewportSize(const int _gl_viewport_w, const int gl_viewport_h);
    void _applyProjection(const char *uniform_location_name);
    
    void _pitch(CameraOrientation orientation);
    void _yaw(CameraOrientation orientation);
    void _roll(CameraOrientation orientation);
    void _move(CameraMovement movement);
    
    void _create(void);
    
    std::string _repr(void);
    
public:
    
    static void applyProgram(GLuint _program) {
        getInstance()._applyProgram(_program);
    }
    
    static void pitch(CameraOrientation orientation) {
        getInstance()._pitch(orientation);
    }
    
    static void yaw(CameraOrientation orientation) {
        getInstance()._yaw(orientation);
    }
    
    static void roll(CameraOrientation orientation) {
        getInstance()._roll(orientation);
    }
    
    static void move(CameraMovement movement) {
        getInstance()._move(movement);
    }
    
    static void updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
        getInstance()._updateViewportSize(_gl_viewport_w, _gl_viewport_h);
    }
    
    static void create(void) {
        getInstance()._create();
    }
    
    static std::string repr(void) {
        return getInstance()._repr();
    }
};

#endif /* Camera_hpp */
