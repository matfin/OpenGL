//
//  Quaternion.hpp
//  OpenGL
//
//  Created by Matt Finucane on 11/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Quaternion_hpp
#define Quaternion_hpp

#include "Matrix.hpp"

class Quaternion {
public:
    static void create_versor(float *q, float a, float x, float y, float z);
    static void quat_to_mat4(Matrix<float> m, float *quaternion);
    static void normalise_quat(float *q);
    static void mult_quat_quat(float * result, float *r, float *s);
};

#endif /* Quaternion_hpp */
