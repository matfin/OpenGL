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
    ShaderLoader();
    ~ShaderLoader();
    std::string load(const char *path) const;
};

#endif /* ShaderLoader_hpp */
