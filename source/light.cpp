//
//  light.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "light.hpp"

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

Light::Light(): shader("shaders/light_shader.vs", "shaders/light_shader.frag"){
  this->material = Material();
  material.setAmbient(0.5f, 0.5f, 0.5f);
  material.setDiffuse(0.8f, 0.8f, 0.8f);
  material.setSpecular(0.8f, 0.8f, 0.8f);
  position = glm::vec3(3.0f,2.0f,1.0f);
  model = glm::mat4(1);
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

void Light::render(glm::mat4 view, glm::mat4 projection) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.3f,0.3f,0.3f));
    model = glm::translate(model, position);
  
  
    shader.use();
    shader.setMat4("view",view);
    shader.setMat4("projection", projection);
    shader.setMat4("model", model);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    int offset = 0;
    glVertexAttribPointer(0, vertexXYZFloats, GL_FLOAT, false, vertexStride*sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(0);
   
  
   
}