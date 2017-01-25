//
//  Matrices.cpp
//  OpenGL
//
//  Created by Matt Finucane on 20/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Matrices.hpp"
#include <iostream>

using namespace std;

Matrices::Matrices() {
    cout << "Construct: Matrices." << std::endl;
    objectCount++;
}
Matrices::~Matrices() {
    cout << "Destruct: Matrices." << std::endl;
}

void Matrices::translateX(Direction direction) {
    switch(direction) {
        case LEFT: {
            translate_x -= 0.05f;
            break;
        }
        case RIGHT: {
            translate_x += 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    translation[12] = translate_x;
}

void Matrices::translateXTo(const float _x) {
    translate_x = _x;
    translation[12] = translate_x;
}
    
void Matrices::translateY(Direction direction) {
    switch(direction) {
        case UP: {
            translate_y += 0.05f;
            break;
        }
        case DOWN: {
            translate_y -= 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    translation[13] = translate_y;
}

void Matrices::translateYTo(const float _y) {
    translate_y = _y;
    translation[13] = translate_y;
}

void Matrices::translateZ(Direction direction) {
    switch(direction) {
        case CLOSER: {
            translate_z += 0.05f;
            break;
        }
        case FURTHER: {
            translate_z -= 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    translation[14] = translate_z;
}

void Matrices::translateZTo(const float _z) {
    translate_z = _z;
    translation[14] = translate_z;
}

void Matrices::rotateX(Direction direction) {
    switch(direction) {
        case UP: {
            rotate_x += 0.05f;
            break;
        }
        case DOWN: {
            rotate_x -= 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    rotation_x[5] = cosf(rotate_x);
    rotation_x[6] = cosf(rotate_x);
    rotation_x[9] = -sinf(rotate_x);
    rotation_x[10] = cosf(rotate_x);
}

void Matrices::rotateXTo(const float _x) {
    rotate_x = _x;
    rotation_x[5] = cosf(rotate_x);
    rotation_x[6] = cosf(rotate_x);
    rotation_x[9] = -sinf(rotate_x);
    rotation_x[10] = cosf(rotate_x);
}
    
void Matrices::rotateY(Direction direction) {
    switch(direction) {
        case LEFT: {
            rotate_y += 0.05f;
            break;
        }
        case RIGHT: {
            rotate_y -= 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    rotation_y[0] = cosf(rotate_y);
    rotation_y[2] = -sinf(rotate_y);
    rotation_y[8] = sinf(rotate_y);
    rotation_y[10] = cosf(rotate_y);
}

void Matrices::rotateYTo(const float _y) {
    rotate_y = _y;
    rotation_y[0] = cosf(rotate_y);
    rotation_y[2] = -sinf(rotate_y);
    rotation_y[8] = sinf(rotate_y);
    rotation_y[10] = cosf(rotate_y);
}
    
void Matrices::rotateZ(Direction direction) {
    switch(direction) {
        case LEFT: {
            rotate_z += 0.05f;
            break;
        }
        case RIGHT: {
            rotate_z -= 0.05f;
            break;
        }
        default: {
            break;
        }
    }
    rotation_z[0] = cosf(rotate_z);
    rotation_z[1] = sinf(rotate_z);
    rotation_z[4] = -sinf(rotate_z);
    rotation_z[5] = cosf(rotate_z);
}

void Matrices::rotateZTo(const float _z) {
    rotate_z = _z;
    rotation_z[0] = cosf(rotate_z);
    rotation_z[1] = sinf(rotate_z);
    rotation_z[4] = -sinf(rotate_z);
    rotation_z[5] = cosf(rotate_z);
}

void Matrices::scale(ScaleMag direction) {
    switch(direction) {
        case LARGER: {
            if(scale_mag <= 0.8f) scale_mag += 0.05f;
            break;
        }
        case SMALLER: {
            if(scale_mag >= 0.1f) scale_mag -= 0.05f;
            break;
        }
    }
    scaling[0] = scaling[5] = scaling[10] = scale_mag;
}

void Matrices::scaleTo(float _scale) {
    scale_mag = _scale;
    scaling[0] = scaling[5] = scaling[10] = scale_mag;
}
