//
//  VecMat.hpp
//  OpenGL
//
//  Created by Matt Finucane on 01/03/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef VecMat_hpp
#define VecMat_hpp

struct vec2;
struct vec3;
struct vec4;
struct mat3;
struct mat4;

struct vec2 {
    vec2();
    vec2(float x, float y);
    
    float v[2];
};

struct vec3 {
    vec3();
    vec3(float x, float y, float z);
    vec3(const vec2 &vv, float z);
    vec3(const vec4 &vv);
    
    vec3 operator+(const vec3 &rhs);
    vec3 operator+(float rhs);
    vec3& operator+=(const vec3 &rhs);
    vec3 operator-(const vec3 &rhs);
    vec3 operator-(float rhs);
    vec3& operator-=(const vec3 &rhs);
    vec3 operator*(float rhs);
    vec3& operator*=(const vec3 &rhs);
    vec3 operator/(float rhs);
    vec3 operator=(const vec3 &rhs);
    
    float v[3];
};

struct vec4 {
    vec4();
    vec4(float x, float y, float z, float w);
    vec4(const vec2 &vv, float z, float w);
    vec4(const vec3 &vv, float w);
    
    float v[4];
};

struct mat3 {
    mat3();
    mat3(
        float a, float b, float c,
        float d, float e, float f,
        float g, float h, float i
    );
    
    float m[9];
};

struct mat4 {
    mat4();
    mat4(
        float a, float b, float c, float d,
        float e, float f, float g, float h,
        float i, float j, float k, float l,
        float mm, float n, float o, float p
    );
    
    vec4 operator*(const vec4 &rhs);
    mat4 operator*(const mat4 &rhs);
    mat4& operator=(const mat4 &rhs);
    
    float m[16];
};

#endif /* VecMat_hpp */
