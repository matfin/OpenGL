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
#include "VecMat.hpp"

enum CameraKey {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    PITCH_UP,
    PITCH_DOWN,
    YAW_LEFT,
    YAW_RIGHT,
    ROLL_LEFT,
    ROLL_RIGHT
};

class Camera {

private:
    Camera();
    ~Camera() {};
    Camera(Camera const &);
    void operator=(Camera const &);
    static Camera& getInstance();
    
    GLuint program;
    int view_mat_location;
    int proj_mat_location;
    
    mat4 T;
    mat4 R;
    mat4 view_mat;
    mat4 proj_mat;
    vec3 cam_pos;
    
    vec4 fwd;
    vec4 rgt;
    vec4 up;
    
    float quaternion[4];
    
    int gl_viewport_h;
    int gl_viewport_w;
    float fov = 67.0f;
    
    float cam_speed = 0.25f;
    float cam_heading_speed = 1.0f;
    float cam_heading = 0.0f;
    
    void _create_versor(float *q, float a, float x, float y, float z);
    void _quat_to_mat4(float *m, float *q);
    void _mult_quat_quat(float *result, float *r, float *s);
    void _normalise_quat(float *q);
    
    void _applyProgram(GLuint _progam);
    
    void _updateViewportSize(const int _gl_viewport_w, const int gl_viewport_h);
    void _create(void);
    void _update(CameraKey key);

    std::string _repr(void);
    
public:
    
    static void applyProgram(GLuint _program) {
        getInstance()._applyProgram(_program);
    }
    
    static void updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
        getInstance()._updateViewportSize(_gl_viewport_w, _gl_viewport_h);
    }
    
    static void create(void) {
        getInstance()._create();
    }
    
    static void update(CameraKey key) {
        getInstance()._update(key);
    }
    
    static std::string repr(void) {
        return getInstance()._repr();
    }
};

#endif /* Camera_hpp */
