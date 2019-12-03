//
//  lightpost.cpp
//  Com3503
//
//  Created by Luke on 30/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//  I declare that this code is my own work
//  lpeacock1@sheffield.ac.uk
//

#include "lightpost.hpp"

/*
 * Constructor for light post, create all nodes and populate scene graph
 * Also add light object in correct place in scene relative to scene graph
 *
 * @param *lightPost: A pointer to the light post model (contains texture and vertices data)
 * @param &lightShader: a reference to the light shader created in the main class
 *
 */
Lightpost::Lightpost(Model *lightPost, Shader &lightShader){
    this->light = Light(lightShader);
    rootXZPos = glm::vec3(-5.0f, 0, 5.0f);
    rootYPos = glm::vec3(0, postHeight/2, 0);
    postScale = glm::vec3(postWidth, postHeight, postWidth);
    
    bulbCoverPos = glm::vec3(0, postHeadLength/6, 0);
    bulbCoverScale = glm::vec3(3.0f, 0.1f, 3.0f);
    
    headPos = glm::vec3(0, postHeight/2 + postWidth/2, 0);
    headScale = glm::vec3(postWidth, postHeadLength, postWidth);
   
    
    root = NameNode("Lightpost Root");
    rootXZTransform = TransformNode("Lightpost Root XZ Transform", glm::translate(glm::mat4(1.0f), rootXZPos));
    rootYTransform = TransformNode("Lightpost Root Y Transform", glm::translate(glm::mat4(1.0f), rootYPos));
    
    post = NameNode("Post");
    glm::mat4 mm = glm::scale(glm::mat4(1.0f), postScale);
    postTransform = TransformNode("Post Transform", mm);
    postShape = ModelNode("Sphere (Post Body)", *lightPost);
    
    
    //=========
    // Head of the post
    postHead = NameNode("Post head");
    
    mm = glm::translate(glm::mat4(1.0f), headPos); // Move to correct position
    postHeadTranslate = TransformNode("Post Head Translate", mm);
    
    mm = glm::rotate(glm::mat4(1.0f), glm::radians(headRotateZAngle), glm::vec3(0,0,1)); // rotate on Z axis
    postHeadRotate = TransformNode("Post Head Rotate", mm);
    
    mm = glm::scale(glm::mat4(1.0f), headScale); // Scale
    postHeadScale = TransformNode("Post Head Scale", mm);
    postHeadShape = ModelNode("Sphere (post head)", *lightPost);
    
    mm = glm::translate(glm::mat4(1.0f), bulbCoverPos);
    mm = glm::scale(mm, bulbCoverScale);
    postBulbCoverTransform = TransformNode("Bulb Cover Transform", mm);
    postBulbCover = ModelNode("Sphere (bulb cover)", *lightPost);
    
    bulbRotateAxis = rootXZPos + glm::vec3(0, postHeight + postWidth/2, 0);
    glm::vec3 bulbPos = bulbRotateAxis + glm::vec3(postHeadLength, 0, 0);
    bulbRotateAxis = bulbRotateAxis / glm::vec3(0.3);
    bulbPos = bulbPos / glm::vec3(0.3);
    this->light.Front = glm::vec3(1,0,0);
    this->light.setPosition(bulbPos);
    
    
    root.addChild(rootXZTransform);
    rootXZTransform.addChild(rootYTransform);
    rootYTransform.addChild(post);
    post.addChild(postTransform);
    postTransform.addChild(postShape);
    post.addChild(postHead);
    postHead.addChild(postHeadTranslate);
    postHeadTranslate.addChild(postHeadRotate);
    postHeadRotate.addChild(postHeadScale);
    postHeadScale.addChild(postHeadShape);
    postHeadScale.addChild(postBulbCoverTransform);
    postBulbCoverTransform.addChild(postBulbCover);
    
    
    root.update();
    root.print(0, false);
}

/*
 * Draw lamp post scene graph and light object
 */
void Lightpost::draw()
{
    root.draw();
    light.render();
}



/*
 *  Rotate the lamp post and bulb around the post
 */
void Lightpost::rotateLight() {
    float elapsedTime = glfwGetTime();
    float bulbDistanceFromPole = postHeadLength + postWidth + 1.0f;
    // Rotate the lamp post
    float rotateAngle = -elapsedTime* 50; // rotate anti-clockwise
    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(1, 0, 0));     // Rotate continuouslt
    transform = glm::rotate(transform, glm::radians(rotateAngle), glm::vec3(0, 0, 1));              // Rotate to lie flat
    postHeadRotate.setTransform(transform);
    postHeadRotate.ModelNode::update();     //Update children
    
    // Rotate the actual bulb
    float bulbX = bulbDistanceFromPole * glm::sin(glm::radians(elapsedTime*50));
    float bulbZ = bulbDistanceFromPole * + glm::cos(glm::radians(elapsedTime*50));
    this->light.setPosition(bulbRotateAxis + glm::vec3(bulbX, 0.0, bulbZ));
    //Calculate front direction of bulb and set its rotation;
    this->light.rotateAngle = -rotateAngle; // rotate bulb clockwise to stay in rotation relative to post
    this->light.setFront(glm::normalize(glm::vec3(bulbX, 0, bulbZ)));
   
}
