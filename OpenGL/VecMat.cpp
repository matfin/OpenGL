//
//  VecMat.cpp
//  OpenGL
//
//  Created by Matt Finucane on 01/03/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "VecMat.hpp"

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
