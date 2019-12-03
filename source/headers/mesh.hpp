//
//  mesh.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#ifndef mesh_hpp
#define mesh_hpp


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
