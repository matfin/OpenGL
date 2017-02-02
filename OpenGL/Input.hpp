//
//  Mouse.hpp
//  OpenGL
//
//  Created by Matt Finucane on 01/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "Structs.h"

enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST,
    NONE
};

class Input {
    
private:
    /**
     *  These prevent direct instantiation and copying.
     */
    Input(void);
    Input(Input const&);
    ~Input();
    void operator=(Input const&);
    
    /**
     *  Member variables
     */
    bool primary_down = false;
    bool secondary_down = false;
    Position current;
    Position downed;
    float distance;
    float distance_x;
    float distance_y;
    Direction direction_x;
    Direction direction_y;
    
    /**
     *  Callback functions
     */
    std::function<void(int)> buttonCallback;
    
public:
    
    static Input &getInstance() {
        static Input instance;
        return instance;
    }
    
    void addMouseButtonHandler(std::function<void(int)> callback) {
        buttonCallback = callback;
    }
    
    static void mousePositionCallback(GLFWwindow *window, double x_pos, double y_pos) {
        getInstance().mousePositionCallbackFunction(window, x_pos, y_pos);
    }
    
    static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        getInstance().mouseButtonCallbackFunction(window, button, action, mods);
    }
    
    static void keyInputCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        getInstance().keyInputCallbackFunction(window, key, scancode, action, mods);
    }
    
    void mouseButtonCallbackFunction(GLFWwindow *window, int button, int action, int mods);
    void mousePositionCallbackFunction(GLFWwindow *window, double x_pos, double y_pos);
    void keyInputCallbackFunction(GLFWwindow *window, int key, int scancode, int action, int mods);
    
    void reset(void);
    void updateDistanceAndDirection(void);
    std::string distanceAndDirection(void) const;
};

#endif /* Input_hpp */
