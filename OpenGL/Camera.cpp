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

void Camera::_normalise_quat(float *q) {
    float sum = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] +  q[3] * q[3];
    const float thresh = 0.0001f;
    if(fabs(1.0f - sum) < thresh) {
        return;
    }
    float mag = sqrt(sum);
    for(int i = 0; i < 4; i++) {
        q[i] = q[i] / mag;
    }
}

void Camera::_mult_quat_quat(float *result, float *r, float *s) {
    result[0] = s[0] * r[0] - s[1] * r[1] - s[2] * r[2] - s[3] * r[3];
    result[1] = s[0] * r[1] + s[1] * r[0] - s[2] * r[3] + s[3] * r[2];
    result[2] = s[0] * r[2] + s[1] * r[3] + s[2] * r[0] - s[3] * r[1];
    result[3] = s[0] * r[3] - s[1] * r[2] + s[2] * r[1] + s[3] * r[0];
    _normalise_quat(result);
}

string Camera::_repr() {
    stringstream oss;
    oss << "Camera fov: \t" << fov << endl;
    return oss.str();
}

void Camera::_applyProgram(GLuint _program) {
    program = _program;
}

void Camera::_updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
    gl_viewport_w = _gl_viewport_w;
    gl_viewport_h = _gl_viewport_h;
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
    aspect = (float)gl_viewport_w / (float)gl_viewport_h;
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
    view_mat_location = glGetUniformLocation(program, "view");
    proj_mat_location = glGetUniformLocation(program, "projection");
    
    glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat.m);
    glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat.m);
}

void Camera::_update(CameraKey key) {
    
    vec3 move(0.0f, 0.0f, 0.0f);
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;
    float q[4];
    
    switch(key) {
        /**
         *  Movement
         */
        case MOVE_FORWARD: {
            move.v[2] -= cam_speed;
            break;
        }
        case MOVE_BACKWARD: {
            move.v[2] += cam_speed;
            break;
        }
        case MOVE_LEFT: {
            move.v[0] -= cam_speed;
            break;
        }
        case MOVE_RIGHT: {
            move.v[0] += cam_speed;
            break;
        }
        case MOVE_UP: {
            move.v[1] += cam_speed;
            break;
        }
        case MOVE_DOWN: {
            move.v[1] -= cam_speed;
            break;
        }
        /**
         *  Rotation
         */
        case PITCH_UP: {
            pitch += cam_heading_speed;
            _create_versor(q, pitch, rgt.v[0], rgt.v[1], rgt.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
        case PITCH_DOWN: {
            pitch -= cam_heading_speed;
            _create_versor(q, pitch, rgt.v[0], rgt.v[1], rgt.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
        case YAW_LEFT: {
            yaw += cam_heading_speed;
            _create_versor(q, yaw, up.v[0], up.v[1], up.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
        case YAW_RIGHT: {
            yaw -= cam_heading_speed;
            _create_versor(q, yaw, up.v[0], up.v[1], up.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
        case ROLL_LEFT: {
            roll -= cam_heading_speed;
            _create_versor(q, roll, fwd.v[0], fwd.v[1], fwd.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
        case ROLL_RIGHT: {
            roll += cam_heading_speed;
            _create_versor(q, roll, fwd.v[0], fwd.v[1], fwd.v[2]);
            _mult_quat_quat(quaternion, q, quaternion);
            _quat_to_mat4(R.m, quaternion);
            fwd = R * vec4 (0.0, 0.0, -1.0, 0.0);
            rgt = R * vec4 (1.0, 0.0, 0.0, 0.0);
            up = R * vec4 (0.0, 1.0, 0.0, 0.0);
            break;
        }
    }
    
    _quat_to_mat4(R.m, quaternion);
    
    cam_pos = cam_pos + vec3(fwd) * -move.v[2];
    cam_pos = cam_pos + vec3(up) * move.v[1];
    cam_pos = cam_pos + vec3(rgt) * move.v[0];
    
    mat4 T = translate(identity_mat4(), vec3(cam_pos));
    
    view_mat = inverse(R) * inverse(T);
    glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat.m);
}

void Camera::_updateFov(float _d) {
    
    if(fov + _d <= 20.0f) {
        return;
    }
    else if(fov + _d >= 100.0f) {
        return;
    }
    
    fov += _d;
    proj_mat = perspective(fov, aspect, near, far);
    proj_mat_location = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(proj_mat_location, 1, GL_FALSE, proj_mat.m);
}
