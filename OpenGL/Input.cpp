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
    reset();
}

Input::~Input() {}

Input::Input(Input const&) {}

void Input::operator=(Input const&) {}

void Input::mouseButtonCallbackFunction(GLFWwindow *window, int button, int action, int mods) {
    downed.px = current.px;
    downed.py = current.py;
    buttonCallback(10);
}

void Input::mousePositionCallbackFunction(GLFWwindow *window, double x_pos, double y_pos) {
    current.px = (float)x_pos;
    current.py = (float)y_pos;
}

void Input::keyInputCallbackFunction(GLFWwindow *window, int key, int scancode, int action, int mods) {
    cout << "Key callback function: " << key << ", " << scancode << ", " << action << ", " << mods << endl;
}

void Input::reset() {
    primary_down = false;
    secondary_down = false;
    downed.px = 0.0f;
    downed.py = 0.0f;
    distance = 0.0f;
    distance_x = 0.0f;
    distance_y = 0.0f;
    direction_x = NONE;
    direction_y = NONE;
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
    if(x2_mn_x1 < 0) direction_x = WEST;
    else if(x2_mn_x1 > 0) direction_x = EAST;
    else direction_x = NONE;
    
    if(y2_mn_y1 < 0) direction_y = NORTH;
    else if(y2_mn_y1 > 0) direction_y = SOUTH;
    else direction_y = NONE;
}

string Input::distanceAndDirection(void) const {
    
    ostringstream oss;
    oss << " distance: " << distance;
    oss << " distance x: " << distance_x;
    oss << " distance y: " << distance_y;
    
    switch(direction_x) {
        case EAST: {
            oss << " - East";
            break;
        }
        case WEST: {
            oss << " - West";
            break;
        }
        default: {
            oss << " - None";
            break;
        }
    }
    switch(direction_y) {
        case NORTH: {
            oss << " - North";
            break;
        }
        case SOUTH: {
            oss << " - South";
            break;
        }
        default: {
            oss << " - None";
            break;
        }
    }
    return oss.str();
}
