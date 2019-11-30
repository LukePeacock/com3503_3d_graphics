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
    Snowman(){};
    Snowman(Model *button, Model*snowman, Model *hat, Model *hatBobble){
        root = NameNode("root");
        glm::mat4 mm = glm::mat4(1.0f);
        mm = glm::translate(mm, rootXZPos);
        rootXZTranslate = TransformNode("Snowman XZ Translate", mm);
        
        mm = glm::translate(glm::mat4(1.0f), rootYPos);
        rootYTranslate = TransformNode("Snowman Y Translate", mm);
        
         
        body = NameNode("Body");
        mm = glm::scale(glm::mat4(1.0f), bodyScale);
        bodyScaleTransform = TransformNode("body Scale", mm);
        bodyShape = ModelNode("Sphere(body)", *snowman);
         
         // THREE BUTTONS
        buttons = NameNode("buttons");
        mm = glm::scale(glm::mat4(1.0f), buttonScale);
        buttonScaleTransform = TransformNode("button Scale", mm);
        
        mm = glm::translate(glm::mat4(1.0f), topButtonPos);
        topButtonTransform = TransformNode ("Top Button Transform", mm);
        
        mm = glm::translate(glm::mat4(1.0f), midButtonPos);
        midButtonTransform = TransformNode("Mid Button Transform", mm);
        mm = glm::translate(glm::mat4(1.0f), bottomButtonPos);
        bottomButtonTransform = TransformNode("Bottm Button Transform", mm);
        topButtonShape = ModelNode("Sphere (top button)", *button);
        midButtonShape = ModelNode("Sphere (mid button)", *button);
        bottomButtonShape = ModelNode("Sphere (bottom button)", *button);
        
    
         //HEAD
        head = NameNode("head");
        mm = glm::mat4(1.0f);

        mm = glm::translate(mm, headPos);
        headTranslate = TransformNode("Head Translate", mm);
        
        mm = glm::scale(glm::mat4(1.0f), headScale);
        headScaleTransform = TransformNode("head transform", mm);
        headShape = ModelNode("Sphere (head)", *snowman);
         
        
        //FACE
        face = NameNode("face");
        mm = glm::translate(glm::mat4(1.0f), facePos);
        faceTransform = TransformNode("face Transform", mm);
         
        eyes = NameNode("eyes");
        mm = glm::scale(glm::mat4(1.0f), eyeScale);
        eyeScaleTransform = TransformNode("Scale Eyes", mm);
        
        mm = glm::translate(glm::mat4(1.0f), eyePos);
        leftEyeTranslate = TransformNode("left eye Translate", mm);
        glm::vec3 rightEyePos = eyePos * glm::vec3(-1,1,1);
        mm = glm::translate(glm::mat4(1.0f), rightEyePos);
        rightEyeTranslate = TransformNode("right eye Translate", mm);
        leftEyeShape = ModelNode("Sphere (left eye)", *button);
        rightEyeShape = ModelNode("Sphere (right eye)", *button);
             
        nose = NameNode("Nose");
        mm = glm::translate(glm::mat4(1.0f), nosePos);
        mm = glm::scale(mm, noseScale);
        noseTransform = TransformNode("nose transform", mm);
        noseShape = ModelNode("Sphere(nose shape)", *button);
            
        mouth = NameNode("mouth");
        mm = glm::translate(glm::mat4(1.0f), mouthPos);
        mouthTranslate = TransformNode("Mouth Translate", mm);
        
        mm = glm::scale(glm::mat4(1.0f), mouthScale);
        mouthScaleTransform = TransformNode("Mouth Scale", mm);
        mouthShape = ModelNode("Sphere(mouth)", *button);
                      
        //======================
        // HAT
        //======================
        hatRoot = NameNode("Hat");
        mm = glm::translate(glm::mat4(1.0f), hatRootPos);
        hatRootTranslate = TransformNode("Hat Root Translate", mm);
        

        // Top of hat
        mm = glm::translate(glm::mat4(1.0f),hatTopPos);
        mm = glm::scale(mm, hatTopScale);
        hatTopTransform = TransformNode("hat top transform", mm);
        hatTopShape = ModelNode("Cube (hat top)", *hat);

        mm = glm::translate(glm::mat4(1.0f), hatBobblePos);
        mm = glm::scale(mm, hatBobbleScale);
        hatBobbleTransform = TransformNode("hat Bobble Translate", mm);
        hatBobbleShape = ModelNode("Sphere (hat top)", *hatBobble);
        // Right Side
        mm = glm::translate(glm::mat4(1.0f), hatSidePos);
        mm = glm::scale(mm, hatSideScale);
        hatRightSideTransform = TransformNode("Right hat transform", mm);
        hatRightShape = ModelNode("Cube (Right hat)", *hat);

        //Left Side
        mm = glm::translate(glm::mat4(1.0f), hatSidePos * glm::vec3(-1,1,1));
        mm = glm::scale(mm, hatSideScale);
        hatLeftSideTransform = TransformNode("Left hat transform", mm);
        hatLeftShape = ModelNode("Cube(Left hat)", *hat);

        // Back
        mm = glm::translate(glm::mat4(1.0f), hatBackPos);
        mm = glm::scale(mm,glm::vec3(hatWidth, hatSideScale.y, hatSideScale.x));
        mm = glm::rotate(mm, glm::radians(90.0f), glm::vec3(0,1,0));
        hatBackSideTransform = TransformNode("back hat transform", mm);
        hatBackShape = ModelNode ("Cube(back hat)", *hat);

         //================================================================================
         // CREATE SNOWMAN SCENE GRAPH
         //================================================================================
        root.addChild(rootXZTranslate);
        rootXZTranslate.addChild(rootYTranslate);
        rootYTranslate.addChild(body);
        body.addChild(bodyScaleTransform);
        bodyScaleTransform.addChild(bodyShape);
        bodyScaleTransform.addChild(buttonScaleTransform);
        buttonScaleTransform.addChild(topButtonTransform);
        topButtonTransform.addChild(topButtonShape);
        buttonScaleTransform.addChild(midButtonTransform);
        midButtonTransform.addChild(midButtonShape);
        buttonScaleTransform.addChild(bottomButtonTransform);
        bottomButtonTransform.addChild(bottomButtonShape);
        body.addChild(head);
        head.addChild(headTranslate);
        headTranslate.addChild(headScaleTransform);
        headScaleTransform.addChild(headShape);
        headScaleTransform.addChild(face);
        face.addChild(faceTransform);
        faceTransform.addChild(eyes);
        eyes.addChild(eyeScaleTransform);
        eyeScaleTransform.addChild(leftEyeTranslate);
        leftEyeTranslate.addChild(leftEyeShape);
        eyeScaleTransform.addChild(rightEyeTranslate);
        rightEyeTranslate.addChild(rightEyeShape);
        faceTransform.addChild(nose);
        nose.addChild(noseTransform);
        noseTransform.addChild(noseShape);
        faceTransform.addChild(mouth);
        mouth.addChild(mouthTranslate);
        mouthTranslate.addChild(mouthScaleTransform);
        mouthScaleTransform.addChild(mouthShape);
        faceTransform.addChild(hatRoot);
        hatRoot.addChild(hatRootTranslate);
        hatRootTranslate.addChild(hatTopTransform);
        hatTopTransform.addChild(hatTopShape);
        hatRootTranslate.addChild(hatLeftSideTransform);
        hatLeftSideTransform.addChild(hatLeftShape);
        hatRootTranslate.addChild(hatRightSideTransform);
        hatRightSideTransform.addChild(hatRightShape);
        hatRootTranslate.addChild(hatBackSideTransform);
        hatBackSideTransform.addChild(hatBackShape);
        hatRootTranslate.addChild(hatBobbleTransform);
        hatBobbleTransform.addChild(hatBobbleShape);
                        

         
         root.update();
         root.print(0, false);
    }
    void draw(){
        root.draw();
    }
    
    float getBodyHeight(){
        return bodyHeight;
    }
    float getHeadHeight(){
        return headHeight;
    }
    float getTotalHeight(){
        return bodyHeight + headHeight;
    }
    
    void resetPosition(){
        glm::mat4 mm = glm::translate(glm::mat4(1.0f), rootXZPos);
        rootXZTranslate.setTransform(mm);
        //rootXZTranslate.ModelNode::update();
        
        mm = glm::translate(glm::mat4(1.0f), headPos);

        headTranslate.setTransform(mm);
        //headTranslate.ModelNode::update();
        
        animationPlaying = false;
        slideReturn = false;
        slideFbSnowman = false;
        slideSsSnowman = false;
        rockReturn = false;
        rockFbSnowman = false;
        rockSsSnowman = false;
        rollStart = false;
        rollEnding = false;
        rollSnowmanHead = false;
        slideRockRoll = false;
        animationPlaying = false;
        root.update();
    }
    
    
    /*
     * Slide the snowman in chosen direction twice. Complete one full movement on each side of original position
     * Mid -> Left -> Mid -> Right -> Mid -> Stop;
     *
     * @param snowmanBaseTransform: a pointer to the base transform transform node
     * @param dir : boolean for direction; true is forward and backwards, fasle is sidways
     * @param xPosition : a pointer to the x position varaible
     *
     */
    void slideMove(bool dir){
        std::cout << "Slide Snowman" << std::endl;
        float elapsedTime = glfwGetTime()-startTime;
        float distance = -glm::sin(glm::radians(elapsedTime*50));
    
        // Exit function if animation has been played
        if (slideReturn && abs(distance) <= 0.02f){ // When animation is on final slide, and distance less than 0.02; stop the animation and exit function
            animationPlaying = false;
            singleAnimEnded = true;
            slideFbSnowman = false;
            slideReturn = false;
            slideSsSnowman = false;
            return;
        }
        else if (animationPlaying)
        {
            // Move the snowman
            glm::mat4 mm = glm::translate(glm::mat4(1.0f), rootXZPos);
            if (dir)
                mm = glm::translate(mm, glm::vec3(0, 0, distance));
            else
                mm = glm::translate(mm, glm::vec3(distance, 0, 0));
            rootXZTranslate.setTransform(mm);
            rootXZTranslate.ModelNode::update();
        }
    
        if (distance >= 0.99f) slideReturn = true;  //return true if snowman is on return to original position
    }
    
    /*
     * Rock the snowman in chosen direction twice. Complete one full movement on each side of original position
     * Mid -> Left -> Mid -> Right -> Mid -> Stop;
     *
     * @param snowmanBaseTransform: a pointer to the base transform' transform node
     * @param dir : boolean for direction; true is forward and backwards, fasle is sidways
     * @param originalPos : a pointer to the original position of the snowman
     * @param scale: pointer to the scale of the head -> stored in variable
     *
     */
    void rockMove(bool dir){
        float elapsedTime = glfwGetTime() - startTime;
        float distance = - glm::sin(glm::radians(elapsedTime*50)) /2;
    
        std::cout << distance << std::endl;
        // Exit function if animation has been played
        if (rockReturn && abs(distance) <= 0.01f){ // When animation is on final rock, and distance less than 0.02; stop the animation and exit function
            
            singleAnimEnded = true;
            animationPlaying = false;
            rockFbSnowman = false;
            rockSsSnowman = false;
            rockReturn = false;
            return;
        }
        else if (animationPlaying)
        {
            glm::mat4 mm = glm::mat4(1.0f); // Init model matrix
    
            // Rotate in appropriate direction
            if (dir)
                mm = glm::rotate(mm, distance, glm::vec3(1, 0, 0));
                //mm = glm::translate(mm, glm::vec3(0, 0, distance));
            else
                mm = glm::rotate(mm, distance, glm::vec3(0, 0, 1));
    
            // Translate and scale to appropriate location.
            mm = glm::translate(mm, bodyPos);              //*originalPos points to contents of originalPos variable
           // mm = glm::scale(mm, glm::vec3(1,1,1));
            //Apply transform and update children
            rootXZTranslate.setTransform(mm);
            rootXZTranslate.ModelNode::update();
        }
    
        if (distance >= 0.49f) rockReturn = true;  //return true if snowman is on return to original position
    }
    
    
    
    
    // Booleans for different animations and user controls
    bool slideFbSnowman = false;
    bool slideSsSnowman = false;
    bool slideReturn = false;

    bool rockFbSnowman = false;
    bool rockSsSnowman = false;
    bool rockReturn = false;

    bool rollSnowmanHead = false;
    bool rollStart = false;
    bool rollEnding = false;

    bool slideRockRoll = false;
    
    bool animationPlaying = false;
    bool singleAnimEnded = false;
    std::vector<bool> AnimationEnded{false, false, false};
    float startTime;
private:
    
    
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

    // Position, Size, and Scale variables
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
