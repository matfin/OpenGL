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

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

Matrices::Matrices() {
//    cout << "Construct: Matrices." << std::endl;
}

Matrices::~Matrices() {
//    cout << "Destruct: Matrices." << std::endl;
}

void Matrices::translate(AdjustmentType type, Adjustments adjustment) {
    
    switch(type) {
        case TRANSLATE_X: {
            switch(adjustment) {
                case LEFT: {
                    translate_x += 0.25f;
                    break;
                }
                case RIGHT: {
                    translate_x -= 0.25f;
                    break;
                }
            }
            break;
        }
        case TRANSLATE_Y: {
            switch(adjustment) {
                case DOWN: {
                    translate_y -= 0.25f;
                    break;
                }
                case UP: {
                    translate_y += 0.25f;
                    break;
                }
            }
            break;
        }
        case TRANSLATE_Z: {
            switch(adjustment) {
                case CLOSER: {
                    translate_z += 0.25f;
                    break;
                }
                case FURTHER: {
                    translate_z -= 0.25f;
                    break;
                }
            }
            break;
        }
    }
}

void Matrices::translateTo(AdjustmentType type, const float _translate) {
    switch(type) {
        case TRANSLATE_X: {
            translate_x = _translate;
            break;
        }
        case TRANSLATE_Y: {
            translate_y = _translate;
            break;
        }
        case TRANSLATE_Z: {
            translate_z = _translate;
            break;
        }
    }
}

void Matrices::rotate(AdjustmentType type, Adjustments adjustment) {
    
    switch(type) {
        case ROTATE_X: {
            switch(adjustment) {
                case UP: {
                    rotate_x += 1.0f * one_deg_in_rad;
                    break;
                }
                case DOWN: {
                    rotate_x -= 1.0f * one_deg_in_rad;
                    break;
                }
            }
            break;
        }
        case ROTATE_Y: {
            switch(adjustment) {
                case LEFT: {
                    rotate_y += 1.0f * one_deg_in_rad;
                    break;
                }
                case RIGHT: {
                    rotate_y -= 1.0f * one_deg_in_rad;
                    break;
                }
            }
            break;
        }
        case ROTATE_Z: {
            switch(adjustment) {
                case LEFT: {
                    rotate_z += 1.0f * one_deg_in_rad;
                    break;
                }
                case RIGHT: {
                    rotate_z -= 1.0f * one_deg_in_rad;
                    break;
                }
            }
            break;
        }
    }
}

void Matrices::rotateTo(AdjustmentType type, const float _rotate) {
    switch(type) {
        case ROTATE_X: {
            rotate_x = _rotate * one_deg_in_rad;
            break;
        }
        case ROTATE_Y: {
            rotate_y = _rotate * one_deg_in_rad;
            break;
        }
        case ROTATE_Z: {
            rotate_z = _rotate * one_deg_in_rad;
            break;
        }
    }
}

void Matrices::scale(Adjustments adjustment) {
    scale_mag += adjustment;
}

void Matrices::scaleTo(float _scale) {
    scale_mag = _scale;
}
