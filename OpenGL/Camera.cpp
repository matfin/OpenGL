//
//  Camera.cpp
//  OpenGL
//
//  Created by Matt Finucane on 24/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Camera.hpp"

using namespace std;

Camera::Camera() {}

Camera& Camera::getInstance() {
    static Camera instance;
    return instance;
}

void Camera::_create_versor (float* q, float a, float x, float y, float z) {
    float rad = one_deg_in_rad * a;
    q[0] = cosf (rad / 2.0f);
    q[1] = sinf (rad / 2.0f) * x;
    q[2] = sinf (rad / 2.0f) * y;
    q[3] = sinf (rad / 2.0f) * z;
}

void Camera::_quat_to_mat4(float *m, float *q) {
    float w = q[0];
    float x = q[1];
    float y = q[2];
    float z = q[3];
    
    m[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
    m[1] = 2.0f * x * y + 2.0f * w * z;
    m[2] = 2.0f * x * z - 2.0f * w * y;
    m[3] = 0.0f;
    
    m[4] = 2.0f * x * y - 2.0f * w * z;
    m[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
    m[6] = 2.0f * y * z + 2.0f * w * x;
    m[7] = 0.0f;
    
    m[8] = 2.0f * x * z + 2.0f * w * y;
    m[9] = 2.0f * y * z - 2.0f * w * x;
    m[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

void Camera::_pitch(CameraOrientation orientation) {
    switch(orientation) {
        case PITCH_UP: {
            break;
        }
        case PITCH_DOWN: {
            break;
        }
    }
}

void Camera::_yaw(CameraOrientation orientation) {
    switch(orientation) {
        case YAW_LEFT: {
            break;
        }
        case YAW_RIGHT: {
            break;
        }
    }
}

void Camera::_roll(CameraOrientation orientation) {
    switch(orientation) {
        case ROLL_LEFT: {
            break;
        }
        case ROLL_RIGHT: {
            break;
        }
    }
}

void Camera::_move(CameraMovement movement) {
    switch(movement) {
        case MOVE_FORWARD: {
            break;
        }
        case MOVE_BACKWARD: {
            break;
        }
        case MOVE_LEFT: {
            break;
        }
        case MOVE_RIGHT: {
            break;
        }
        case MOVE_UP: {
            break;
        }
        case MOVE_DOWN: {
            break;
        }
    }
}

string Camera::_repr() {
    stringstream oss;
    oss << "Camera program: " << program << endl;
    oss << "Camera fov: " << fov << endl;
    return oss.str();
}

void Camera::_applyProgram(GLuint _program) {
    program = _program;
}

void Camera::_create(void) {
    
    /**
     *  Set the camera position and update the 
     *  translation matrix.
     */
    cam_pos = vec3(0.0f, 0.0f, 15.0f);
    T = translate(identity_mat4(), vec3(-cam_pos.v[0], -cam_pos.v[1], -cam_pos.v[2]));
    
    /**
     *  Set up the projection matrix
     */
    float near = 0.1f;
    float far = 100.0f;
    float aspect = (float)gl_viewport_w / (float)gl_viewport_h;
    proj_mat = perspective(fov, aspect, near, far);
    
    /**
     *  Create a Quaternion using the initial cam heading,
     *  then apply it to the rotation mat4.
     */
    _create_versor(quaternion, -cam_heading, 0.0f, 1.0f, 0.0f);
    _quat_to_mat4(R.m, quaternion);
    
    /**
     *  Create the view mat4 by multiplying
     *  the translation and rotation mat4.
     */
    view_mat = R * T;
    
    /**
     *  Then we will create these vectors to keep
     *  track of movement.
     */
    fwd = vec4(0.0f, 0.0f, -1.0f, 0.0f);
    rgt = vec4(1.0f, 0.0f, 0.0f, 0.0f);
    up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    
    /**
     *  Apply to the vertex shaders
     */
    int view_mat_location = glGetUniformLocation(program, "view");
    int proj_mat_location = glGetUniformLocation(program, "projection");
    
    glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat.m);
    glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat.m);
}

void Camera::_updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
    gl_viewport_w = _gl_viewport_w;
    gl_viewport_h = _gl_viewport_h;
}
