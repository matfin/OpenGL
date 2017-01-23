//
//  Enumerations.h
//  OpenGL
//
//  Created by Matt Finucane on 20/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef Enumerations_h
#define Enumerations_h

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum ScaleMag {
    LARGER,
    SMALLER
};

enum ModelLineType {
    VERTEX,
    NORMAL,
    TEXTURE_COORDINATE,
    FACE,
    UNKNOWN
};

#endif /* Enumerations_h */
