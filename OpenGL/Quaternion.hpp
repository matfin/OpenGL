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
    static void create_versor(Matrix<float> &m, float a, float x, float y, float z);
    static void quat_to_mat4(Matrix<float> &m, Matrix<float> q);
    static void normalise_quat(Matrix<float> &q);
    static void mult_quat_quat(Matrix<float> &result, Matrix<float> r, Matrix<float> s);
};

#endif /* Quaternion_hpp */
