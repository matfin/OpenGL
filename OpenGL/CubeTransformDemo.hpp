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
#include "Matrices.hpp"

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
    Matrices *m = new Matrices();
    
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
    void applyMatrices(void);
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
