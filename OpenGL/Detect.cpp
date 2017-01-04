//
//  Detect.cpp
//  OpenGL
//
//  Created by Matt Finucane on 04/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Detect.hpp"

using namespace std;

auto OpenGLDetect(void) -> int {
    if(!glfwInit()) {
        cout << "Unable to initialise GLFW3." << endl;
        return -1;
    }
    return 1;
};

