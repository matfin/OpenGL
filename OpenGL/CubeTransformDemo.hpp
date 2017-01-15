//
//  CubeTransformDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 13/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef CubeTransformDemo_hpp
#define CubeTransformDemo_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <cmath>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

struct Matrices {
    
    float rotate = 0.0f;
    float move = 0.0f;
    
    float rotation[3][16] = {
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, cosf(rotate), sinf(rotate), 0.0f,
            0.0f, -sinf(rotate), cosf(rotate), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        },
        {
            cosf(move), 0.0f, -sinf(move), 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            sinf(move), 0.0f, cosf(move), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        },
        {
            cosf(move), sinf(move), 0.0f, 0.0f,
            -sinf(move), cosf(move), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }
    };
    float translation[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        (0.0f + move), 0.0f, 0.0f, 1.0f
    };
    float scale[16] = {};
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
    void rotateX(float rotation);
    void rotateY(float rotation);
    void rotateZ(float rotation);
    void translateX(float translation);
    void translateY(float translation);
    void translateZ(float translation);
    void scale(float scale);
    int run(void);
};

#endif /* CubeTransformDemo_hpp */
