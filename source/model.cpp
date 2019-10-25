//
//  model.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "model.hpp"
#include <glm/gtx/string_cast.hpp>

Model::Model(glm::mat4 modelMatrix, float *vertices, unsigned int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize, unsigned int diffuse){
   // this->mesh = mesh;
   // this->material = material;
    std::cout << "VC: " << verticesCount;
    std::cout << " VS: " << verticesSize;
    std::cout << " IC: " << indicesCount;
    std::cout << " IS: " << indicesSize << std::endl;
    this->verticesCount = verticesCount;
    this->indicesCount = indicesCount;
    this->verticesSize = verticesSize;
    this->indicesSize = indicesSize;
    this->modelMatrix = modelMatrix;
    this->vertices = vertices;
    this->indices = indices;
    this->diffuse = diffuse;
    fillBuffers();
   // this->shader = shader;
}
void Model::setModelMatrix(glm::mat4 m) {
    modelMatrix = m;
}

void Model::render(glm::mat4 modelMatrix, Shader shader) {
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse);
    
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", modelMatrix);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
//  shader.setVec3("material.ambient", material.getAmbient());
//  shader.setVec3("material.diffuse", material.getDiffuse());
//  shader.setVec3("material.specular", material.getSpecular());
//  shader.setFloat("material.shininess", material.getShininess());

    
    //mesh.render(indicesLength);
}

void Model::render(Shader shader) {
    render(modelMatrix, shader);
}

void Model::dispose() {
    //mesh.dispose();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    
}

void Model::fillBuffers() {
    std::cout << "fillBuffers()" << std::endl;
    std::cout << "VC: " << verticesCount;
    std::cout << " VS: " << verticesSize;
    std::cout << " IC: " << indicesCount;
    std::cout << " IS: " << indicesSize << std::endl;
    
    std::cout << "V: " << vertices << std::endl;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, indices, GL_STATIC_DRAW);
    
    //coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    //textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
  
    
   
}
