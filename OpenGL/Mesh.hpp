//
//  Mesh.hpp
//  OpenGL
//
//  Created by Matt Finucane on 24/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "Matrices.hpp"
#include "Structs.h"

class Mesh {
    
private:
    std::vector<Point> points;
    std::vector<Colour> colours;
    mutable Matrices m;
    GLuint vao;
    
public:
    Mesh(std::vector<Point> _points, std::vector<Colour> _colours);
    ~Mesh();
    
    GLuint getVao() const;
    int pointsSize() const;
    int coloursSize() const;
    Position originDifference() const;
    Matrices* getMatrices() const;
    
    std::vector<GLfloat> pointsUnwound();
    std::vector<GLfloat> coloursUnwound();
    
    void applyMatrices(GLuint program) const;
    void setVao(GLuint _vao);
};

#endif /* Mesh_hpp */
