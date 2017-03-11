//
//  PhongLightingDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 11/03/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef PhongLightingDemo_hpp
#define PhongLightingDemo_hpp

#include <Opengl/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Structs.h"
#include "Mesh.hpp"

class PhongLightingDemo {
    
private:
    PhongLightingDemo();
    ~PhongLightingDemo() {};
    PhongLightingDemo(PhongLightingDemo const &);
    void operator=(PhongLightingDemo const &);
    
    GLFWwindow *window;
    GLuint program;
    GLenum drawing_method = GL_TRIANGLES;
    
    std::vector<Mesh> meshes;
    
    void createProgram(void);
    void prepareMeshes(void);
    void drawLoop(void);
    void keyActionListener(void);
    int start(void);
    
public:
    static PhongLightingDemo& getInstance();
    static void addMesh(Mesh mesh, const Position position, const Rotation rotation);
    static int run(void);
};

#endif /* PhongLightingDemo_hpp */
