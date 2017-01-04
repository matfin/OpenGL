//
//  ShaderLoader.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "ShaderLoader.hpp"

using namespace std;

ShaderLoader::ShaderLoader(){};
ShaderLoader::~ShaderLoader(){};

string ShaderLoader::load(const char *path) const {
    string content, line = "";
    ifstream fileStream(path, ios::in);
    
    try {
        if(!fileStream.is_open()) {
            throw runtime_error("File not found.");
        }
        while(!fileStream.eof()) {
            getline(fileStream, line);
            content.append(line + "\n");
        }
    }
    catch(exception &e) {
        cerr << e.what() << ": " << path << endl;
    }
    
    fileStream.close();
    return content;
}
