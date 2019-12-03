//
//  lightpost.hpp
//  Com3503
//
//  Created by Luke on 30/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//  I declare that this code is my own work
//  lpeacock1@sheffield.ac.uk
//

#ifndef lightpost_hpp
#define lightpost_hpp

#include <stdio.h>
#include <nameNode.hpp>
#include <model.hpp>
#include <light.hpp>
#include <transformNode.hpp>
#include <modelNode.hpp>
#include <GLFW/glfw3.h>

class Lightpost {
public:
    Lightpost(Model *lightPost, Shader &lightShader);
    void draw();
    void rotateLight();
    Light light;
    
private:
    Model lightPost;
    

    // Scene graph nodes for light post
    NameNode root;
    TransformNode rootXZTransform;
    TransformNode rootYTransform;
    
    NameNode post;
    TransformNode postTransform;
    ModelNode postShape;
    
    NameNode postHead;
    TransformNode postHeadTranslate;
    TransformNode postHeadRotate;
    TransformNode postHeadScale;
    ModelNode postHeadShape;
    
    TransformNode postBulbCoverTransform;
    ModelNode postBulbCover;
    
    
    // positions and scale vectors for nodes
    glm::vec3 rootXZPos;
    glm::vec3 rootYPos;
    glm::vec3 postScale;
    glm::vec3 headPos;
    glm::vec3 headScale;
    glm::vec3 bulbCoverPos;
    glm::vec3 bulbCoverScale;
    
    // Size variables
    float postHeight = 3.0f;
    float postWidth = 0.5f;
    float postHeadLength = 2.0f;
    float headRotateZAngle = 90.0f;
    
    // Store bulb rotation axis
    glm::vec3 bulbRotateAxis;
    
};

#endif /* lightpost_hpp */
