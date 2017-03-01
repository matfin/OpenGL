//
//  Quaternion.cpp
//  OpenGL
//
//  Created by Matt Finucane on 11/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Quaternion.hpp"
#include <cmath>
#include <iostream>

using namespace std;

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

void Quaternion::normalise_quat(Matrix<float> &q) {
    float q_0 = q.getValueAtIndex(0);
    float q_1 = q.getValueAtIndex(1);
    float q_2 = q.getValueAtIndex(2);
    float q_3 = q.getValueAtIndex(3);
    float sum = q_0 * q_0 + q_1 * q_1 + q_2 * q_2 + q_3 * q_3;
    
    const float thresh = 0.0001f;
    if(fabs(1.0f - sum) < thresh) {
        return;
    }
    
    float mag = sqrt(sum);
    for(int i = 0; i < 4; i++) {
        int x = q.getValueAtIndex(i);
        int val = x / mag;
        q.adjust(0, i, val);
    }
    
}

void Quaternion::create_versor(Matrix<float> &m, float a, float x, float y, float z) {
    
    float radians = one_deg_in_rad * a;
    
    cout << "Create versor a: " << a <<  ", x: " << x << ", y: " << y << ", z: " << z << endl;
    
    if(m.getRows().size() != 0) {
        m.adjust(0, 0, cosf(radians / 2.0f));
        m.adjust(0, 0, cosf(radians / 2.0f) * x);
        m.adjust(0, 0, cosf(radians / 2.0f) * y);
        m.adjust(0, 0, cosf(radians / 2.0f) * z);
    }
    else {
        Row<float> result({
            cosf(radians / 2.0f),
            sinf(radians / 2.0f) * x,
            sinf(radians / 2.0f) * y,
            sinf(radians / 2.0f) * z
        });
        m.addRow(result);
    }
}

void Quaternion::quat_to_mat4(Matrix<float> &m, Matrix<float> q) {
    float w = q.getValueAtIndex(0);
    float x = q.getValueAtIndex(1);
    float y = q.getValueAtIndex(2);
    float z = q.getValueAtIndex(3);
    
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
    m.adjust(3, 3, 1.0f);
}

void Quaternion::mult_quat_quat(Matrix<float> &result, Matrix<float> r, Matrix<float> s) {
    
    float s_0 = s.getValueAtIndex(0);
    float s_1 = s.getValueAtIndex(1);
    float s_2 = s.getValueAtIndex(2);
    float s_3 = s.getValueAtIndex(3);
    
    float r_0 = r.getValueAtIndex(0);
    float r_1 = r.getValueAtIndex(1);
    float r_2 = r.getValueAtIndex(2);
    float r_3 = r.getValueAtIndex(3);

    float adj_1 = s_0 * r_0 - s_1 * r_1 - s_2 * r_2 - s_3 * r_3;
    float adj_2 = s_0 * r_1 + s_1 * r_0 - s_2 * r_3 + s_3 * r_2;
    float adj_3 = s_0 * r_2 + s_1 * r_3 + s_2 * r_0 - s_3 * r_1;
    float adj_4 = s_0 * r_3 - s_1 * r_2 + s_2 * r_1 + s_3 * r_0;
    
    result.adjust(0, 0, adj_1);
    result.adjust(0, 1, adj_2);
    result.adjust(0, 2, adj_3);
    result.adjust(0, 3, adj_4);
    
    normalise_quat(result);
}




