//
//  VecMat.hpp
//  OpenGL
//
//  Created by Matt Finucane on 01/03/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef VecMat_hpp
#define VecMat_hpp

#define one_deg_in_rad (2.0 * M_PI) / 360.0f
#define one_rad_in_deg 360.0f / (2.0 * M_PI)

struct vec2;
struct vec3;
struct vec4;
struct mat3;
struct mat4;
struct versor;

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

struct versor {
    versor();
    versor operator/(float rhs);
    versor operator*(float rhs);
    versor operator*(const versor &rhs);
    versor operator+(const versor &rhs);
    float q[4];
};

/**
 *  Functions for vectors
 */
float length(const vec3 &v);
float length2(const vec3 &v);
float dot(const vec3 &a, const vec3 &b);
float get_squared_dist(vec3 from, vec3 to);
float direction_to_heading(vec3 d);
vec3 cross(const vec3 &a, const vec3 &b);
vec3 normalise(const vec3 &v);
vec3 heading_to_direction(float degrees);

/**
 *  Functions for matrices
 */
mat3 zero_mat3();
mat3 identity_mat3();
mat4 zero_mat4();
mat4 identity_mat4();
mat4 translate(const mat4 &m, const vec3 &v);
mat4 perspective(float fovy, float aspect, float near, float far);
mat4 look_at(const vec3 &cam_pos, vec3 target_pos, const vec3 &up);
float determinant(const mat4 &mm);
mat4 inverse(const mat4 &mm);
mat4 transpose(const mat4 &mm);
mat4 rotate_x_deg(const mat4 &m, float deg);
mat4 rotate_y_deg(const mat4 &m, float deg);
mat4 rotate_z_deg(const mat4 &m, float deg);
mat4 scale(const mat4 &m, const vec3 &v);

/**
 *  Functions versors - helpful for Quaternions
 */
versor quat_from_axis_rad(float radians, float x, float y, float z);
versor quat_from_axis_deg(float degress, float x, float y, float z);
mat4 quat_to_mat4(const versor &q);
float dot(const versor &q, const versor &r);
versor slerp(versor &q, versor &r, float t);
versor normalise(versor &q);

#endif /* VecMat_hpp */
