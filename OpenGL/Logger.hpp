//
//  Logger.hpp
//  OpenGL
//
//  Created by Matt Finucane on 06/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

class Logger {
public:
    Logger();
    ~Logger();
    void write(const char *message, ...);
};

#endif /* Logger_hpp */
