//
//  twoTriangles.cpp
//  Com3503
//
//  Created by Luke on 31/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//  I declare that this code is my own work
//  lpeacock1@sheffield.ac.uk
//

#include "twoTriangles.hpp"

float * TwoTriangles::getVertices(){
    return vertices;
}

unsigned int * TwoTriangles::getIndices(){
    return indices;
}

int TwoTriangles::getVertexSize(){
    return sizeof(vertices);
};

int TwoTriangles::getIndicesSize(){
    return sizeof(indices);
}

int TwoTriangles::getIndicesCount(){
    return sizeof(indices)/sizeof(indices[0]);
}

