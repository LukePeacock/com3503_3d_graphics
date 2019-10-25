//
//  cube.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
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
