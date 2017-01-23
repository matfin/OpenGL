//
//  Structs.h
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Structs_h
#define Structs_h

#include <GLFW/glfw3.h>
#include <vector>

struct Point {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Colour {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

struct Mesh {
    std::vector<Point> points;
    std::vector<Colour> colours;
    GLuint vao;
};

#endif /* Structs_h */
