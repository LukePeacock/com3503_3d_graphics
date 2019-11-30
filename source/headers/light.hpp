//
//  light.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//  Updates for assignment also by Luke Peacock.
//

#ifndef light_hpp
#define light_hpp
#include <material.hpp>
#include <shader.h>
#include <stdio.h>
class Light{

private:
    Material material;
    glm::vec3 position;
    glm::mat4 model;
    Shader shader;

      
    int vertexStride = 3;
    int vertexXYZFloats = 3;
    
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    void fillBuffers();
    
public:
    Light(Shader shader);
    Light();
    void setPosition(glm::vec3 pos);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition();
    void setMaterial(Material m);
    Material getMaterial();
    void render();
    void dispose();
    glm::vec3 Front;
    float rotateAngle;

    void setFront(glm::vec3 front);
};

#endif /* light_hpp */
