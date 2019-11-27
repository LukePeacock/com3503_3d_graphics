//
//  material.hpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//
//  Based on Dr. Steve Maddock's Tutorials, updated from Java to C++ by Luke Peacock.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
class Material{
 
public:
    constexpr static glm::vec3 DEFAULT_AMBIENT = glm::vec3(0.2f, 0.2f, 0.2f);
    constexpr static glm::vec3 DEFAULT_DIFFUSE = glm::vec3(0.8f, 0.8f, 0.8f);
    constexpr static glm::vec3 DEFAULT_SPECULAR = glm::vec3(0.5f, 0.5f, 0.5f);
    constexpr static glm::vec3 DEFAULT_EMISSION = glm::vec3(0.0f, 0.0f, 0.0f);
    constexpr static float DEFAULT_SHININESS = 32;
 
    Material();
    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    void setAmbient(float red, float green, float blue);
    void setAmbient(glm::vec3 rgb);
    glm::vec3 getAmbient();
    void setDiffuse(float red, float green, float blue);
    void setDiffuse(glm::vec3 rgb);
    glm::vec3 getDiffuse();
    void setSpecular(float red, float green, float blue);
    void setSpecular(glm::vec3 rgb);
    glm::vec3 getSpecular();
    void setEmission(float red, float green, float blue);
    void setEmission(glm::vec3 rgb);
    glm::vec3 getEmission();
    void setShininess(float shininess);
    float getShininess();
    
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float shininess;
};
#endif /* material_hpp */
