//
//  VecMat.cpp
//  OpenGL
//
//  Created by Matt Finucane on 01/03/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "VecMat.hpp"
#include <iostream>
#include <cmath>

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

vec2::vec2() {}

vec2::vec2(float x, float y) {
    v[0] = x;
    v[1] = y;
}

vec3::vec3() {}

vec3::vec3(float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

vec3::vec3(const vec2 &vv, float z) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = z;
}

vec3::vec3(const vec4 &vv) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = vv.v[2];
}

mat3 zero_mat3() {
    return mat3(
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    );
}

vec4::vec4() {}

vec4::vec4(float x, float y, float z, float w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

vec4::vec4(const vec2 &vv, float z, float w) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = z;
    v[3] = w;
}

vec4::vec4(const vec3 &vv, float w) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = vv.v[2];
    v[3] = w;
}

vec3 vec3::operator+(const vec3 &rhs) {
    vec3 result;
    result.v[0] = v[0] + rhs.v[0];
    result.v[1] = v[1] + rhs.v[1];
    result.v[2] = v[2] + rhs.v[2];
    return result;
}

vec3 vec3::operator+(float rhs) {
    vec3 result;
    result.v[0] = v[0] + rhs;
    result.v[1] = v[1] + rhs;
    result.v[2] = v[2] + rhs;
    return result;
}

vec3& vec3::operator+=(const vec3 &rhs) {
    v[0] += rhs.v[0];
    v[1] += rhs.v[1];
    v[2] += rhs.v[2];
    return *this;
}

vec3 vec3::operator-(const vec3 &rhs) {
    vec3 result;
    result.v[0] = v[0] = rhs.v[0];
    result.v[1] = v[1] = rhs.v[1];
    result.v[2] = v[2] = rhs.v[2];
    return result;
}

vec3 vec3::operator-(float rhs) {
    vec3 result;
    result.v[0] = v[0] - rhs;
    result.v[1] = v[1] - rhs;
    result.v[2] = v[2] - rhs;
    return result;
}

vec3& vec3::operator-=(const vec3 &rhs) {
    v[0] -= rhs.v[0];
    v[1] -= rhs.v[1];
    v[2] -= rhs.v[2];
    return *this;
}

vec3 vec3::operator*(float rhs) {
    vec3 result;
    result.v[0] = v[0] * rhs;
    result.v[1] = v[1] * rhs;
    result.v[2] = v[2] * rhs;
    return result;
}

vec3& vec3::operator*=(const vec3 &rhs) {
    v[0] *= rhs.v[0];
    v[1] *= rhs.v[1];
    v[2] *= rhs.v[2];
    return *this;
}

vec3 vec3::operator/(float rhs) {
    vec3 result;
    result.v[0] = v[0] / rhs;
    result.v[1] = v[1] / rhs;
    result.v[2] = v[2] / rhs;
    return result;
}

vec3 vec3::operator=(const vec3 &rhs) {
    vec3 result;
    result.v[0] = rhs.v[0];
    result.v[1] = rhs.v[1];
    result.v[2] = rhs.v[2];
    return result;
}

mat3::mat3() {}

mat3::mat3(
    float a, float b, float c,
    float d, float e, float f,
    float g, float h, float i) {
    m[0] = a;
    m[1] = b;
    m[2] = c;
    m[3] = d;
    m[4] = e;
    m[5] = f;
    m[6] = g;
    m[7] = h;
    m[8] = i;
}

mat4::mat4() {}

mat4::mat4(
    float a, float b, float c, float d,
    float e, float f, float g, float h,
    float i, float j, float k, float l,
    float mm, float n, float o, float p) {
    m[0] = a;
    m[1] = b;
    m[2] = c;
    m[3] = d;
    m[4] = e;
    m[5] = f;
    m[6] = g;
    m[7] = h;
    m[8] = i;
    m[9] = j;
    m[10] = k;
    m[11] = l;
    m[12] = mm;
    m[13] = n;
    m[14] = o;
    m[14] = p;
}

mat4 zero_mat4() {
    return mat4(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    );
}

mat4 identity_mat4() {
    return mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    );
}

vec4 mat4::operator*(const vec4 &rhs) {
    float x =
        m[0] * rhs.v[0] +
        m[4] * rhs.v[1] +
        m[8] * rhs.v[2] +
        m[12] * rhs.v[3];
    
    float y =
        m[1] * rhs.v[0] +
        m[5] * rhs.v[1] +
        m[9] * rhs.v[2] +
        m[13] * rhs.v[3];
    
    float z =
        m[2] * rhs.v[0] +
        m[6] * rhs.v[1] +
        m[10] * rhs.v[2] +
        m[14] * rhs.v[3];

    float w =
        m[3] * rhs.v[0] +
        m[7] * rhs.v[1] +
        m[11] * rhs.v[2] +
        m[15] * rhs.v[3];
    
    return vec4(x, y, z, w);
}

