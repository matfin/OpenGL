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
#include <iostream>

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
private:
    std::vector<Point> points;
    std::vector<Colour> colours;
    GLuint vao;
public:
    Mesh(std::vector<Point> _points, std::vector<Colour> _colours) : points(_points), colours(_colours) {
        std::cout << "Construct: Mesh" << std::endl;
    }
    
    ~Mesh() {
        std::cout << "Desturct: Mesh" << std::endl;
    }
    
    GLuint getVao() {
        return vao;
    }
    
    std::vector<GLfloat> pointsUngrouped() {
        std::vector<GLfloat> points_ungrouped;
        points_ungrouped.reserve(points.size() * 3);
        for(const auto &point: points) {
            points_ungrouped.push_back(point.x);
            points_ungrouped.push_back(point.y);
            points_ungrouped.push_back(point.z);
        }
        return points_ungrouped;
    }
    
    std::vector<GLfloat> coloursUngrouped() {
        std::vector<GLfloat> colours_ungrouped;
        colours_ungrouped.reserve(colours.size() * 3);
        for(const auto &colour: colours) {
            colours_ungrouped.push_back(colour.r);
            colours_ungrouped.push_back(colour.g);
            colours_ungrouped.push_back(colour.b);
        }
        return colours_ungrouped;
    }

    void transformOrigin(const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) {
        std::transform(std::begin(points), std::end(points), std::begin(points), [pos_x, pos_y, pos_z](Point &point) {
            point.x += pos_x;
            point.y += pos_y;
            point.z += pos_z;
            return point;
        });
    }
    
    void setVao(GLuint _vao) {
        vao = _vao;
    }
};

#endif /* Structs_h */
