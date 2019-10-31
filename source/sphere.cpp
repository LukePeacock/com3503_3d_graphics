//
//  sphere.cpp
//  Com3503
//
//  Created by Luke on 31/10/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sphere::Sphere(){
    createVertices();
    createIndices();
}


float * Sphere::GetVertices(){
    return vertices;
}

unsigned int * Sphere::GetIndices(){
    return indices;
}

int Sphere::getVertexSize(){
    return sizeof(vertices);
}

int Sphere::getIndicesSize(){
    return sizeof(indices);
}

int Sphere::getIndicesCount(){
    return sizeof(indices)/sizeof(indices[0]);
}

void Sphere::createVertices(){
    double r = 0.5;
    int step = 8;
    //float[]
    for (int j = 0; j<YLAT; ++j) {
      double b = glm::radians(-90+180*(double)(j)/(YLAT-1));
      for (int i = 0; i<XLONG; ++i) {
        double a = glm::radians(360*(double)(i)/(XLONG-1));
        double z = glm::cos(b) * glm::cos(a);
        double x = glm::cos(b) * glm::sin(a);
        double y = glm::sin(b);
        int base = j*XLONG*step;
        vertices[base + i*step+0] = (float)(r*x);
        vertices[base + i*step+1] = (float)(r*y);
        vertices[base + i*step+2] = (float)(r*z);
        vertices[base + i*step+3] = (float)x;
        vertices[base + i*step+4] = (float)y;
        vertices[base + i*step+5] = (float)z;
        vertices[base + i*step+6] = (float)(i)/(float)(XLONG-1);
        vertices[base + i*step+7] = (float)(j)/(float)(YLAT-1);
      }
    }
}

void Sphere::createIndices(){
    for (int j = 0; j<YLAT-1; ++j) {
      for (int i = 0; i<XLONG-1; ++i) {
        int base = j*(XLONG-1)*6;
        indices[base + i*6+0] = j*XLONG+i;
        indices[base + i*6+1] = j*XLONG+i+1;
        indices[base + i*6+2] = (j+1)*XLONG+i+1;
        indices[base + i*6+3] = j*XLONG+i;
        indices[base + i*6+4] = (j+1)*XLONG+i+1;
        indices[base + i*6+5] = (j+1)*XLONG+i;
      }
    }
}


