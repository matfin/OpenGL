//
//  Mesh.hpp
//  OpenGL
//
//  Created by Matt Finucane on 24/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <OpenGL/gl3.h>
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
    Mesh();
    Mesh(std::vector<Point> _points, std::vector<Colour> _colours);
    ~Mesh();
    
    void prepareBuffers();
    GLuint getVao() const;
    int pointsSize() const;
    int coloursSize() const;
    Matrices* getMatrices() const;
    
    std::vector<GLfloat> pointsUnwound() const;
    std::vector<GLfloat> coloursUnwound() const;
    
    void generateCube(float size);
    void applyIdentityMatrix(GLuint program) const;
    void applyTranslationMatrix(GLuint program) const;
    void applyMatrices(GLuint program) const;
};

#endif /* Mesh_hpp */
