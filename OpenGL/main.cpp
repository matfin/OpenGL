//
//  main.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include <vector>
#include "Points.hpp"
#include "Meshes.h"
#include "Shapes.hpp"
#include "Structs.h"
#include "Matrix.hpp"
#include "Shaders.hpp"
#include "ObjectLoader.hpp"
#include "VertexBufferObjects.hpp"
#include "CubeTransformDemo.hpp"
#include "CameraPerspectiveDemo.hpp"
#include "QuaternionDemo.hpp"

using namespace std;

int runCubeTransformDemo(void) {
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

int runModelLoadDemo(void) {
    ObjectLoader loader;
    loader.load("structure.obj");
    
    vector<GLfloat> vertices = loader.getVertices();
    vector<GLfloat> colours(vertices.size());
    
    int i = 0;
    
    transform(begin(colours), end(colours), begin(colours), [&i](GLfloat c) {
        GLfloat x = 0;
        if(i++ == 0) x = 1.0f;
        else if(i % 4 == 0) x =  1.0f;
        else if(i % 8 == 0) x = 1.0f;
        return x;
    });
    
    CubeTransformDemo *model_demo = new CubeTransformDemo(vertices, colours);
    int run = model_demo->run();
    delete(model_demo);
    return run;
}

int matrixOperations() {
    
    {
        Matrix<int> mul1({
            Row<int>({1, 4}),
            Row<int>({19, 7})
        });
        
        Matrix<int> mul2({
            Row<int>({9}),
            Row<int>({16})
        });
        
        Matrix<int> result = mul1 * mul2;
        bool wait = true;
    }
    {
        Matrix<int> mul1({
            Row<int>({1,4,3,6}),
            Row<int>({5,2,1,0})
        });
        Matrix<int> mul2({
            Row<int>({1,3}),
            Row<int>({4,0}),
            Row<int>({5,-1}),
            Row<int>({6,8})
        });
        
        Matrix<int> result = mul1 * mul2;
        bool wait = true;
    }
    {
        Matrix<int> mul1({
            Row<int>({0,2,6}),
            Row<int>({9,7,4}),
            Row<int>({3,1,8})
        });
        Matrix<int> mul2({
            Row<int>({9,5,6}),
            Row<int>({2,2,1}),
            Row<int>({0,0,3})
        });
        
        Matrix<int> result = mul1 * mul2;
        bool wait = true;
    }
    {
        Matrix<int> add_one({
            Row<int>({1,2,3}),
            Row<int>({4,5,6})
        });
        Matrix<int> add_two({
            Row<int>({1,2,3}),
            Row<int>({4,5,6})
        });
        add_one += add_two;
    }
    {
        Matrix<int> sub_one({
            Row<int>({3,4,5}),
            Row<int>({6,7,8})
        });
        Matrix<int> sub_two({
            Row<int>({1,2,3}),
            Row<int>({4,5,6})
        });
        
        sub_one -= sub_two;
        int x = 1;
    }
    {
        Matrix<int> scalar_mul({
            Row<int>({1,2,3}),
            Row<int>({4,5,6})
        });
        scalar_mul *= 4;
        int x = 1;
    }
    {
        Matrix<int> mul_one({
            Row<int>({0,2,6}),
            Row<int>({9,7,4}),
            Row<int>({3,1,8})
        });
        Matrix<int> mul_two({
            Row<int>({9,5,6}),
            Row<int>({2,2,1}),
            Row<int>({0,0,3})
        });
        
        Matrix<int> x = mul_one * mul_two;
        mul_one *= mul_two;
        int f = 1;
    }
    
    return 0;
}

int distanceCalculatorDemo() {
    
    Matrix<GLfloat> camera_position({
        Row<GLfloat>({20}),
        Row<GLfloat>({2}),
        Row<GLfloat>({-15})
    });
    
    Matrix<GLfloat> item_position({
        Row<GLfloat>({10.5}),
        Row<GLfloat>({1}),
        Row<GLfloat>({-20})
    });
    
    Matrix<GLfloat> origin_position({
        Row<GLfloat>({0}),
        Row<GLfloat>({0}),
        Row<GLfloat>({0})
    });
    
    Matrix<GLfloat> movement = origin_position - camera_position;
    Matrix<GLfloat> translated_to = movement + item_position;
    
    return 0;
    
}

int runCameraPerspectiveDemo(void) {
    
    CameraPerspectiveDemo *demo = new CameraPerspectiveDemo();
    
    /**
     *  Generating a cube mesh and adding it to the world:
     *  
     *  - The first parameter is the generated mesh
     *  - The second parameter is the world position
     *  - The third parameter is the world rotation
     */
    Mesh mesh;
    mesh.generateCube(2.0f);
    demo->addMesh(mesh, {0.0f, 0.0f, 3.0f}, {0.0f, 0.0f, 0.0f});
    
    int run = demo->run();
    delete(demo);
    return run;
}

int runQuaternionDemo(void) {
    Mesh mesh;
    mesh.generateCube(2.0f);
    QuaternionDemo::addMesh(mesh, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {-3.0f, 1.0f, 0.0f}, {45.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {3.0f, -1.0f, 2.0f}, {0.0f, 0.0f, 45.0f});

    QuaternionDemo::addMesh(mesh, {0.0f, 4.0f, 6.0f}, {0.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {-3.0f, 5.0f, 6.0f}, {45.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {3.0f, 3.0f, 8.0f}, {0.0f, 0.0f, 45.0f});
    
    QuaternionDemo::addMesh(mesh, {0.0f, 0.0f, 6.0f}, {0.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {-3.0f, 1.0f, 6.0f}, {45.0f, 0.0f, 0.0f});
    QuaternionDemo::addMesh(mesh, {3.0f, -1.0f, 8.0f}, {0.0f, 0.0f, 45.0f});

    
    return QuaternionDemo::run();
    return 0;
}

int main(int argc, const char * argv[]) {
//    return shapes_main();
//    return shaders_main();
//    return vertex_buffer_objects_main();
//    int run = runModelLoadDemo();
//    int run = runCubeTransformDemo();
//    int matrix_run = matrixOperations();
//    int mo_run = distanceCalculatorDemo();
//    int run = runCameraPerspectiveDemo();
    int run = runQuaternionDemo();
    
    return 0;
}
