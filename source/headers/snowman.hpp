//
//  snowman.hpp
//  Com3503
//
//  Created by Luke on 30/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#ifndef snowman_hpp
#define snowman_hpp

#include <stdio.h>
#include <nameNode.hpp>
#include <model.hpp>
#include <transformNode.hpp>
#include <modelNode.hpp>
#include <GLFW/glfw3.h>

class Snowman{
public:
    // Constructors

    Snowman(Model *button, Model*snowman, Model *hat, Model *hatBobble);
    void createSceneGraph();
    void draw();
    
    // Getters for various heights
    float getBodyHeight();
    float getHeadHeight();
    float getTotalHeight();
    
    // Position Reset
    void resetPosition();
    
    // Animations
    void slideMove(bool dir);
    void rockMove(bool dir);
    void rollMove();
    void rockRollSlideMove();
    
    
    
    // Booleans for different animations and user controls
    bool slideReturn = false;
    bool rockReturn = false;
    bool rollStarted = false;
    bool rollEnding = false;
    // Booleans for if an animation is currently playing, if an animation has ended, and if each of the animations has ended in the combination animation.
    bool animationPlaying = false;
    bool singleAnimEnded = false;
    std::vector<bool> animationEnded{false, false, false};
    
    // Start times for various parts of animation
    float startTime;
    float rollStartTime;
private:
    
    // Scene Graph Nodes
    NameNode root;
    TransformNode rootXZTranslate;
    TransformNode rootYTranslate;
    
    NameNode body;
    TransformNode bodyScaleTransform;
    ModelNode bodyShape;
    
    NameNode buttons;
    TransformNode buttonScaleTransform;
    TransformNode topButtonTransform;
    TransformNode midButtonTransform;
    TransformNode bottomButtonTransform;
    ModelNode topButtonShape;
    ModelNode midButtonShape;
    ModelNode bottomButtonShape;
    
    
    NameNode head;
    TransformNode headTranslate;
    TransformNode headScaleTransform;
    ModelNode headShape;
    
    NameNode face;
    TransformNode faceTransform;
    
    NameNode eyes;
    TransformNode eyeScaleTransform;
    TransformNode leftEyeTranslate;
    TransformNode rightEyeTranslate;
    ModelNode leftEyeShape;
    ModelNode rightEyeShape;
    
    NameNode nose;
    TransformNode noseTransform;
    ModelNode noseShape;
    
    NameNode mouth;
    TransformNode mouthTranslate;
    TransformNode mouthScaleTransform;
    ModelNode mouthShape;
    
    NameNode hatRoot;
    TransformNode hatRootTranslate;
    TransformNode hatBobbleTransform;
    TransformNode hatTopTransform;
    TransformNode hatLeftSideTransform;
    TransformNode hatRightSideTransform;
    TransformNode hatBackSideTransform;
    ModelNode hatTopShape;
    ModelNode hatLeftShape;
    ModelNode hatRightShape;
    ModelNode hatBackShape;
    ModelNode hatBobbleShape;

    // Size variables.
    float bodyHeight = 3.0f;
    float headHeight = 2.0f;
    float buttonSize = 0.1f;
    float eyeSize = 0.2f;
    float noseWidth = 0.15f;
    float noseLength = 0.2f;
    float mouthWidth = 0.5f;
    float mouthHeight = 0.25f;
    float hatHeight = 0.4f;
    float hatWidth = 1.0f;
    float hatTopHeight = 0.4f;
    float hatSideDepth = 0.2f;
    float hatBobbleSize = 0.4f;
    
    // Position, and Scale variables for use in scene graph construction
    // Edit values here to change the position of elements of scene graph
    glm::vec3 rootXZPos = glm::vec3(0,0,0);
    glm::vec3 rootYPos = glm::vec3(0, bodyHeight/2, 0);
    glm::vec3 bodyScale = glm::vec3(bodyHeight);
    
    
    glm::vec3 buttonScale = glm::vec3(buttonSize);
    glm::vec3 topButtonPos = glm::vec3(0,bodyHeight,bodyHeight + 1.0f);
    glm::vec3 midButtonPos = glm::vec3(0,bodyHeight/2,bodyHeight + 1.75f);
    glm::vec3 bottomButtonPos = glm::vec3(0,0, bodyHeight + 2.0f);
    glm::vec3 facePos = glm::vec3(0.0f);
    
    glm::vec3 eyeScale = glm::vec3(eyeSize);
    glm::vec3 eyePos = glm::vec3(headHeight/2-eyeSize/2, headHeight/4+eyeSize/2, headHeight + eyeSize);
   
    glm::vec3 nosePos = glm::vec3(0,0, headHeight/4);
    glm::vec3 noseScale = glm::vec3(noseWidth, noseWidth, noseLength);
    
    glm::vec3 mouthPos = glm::vec3(0, -headHeight/4 + mouthHeight, mouthHeight*1.5);
    glm::vec3 mouthScale = glm::vec3(mouthWidth, mouthHeight, mouthHeight);
    
    glm::vec3 headPos = glm::vec3(0, bodyHeight/2+headHeight/2, 0);
    glm::vec3 headScale = glm::vec3(headHeight);
    glm::vec3 bodyPos = glm::vec3(0, 0, 0);
   
    
    glm::vec3 hatRootPos = glm::vec3(0,0,0);
    glm::vec3 hatTopPos = glm::vec3(0, headHeight/4, 0);
    glm::vec3 hatTopScale = glm::vec3(hatWidth, hatTopHeight, hatWidth);
    glm::vec3 hatBobblePos = glm::vec3(0, headHeight/4 + hatBobbleSize, 0);
    glm::vec3 hatBobbleScale = glm::vec3(hatBobbleSize);
    glm::vec3 hatSidePos = glm::vec3(headHeight/4, hatHeight/2, 0);
    glm::vec3 hatSideScale = glm::vec3(hatSideDepth, hatWidth - 0.001, hatWidth - 0.001);
    glm::vec3 hatBackPos = glm::vec3(hatSidePos.z, hatSidePos.y, - hatSidePos.x + hatSideDepth/2 - 0.002);
    

};
#endif /* snowman_hpp */
