//
//  CubeTransformDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 13/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef CubeTransformDemo_hpp
#define CubeTransformDemo_hpp

//#include <OpenGL/gl3.h>
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
                move_x -= 0.005f;
                break;
            }
            case RIGHT: {
                move_x += 0.005f;
                break;
            }
        }
        translation[12] = move_x;
    }
    
    void translateY(Direction direction) {
        switch(direction) {
            case UP: {
                move_y += 0.005f;
                break;
            }
            case DOWN: {
                move_y -= 0.005f;
                break;
            }
        }
        translation[13] = move_y;
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
    
    /**
     *  private transformation functions
     */
    void rotateX(Direction direction);
    void rotateY(float rotation, Direction direction);
    void rotateZ(float rotation, Direction direction);
    void translateX(Direction direction);
    void translateY(Direction direction);
    void translateZ(float translation, Direction direction);
    void scale(float scale);

public:
    /**  
     *  public functions
     */
    CubeTransformDemo(std::vector<GLfloat> _vertex_floats, std::vector<GLfloat> _colour_floats);
    ~CubeTransformDemo();
    int run(void);
};

#endif /* CubeTransformDemo_hpp */
