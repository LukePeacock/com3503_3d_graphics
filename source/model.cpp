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
//    this->diffuse = diffuse;
//    this->ambient = ambient;
//    this->specular = specular;
//    this->shininess = shininess;
    this->diffusemap = diffusemap;
}
void Model::setModelMatrix(glm::mat4 m) {
    modelMatrix = m;
}

void Model::render(glm::mat4 modelMatrix) {
   
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffusemap);
    shader.setMat4("model", modelMatrix);
    
    shader.setVec3("material.ambient", material.getAmbient());
    shader.setVec3("material.diffuse", material.getDiffuse());
    shader.setVec3("material.specular", material.getSpecular());
    shader.setFloat("material.shininess", material.getShininess());
    mesh.render();
}

void Model::render() {
    render(modelMatrix);
}

void Model::dispose() {
    mesh.dispose();
}