mat4 mat4::operator*(const mat4 &rhs) {
    mat4 result = zero_mat4();
    
    int r_index = 0;
    for(int col = 0; col < 4; col++) {
        for(int r = 0; r < 4; r++) {
            float sum = 0.0f;
            for(int i = 0; i < 4; i++) {
                sum += rhs.m[i + col * 4] * m[r + i * 4];
            }
            result.m[r_index] = sum;
            r_index++;
        }
    }
    return result;
}

mat4& mat4::operator=(const mat4 &rhs) {
    for(int i = 0; i < 16; i++) {
        m[i] = rhs.m[i];
    }
    return *this;
}

mat4 translate(const mat4 &m, const vec3 &v) {
    mat4 m_t = identity_mat4();
    m_t.m[12] = v.v[0];
    m_t.m[13] = v.v[1];
    m_t.m[14] = v.v[2];
    return m_t * m;
}

mat4 perspective(float fovy, float aspect, float near, float far) {
    float fov_rads = fovy * one_deg_in_rad;
    float range = tan(fov_rads / 2.0f) * near;
    float sx = (2.0f * near) / (range * aspect + range * aspect);
    float sy = near / range;
    float sz = -(far + near) / (far - near);
    float pz = -(2.0f * far * near) / (far - near);
    mat4 m = zero_mat4();
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    m.m[14] = pz;
    m.m[11] = -1.0f;
    return m;
}

float determinant(const mat4 &mm) {
    return
        mm.m[12] * mm.m[9] * mm.m[6] * mm.m[3] -
        mm.m[8] * mm.m[13] * mm.m[6] * mm.m[3] -
        mm.m[12] * mm.m[5] * mm.m[10] * mm.m[3] +
        mm.m[4] * mm.m[13] * mm.m[10] * mm.m[3] +
        
        mm.m[8] * mm.m[5] * mm.m[14] * mm.m[3] -
        mm.m[4] * mm.m[9] * mm.m[14] * mm.m[3] -
        mm.m[12] * mm.m[9] * mm.m[2] * mm.m[7] +
        mm.m[8] * mm.m[13] * mm.m[2] * mm.m[7] +
        
        mm.m[12] * mm.m[1] * mm.m[10] * mm.m[7] -
        mm.m[0] * mm.m[13] * mm.m[10] * mm.m[7] -
        mm.m[8] * mm.m[1] * mm.m[14] * mm.m[7] +
        mm.m[0] * mm.m[9] * mm.m[14] * mm.m[7] +
        
        mm.m[12] * mm.m[5] * mm.m[2] * mm.m[11] -
        mm.m[4] * mm.m[13] * mm.m[2] * mm.m[11] -
        mm.m[12] * mm.m[1] * mm.m[6] * mm.m[11] +
        mm.m[0] * mm.m[13] * mm.m[6] * mm.m[11] +
        
        mm.m[4] * mm.m[1] * mm.m[14] * mm.m[11] -
        mm.m[0] * mm.m[5] * mm.m[14] * mm.m[11] -
        mm.m[8] * mm.m[5] * mm.m[2] * mm.m[15] +
        mm.m[4] * mm.m[9] * mm.m[2] * mm.m[15] +
        
        mm.m[8] * mm.m[1] * mm.m[6] * mm.m[15] -
        mm.m[0] * mm.m[9] * mm.m[6] * mm.m[15] -
        mm.m[4] * mm.m[1] * mm.m[10] * mm.m[15] +
        mm.m[0] * mm.m[5] * mm.m[10] * mm.m[15];
}

