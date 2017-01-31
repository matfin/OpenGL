//
//  Matrices.hpp
//  OpenGL
//
//  Created by Matt Finucane on 20/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Matrices_hpp
#define Matrices_hpp

#include <cmath>
#include "Enumerations.h"
#include "Structs.h"
#include "Matrix.hpp"

enum Adjustments {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LARGER,
    SMALLER,
    CLOSER,
    FURTHER
};

enum MatrixType {
    ROTATION_X,
    ROTATION_Y,
    ROTATION_Z,
    TRANSLATION,
    SCALING,
    IDENTITY_MAT3,
    IDENTITY_MAT4
};

enum AdjustmentType {
    ROTATE_X,
    ROTATE_Y,
    ROTATE_Z,
    TRANSLATE_X,
    TRANSLATE_Y,
    TRANSLATE_Z,
    SCALE
};

class Matrices {
private:
    float rotate_x = 0.0f;
    float rotate_y = 0.0f;
    float rotate_z = 0.0f;
    float translate_x = 0.0f;
    float translate_y = 0.0f;
    float translate_z = 0.0f;
    float scale_mag = 1.0f;
    
public:
    Matrices();
    ~Matrices();
    
    /**
     *  Returning Matrix objects
     */
    const Matrix<float> getMatrixOfType(MatrixType type) const {
        switch(type) {
            case ROTATION_X: {
                return rotation_x_matrix();
            }
            case ROTATION_Y: {
                return rotation_y_matrix();
            }
            case ROTATION_Z: {
                return rotation_z_matrix();
            }
            case TRANSLATION: {
                return translation_matrix();
            }
            case SCALING: {
                return scaling_matrix();
            }
            case IDENTITY_MAT3: {
                return identity_mat3();
            }
            case IDENTITY_MAT4: {
                return identity_mat4();
            }
        }
    }
    
    Matrix<float> rotation_x_matrix() const {
        return Matrix<float>({
            Row<float>({
                1.0f, 0.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, cosf(rotate_x), sinf(rotate_x), 0.0f
            }),
            Row<float>({
                0.0f, -sinf(rotate_x), cosf(rotate_x), 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 0.0f, 1.0f
            })
        });
    }
    
    Matrix<float> rotation_y_matrix() const {
        return Matrix<float>({
            Row<float>({
                cosf(rotate_y), 0.0f, -sinf(rotate_y), 0.0f
            }),
            Row<float>({
                0.0f, 1.0f, 0.0f, 0.0f
            }),
            Row<float>({
                sinf(rotate_y), 0.0f, cosf(rotate_y), 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 0.0f, 1.0f
            })
        });
    }
    
    Matrix<float> rotation_z_matrix() const {
        return Matrix<float>({
            Row<float>({
                cosf(rotate_z), sinf(rotate_z), 0.0f, 0.0f
            }),
            Row<float>({
                -sinf(rotate_z), cosf(rotate_z), 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 1.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 0.0f, 1.0f
            })
        });
    }
    
    Matrix<float> translation_matrix() const {
        return Matrix<float>({
            Row<float>({
                1.0f, 0.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 1.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 1.0f, 0.0f
            }),
            Row<float>({
                translate_x, translate_y, translate_z, 1.0f
            })
        });
    }
    
    Matrix<float> scaling_matrix() const {
        return Matrix<float>({
            Row<float>({
                scale_mag, 0.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, scale_mag, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, scale_mag, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 0.0f, 1.0f
            })
        });
    }
    
    Matrix<float> identity_mat3() const {
        return Matrix<float>({
            Row<float>({1.0f, 0.0f, 0.0f}),
            Row<float>({0.0f, 1.0f, 0.0f}),
            Row<float>({0.0f, 0.0f, 1.0f}),
        });
    }
    
    Matrix<float> identity_mat4() const {
        return Matrix<float>({
            Row<float>({
                1.0f, 0.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 1.0f, 0.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 1.0f, 0.0f
            }),
            Row<float>({
                0.0f, 0.0f, 0.0f, 1.0f
            })
        });
    }
    
    std::vector<float> getMatrixUnwound(MatrixType type) const {
        switch(type) {
            case ROTATION_X: {
                return rotation_x_matrix().unwind();
                break;
            }
            case ROTATION_Y: {
                return rotation_y_matrix().unwind();
                break;
            }
            case ROTATION_Z: {
                return rotation_z_matrix().unwind();
                break;
            }
            case TRANSLATION: {
                return translation_matrix().unwind();
                break;
            }
            case SCALING: {
                return scaling_matrix().unwind();
                break;
            }
            case IDENTITY_MAT3: {
                return identity_mat3().unwind();
                break;
            }
            case IDENTITY_MAT4: {
                return identity_mat4().unwind();
                break;
            }
            default: {
                return std::vector<float>{};
            }
        }
    }
    
    const float getCurrentAdjustment(AdjustmentType type) const {
        switch(type) {
            case ROTATE_X: {
                return rotate_x;
            }
            case ROTATE_Y: {
                return rotate_y;
            }
            case ROTATE_Z: {
                return rotate_z;
            }
            case TRANSLATE_X: {
                return translate_x;
            }
            case TRANSLATE_Y: {
                return translate_y;
            }
            case TRANSLATE_Z: {
                return translate_z;
            }
            case SCALE: {
                return scale_mag;
            }
        }
    }
    
    void translate(AdjustmentType type, Adjustments adjustment);
    void translateTo(AdjustmentType type, const float _translate);
    void rotate(AdjustmentType type, Adjustments adjustment);
    void rotateTo(AdjustmentType type, const float _rotate);
    void scale(Adjustments adjustment);
    void scaleTo(float _scale);
};

#endif /* Matrices_hpp */
