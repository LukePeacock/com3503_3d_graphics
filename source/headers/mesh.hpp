//
//  mesh.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <vector>
class Mesh{
    
public:
    Mesh();
    Mesh(float *vertices, unsigned int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize);
    void render();
    void dispose();
    
private:
    int verticesCount;
    int indicesCount;
    int verticesSize;
    int indicesSize;
    void fillBuffers();
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int vertexStride = 8;
    int vertexXYZFloats = 3;
    int vertexNormalFloats = 3;
    int vertexTexFloats = 2;
    float * vertices;
    unsigned int * indices;
    
};


#endif /* mesh_hpp */
