//
//  model.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "model.hpp"


Model::Model(Shader shader, Material material, glm::mat4 modelMatrix, Mesh mesh, int indicesLength): mesh(),shader("shaders/default_shader.vs", "shaders/default_shader.frag") {
    this->mesh = mesh;
    this->material = material;
    this->modelMatrix = modelMatrix;
    this->shader = shader;
    this->indicesLength = indicesLength;
}
void Model::setModelMatrix(glm::mat4 m) {
  modelMatrix = m;
}

void Model::render(glm::mat4 modelMatrix) {
  shader.use();
  shader.setMat4("model", modelMatrix);

  shader.setVec3("material.ambient", material.getAmbient());
  shader.setVec3("material.diffuse", material.getDiffuse());
  shader.setVec3("material.specular", material.getSpecular());
  shader.setFloat("material.shininess", material.getShininess());

  mesh.render(indicesLength);
}

void Model::render() {
  render(modelMatrix);
}

void Model::dispose() {
  mesh.dispose();
}
