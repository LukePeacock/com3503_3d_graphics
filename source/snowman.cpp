//
//  snowman.cpp
//  Com3503
//
//  Created by Luke on 30/11/2019.
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include "snowman.hpp"

Snowman::Snowman(Model *button, Model*snowman, Model*hat, Model*hatBobble){
    root = NameNode("root");                                // Root XYZ Translations
    glm::mat4 mm = glm::mat4(1.0f);
    mm = glm::translate(mm, rootXZPos);
    rootXZTranslate = TransformNode("Snowman XZ Translate", mm);
           
    mm = glm::translate(glm::mat4(1.0f), rootYPos);
    rootYTranslate = TransformNode("Snowman Y Translate", mm);
           
            
    body = NameNode("Body");                                // Body
    mm = glm::scale(glm::mat4(1.0f), bodyScale);
    bodyScaleTransform = TransformNode("body Scale", mm);
    bodyShape = ModelNode("Sphere(body)", *snowman);
            
    
    buttons = NameNode("buttons");                          // THREE BUTTONS
    mm = glm::scale(glm::mat4(1.0f), buttonScale);
    buttonScaleTransform = TransformNode("button Scale", mm);
           
    mm = glm::translate(glm::mat4(1.0f), topButtonPos);
    topButtonTransform = TransformNode ("Top Button Transform", mm);
    topButtonShape = ModelNode("Sphere (top button)", *button);
           
    mm = glm::translate(glm::mat4(1.0f), midButtonPos);
    midButtonTransform = TransformNode("Mid Button Transform", mm);
    midButtonShape = ModelNode("Sphere (mid button)", *button);
    
    mm = glm::translate(glm::mat4(1.0f), bottomButtonPos);
    bottomButtonTransform = TransformNode("Bottm Button Transform", mm);
    bottomButtonShape = ModelNode("Sphere (bottom button)", *button);
           
    
    head = NameNode("head");                                // HEAD
    mm = glm::mat4(1.0f);
    mm = glm::translate(mm, headPos);
    headTranslate = TransformNode("Head Translate", mm);
           
    mm = glm::scale(glm::mat4(1.0f), headScale);
    headScaleTransform = TransformNode("head transform", mm);
    headShape = ModelNode("Sphere (head)", *snowman);
            
           
    
    face = NameNode("face");                                // FACE
    mm = glm::translate(glm::mat4(1.0f), facePos);
    faceTransform = TransformNode("face Transform", mm);
            
    eyes = NameNode("eyes");                                // Eyes
    mm = glm::scale(glm::mat4(1.0f), eyeScale);
    eyeScaleTransform = TransformNode("Scale Eyes", mm);
           
    mm = glm::translate(glm::mat4(1.0f), eyePos);
    leftEyeTranslate = TransformNode("left eye Translate", mm);
    leftEyeShape = ModelNode("Sphere (left eye)", *button);
    
    glm::vec3 rightEyePos = eyePos * glm::vec3(-1,1,1);
    mm = glm::translate(glm::mat4(1.0f), rightEyePos);
    rightEyeTranslate = TransformNode("right eye Translate", mm);
    rightEyeShape = ModelNode("Sphere (right eye)", *button);
                
    nose = NameNode("Nose");                                // Nose
    mm = glm::translate(glm::mat4(1.0f), nosePos);
    mm = glm::scale(mm, noseScale);
    noseTransform = TransformNode("nose transform", mm);
    noseShape = ModelNode("Sphere(nose shape)", *button);
            
    mouth = NameNode("mouth");                              // Mouth
    mm = glm::translate(glm::mat4(1.0f), mouthPos);
    mouthTranslate = TransformNode("Mouth Translate", mm);
    mm = glm::scale(glm::mat4(1.0f), mouthScale);
    mouthScaleTransform = TransformNode("Mouth Scale", mm);
    mouthShape = ModelNode("Sphere(mouth)", *button);
                         
    //==============================================================
    //                              HAT
    //==============================================================
    hatRoot = NameNode("Hat");                              // Hat root translate
    mm = glm::translate(glm::mat4(1.0f), hatRootPos);
    hatRootTranslate = TransformNode("Hat Root Translate", mm);
           

    // Top of hat
    mm = glm::translate(glm::mat4(1.0f),hatTopPos);
    mm = glm::scale(mm, hatTopScale);
    hatTopTransform = TransformNode("hat top transform", mm);
    hatTopShape = ModelNode("Cube (hat top)", *hat);

    // Bobble on top of hat
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

    createSceneGraph();
}

