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
    Model(Shader shader, Material material, glm::mat4 modelMatrix, Mesh mesh, int indicesLength);
    void render(glm::mat4 modelMatrix);
    void setModelMatrix(glm::mat4 m);
    void render();
    void dispose();
private:
    Mesh mesh;
    Material material;
    Shader shader;
    glm::mat4 modelMatrix;
    int indicesLength;
    
};
#endif /* model_hpp */
