//
//  Mesh.cpp
//  OpenGL
//
//  Created by Matt Finucane on 24/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Mesh.hpp"

using namespace std;

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

Position Mesh::originDifference() const {
    return m.getTranslationDifference();
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
        glUniformMatrix4fv(rot_x_matrix, 1, GL_FALSE, m.getRotationX());
        glUniformMatrix4fv(rot_y_matrix, 1, GL_FALSE, m.getRotationY());
        glUniformMatrix4fv(rot_z_matrix, 1, GL_FALSE, m.getRotationZ());
        glUniformMatrix4fv(scale_matrix, 1, GL_FALSE, m.getScaling());
        glUniformMatrix4fv(translate_matrix, 1, GL_FALSE, m.getTranslation());
    }
    else {
        cout << "Unable to apply matrices to this mesh." << endl;
    }
}

void Mesh::setVao(GLuint _vao) {
    vao = _vao;
}