//================================================================================
//                          CREATE SNOWMAN SCENE GRAPH
//================================================================================
void Snowman::createSceneGraph()
{
    // Add all nodes to the scene graph in correct order
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
                    // Head
                    head.addChild(headTranslate);
                        headTranslate.addChild(headScaleTransform);
                            headScaleTransform.addChild(headShape);
                            headScaleTransform.addChild(face);
                                // Face
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
                            // Hat
                            headScaleTransform.addChild(hatRoot);
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
                           

    // Update the tree and print it to the command line
    root.update();
    root.print(0, false);
}

void Snowman::draw()
{
    root.draw();
}

// Getters for various heights
float Snowman::getBodyHeight(){
    return bodyHeight;
}

float Snowman::getHeadHeight(){
    return headHeight;
}

float Snowman::getTotalHeight(){
    return bodyHeight + headHeight;
}
/*
 * Reset the snowmans position
 */
void Snowman::resetPosition()
{
    glm::mat4 mm = glm::translate(glm::mat4(1.0f), rootXZPos);
    rootXZTranslate.setTransform(mm);
    //rootXZTranslate.ModelNode::update();
    
    mm = glm::translate(glm::mat4(1.0f), headPos);

    headTranslate.setTransform(mm);
    //headTranslate.ModelNode::update();
    
    animationPlaying = false;
    slideReturn = false;
    rockReturn = false;
    rollStarted = false;
    rollEnding = false;
    singleAnimEnded = false;
    animationEnded = {false, false, false};
    root.update();
}


/*
 * Rock the snowman in chosen direction twice. Complete one full movement on each side of original position
 * Mid -> Left -> Mid -> Right -> Mid -> Stop;
 *
 * @param dir : boolean for direction; true is forward and backwards, fasle is sidways
 *
 */
