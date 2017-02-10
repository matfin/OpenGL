//
//  QuaternionDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 10/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef QuaternionDemo_hpp
#define QuaternionDemo_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class QuaternionDemo {

private:
    GLuint program;
    GLFWwindow *window;
    GLenum drawing_method;
    
    void prepareMeshes(void);
    void drawLoop(void);
    int start(void);

public:
    QuaternionDemo();
    ~QuaternionDemo();
    
    static QuaternionDemo &getInstance() {
        static QuaternionDemo instance;
        return instance;
    }
    
    static int run(void);
};

#endif /* QuaternionDemo_hpp */
