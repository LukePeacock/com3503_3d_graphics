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
    Mesh(float *vertices, int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize);
    void render(int indicesLength);
    void fillBuffers(float *vertices, int verticesSize, int *indices, int indicesSize);
    void dispose();
private:
    int vertexStride = 8;
    int vertexXYZFloats = 3;
    int vertexNormalFloats = 3;
    int vertexTexFloats = 2;
    unsigned int vertexBufferId;
    unsigned int vertexArrayId;
    unsigned int elementBufferId;
    std::vector<float> vertices;  //Flexible array members initialised as 1
    std::vector<int> indices;     // More memory is allocated when they are used
    
};


#endif /* mesh_hpp */