void Snowman::rockMove(bool dir){
    float elapsedTime = glfwGetTime() - startTime;
        float distance = - glm::sin(glm::radians(elapsedTime*50)) /2;
    
       
        // Exit function if animation has been played
        if (rockReturn && abs(distance) <= 0.01f){ // When animation is on final rock, and distance less than 0.02; stop the animation and exit function
            
            singleAnimEnded = true;
            animationPlaying = false;
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

/*
 * Slide the snowman in chosen direction twice. Complete one full movement on each side of original position
 * Mid -> Left -> Mid -> Right -> Mid -> Stop;
 *
 * @param dir : boolean for direction; true is forward and backwards, fasle is sidways
 *
 */
void Snowman::slideMove(bool dir){
    float elapsedTime = glfwGetTime()-startTime;
        float distance = -glm::sin(glm::radians(elapsedTime*50));
    
        // Exit function if animation has been played
        if (slideReturn && abs(distance) <= 0.02f){ // When animation is on final slide, and distance less than 0.02; stop the animation and exit function
            animationPlaying = false;
            singleAnimEnded = true;
            slideReturn = false;
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
 * Roll the snowman's head around its body. Complete one full rotation before stopping. Tilt head down/up before rotation begins/ends.
 */
void Snowman::rollMove()
{

       if (animationPlaying)
       {
           glm::mat4 mm = glm::mat4(1.0f); // Init model matrix
          
           // If is starting, rotate down the body to chosen level (rotate by 0.45 radians).
           if (!rollStarted) {
               float elapsedTime = glfwGetTime() - startTime;  // get elapsed time
               float distance = glm::sin(glm::radians(elapsedTime*50)) /2; // calcualte distance from original position to rotate
               
               mm = glm::rotate(mm, distance, glm::vec3(1, 0, 0));     // apply rotation
               
               // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
               if (distance >= 0.45f)
               {
                   rollStartTime = glfwGetTime();
                   rollStarted = true;
               }
           }
           else
           {
               float elapsedTime = glfwGetTime() - rollStartTime;  // get elapsed time since roll around body began
               float distance = glm::sin(glm::radians(elapsedTime*50)) /2; // calcualte distance from original position to rotate
               
               // if roll is ending, rotate head up the body back to original position
               if (rollEnding){
                   
                   mm = glm::rotate(mm, 0.45f-distance, glm::vec3(1, 0, 0));   // rotate vertically
                   
                   // if distance is equal to or greater than 0.45 then head has been returned, make bools false and exit function
                   if (abs(distance) >= 0.45f)
                   {
                       singleAnimEnded = true;
                       animationPlaying = false;
                       rollEnding = false;
                       rollStarted = false;
                       return;
                   }
               }
               // else roll is not starting or ending, hence it is in motion, so calculate the angle and apply it
               else {
       
                   // calculate angle to rotate around the body
                   float rotateAngle = glm::radians(elapsedTime*50);
       
                   // Rotate around the head around the y axis and down by 0.45 radians in x axis.
                   mm = glm::rotate(mm, -rotateAngle, glm::vec3(0,1,0));
                   mm = glm::rotate(mm, 0.45f, glm::vec3(1,0,0));
       
                   // Once a full loop is complete, activate ending sequence (full loop is 2*pi, or approximately 6.3
                   if (rotateAngle >= 6.3f) rollEnding = true;  //return true if head is approximately return to original rotation
               }
           }
       
           // do translation and scale
           mm = glm::translate(mm, headPos);              //*originalPos points to contents of originalPos variable
           //Apply transform and update children
           headTranslate.setTransform(mm);
           headTranslate.ModelNode::update();
       }
}


/*
 * Combine the slide, rock, and roll moves.
 * Slide side to side, rock back and forward, and roll head around body simultaneously.
 */
void Snowman::rockRollSlideMove()
{
    // Elapsed time since animation began
    float elapsedTime;

    // Model matrices for body and head
    glm::mat4 mm = glm::mat4(1.0f);
    glm::mat4 mmHead = glm::mat4(1.0f);

    // If animation is starting, rotate head down the body to chosen level (rotate by 0.45 radians).
    
    if (!rollStarted) {
        float elapsedTime = glfwGetTime() - startTime;  // get elapsed time
        float rollDistance = glm::sin(glm::radians(elapsedTime*50)) /2; // calcualte distance from original position to rotate
        
        mmHead = glm::rotate(mmHead, rollDistance, glm::vec3(1, 0, 0));     // apply rotation
        
        // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
        if (rollDistance >= 0.45f)
        {
            rollStartTime = glfwGetTime();
            rollStarted = true;
        }
    }


    // Else if animation is not just starting, run rest of animations
    else {
        elapsedTime = glfwGetTime()-rollStartTime;  // time since combination part of animation began
        
        // Distances, and angles
        float slideDistance = -glm::sin(glm::radians(elapsedTime*50));
        float rockDistance = -glm::sin(glm::radians(elapsedTime*50)) /2;
        float rotateAngle = glm::radians(elapsedTime*50); // calculate angle to rotate around the body
        float rollDistance = glm::sin(glm::radians(elapsedTime*50)) /2; // calculte distance from original position to rotate
        
        
        //Ending criteria
        if (slideReturn && (abs(slideDistance) <= 0.02f))
            animationEnded[0] = true;
        if (rockReturn && (abs(rockDistance) <= 0.01f))
            animationEnded[1] = true;
        if(rollEnding && (abs(rollDistance) >= 0.45f))
            animationEnded[2] = true;

        
        if (animationEnded[0] && animationEnded[1] && animationEnded[2]){
            animationPlaying = false;
            singleAnimEnded = true;
            slideReturn = false;
            rockReturn = false;
            rollStarted = false;
            rollEnding = false;
            animationEnded = {false, false, false};
            return;
        }

        // SLIDE SIDEWAYS
        // if slide not complete
        if (!animationEnded[0])
        {
            mm = glm::translate(glm::mat4(1.0f), bodyPos);
            mm = glm::translate(mm, glm::vec3(slideDistance, 0, 0));
        }


        // ROCK BACK TO FRONT
        // If rock not compelte
        if (!animationEnded[1])
        {
            mm = glm::rotate(mm, rockDistance, glm::vec3(1, 0, 0)); // Rotate in appropriate direction
            mm = glm::translate(mm, bodyPos); // Translate and scale to appropriate location.
        }


        // ROLL HEAD

        // If roll is not complete
        if (!animationEnded[2])
        {
            // if roll is ending, rotate head up the body back to original position
            if (rollEnding){
                mmHead = glm::rotate(mmHead, 0.45f-rollDistance, glm::vec3(1, 0, 0));
            }
            // else roll around body
            else {
                // Rotate around the head around the y axis and down by 0.45 radians in x axis.
                mmHead = glm::rotate(mmHead, -rotateAngle, glm::vec3(0,1,0));
                mmHead = glm::rotate(mmHead, 0.45f, glm::vec3(1,0,0));
            }
        }

//        // Ending booleans
        if (rockDistance >= 0.49f) rockReturn = true;  //return true if snowman is on return to original position
        if (slideDistance >= 0.99f) slideReturn = true;  //return true if snowman is on return to original position
        // Once a full loop is complete, activate ending sequence (full loop is 2*pi, or approximately 6.3
        if (rotateAngle >= 6.3f) rollEnding = true;  //return true if head is approximately return to original rotation
    }
    // do translation and scale
    mmHead = glm::translate(mmHead, headPos);
    rootXZTranslate.setTransform(mm);
    rootXZTranslate.ModelNode::update();
    headTranslate.setTransform(mmHead);
    headTranslate.ModelNode::update();
}
