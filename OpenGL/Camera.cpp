//
//  Camera.cpp
//  OpenGL
//
//  Created by Matt Finucane on 24/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Camera.hpp"
#include <vector>
#include "Quaternion.hpp"
#include "Structs.h"
#include "Matrix.hpp"

using namespace std;

Camera::Camera() {}

Camera& Camera::getInstance() {
    static Camera instance;
    
    instance.fwd_mat4 = Matrix<float>({
        Row<float>({0.0f, 0.0f, -1.0f, 0.0f})
    });
    
    instance.rgt_mat4 = Matrix<float>({
        Row<float>({1.0f, 0.0f, 0.0f, 0.0f})
    });
    
    instance.up_mat4 = Matrix<float>({
        Row<float>({0.0f, 1.0f, 0.0f, 0.0f})
    });
    
    instance.rotation_mat4 = instance.m.getMatrixOfType(ZERO_MAT4);
    
    return instance;
}

void Camera::_pitch(CameraRotation rotation) {
    switch(rotation) {
        case ROT_UP: {
            cam_pitch += cam_pitch_speed;
            break;
        }
        case ROT_DOWN: {
            cam_pitch -= cam_pitch_speed;
            break;
        }
    }
    
    _updateViewQuaternionOnAxis(AXIS_X);
}

void Camera::_yaw(CameraRotation rotation) {
    switch(rotation) {
        case ROT_RIGHT: {
            cam_yaw += cam_yaw_speed;
            break;
        }
        case ROT_LEFT: {
            cam_yaw -= cam_yaw_speed;
            break;
        }
    }
    
    _updateViewQuaternionOnAxis(AXIS_Y);
}

void Camera::_roll(CameraRotation rotation) {
    switch(rotation) {
        case ROT_LEFT: {
            cam_roll += cam_roll_speed;
            break;
        }
        case ROT_RIGHT: {
            cam_roll -= cam_roll_speed;
            break;
        }
    }
    
    _updateViewQuaternionOnAxis(AXIS_Z);
}

void Camera::_move(CameraMovement movement) {
    switch(movement) {
        case MOVE_FORWARD: {
            cam_pos_z -= cam_move_speed;
            break;
        }
        case MOVE_BACKWARD: {
            cam_pos_z += cam_move_speed;
            break;
        }
        case MOVE_LEFT: {
            cam_pos_x -= cam_move_speed;
            break;
        }
        case MOVE_RIGHT: {
            cam_pos_x += cam_move_speed;
            break;
        }
        case MOVE_UP: {
            cam_pos_y -= cam_move_speed;
            break;
        }
        case MOVE_DOWN: {
            cam_pos_y += cam_move_speed;
            break;
        }
    }
    
    _updateTranslation();
}

void Camera::_pitchTo(float deg) {
    cam_pitch = deg;
}

void Camera::_yawTo(float deg) {
    cam_yaw = deg;
}

void Camera::_rollTo(float deg) {
    cam_roll = deg;
}

void Camera::_moveTo(float _x, float _y, float _z) {
    cam_pos_x = _x;
    cam_pos_y = _y;
    cam_pos_z = _z;
}

string Camera::_repr() {
    stringstream oss;
    
    oss << "Camera program: " << program << endl;
    oss << "Camera pitch: " << cam_pitch << ", yaw: " << cam_yaw << ", roll: " << cam_roll << endl;
    oss << "Camera position x: " << cam_pos_x << ", y: " << cam_pos_y << ", z: " << cam_pos_z << endl;
    oss << "Camera fov: " << fov << endl;
    
    return oss.str();
}

void Camera::_applyProgram(GLuint _program) {
    program = _program;
}

void Camera::_reset(void) {
    
    cam_pos_x = 0.0f;
    cam_pos_y = 0.0f;
    cam_pos_z = 15.0f;
    
    cam_pitch = 0.0f;
    cam_yaw = 0.0f;
    cam_roll = 0.0f;
    
    cam_heading = 0.0f;
    
    _updateTranslation();
    _applyProjection("projection");
    
    Quaternion::create_versor(quaternion_mat4, -cam_heading, 0.0f, 1.0f, 0.0f);
    Quaternion::quat_to_mat4(rotation_mat4, quaternion_mat4);
    
    Matrix<float> translation_mat4 = m.getMatrixOfType(TRANSLATION);
    Matrix<float> view_mat4 = translation_mat4 * rotation_mat4;
    vector<float> view_mat4_unwound = view_mat4.unwind();
    
    GLuint view_loc = glGetUniformLocation(program, "view");
    if(GL_TRUE != view_loc) {
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_mat4_unwound[0]);
    }
    else {
        cout << "Camera reset was unable to apply the view quaternion matrix." << endl;
    }
    
    cout << "Camera reset:" << _repr() << endl;
    cout << "T mat4: " << translation_mat4.repr() << endl;
    cout << "R mat4: " << rotation_mat4.repr() << endl;
    cout << "Q mat4: " << quaternion_mat4.repr() << endl;
    
    cout << "FW mat4: " << fwd_mat4.repr() << endl;
    cout << "RT mat4: " << rgt_mat4.repr() << endl;
    cout << "UP mat4: " << up_mat4.repr() << endl;
}

