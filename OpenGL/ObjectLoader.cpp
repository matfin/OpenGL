//
//  ObjectLoader.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "ObjectLoader.hpp"

using namespace std;

ObjectLoader::ObjectLoader(void) {
    cout << "Construct: ObjectLoader" << endl;
}

ObjectLoader::~ObjectLoader(void) {
    cout << "Destruct: ObjectLoader" << endl;
    vertices.clear();
    normals.clear();
    texture_coords.clear();
    faces.clear();
}

vector<GLfloat> ObjectLoader::getVertices() const {
    return vertices;
}

vector<GLfloat> ObjectLoader::getNormals() const {
    return normals;
}

vector<GLfloat> ObjectLoader::getTextureCoords() const {
    return texture_coords;
}

vector<GLfloat> ObjectLoader::getFaces() const {
    return faces;
}

bool ObjectLoader::verticesLoaded() const {
    return vertices_loaded;
}

bool ObjectLoader::normalsLoaded() const {
    return normals_loaded;
}

bool ObjectLoader::facesLoaded() const {
    return faces_loaded;
}

vector<string> ObjectLoader::split(const string &s, char delim) const {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while(getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

ModelLineType ObjectLoader::lineType(const string &line) const {
    string face = "f";
    string vertex = "v";
    string normal = "vn";
    string texture = "vt";
    
    if(line.compare(0, normal.length(), normal) == 0) {
        return NORMAL;
    }
    else if(line.compare(0, texture.length(), texture) == 0) {
        return TEXTURE_COORDINATE;
    }
    else if(line.compare(0, face.length(), face) == 0) {
        return FACE;
    }
    else if(line.compare(0, vertex.length(), vertex) == 0) {
        return VERTEX;
    }
    else return UNKNOWN;
}

vector<GLfloat> ObjectLoader::lineToVertex(const string &line) const {
    vector<GLfloat> points(3);
    vector<string> tokens = split(line, ' ');
    if(tokens.size() != 4) {
        throw runtime_error("Not enough coordinates in line to create a vertex: " + line);
    }
    else {
        transform(begin(tokens) + 1, end(tokens), begin(points), [](string coordinate) {
            return stof(coordinate);
        });
    }
    return points;
}

void ObjectLoader::load(const char *path) {
    string line = "";
    ifstream fileStream(path, ios::in);
    
    try {
        if(!fileStream.is_open()) {
            string error = "File not found: ";
            error.append(path);
            throw runtime_error(error);
        }
        while(!fileStream.eof()) {
            getline(fileStream, line);
            ModelLineType line_type =  lineType(line);
            
            switch (line_type) {
                case FACE: {
                    break;
                }
                case VERTEX: {
                    vector<GLfloat> vertex_coords = lineToVertex(line);
                    pushVertex(vertex_coords);
                    break;
                }
                case NORMAL: {
                    break;
                }
                case TEXTURE_COORDINATE: {
                    break;
                }
                default: {
                    cout << "This is none of the above." << endl;
                }
            }
        }
    }
    catch(exception &e) {
        cerr << e.what() << endl;
    }
    
    fileStream.close();
}

void ObjectLoader::pushVertex(const vector<GLfloat> vertex) {
    vertices.insert(end(vertices), begin(vertex), end(vertex));
}
