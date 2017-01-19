//
//  main.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <vector>
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
    vector<GLfloat> square_points {
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    vector<GLfloat> square_colours {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f
    };
    
    vector<GLfloat> triangle_points {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };
    vector<GLfloat> triangle_colours {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    CubeTransformDemo *cube_demo = new CubeTransformDemo(triangle_points, triangle_colours);
    int run = cube_demo->run();
    delete(cube_demo);
//    return run;
    return 0;
}
