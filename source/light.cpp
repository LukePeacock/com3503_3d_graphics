//
//  light.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "light.hpp"
#include <glm/gtx/string_cast.hpp>
float vertices[] = {  // x,y,z
    -0.5f, -0.5f, -0.5f,  // 0
    -0.5f, -0.5f,  0.5f,  // 1
    -0.5f,  0.5f, -0.5f,  // 2
    -0.5f,  0.5f,  0.5f,  // 3
     0.5f, -0.5f, -0.5f,  // 4
     0.5f, -0.5f,  0.5f,  // 5
     0.5f,  0.5f, -0.5f,  // 6
     0.5f,  0.5f,  0.5f   // 7
};
  
int indices[] =  {
    0,1,3, // x -ve
    3,2,0, // x -ve
    4,6,7, // x +ve
    7,5,4, // x +ve
    1,5,7, // z +ve
    7,3,1, // z +ve
    6,4,0, // z -ve
    0,2,6, // z -ve
    0,4,5, // y -ve
    5,1,0, // y -ve
    2,3,7, // y +ve
    7,6,2  // y +ve
  };

Light::Light(Shader shader) : shader("shaders/light_shader.vs", "shaders/light_shader.frag"){
    this->material = Material();
    this->shader = shader;
    this->rotateAngle = 0.0f;
    material.setAmbient(0.5f, 0.5f, 0.5f);
    material.setDiffuse(0.8f, 0.8f, 0.8f);
    material.setSpecular(0.8f, 0.8f, 0.8f);
    position = glm::vec3(0.0f,0.0f,0.0f);
    this->model = glm::mat4(1.0f);
    fillBuffers();
}

void Light::setPosition(glm::vec3 pos) {
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

void Light::setPosition(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

glm::vec3 Light::getPosition() {
    return position;
}

void Light::setMaterial(Material m) {
    material = m;
}

Material Light::getMaterial() {
    return material;
}

void Light::render() {
    glm::mat4 nmodel = glm::scale(model, glm::vec3(0.3f,0.3f,0.3f));
    nmodel = glm::translate(nmodel, position);
    nmodel = glm::rotate(nmodel, glm::radians(rotateAngle), glm::vec3(0,1,0));
    shader.use();
    shader.setMat4("model", nmodel);
    glBindVertexArray(VAO);
    int indexcount =sizeof(indices)/sizeof(indices[0]);
    glDrawElements(GL_TRIANGLES, indexcount, GL_UNSIGNED_INT, 0);
}

void Light::dispose() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}


void Light::fillBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
      
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, vertexXYZFloats, GL_FLOAT, GL_FALSE, vertexStride*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
}

void Light::setFront(glm::vec3 front){
    this->Front = front;
}


