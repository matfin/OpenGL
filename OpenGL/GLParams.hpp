//
//  GLParams.hpp
//  OpenGL
//
//  Created by Matt Finucane on 07/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef GLParams_hpp
#define GLParams_hpp

#include <vector>
#include <string>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class GLParams {
public:
    std::vector<std::string> getGLParams() const;
    void logGLParams(std::vector<std::string> params) const;
    void updateWindowFPSCounter(GLFWwindow *window);
};

#endif /* GLParams_hpp */
