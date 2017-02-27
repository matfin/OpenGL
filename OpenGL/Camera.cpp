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
    
    instance.quaternion_mat4 = Matrix<float>({
        Row<float>({0.0f, 0.0f, 0.0f, 0.0f})
    });
    
    instance.rotation_mat4 = instance.m.zero_mat4();
    
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
    
    _updateTranslation();
    
    Quaternion::create_versor(quaternion_mat4, -cam_yaw, 0.0f, 1.0f, 0.0f);
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
}

void Camera::_updateTranslation(void) {
    m.translateTo(TRANSLATE_X, -cam_pos_x);
    m.translateTo(TRANSLATE_Y, -cam_pos_y);
    m.translateTo(TRANSLATE_Z, -cam_pos_z);
}

void Camera::_applyViewQuaternionOnAxis(RotationAxis axis) {
    
    float q[4];
    
    switch(axis) {
        case AXIS_X: {
            break;
        }
        case AXIS_Y: {
            break;
        }
        case AXIS_Z: {
            vector<float> fwd_mat4_unwound = fwd_mat4.unwind();
//            Quaternion::create_versor(q, cam_roll, &fwd_mat4_unwound[0], &fwd_mat4_unwound[1], &fwd_mat4_unwound[2]);
            break;
        }
        case AXIS_ALL: {
            break;
        }
    }
    
//    Quaternion::mult_quat_quat(quaternion, q, quaternion);
//    Quaternion::quat_to_mat4(rotation_mat4, quaternion);
//    fwd = rotation_mat4 * 
}
