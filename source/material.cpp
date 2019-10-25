//
//  material.cpp
//  Com3503
//
//  Created by Luke on 25/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "material.hpp"

constexpr glm::vec3 Material::DEFAULT_AMBIENT;
constexpr glm::vec3 Material::DEFAULT_DIFFUSE;
constexpr glm::vec3 Material::DEFAULT_SPECULAR;
constexpr glm::vec3 Material::DEFAULT_EMISSION;
constexpr float Material::DEFAULT_SHININESS;

Material::Material() {
    ambient = DEFAULT_AMBIENT;
    diffuse = DEFAULT_DIFFUSE;
    specular = DEFAULT_SPECULAR;
    emission = DEFAULT_EMISSION;
    shininess = DEFAULT_SHININESS;
};

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  emission = glm::vec3(DEFAULT_EMISSION);
  this->shininess = shininess;
    
    
}

void Material::setAmbient(float red, float green, float blue) {
  ambient.x = red;
  ambient.y = green;
  ambient.z = blue;
}

void Material::setAmbient(glm::vec3 rgb) {
  setAmbient(rgb.x, rgb.y, rgb.z);
}

glm::vec3 Material::getAmbient() {
  return ambient;
}

void Material::setDiffuse(float red, float green, float blue) {
  diffuse.x = red;
  diffuse.y = green;
  diffuse.z = blue;
}

void Material::setDiffuse(glm::vec3 rgb) {
  setDiffuse(rgb.x, rgb.y, rgb.z);
}

glm::vec3 Material::getDiffuse() {
  return diffuse;
}

void Material::setSpecular(float red, float green, float blue) {
  specular.x = red;
  specular.y = green;
  specular.z = blue;
}

void Material::setSpecular(glm::vec3 rgb) {
  setSpecular(rgb.x, rgb.y, rgb.z);
}

glm::vec3 Material::getSpecular() {
    return specular;
}

void Material::setEmission(float red, float green, float blue) {
  emission.x = red;
  emission.y = green;
  emission.z = blue;
}
void Material::setEmission(glm::vec3 rgb) {
  setEmission(rgb.x, rgb.y, rgb.z);
}

glm::vec3 Material::getEmission() {
  return emission;
}

void Material::setShininess(float shininess) {
  this->shininess = shininess;
}

float Material::getShininess() {
  return shininess;
}
