//
//  ShaderLoader.hpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp

#include <iostream>
#include <string>
#include <fstream>

class ShaderLoader {
public:
    static std::string load(const char *path);
};

#endif /* ShaderLoader_hpp */
