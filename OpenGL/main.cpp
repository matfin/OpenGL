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
        return p * 0.4;
    });
    /**
     *  Set up the colours too.
     *  Note:   I know this is a horrible way to do it,
     *          but we will move on to texture mapping soon!
     */
    vector<GLfloat> cube_colours(108);
    
    int i = 0;
    
    transform(begin(cube_colours), end(cube_colours), begin(cube_colours), [&i](GLfloat c) {
        GLfloat x = 0;
        
        if(i++ == 0) x = 1.0f;
        else if(i % 4 == 0) x =  1.0f;
        else if(i % 8 == 0) x = 1.0f;
        
        return x;
    });
    
    
    CubeTransformDemo *cube_demo = new CubeTransformDemo(cube_points, cube_colours);
    int run = cube_demo->run();
    delete(cube_demo);
    return run;
}
