//
//  main.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <vector>
#include <OpenGL/gl3.h>
#include "Shapes.hpp"
#include "Shaders.hpp"
#include "VertexBufferObjects.hpp"
#include "CubeTransformDemo.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
//    return shapes_main();
//    return shaders_main();
//    return vertex_buffer_objects_main();
    
    /**
     *  Teeing up the points and colours 
     *  for a square.
     */
    vector<GLfloat> points {
        /**
         *  Front 2 triangles
         */
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
        
        /**
         *  Left side 2 triangles
         */
//        -0.5f, 0.5f, -0.5f,
    };
    vector<GLfloat> colours {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f
    };
    
    CubeTransformDemo *cube_demo = new CubeTransformDemo(points, colours);
    cube_demo->run();
    delete(cube_demo);
}
