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
#include "ShaderLoader.hpp"
#include "GLParams.hpp"

struct Matrices {
    float rotation[16] = {};
    float translation[16] = {};
    float scale[16] = {};
};

class CubeTransformDemo {
private:
    
    /**
     *  private variables
     */
    GLFWwindow *window;
    std::vector<float> vertex_floats;
    
    /** 
     *  private functions
     */
    bool setupWindow(void) const;
    GLuint compileShader(const std::string shader_source, GLenum shader_type);
    GLuint linkShaders(const GLuint vertex_shader, const GLuint fragment_shader);
    GLuint prepareCubeMesh(const std::vector<GLfloat> points, const std::vector<GLfloat> colours);
    void drawLoop(GLFWwindow *window, const GLuint program, const GLuint vao);
public:
    
    /**  
     *  public functions
     */
    CubeTransformDemo(std::vector<float> _vertex_floats);
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
