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
    Model();
    Model(Shader shader, Material mat, glm::mat4 modelMatrix, Mesh mesh, unsigned int diffusemap);
    void render(glm::mat4 modelMatrix);
    void setModelMatrix(glm::mat4 m);
    void render();
    void dispose();
private:
    Mesh mesh;
    Material material;
    Shader shader;
    glm::mat4 modelMatrix;
    unsigned int diffusemap;
};
#endif /* model_hpp */