mat4 inverse(const mat4 &mm) {
    float det = determinant(mm);
    if(0.0f == det) {
        std::cout << "Unable to get the determinant for this mat4." << std::endl;
        return mm;
    }
    
    float inv_det = 1.0f / det;
    
    return mat4(
        inv_det * (
            mm.m[9] * mm.m[14] * mm.m[7] - mm.m[13] * mm.m[10] * mm.m[7] +
            mm.m[13] * mm.m[6] * mm.m[11] - mm.m[5] * mm.m[14] * mm.m[11] -
            mm.m[9] * mm.m[6] * mm.m[15] + mm.m[5] * mm.m[10] * mm.m[15]
        ),
        inv_det * (
            mm.m[13] * mm.m[10] * mm.m[3] - mm.m[9] * mm.m[14] * mm.m[3] -
            mm.m[13] * mm.m[2] * mm.m[11] + mm.m[1] * mm.m[14] * mm.m[11] +
            mm.m[9] * mm.m[2] * mm.m[15] - mm.m[1] * mm.m[10] * mm.m[15]
        ),
        inv_det * (
            mm.m[5] * mm.m[14] * mm.m[3] - mm.m[13] * mm.m[6] * mm.m[3] +
            mm.m[13] * mm.m[2] * mm.m[7] - mm.m[1] * mm.m[14] * mm.m[7] -
            mm.m[5] * mm.m[2] * mm.m[15] + mm.m[1] * mm.m[6] * mm.m[15]
        ),
        inv_det * (
            mm.m[9] * mm.m[6] * mm.m[3] - mm.m[5] * mm.m[10] * mm.m[3] -
            mm.m[9] * mm.m[2] * mm.m[7] + mm.m[1] * mm.m[10] * mm.m[7] +
            mm.m[5] * mm.m[2] * mm.m[11] - mm.m[1] * mm.m[6] * mm.m[11]
        ),
        inv_det * (
            mm.m[12] * mm.m[10] * mm.m[7] - mm.m[8] * mm.m[14] * mm.m[7] -
            mm.m[12] * mm.m[6] * mm.m[11] + mm.m[4] * mm.m[14] * mm.m[11] +
            mm.m[8] * mm.m[6] * mm.m[15] - mm.m[4] * mm.m[10] * mm.m[15]
                   ),
        inv_det * (
            mm.m[8] * mm.m[14] * mm.m[3] - mm.m[12] * mm.m[10] * mm.m[3] +
            mm.m[12] * mm.m[2] * mm.m[11] - mm.m[0] * mm.m[14] * mm.m[11] -
            mm.m[8] * mm.m[2] * mm.m[15] + mm.m[0] * mm.m[10] * mm.m[15]
        ),
        inv_det * (
            mm.m[12] * mm.m[6] * mm.m[3] - mm.m[4] * mm.m[14] * mm.m[3] -
            mm.m[12] * mm.m[2] * mm.m[7] + mm.m[0] * mm.m[14] * mm.m[7] +
            mm.m[4] * mm.m[2] * mm.m[15] - mm.m[0] * mm.m[6] * mm.m[15]
        ),
        inv_det * (
            mm.m[4] * mm.m[10] * mm.m[3] - mm.m[8] * mm.m[6] * mm.m[3] +
            mm.m[8] * mm.m[2] * mm.m[7] - mm.m[0] * mm.m[10] * mm.m[7] -
            mm.m[4] * mm.m[2] * mm.m[11] + mm.m[0] * mm.m[6] * mm.m[11]
        ),
        inv_det * (
            mm.m[8] * mm.m[13] * mm.m[7] - mm.m[12] * mm.m[9] * mm.m[7] +
            mm.m[12] * mm.m[5] * mm.m[11] - mm.m[4] * mm.m[13] * mm.m[11] -
            mm.m[8] * mm.m[5] * mm.m[15] + mm.m[4] * mm.m[9] * mm.m[15]
        ),
        inv_det * (
            mm.m[12] * mm.m[9] * mm.m[3] - mm.m[8] * mm.m[13] * mm.m[3] -
            mm.m[12] * mm.m[1] * mm.m[11] + mm.m[0] * mm.m[13] * mm.m[11] +
            mm.m[8] * mm.m[1] * mm.m[15] - mm.m[0] * mm.m[9] * mm.m[15]
        ),
        inv_det * (
            mm.m[4] * mm.m[13] * mm.m[3] - mm.m[12] * mm.m[5] * mm.m[3] +
            mm.m[12] * mm.m[1] * mm.m[7] - mm.m[0] * mm.m[13] * mm.m[7] -
            mm.m[4] * mm.m[1] * mm.m[15] + mm.m[0] * mm.m[5] * mm.m[15]
        ),
        inv_det * (
            mm.m[8] * mm.m[5] * mm.m[3] - mm.m[4] * mm.m[9] * mm.m[3] -
            mm.m[8] * mm.m[1] * mm.m[7] + mm.m[0] * mm.m[9] * mm.m[7] +
            mm.m[4] * mm.m[1] * mm.m[11] - mm.m[0] * mm.m[5] * mm.m[11]
        ),
        inv_det * (
            mm.m[12] * mm.m[9] * mm.m[6] - mm.m[8] * mm.m[13] * mm.m[6] -
            mm.m[12] * mm.m[5] * mm.m[10] + mm.m[4] * mm.m[13] * mm.m[10] +
            mm.m[8] * mm.m[5] * mm.m[14] - mm.m[4] * mm.m[9] * mm.m[14]
        ),
        inv_det * (
            mm.m[8] * mm.m[13] * mm.m[2] - mm.m[12] * mm.m[9] * mm.m[2] +
            mm.m[12] * mm.m[1] * mm.m[10] - mm.m[0] * mm.m[13] * mm.m[10] -
            mm.m[8] * mm.m[1] * mm.m[14] + mm.m[0] * mm.m[9] * mm.m[14]
        ),
        inv_det * (
            mm.m[12] * mm.m[5] * mm.m[2] - mm.m[4] * mm.m[13] * mm.m[2] -
            mm.m[12] * mm.m[1] * mm.m[6] + mm.m[0] * mm.m[13] * mm.m[6] +
            mm.m[4] * mm.m[1] * mm.m[14] - mm.m[0] * mm.m[5] * mm.m[14]
        ),
        inv_det * (
            mm.m[4] * mm.m[9] * mm.m[2] - mm.m[8] * mm.m[5] * mm.m[2] +
            mm.m[8] * mm.m[1] * mm.m[6] - mm.m[0] * mm.m[9] * mm.m[6] -
            mm.m[4] * mm.m[1] * mm.m[10] + mm.m[0] * mm.m[5] * mm.m[10]
        )
    );
}
