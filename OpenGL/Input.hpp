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
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST,
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
    Position current;
    Position downed;
    bool held;
    float distance;
    float distance_x;
    float distance_y;
    Direction direction;
    
    /**
     *  Callback functions
     */
    std::function<void(int, int, int)> mouseDown;
    std::function<void(int, int, int)> mouseUp;
    std::function<void(float, float)> mouseMove;
    std::function<void(float, float, float, float, Direction)> mouseDrag;
    std::function<void(int, int, int, int)> keyDown;
    std::function<void(int, int, int, int)> keyStrobe;
    std::function<void(int, int, int, int)> keyUp;
    
public:
    
    /**
     *  This uses the singleton pattern
     *  to return a static instance of 
     *  an Input.
     */
    static Input &getInstance() {
        static Input instance;
        return instance;
    }
    
    /**
     *  These will set the member parameters.
     */
    void updateDistanceAndDirection(void);
    void reset(void);
    
    /**
     *  Assigning an std::function callback for the mouse 
     *  button press.
     */
    void onMouseDown(std::function<void(int, int, int)> cb) {
        mouseDown = cb;
    };
    
    /**
     *  Assigning an std::function callback for the mouse
     *  button release.
     */
    void onMouseUp(std::function<void(int, int, int)> cb) {
        mouseUp = cb;
    };
    
    /**
     *  Assigning an std::function callback for mouse movement.
     */
    void onMouseMove(std::function<void(float, float)> cb) {
        mouseMove = cb;
    }
    
    /**
     *  Assigning an std::function callback for mouse 
     *  button down and movement.
     */
    void onMouseDrag(std::function<void(float, float, float, float, Direction)> cb) {
        mouseDrag = cb;
    }
    
    /**
     *  Assigning an std::function callback for keyboard key press.
     */
    void onKeyDown(std::function<void(int, int, int, int)> cb) {
        keyDown = cb;
    }
    
    /**
     *  Assigning an std::function callback for keyboard key strobe.
     */
    void onKeyStrobe(std::function<void(int, int, int, int)> cb) {
        keyStrobe = cb;
    }
    
    /**
     *  Assigning an std::function callback for keyboard key release.
     */
    void onKeyUp(std::function<void(int, int, int, int)> cb) {
        keyUp = cb;
    }
    
    /**
     *  Static function passed in to GLFW and called when a mouse button is pressed/released.
     */
    static void glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        getInstance().mouseButtonCallback(button, action, mods);
    }
    
    /**
     *  Static function passed in to GLFW and called when the mouse is moved.
     */
    static void glfwMouseMoveCallback(GLFWwindow *window, double x_pos, double y_pos) {
        getInstance().mouseMoveCallback(x_pos, y_pos);
    }
    
    /**
     *  Static function passed in to GLFW and called on keyboard key press/release.
     */
    static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        getInstance().keyCallback(key, scancode, action, mods);
    }
    
    /**
     *  Member functions of the instance of the class. 
     *
     *  These will fire the std::function callbacks.
     */
    void mouseButtonCallback(int button, int action, int mods);
    void mouseMoveCallback(double x_pos, double y_pos);
    void keyCallback(int key, int scancode, int action, int mods);
};

#endif /* Input_hpp */
