//
//  model.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "model.hpp"
#include <glm/gtx/string_cast.hpp>

// default constructor - only used to instantiation errors with scene graph
Model::Model(): shader("shaders/default_shader.vs", "shaders/default_shader.frag"), mesh()
{
}


Model::Model(Shader shader,Material mat,glm::mat4 modelMatrix, Mesh mesh, unsigned int diffusemap) : shader("shaders/default_shader.vs", "shaders/default_shader.frag"), mesh(){
    this->shader = shader;
    this->mesh = mesh;
    this->material = mat;
    this->modelMatrix = modelMatrix;
    this->diffusemap = diffusemap;
}

Model::Model(Shader shader,Material mat,glm::mat4 modelMatrix, Mesh mesh, unsigned int diffusemap, unsigned int specularmap) : shader("shaders/default_shader.vs", "shaders/default_shader.frag"), mesh(){
    this->shader = shader;
    this->mesh = mesh;
    this->material = mat;
    this->modelMatrix = modelMatrix;
    this->diffusemap = diffusemap;
    this->specularmap = specularmap;
}

void Model::setModelMatrix(glm::mat4 m) {
    modelMatrix = m;
}

void Model::render(glm::mat4 modelMatrix, glm::vec2 texOffset) {
   
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffusemap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularmap);
    shader.setMat4("model", modelMatrix);
    shader.setVec2("offset", texOffset);
    shader.setVec3("material.ambient", material.getAmbient());
    shader.setVec3("material.diffuse", material.getDiffuse());
    shader.setVec3("material.specular", material.getSpecular());
    shader.setFloat("material.shininess", material.getShininess());
    mesh.render();
     shader.setVec2("offset", glm::vec2(0.0f));
}

void Model::render(glm::vec2 texOffset) {
    render(modelMatrix, texOffset);
}

void Model::dispose() {
    mesh.dispose();
}

