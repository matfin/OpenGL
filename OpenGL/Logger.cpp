//
//  Logger.cpp
//  OpenGL
//
//  Created by Matt Finucane on 06/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "Logger.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdarg.h>
#include <cstdio>
#include <fstream>

using namespace std;

Logger::Logger(){};
Logger::~Logger(){};


void Logger::write(const char *message, ...) {
    
    /**
     *  Use this to create a path name based on 
     *  the time and the date.
     */
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y");
    auto str = oss.str();
    auto path = "/Users/matfin/OpenGL/" + str + ".log";
    
    /**
     *  Create the log file for writing and appending
     */
    try {
        
        FILE *file = fopen(path.c_str(), "a");
        
        if(file) {
            va_list argptr;
            va_start(argptr, message);
            vfprintf(file, message, argptr);
            va_end(argptr);
            fclose(file);
        }
        else {
            throw runtime_error("Could not open file for writing: " + path);
        }
    }
    catch(exception &e) {
        cout << e.what() << endl;
    }
}


