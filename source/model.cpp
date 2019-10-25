//
//  model.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "model.hpp"
#include <glm/gtx/string_cast.hpp>

Model::Model(Shader shader,glm::mat4 modelMatrix, Mesh mesh, unsigned int diffuse) : shader("shaders/default_shader.vs", "shaders/default_shader.frag"), mesh(){
    this->shader = shader;
    this->mesh = mesh;
    this->modelMatrix = modelMatrix;
    this->diffuse = diffuse;
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
}

void Model::render() {
    render(modelMatrix);
}

void Model::dispose() {
    mesh.dispose();
}

