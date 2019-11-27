//
//  sphere.hpp
//  Com3503
//
//  Created by Luke on 31/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>

class Sphere{
    
public:
    Sphere();
    float * GetVertices();
    unsigned int * GetIndices();
    int getVertexSize();
    int getIndicesSize();
    int getIndicesCount();
    float vertices[7200];
    unsigned int indices[5046];
    
private:
    const static int XLONG = 30;
    const static int YLAT = 30;
    void createVertices();
    void createIndices();
    
    
};

#endif /* sphere_hpp */
