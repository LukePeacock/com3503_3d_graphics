//
//  model.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "model.hpp"
#include <glm/gtx/string_cast.hpp>

Model::Model(Shader shader,glm::mat4 modelMatrix, float *vertices, unsigned int *indices, int verticesCount, int indicesCount, int verticesSize, int indicesSize, unsigned int diffuse) : shader("shaders/default_shader.vs", "shaders/default_shader.frag"){
   // this->mesh = mesh;
   // this->material = material;
    std::cout << "VC: " << verticesCount;
    std::cout << " VS: " << verticesSize;
    std::cout << " IC: " << indicesCount;
    std::cout << " IS: " << indicesSize << std::endl;
    this->shader = shader;
    this->mesh = Mesh(vertices, indices, verticesCount, indicesCount, verticesSize, indicesSize);
//    this->verticesCount = verticesCount;
//    this->indicesCount = indicesCount;
//    this->verticesSize = verticesSize;
//    this->indicesSize = indicesSize;
    this->modelMatrix = modelMatrix;
//    this->vertices = vertices;
//    this->indices = indices;
    this->diffuse = diffuse;
   // fillBuffers();
   // this->shader = shader;
}
void Model::setModelMatrix(glm::mat4 m) {
    modelMatrix = m;
}

void Model::render(glm::mat4 modelMatrix) {
   
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    shader.setMat4("model", modelMatrix);
    mesh.render();
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    //mesh.render(indicesLength);
}

void Model::render() {
    render(modelMatrix);
}

void Model::dispose() {
    mesh.dispose();
//    glDeleteBuffers(1, &VBO);
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &EBO);
    
}

//void Model::fillBuffers() {
//    std::cout << "fillBuffers()" << std::endl;
//    std::cout << "VC: " << verticesCount;
//    std::cout << " VS: " << verticesSize;
//    std::cout << " IC: " << indicesCount;
//    std::cout << " IS: " << indicesSize << std::endl;
//
//    std::cout << "V: " << vertices << std::endl;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indicesSize, indices, GL_STATIC_DRAW);
//
//    //coords
//    int offset = 0;
//    glVertexAttribPointer(0, vertexXYZFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)offset);
//    glEnableVertexAttribArray(0);
//    //normals
//    offset = vertexXYZFloats;
//    glVertexAttribPointer(1, vertexNormalFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
//    glEnableVertexAttribArray(1);
//    //textures
//    offset += vertexNormalFloats;
//    glVertexAttribPointer(2, vertexTexFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//
//}
