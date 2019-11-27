//
//  cube.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#include <cube.hpp>

float * Cube::GetVertices(){
    return vertices;
}

unsigned int * Cube::GetIndices(){
    return indices;
}

int Cube::GetVertexSize(){
    return sizeof(vertices);
}

int Cube::GetIndicesSize(){
    return sizeof(indices);
}

int Cube::GetIndicesCount(){
    return sizeof(indices)/sizeof(indices[0]);
}

int Cube::GetVerticesCount(){
    return sizeof(vertices)/sizeof(vertices[0]);
}
