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
}

Matrices::~Matrices() {
    cout << "Destruct: Matrices." << std::endl;
//    delete(rotation_x_matrix);
//    delete(rotation_y_matrix);
//    delete(rotation_z_matrix);
//    delete(translation_matrix);
//    delete(scaling_matrix);
}

void Matrices::translate(AdjustmentType type, Adjustments adjustment) {
    
    switch(type) {
        case TRANSLATE_X: {
            switch(adjustment) {
                case LEFT: {
                    translate_x -= 0.025f;
                    break;
                }
                case RIGHT: {
                    translate_x += 0.025f;
                    break;
                }
            }
            translation_matrix->adjust(3, 0, translate_x);
            break;
        }
        case TRANSLATE_Y: {
            switch(adjustment) {
                case DOWN: {
                    translate_y -= 0.025f;
                    break;
                }
                case UP: {
                    translate_y += 0.025f;
                    break;
                }
            }
            translation_matrix->adjust(3, 1, translate_y);
            break;
        }
        case TRANSLATE_Z: {
            switch(adjustment) {
                case CLOSER: {
                    translate_z += 0.025f;
                    break;
                }
                case FURTHER: {
                    translate_z -= -0.025f;
                    break;
                }
            }
            translation_matrix->adjust(3, 2, translate_z);
            break;
        }
    }
}

void Matrices::translateTo(AdjustmentType type, const float _translate) {
    switch(type) {
        case TRANSLATE_X: {
            translate_x = _translate;
            translation_matrix->adjust(3, 0, translate_x);
            break;
        }
        case TRANSLATE_Y: {
            translate_y = _translate;
            translation_matrix->adjust(3, 1, translate_y);
            break;
        }
        case TRANSLATE_Z: {
            translate_z = _translate;
            translation_matrix->adjust(3, 2, translate_z);
            break;
        }
    }
}

void Matrices::rotate(AdjustmentType type, Adjustments adjustment) {
    
    switch(type) {
        case ROTATE_X: {
            switch(adjustment) {
                case UP: {
                    rotate_x += 0.025f;
                    break;
                }
                case DOWN: {
                    rotate_x -= 0.025f;
                    break;
                }
            }
            rotation_x_matrix->adjust(1, 1, cosf(rotate_x));
            rotation_x_matrix->adjust(1, 2, sinf(rotate_x));
            rotation_x_matrix->adjust(2, 1, -sinf(rotate_x));
            rotation_x_matrix->adjust(2, 2, cosf(rotate_x));
            break;
        }
        case ROTATE_Y: {
            switch(adjustment) {
                case LEFT: {
                    rotate_y += 0.025f;
                    break;
                }
                case RIGHT: {
                    rotate_y -= 0.025f;
                    break;
                }
            }
            rotation_y_matrix->adjust(0, 0, cosf(rotate_y));
            rotation_y_matrix->adjust(0, 2, -sinf(rotate_y));
            rotation_y_matrix->adjust(2, 0, sinf(rotate_y));
            rotation_y_matrix->adjust(2, 2, cosf(rotate_y));
            break;
        }
        case ROTATE_Z: {
            switch(adjustment) {
                case LEFT: {
                    rotate_z += 0.025f;
                    break;
                }
                case RIGHT: {
                    rotate_z -= 0.025f;
                    break;
                }
            }
            rotation_z_matrix->adjust(0, 0, cosf(rotate_z));
            rotation_z_matrix->adjust(0, 1, sinf(rotate_z));
            rotation_z_matrix->adjust(1, 0, -sinf(rotate_z));
            rotation_z_matrix->adjust(1, 1, cosf(rotate_z));
            break;
        }
    }
}

void Matrices::rotateTo(AdjustmentType type, const float _rotate) {
    switch(type) {
        case ROTATE_X: {
            rotate_x = _rotate;
            rotation_x_matrix->adjust(1, 1, cosf(rotate_x));
            rotation_x_matrix->adjust(1, 2, sinf(rotate_x));
            rotation_x_matrix->adjust(2, 1, -sinf(rotate_x));
            rotation_x_matrix->adjust(2, 2, cosf(rotate_x));
            break;
        }
        case ROTATE_Y: {
            rotate_y = _rotate;
            rotation_y_matrix->adjust(0, 0, cosf(rotate_y));
            rotation_y_matrix->adjust(0, 2, -sinf(rotate_y));
            rotation_y_matrix->adjust(2, 0, sinf(rotate_y));
            rotation_y_matrix->adjust(2, 2, cosf(rotate_y));
            break;
        }
        case ROTATE_Z: {
            rotate_z = _rotate;
            rotation_z_matrix->adjust(0, 0, cosf(rotate_z));
            rotation_z_matrix->adjust(0, 1, sinf(rotate_z));
            rotation_z_matrix->adjust(1, 0, -sinf(rotate_z));
            rotation_z_matrix->adjust(1, 1, cosf(rotate_z));
            break;
        }
    }
}

void Matrices::scale(Adjustments adjustment) {
    scale_mag += adjustment;
    scaling_matrix->getRows().at(0).items.at(0) = scale_mag;
    scaling_matrix->getRows().at(1).items.at(1) = scale_mag;
    scaling_matrix->getRows().at(2).items.at(2) = scale_mag;
    scaling_matrix->getRows().at(3).items.at(3) = scale_mag;
}

void Matrices::scaleTo(float _scale) {
    scale_mag = _scale;
    scaling_matrix->getRows().at(0).items.at(0) = scale_mag;
    scaling_matrix->getRows().at(1).items.at(1) = scale_mag;
    scaling_matrix->getRows().at(2).items.at(2) = scale_mag;
    scaling_matrix->getRows().at(3).items.at(3) = scale_mag;
}
