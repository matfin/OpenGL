//
//  Quaternion.cpp
//  OpenGL
//
//  Created by Matt Finucane on 11/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Quaternion.hpp"
#include <cmath>

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

void Quaternion::create_versor(float *q, float a, float x, float y, float z) {
    float radians = one_deg_in_rad * a;
    q[0] = cosf(radians / 2.0f);
    q[1] = sinf(radians / 2.0f) * x;
    q[2] = sinf(radians / 2.0f) * y;
    q[3] = sinf(radians / 2.0f) * z;
}

void Quaternion::quat_to_mat4(Matrix<float> m, float *quaternion) {
    float w = quaternion[0];
    float x = quaternion[1];
    float y = quaternion[2];
    float z = quaternion[3];
    
    m.adjust(0, 0, (1.0f - 2.0f * y * y - 2.0f * z * z));
    m.adjust(0, 1, (2.0f * x * y + 2.0f * w * z));
    m.adjust(0, 2, (2.0f * x * z - 2.0f * w * y));
    m.adjust(0, 3, 0.0f);
    
    m.adjust(1, 0, (2.0f * x * y - 2.0f * w * z));
    m.adjust(1, 1, (1.0f - 2.0f * x * x -2.0f * z * z));
    m.adjust(1, 2, (2.0f * y * z + 2.0f * w * x));
    m.adjust(1, 3, 0.0f);
    
    m.adjust(2, 0, (2.0f * x * z + 2.0f * w * y));
    m.adjust(2, 1, (2.0f * y * z - 2.0f * w * x));
    m.adjust(2, 2, (1.0f - 2.0f * x * x - 2.0f * y * y));
    m.adjust(2, 3, 0.0f);
    
    m.adjust(3, 0, 0.0f);
    m.adjust(3, 1, 0.0f);
    m.adjust(3, 2, 0.0f);
    m.adjust(3, 3, 0.0f);
}

void Quaternion::normalise_quat(float *q) {
    float sum = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    const float thresh = 0.0001f;
    if(fabs(1.0f - sum) < thresh) {
        return;
    }
    float mag = sqrt(sum);
    for(int i = 0; i < 4; i++) {
        q[i] = q[i] / mag;
    }
}

void Quaternion::mult_quat_quat(float * result, float *r, float *s) {
    result[0] = s[0] * r[0] - s[1] * r[1] - s[2] * r[2] - s[3] * r[3];
    result[1] = s[0] * r[1] + s[1] * r[0] - s[2] * r[3] + s[3] * r[2];
    result[2] = s[0] * r[2] + s[1] * r[3] + s[2] * r[0] - s[3] * r[1];
    result[3] = s[0] * r[3] - s[1] * r[2] + s[2] * r[1] + s[3] * r[0];
    normalise_quat(result);
}




