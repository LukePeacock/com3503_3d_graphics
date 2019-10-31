//
//  twoTriangles.hpp
//  Com3503
//
//  Created by Luke on 31/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef twoTriangles_hpp
#define twoTriangles_hpp

#include <stdio.h>

class TwoTriangles {
public:
    float vertices[32] = {   // position, colour, tex coords
         -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // top left
         -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // bottom left
          0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom right
          0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f   // top right
    };
    unsigned int indices[6] = {         // Note that we start from 0!
        0, 1, 2,
        0, 2, 3
    };
    float * getVertices();
    unsigned int * getIndices();
    int getVertexSize();
    int getIndicesSize();
    int getIndicesCount();
    
    
};
#endif /* twoTriangles_hpp */
