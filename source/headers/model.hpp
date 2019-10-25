//
//  model.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <mesh.hpp>
#include <material.hpp>
#include <shader.h>

class Model {
   
public:
    Model(glm::mat4 modelMatrix, float *vertices, unsigned int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize, unsigned int diffuse);
    void render(glm::mat4 modelMatrix, Shader shader, glm::mat4 projection, glm::mat4 view);
    void setModelMatrix(glm::mat4 m);
    void render(Shader shader, glm::mat4 projection, glm::mat4 view);
    void dispose();
private:
   // Mesh mesh;
   // Material material;
   // Shader shader;
    glm::mat4 modelMatrix;
    float * vertices;
    unsigned int * indices;
    int verticesCount;
    int indicesCount;
    int verticesSize;
    int indicesSize;
    void fillBuffers();
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    unsigned int diffuse;
    
};
#endif /* model_hpp */
