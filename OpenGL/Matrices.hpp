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

class Matrices {
private:
    float rotate_x = 0.0f;
    float rotate_y = 0.0f;
    float rotate_z = 0.0f;
    float move_x = 0.0f;
    float move_y = 0.0f;
    float scale_mag = 1.0f;
    
public:
    Matrices();
    ~Matrices();
    
    void scale(ScaleMag direction);
    void translateX(Direction direction);
    void translateY(Direction direction);
    void rotateX(Direction direction);
    void rotateY(Direction direction);
    void rotateZ(Direction direction);
    
    float rotation_x[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosf(rotate_x), sinf(rotate_x), 0.0f,
        0.0f, -sinf(rotate_x), cosf(rotate_x), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float rotation_y[16] = {
        cosf(rotate_y), 0.0f, -sinf(rotate_y), 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sinf(rotate_y), 0.0f, cosf(rotate_y), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float rotation_z[16] = {
        cosf(rotate_z), sinf(rotate_z), 0.0f, 0.0f,
        -sinf(rotate_z), cosf(rotate_z), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    float translation[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        move_x, move_y, 0.0f, 1.0f
    };
    
    float scaling[16] = {
        scale_mag, 0.0f, 0.0f, 0.0f,
        0.0f, scale_mag, 0.0f, 0.0f,
        0.0f, 0.0f, scale_mag, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
};

#endif /* Matrices_hpp */
