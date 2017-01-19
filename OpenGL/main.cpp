//
//  main.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <vector>
#include "Points.hpp"
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
     *  Cube points are too big, let's 
     *  reduce their values.
     */
    transform(begin(cube_points), end(cube_points), begin(cube_points), [](GLfloat p) {
        return p / 2;
    });
    /**
     *  Set up the colours too.
     *  Note:   I know this is a horrible way to do it,
     *          but we will move on to texture mapping soon!
     */
    vector<GLfloat> cube_colours(108);
    
    GLfloat x = 0.0f;
    
    transform(begin(cube_colours), end(cube_colours), begin(cube_colours), [&x](GLfloat c) {
        x += 0.002f;
        return 0.5f + x;
    });
    
    
    CubeTransformDemo *cube_demo = new CubeTransformDemo(cube_points, cube_colours);
    int run = cube_demo->run();
    delete(cube_demo);
    return run;
}
