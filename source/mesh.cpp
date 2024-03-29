//
//  mesh.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#include "mesh.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(){
}

Mesh::Mesh(float *vertices, unsigned int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize) {
   // this->vertices.resize(verticesCount);
   // this->indices.resize(indicesCount);
    this->verticesCount = verticesCount;
    this->indicesCount = indicesCount;
    this->verticesSize = verticesSize;
    this->indicesSize = indicesSize;
    this->vertices = vertices;
    this->indices = indices;
    fillBuffers();
}

void Mesh::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

void Mesh::fillBuffers() {
      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);
      
      glBindVertexArray(VAO);
    
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, indices, GL_STATIC_DRAW);
    
      //coords
      int offset = 0;
      glVertexAttribPointer(0, vertexXYZFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
      glEnableVertexAttribArray(0);
      //normals
      offset = vertexXYZFloats;
      glVertexAttribPointer(1, vertexNormalFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
      glEnableVertexAttribArray(1);
      //textures
      offset += vertexNormalFloats;
      glVertexAttribPointer(2, vertexTexFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
      glEnableVertexAttribArray(2);
    
}

void Mesh::dispose() {
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &EBO);
}
