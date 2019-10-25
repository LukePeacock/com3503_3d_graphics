//
//  mesh.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "mesh.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(){
}
Mesh::Mesh(float *vertices, int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize) {
   // this->vertices.resize(verticesCount);
   // this->indices.resize(indicesCount);
    this->vertices.assign(vertices, vertices + verticesCount);
    this->indices.assign(indices, indices + indicesCount);
    fillBuffers(vertices, verticesSize, indices, indicesSize);
}

void Mesh::render(int indicesLength) {
    glBindVertexArray(vertexArrayId);
    glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::fillBuffers(float *vertices, int verticesSize, int *indices, int indicesSize) {
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    
    glBufferData(GL_ARRAY_BUFFER, verticesSize, &vertices, GL_STATIC_DRAW);
  
    int stride = vertexStride;
    int numXYZFloats = vertexXYZFloats;
    int offset = 0;
    glVertexAttribPointer(0, numXYZFloats, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)offset);
    glEnableVertexAttribArray(0);

    int numNormalFloats = vertexNormalFloats; // x,y,z for each vertex
    offset = numXYZFloats*sizeof(float);  // the normal values are three floats after the three x,y,z values
                                  // so change the offset value
    glVertexAttribPointer(1, numNormalFloats, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)offset);
                                  // the vertex shader uses location 1 (sometimes called index 1)
                                  // for the normal information
                                  // location, size, type, normalize, stride, offset
                                  // offset is relative to the start of the array of data
    glEnableVertexAttribArray(1);// Enable the vertex attribute array at location 1

    // now do the texture coordinates  in vertex attribute 2
    int numTexFloats = vertexTexFloats;
    offset = (numXYZFloats+numNormalFloats)*sizeof(float);
    glVertexAttribPointer(2, numTexFloats, GL_FLOAT, GL_FALSE, stride*sizeof(float), (void*)offset);
    glEnableVertexAttribArray(2);
  
    glGenBuffers(1, &elementBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, &indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Mesh::dispose() {
  glDeleteBuffers(1, &vertexBufferId);
  glDeleteVertexArrays(1, &vertexArrayId);
  glDeleteBuffers(1, &elementBufferId);
}
