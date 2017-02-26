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
    
    switch(r_type) {
        case QUATERNION: {
            applyViewQuaternion();
            break;
        }
        case EULER: {
            applyViewEuler();
            break;
        }
    }
}

void Camera::_yaw(CameraRotation rotation) {
    switch(rotation) {
        case ROT_LEFT: {
            cam_yaw += cam_yaw_speed;
            break;
        }
        case ROT_RIGHT: {
            cam_yaw -= cam_yaw_speed;
            break;
        }
    }
    
    switch(r_type) {
        case QUATERNION: {
            applyViewQuaternion();
            break;
        }
        case EULER: {
            applyViewEuler();
            break;
        }
    }
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
    
    switch(r_type) {
        case QUATERNION: {
            applyViewQuaternion();
            break;
        }
        case EULER: {
            applyViewEuler();
            break;
        }
    }
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
    
    switch(r_type) {
        case QUATERNION: {
            applyViewQuaternion();
            break;
        }
        case EULER: {
            applyViewEuler();
            break;
        }
    }
}

void Camera::_pitchTo(float deg) {
    cam_pitch = deg;
    applyViewQuaternion();
}

void Camera::_yawTo(float deg) {
    cam_yaw = deg;
    applyViewQuaternion();
}

void Camera::_rollTo(float deg) {
    cam_roll = deg;
    applyViewQuaternion();
}

void Camera::_moveTo(float _x, float _y, float _z) {
    cam_pos_x = _x;
    cam_pos_y = _y;
    cam_pos_z = _z;
    applyViewQuaternion();
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
    applyViewQuaternion();
}

void Camera::_switchRotationType(RotationType _r_type) {
    r_type = _r_type;
}

void Camera::applyViewQuaternion(void) {
    m.translateTo(TRANSLATE_X, -cam_pos_x);
    m.translateTo(TRANSLATE_Y, -cam_pos_y);
    m.translateTo(TRANSLATE_Z, -cam_pos_z);
    
    Matrix<float> quat_mat4_pitch = m.getMatrixOfType(ZERO_MAT4);
    Matrix<float> quat_mat4_yaw = m.getMatrixOfType(ZERO_MAT4);
    Matrix<float> quat_mat4_roll = m.getMatrixOfType(ZERO_MAT4);
    
    float quaternion_pitch[4];
    float quaternion_yaw[4];
    float quaternion_roll[4];
    
    Quaternion::create_versor(quaternion_pitch, -cam_pitch, 1.0f, 0.0f, 0.0f);
    Quaternion::quat_to_mat4(quat_mat4_pitch, quaternion_pitch);
    
    Quaternion::create_versor(quaternion_yaw, -cam_yaw, 0.0f, 1.0f, 0.0f);
    Quaternion::quat_to_mat4(quat_mat4_yaw, quaternion_yaw);
    
    Quaternion::create_versor(quaternion_roll, -cam_roll, 0.0f, 0.0f, 1.0f);
    Quaternion::quat_to_mat4(quat_mat4_roll, quaternion_roll);
    
    Matrix<float> translation_mat4 = m.getMatrixOfType(TRANSLATION);
    
    Matrix<float> view_mat4 = (
        translation_mat4 *
        quat_mat4_pitch *
        quat_mat4_yaw *
        quat_mat4_roll
    );
    
    vector<float> view_mat4_unwound = view_mat4.unwind();
    
    GLuint view_loc = glGetUniformLocation(program, "view");
    
    if(GL_TRUE != view_loc) {
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_mat4_unwound[0]);
    }
}

void Camera::applyViewEuler(void) {
    m.translateTo(TRANSLATE_X, -cam_pos_x);
    m.translateTo(TRANSLATE_Y, -cam_pos_y);
    m.translateTo(TRANSLATE_Z, -cam_pos_z);
    
    m.rotateTo(ROTATE_X, -cam_pitch);
    m.rotateTo(ROTATE_Y, -cam_yaw);
    m.rotateTo(ROTATE_Z, -cam_roll);
    
    Matrix<float> T = m.translation_matrix();
    Matrix<float> Rx = m.rotation_x_matrix();
    Matrix<float> Ry = m.rotation_y_matrix();
    Matrix<float> Rz = m.rotation_z_matrix();
    
    Matrix<float> view_matrix = (Rx * Ry * Rz) * T;
    vector<float> view_matrix_unwound = view_matrix.unwind();
    
    GLuint view_loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_matrix_unwound[0]);
}
