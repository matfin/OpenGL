//
//  QuaternionDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 10/02/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "QuaternionDemo.hpp"
#include <iostream>
#include <string>

using namespace std;

QuaternionDemo::QuaternionDemo() {
    cout << "Construct: QuaternionDemo." << endl;
}

QuaternionDemo::~QuaternionDemo() {
    cout << "Destruct: QuaternionDemo." << endl;
}

void QuaternionDemo::prepareMeshes(void) {
    
}

void QuaternionDemo::drawLoop(void) {
    
}

int QuaternionDemo::start() {
    cout << "Starting the Quaternion Demo!!" << endl;
    return 0;
}

int QuaternionDemo::run() {
    return getInstance().start();
}
