//
//  model.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
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
    // Constructors
    Model(); // default for use in implicit definitions NOT explicit ones!
    Model(Shader shader, Material mat, glm::mat4 modelMatrix, Mesh mesh, unsigned int diffusemap);
    Model(Shader shader, Material mat, glm::mat4 modelMatrix, Mesh mesh, unsigned int diffusemap, unsigned int specularmap);
    
    void render(glm::mat4 modelMatrix, glm::vec2 texOffset = glm::vec2(0.0f));
    void setModelMatrix(glm::mat4 m);
    void render(glm::vec2 texOffset = glm::vec2(0.0f));
    void dispose();
private:
    Mesh mesh;
    Material material;
    Shader shader;
    glm::mat4 modelMatrix;
    unsigned int diffusemap;
    unsigned int specularmap;
};
#endif /* model_hpp */
