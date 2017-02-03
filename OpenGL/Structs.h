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

struct Position {
    GLfloat px;
    GLfloat py;
    GLfloat pz;
};

struct Rotation {
    GLfloat rx;
    GLfloat ry;
    GLfloat rz;
};

#endif /* Structs_h */