void Camera::_updateTranslation(void) {
    m.translateTo(TRANSLATE_X, -cam_pos_x);
    m.translateTo(TRANSLATE_Y, -cam_pos_y);
    m.translateTo(TRANSLATE_Z, -cam_pos_z);
}

void Camera::_updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
    gl_viewport_w = _gl_viewport_w;
    gl_viewport_h = _gl_viewport_h;
}

void Camera::_updateViewQuaternionOnAxis(RotationAxis axis) {
    
    _updateTranslation();
    
    Matrix<float> local_q_mat4;

    switch(axis) {
        case AXIS_X: {
            Quaternion::create_versor(local_q_mat4, cam_pitch, rgt_mat4.getValueAtIndex(0), rgt_mat4.getValueAtIndex(1), rgt_mat4.getValueAtIndex(2));
            break;
        }
        case AXIS_Y: {
            Quaternion::create_versor(local_q_mat4, cam_yaw, up_mat4.getValueAtIndex(0), up_mat4.getValueAtIndex(1), up_mat4.getValueAtIndex(2));
            break;
        }
        case AXIS_Z: {
            Quaternion::create_versor(local_q_mat4, cam_roll, fwd_mat4.getValueAtIndex(0), fwd_mat4.getValueAtIndex(1), fwd_mat4.getValueAtIndex(2));
            break;
        }
    }
    
    Quaternion::mult_quat_quat(quaternion_mat4, local_q_mat4, quaternion_mat4);
    Quaternion::quat_to_mat4(rotation_mat4, quaternion_mat4);
    
    Matrix<float> translation_mat4 = m.getMatrixOfType(TRANSLATION);
    Matrix<float> view_mat4 = translation_mat4.inverse() * rotation_mat4.inverse();
    vector<float> view_mat4_unwound = view_mat4.unwind();
    
    fwd_mat4 *= rotation_mat4;
    rgt_mat4 *= rotation_mat4;
    up_mat4 *= rotation_mat4;
    
    GLuint view_loc = glGetUniformLocation(program, "view");
    if(GL_TRUE != view_loc) {
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_mat4_unwound[0]);
    }
    else {
        cout << "Camera was unable to apply the view quaternion matrix." << endl;
    }
}

void Camera::_applyView(void) {
}

Matrix<float> Camera::_calculateProjectionMatrix(void) {
    float near = 0.1f;
    float far = 100.0f;
    float aspect = (float)gl_viewport_w / (float)gl_viewport_h;
    float range = tan(fov * 0.5f) * near;
    
    float Sx = (2.0f * near) / ((range * aspect) + (range * aspect));
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2.0f * far * near) / (far - near);
    
    /**
     *  With the above calculations completed, we can then put
     *  this projection matrix together.
     */
    Matrix<float> projection_matrix({
        Row<float>({Sx, 0.0f, 0.0f, 0.0f}),
        Row<float>({0.0f, Sy, 0.0f, 0.0f}),
        Row<float>({0.0f, 0.0f, Sz, -1.0f}),
        Row<float>({0.0f, 0.0f, Pz, 0.0f})
    });
    
    return projection_matrix;
}

void Camera::_applyProjection(const char *uniform_location_name) {
    Matrix<GLfloat> projection_matrix = _calculateProjectionMatrix();
    vector<GLfloat> projection_matrix_unwound = projection_matrix.unwind();
    GLuint projection_loc = glGetUniformLocation(program, uniform_location_name);
    if(GL_TRUE != projection_loc) {
        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection_matrix_unwound[0]);
    }
    else {
        cout << "Projection matrix could not be applied. Could not find the location: " << uniform_location_name << endl;
    }
}
