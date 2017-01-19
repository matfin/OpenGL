//
//  CubeTransformDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 13/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef CubeTransformDemo_hpp
#define CubeTransformDemo_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <cmath>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Matrices {
private:
    float rotate_x = 0.0f;
    float rotate_y = 0.0f;
    float rotate_z = 0.0f;
    float move_x = 0.0f;
    float move_y = 0.0f;
    
public:
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
    
    float scale[16] = {};
    
    void translateX(Direction direction) {
        switch(direction) {
            case LEFT: {
                move_x -= 0.05f;
                break;
            }
            case RIGHT: {
                move_x += 0.05f;
                break;
            }
        }
        translation[12] = move_x;
    }
    
    void translateY(Direction direction) {
        switch(direction) {
            case UP: {
                move_y += 0.05f;
                break;
            }
            case DOWN: {
                move_y -= 0.05f;
                break;
            }
        }
        translation[13] = move_y;
    }
    
    void rotateX(Direction direction) {
        switch(direction) {
            case UP: {
                rotate_x += 0.05f;
                break;
            }
            case DOWN: {
                rotate_x -= 0.05f;
                break;
            }
        }
        rotation_x[5] = cosf(rotate_x);
        rotation_x[6] = cosf(rotate_x);
        rotation_x[9] = -sinf(rotate_x);
        rotation_x[10] = cosf(rotate_x);
    }
    
    void rotateY(Direction direction) {
        switch(direction) {
            case LEFT: {
                rotate_y += 0.05f;
                break;
            }
            case RIGHT: {
                rotate_y -= 0.05f;
                break;
            }
        }
        rotation_y[0] = cosf(rotate_y);
        rotation_y[2] = -sinf(rotate_y);
        rotation_y[8] = sinf(rotate_y);
        rotation_y[10] = cosf(rotate_y);
    }
    
    void rotateZ(Direction direction) {
        switch(direction) {
            case LEFT: {
                rotate_z += 0.05f;
                break;
            }
            case RIGHT: {
                rotate_z -= 0.05f;
                break;
            }
        }
        
        rotation_z[0] = cosf(rotate_z);
        rotation_z[1] = sinf(rotate_z);
        rotation_z[4] = -sinf(rotate_z);
        rotation_z[5] = cosf(rotate_z);
    }
};

class CubeTransformDemo {
private:
    /**
     *  private variables
     */
    GLuint program;
    GLFWwindow *window;
    std::vector<GLfloat> vertex_floats;
    std::vector<GLfloat> colour_floats;
    GLuint vao;
    
    /**
     *  utility items
     */
    ShaderLoader shader_loader;
    GLParams gl_params;
    
    /**
     *  Matrices for transformation and rotation.
     */
    Matrices m;
    float *current_matrix;
    
    /**
     *  Used to track interpolation, where we 
     *  make the colours and points GLFloat 
     *  vectors more fine grained and the shape 
     *  smoother as a result.
     */
    float interpolation = 0.0f;

    
    /** 
     *  private functions
     */
    bool setupWindow(void);
    GLuint compileShader(std::string shader_src_str , GLenum shader_type);
    GLuint linkShaders(const GLuint vertex_shader, const GLuint fragment_shader);
    GLuint prepareMesh(const std::vector<GLfloat> points, const std::vector<GLfloat> colours);
    void drawLoop(GLuint vao);
    void applyTransformationMatrix(void);
    void keyActionListener(void);
    
public:
    /**  
     *  public functions
     */
    CubeTransformDemo(std::vector<GLfloat> _vertex_floats, std::vector<GLfloat> _colour_floats);
    ~CubeTransformDemo();
    int run(void);
};

#endif /* CubeTransformDemo_hpp */
