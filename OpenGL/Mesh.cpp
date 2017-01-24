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

void Mesh::transformOrigin(const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) {
    transform(begin(points), end(points), begin(points), [pos_x, pos_y, pos_z](Point &point) {
        point.x += pos_x;
        point.y += pos_y;
        point.z += pos_z;
        return point;
    });
}

void Mesh::scaleMesh(const GLfloat value) {
    
}

void Mesh::setVao(GLuint _vao) {
    vao = _vao;
}


