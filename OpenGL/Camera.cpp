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
    
    m.translateTo(TRANSLATE_X, 0.0f);
    m.translateTo(TRANSLATE_Y, 0.0f);
    m.translateTo(TRANSLATE_Z, -15.0f);
    
    rotation_mat4 = m.getMatrixOfType(ZERO_MAT4);
    Matrix<float> translation_mat4 = m.getMatrixOfType(TRANSLATION);
    
    Quaternion::create_versor(quaternion, -cam_heading, 0.0f, 0.0f, 0.0f);
    Quaternion::quat_to_mat4(rotation_mat4, quaternion);
    
    Matrix<float> view_mat4 = translation_mat4 * rotation_mat4;
    vector<float> view_mat4_unwound = view_mat4.unwind();
    
    fwd = Matrix<float>({
        Row<float>({0.0f, 0.0f, -1.0f, 0.0f})
    });
    
    rgt = Matrix<float>({
        Row<float>({1.0f, 0.0f, 0.0f, 0.0f})
    });
    
    up = Matrix<float>({
        Row<float>({0.0f, 1.0f, 0.0f, 0.0f})
    });
    
    _applyProjection("projection");
    
    GLuint view_loc = glGetUniformLocation(program, "view");
    if(GL_TRUE != view_loc) {
        glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_mat4_unwound[0]);
    }
    else {
        cout << "Camera reset was unable to apply the view quaternion matrix." << endl;
    }
}

void Camera::_updateViewportSize(const int _gl_viewport_w, const int _gl_viewport_h) {
    gl_viewport_w = _gl_viewport_w;
    gl_viewport_h = _gl_viewport_h;
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
