//
//  ObjectLoader.hpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef ObjectLoader_hpp
#define ObjectLoader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <GLFW/glfw3.h>
#include "Enumerations.h"

class ObjectLoader {
private:
    std::vector<GLfloat>vertices = {};
    std::vector<GLfloat>normals = {};
    std::vector<GLfloat>texture_coords = {};
    std::vector<GLfloat>faces = {};
    
    bool vertices_loaded = false;
    bool normals_loaded = false;
    bool texture_coords_loaded = false;
    bool faces_loaded = false;
    
    std::vector<std::string>split(const std::string &s, char delim) const;
    ModelLineType lineType(const std::string &line) const;
    std::vector<GLfloat>lineToVertex(const std::string &line) const;
    
public:
    ObjectLoader(void);
    ~ObjectLoader(void);
    std::vector<GLfloat>getVertices() const;
    std::vector<GLfloat>getNormals() const;
    std::vector<GLfloat>getTextureCoords() const;
    std::vector<GLfloat>getFaces() const;
    bool verticesLoaded() const;
    bool normalsLoaded() const;
    bool textureCoordsLoaded() const;
    bool facesLoaded() const;
    void load(const char *path);
    void pushVertex(std::vector<GLfloat> vertex);
};

#endif /* ObjectLoader_hpp */
