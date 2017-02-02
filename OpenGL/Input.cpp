//
//  Input.cpp
//  OpenGL
//
//  Created by Matt Finucane on 01/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Input.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

Input::Input(void) {
    mouseDown = nullptr;
    mouseUp = nullptr;
    mouseMove = nullptr;
    mouseDrag = nullptr;
    keyDown = nullptr;
    keyStrobe = nullptr;
    keyUp = nullptr;
    reset();
}

Input::~Input() {}

Input::Input(Input const&) {}

void Input::operator=(Input const&) {}

void Input::mouseButtonCallback(int button, int action, int mods) {
    /**
     *  Mouse click
     */
    if(action == 1) {
        downed = current;
        held = true;
        if(mouseDown != nullptr) {
            mouseDown(button, action, mods);
        }
    }
    /**
     *  Mouse release
     */
    else {
        reset();
        if(mouseUp != nullptr) {
            mouseUp(button, action, mods);
        }
    }
}

void Input::mouseMoveCallback(double x_pos, double y_pos) {
    /**
     *  Always update the current position of the mouse.
     */
    current.px = (float)x_pos;
    current.py = (float)y_pos;
    
    if(mouseMove != nullptr) {
        mouseMove(current.px, current.py);
    }
    
    if(held && mouseDrag != nullptr) {
        updateDistanceAndDirection();
        mouseDrag(current.px, current.py, distance_x, distance_y, direction);
    }
}

void Input::keyCallback(int key, int scancode, int action, int mods) {
    switch(action) {
        case 0: {
            if(keyUp != nullptr) {
                keyUp(key, scancode, action, mods);
            }
            break;
        }
        case 1: {
            if(keyDown != nullptr) {
                keyDown(key, scancode, action, mods);
            }
            break;
        }
        case 2: {
            if(keyStrobe != nullptr) {
                keyStrobe(key, scancode, action, mods);
            }
            break;
        }
    }
}

void Input::reset() {
    downed.px = 0.0f;
    downed.py = 0.0f;
    held = false;
    distance = 0.0f;
    distance_x = 0.0f;
    distance_y = 0.0f;
    direction = NONE;
}

void Input::updateDistanceAndDirection(void) {
    /**
     *  Distance calculation formula.
     */
    float x2_mn_x1 = (current.px - downed.px);
    float y2_mn_y1 = (current.py - downed.py);
    float sqr_x = x2_mn_x1 * x2_mn_x1;
    float sqr_y = y2_mn_y1 * y2_mn_y1;
    
    distance = sqrtf(sqr_x + sqr_y);
    distance_x = abs(x2_mn_x1);
    distance_y = abs(y2_mn_y1);
    
    /**
     *  Direction
     */
//    if(x2_mn_x1 < 0) direction_x = WEST;
//    else if(x2_mn_x1 > 0) direction_x = EAST;
//    else direction_x = NONE;
//    
//    if(y2_mn_y1 < 0) direction_y = NORTH;
//    else if(y2_mn_y1 > 0) direction_y = SOUTH;
//    else direction_y = NONE;
}
