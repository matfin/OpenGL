//
//  Mesh.cpp
//  OpenGL
//
//  Created by Matt Finucane on 24/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Mesh.hpp"

using namespace std;

Mesh::Mesh(){}

Mesh::Mesh(std::vector<Point> _points, std::vector<Colour> _colours) : points(_points), colours(_colours) {
    cout << "Construct: Mesh" << endl;
}

Mesh::~Mesh() {
    cout << "Destruct: Mesh" << endl;
}

GLuint Mesh::getVao() const {
    return vao;
}

int Mesh::pointsSize() const {
    return points.size();
}

int Mesh::coloursSize() const {
    return colours.size();
}

Matrices* Mesh::getMatrices() const {
    return &m;
}

vector<GLfloat> Mesh::pointsUnwound() {
    vector<GLfloat> points_unwound;
    points_unwound.reserve(points.size() * 3);
    for(const auto &point: points) {
        points_unwound.push_back(point.x);
        points_unwound.push_back(point.y);
        points_unwound.push_back(point.z);
    }
    return points_unwound;
}

vector<GLfloat> Mesh::coloursUnwound() {
    std::vector<GLfloat> colours_unwound;
    colours_unwound.reserve(colours.size() * 3);
    for(const auto &colour: colours) {
        colours_unwound.push_back(colour.r);
        colours_unwound.push_back(colour.g);
        colours_unwound.push_back(colour.b);
    }
    return colours_unwound;
}

void Mesh::generateCube(float size) {
    
    size *= 0.5f;
    
    points = vector<Point> {
        // bottom face
        {size, -size, -size},
        {size, -size, size},
        {-size, -size, -size},
        
        {size, -size, size},
        {-size, -size, size},
        {-size, -size, -size},
        
        // rear face
        {size, size, -size},
        {size, -size, -size},
        {-size, -size, -size},
        
        {size, size, -size},
        {-size, -size, -size},
        {-size, size, -size},
        
        // left face
        {-size, -size, -size},
        {-size, -size, size},
        {-size, size, -size},
        
        {-size, -size, size},
        {-size, size, size},
        {-size, size, -size},
        
        // top face
        {-size, size, -size},
        {-size, size, size},
        {size, size, size},
        
        {size, size, size},
        {size, size, -size},
        {-size, size, -size},
        
        // front face
        {-size, size, size},
        {-size, -size, size},
        {size, -size, size},
        
        {size, -size, size},
        {size, size, size},
        {-size, size, size},
        
        // right face
        {size, size, size},
        {size, -size, size},
        {size, -size, -size},
        
        {size, -size, -size},
        {size, size, -size},
        {size, size, size}
    };
    
    colours = vector<Colour> {
        // bottom face
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        
        // rear face
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        
        // left face
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        
        // top face
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        {1.0f, 0.75f, 0.75f},
        
        // front face
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        {0.5f, 1.0f, 0.75f},
        
        // right face
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
        {0.25f, 0.5f, 1.0f},
    };
    
}

void Mesh::applyIdentityMatrix(GLuint program) const {
    GLuint identity_matrix_loc = glGetUniformLocation(program, "identity_matrix");
    
    Matrix<GLfloat> identity_matrix = m.identity_matrix();
    vector<GLfloat> identity_matrix_unwound = identity_matrix.unwind();
    
    if(GL_TRUE != identity_matrix_loc) {
        glUniformMatrix4fv(identity_matrix_loc, 1, GL_FALSE, &identity_matrix_unwound[0]);
    }
    else {
        cout << "The identity matrix could not be applied to this mesh." << endl;
    }
}

void Mesh::applyMatrices(GLuint program) const {
    GLuint rot_x_matrix = glGetUniformLocation(program, "rot_x_matrix");
    GLuint rot_y_matrix = glGetUniformLocation(program, "rot_y_matrix");
    GLuint rot_z_matrix = glGetUniformLocation(program, "rot_z_matrix");
    GLuint scale_matrix = glGetUniformLocation(program, "scale_matrix");
    GLuint translate_matrix = glGetUniformLocation(program, "translate_matrix");
    
    if(
       GL_TRUE != rot_x_matrix ||
       GL_TRUE != rot_y_matrix ||
       GL_TRUE != rot_z_matrix ||
       GL_TRUE != scale_matrix ||
       GL_TRUE != translate_matrix
       ) {
        glUniformMatrix4fv(rot_x_matrix, 1, GL_FALSE, &m.getMatrixUnwound(ROTATION_X)[0]);
        glUniformMatrix4fv(rot_y_matrix, 1, GL_FALSE, &m.getMatrixUnwound(ROTATION_Y)[0]);
        glUniformMatrix4fv(rot_z_matrix, 1, GL_FALSE, &m.getMatrixUnwound(ROTATION_Z)[0]);
        glUniformMatrix4fv(scale_matrix, 1, GL_FALSE, &m.getMatrixUnwound(SCALING)[0]);
        glUniformMatrix4fv(translate_matrix, 1, GL_FALSE, &m.getMatrixUnwound(TRANSLATION)[0]);
    }
    else {
        cout << "Unable to apply matrices to this mesh." << endl;
    }
}

void Mesh::setVao(GLuint _vao) {
    vao = _vao;
}


