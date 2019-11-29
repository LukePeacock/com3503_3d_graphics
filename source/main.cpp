//
//  main.cpp
//  COM3503
//
//  Created by Luke Peacock on 24/10/2019.
//  lpeacock1@sheffield.ac.uk
//
//  Some code based on Dr Steve Maddock's Tutorial
//  Based tutorials by Joey De Vries': https://learnopengl.com
//
//  Copyright © 2019 Luke Peacock. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cube.hpp>
#include <sphere.hpp>
#include <twoTriangles.hpp>
#include <camera.hpp>
#include <mesh.hpp>
#include <material.hpp>
#include <model.hpp>
#include <light.hpp>
#include <glm/gtx/string_cast.hpp>
#include <nameNode.hpp>
#include <transformNode.hpp>
#include <modelNode.hpp>

//Function protos
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);
void rotateLight(Light &bulb, float distanceFromPole);
void slideSnowman(TransformNode *snowmanBaseTranslate, bool dir, float *xPosition);
void rockSnowman(TransformNode *snowmanBaseTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale);
void rollSnowman(TransformNode *snowmanHeadTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale);
void resetPosition(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale);
void rockRollSlide(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale);


// Global Variables
TransformNode postHeadRotate = TransformNode("Post Head Rotate", glm::mat4(1.0f));
glm::vec3 postBulbPosition;
float xPosition = 0;
// global settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 50.0f;

// Booleans for different animations and user controls
static bool lightAnimate = true;
static bool spotlightOn = true;
static bool generalLightOn = true;
static bool slideFbSnowman = false;
static bool slideSsSnowman = false;
static bool slideReturn = false;

static bool rockFbSnowman = false;
static bool rockSsSnowman = false;
static bool rockReturn = false;

static bool rollSnowmanHead = false;
static bool rollStart = false;
static bool rollEnding = false;

static bool resetSnowman = false;

static bool slideRockRoll = false;

static bool animationPlaying = false;
std::vector<bool> AnimationEnded{false, false, false};


static unsigned char wireframe;         // Allows scene to be rendered in wireframe
static bool userCam = false;            // Gives user control of camera

// camera settings
Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;    // Timing ensures consistent framerate independent of hardware
float startTime = 0.0f;

// global

glm::vec3 globalLightPos = glm::vec3(3.0f, 3.0f, 3.0f);
// Self-explanatory
int main()
{
    // initialize and configure GLFW
    // -----------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this statement to fixes compilation on OS X
    #endif

    // Create GLFW window and make it the current context
    // ------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "COM3503 - Luke Peacock", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);   //Mouse to move camera
    glfwSetScrollCallback(window, scroll_callback);     //Scroll Mouse to zoom
    glfwSetKeyCallback(window, key_callback);   // Prevents multiple actions from one key press
    

    // load all OpenGL function pointers using GLAD
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    
    Shader defaultShader("shaders/default_shader.vs", "shaders/default_shader.frag");
    Shader lightShader("shaders/light_shader.vs", "shaders/light_shader.frag");

    
    Cube cubeData;
    Sphere sphereData;
    TwoTriangles planeData;
    // load and create a texture
    // -------------------------
    unsigned int snowDiffTex = loadTexture("assets/snow2.jpg");
    unsigned int snow2DiffTex = loadTexture("assets/snow.jpeg");
    unsigned int metalTex = loadTexture("assets/metal.jpg");
    unsigned int treesTex = loadTexture("assets/trees.jpg");
    unsigned int buttonTex = loadTexture("assets/stone.jpg");
    unsigned int containerTex = loadTexture("assets/container.png");
    unsigned int containerSpecTex = loadTexture("assets/container_specular.png");
    unsigned int woolTex = loadTexture("assets/wool.jpeg");
    
    defaultShader.use();
    defaultShader.setInt("material.diffusemap", 0);
    defaultShader.setInt("material.specularmap", 1);
    
    
    // Default material
    Material mat = Material(glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f),16.0f);

    // Two Triangles Mesh
    Mesh t = Mesh(planeData.getVertices(), planeData.getIndices(), 0, planeData.getIndicesCount(), planeData.getVertexSize(), planeData.getIndicesSize());
    
    // Floor object
    Material floorMat = Material(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 16.0f);
    glm::mat4 mm = glm::mat4(1.0f);
    mm = glm::translate(mm, glm::vec3(0.0f, 0.0f, 0.0f));
    mm = glm::scale(mm, glm::vec3(20.0f, 1.0f, 20.0f));
    Model floor = Model(defaultShader, floorMat, mm, t, snow2DiffTex);
    
    // background object
    mm = glm::mat4(1.0f);
    mm = glm::rotate(mm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mm = glm::rotate(mm, glm::radians(180.0f), glm::vec3(0, 0, 1));
    mm = glm::scale(mm, glm::vec3(20.0f, 1.0f, 20.0f));
    mm = glm::translate(mm, glm::vec3(0.0f, -10.0f, 0.5f));
    Model background = Model(defaultShader, mat, mm, t, treesTex);
    
   
    
    // =======================================================
    // Create Light Post
     Mesh s = Mesh(sphereData.GetVertices(), sphereData.GetIndices(), 0, sphereData.getIndicesCount(), sphereData.getVertexSize(), sphereData.getIndicesSize());
    Model lightPost = Model(defaultShader, mat, glm::mat4(1.0f), s, metalTex);      // basic model
    Light light = Light(lightShader);                                               // Light object
   
    // Params
    float lightPostHeight = 3.0f;
    float lightPostWidth = 0.5f;
    float lightPostHeadLength = 2.0f;
    
    // Generate the nodes
    NameNode lightPostRoot = NameNode("Light Post Root");
        // Root translations
        TransformNode lightPostMoveTranslate = TransformNode("light post transform", glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 0, 5.0f)));
    
        TransformNode lightPostTranslate = TransformNode("light post transform 2", glm::translate(glm::mat4(1.0f), glm::vec3(0, lightPostHeight/2, 0)));
    
    // Main post Nodes
    NameNode post = NameNode("Post");
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(lightPostWidth, lightPostHeight, lightPostWidth));
        TransformNode postTransform = TransformNode("post Transform", mm);
        ModelNode postShape = ModelNode("Sphere(post body)", lightPost);

    // Post head nodes
    NameNode postHead = NameNode("Post Head");
        // Post head body nodes
        mm = glm::mat4(1.0f);
        TransformNode postHeadTranslate = TransformNode("Translate", glm::translate(mm, glm::vec3(0.0f, lightPostHeight/2 + lightPostWidth/2, 0.0f)));
        postHeadRotate= TransformNode("post head Rotate", glm::rotate(mm, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
        TransformNode postHeadScale = TransformNode("scale", glm::scale(mm, glm::vec3(lightPostWidth, lightPostHeadLength, lightPostWidth)));
        ModelNode postHeadShape = ModelNode("sphere(post head)", lightPost);
    
        // Post head bulb cover nodes
        mm = glm::mat4(1.0f);
        mm = glm::translate(mm, glm::vec3(0.0f, lightPostHeadLength/6, 0.0f));
        mm = glm::scale(mm, glm::vec3(3.0f, 0.1f, 3.0f));
        TransformNode postBulbCoverTransform = TransformNode("Translate cover", mm);
        ModelNode postBulbCover = ModelNode("cube(cover)", lightPost);
        
        // Calculate bulb position
        postBulbPosition = glm::vec3(-5.0f, lightPostHeight + lightPostWidth/2, 5.0f);
        postBulbPosition = postBulbPosition / glm::vec3(0.3);
        light.Front = glm::vec3(1,0,0);
        light.setPosition(postBulbPosition);
        
    
    
    // create scene graph
    lightPostRoot.addChild(lightPostMoveTranslate);
        lightPostMoveTranslate.addChild(lightPostTranslate);
            lightPostTranslate.addChild(post);
                post.addChild(postTransform);
                    postTransform.addChild(postShape);
                post.addChild(postHead);
                    postHead.addChild(postHeadTranslate);
                        postHeadTranslate.addChild(postHeadRotate);
                            postHeadRotate.addChild(postHeadScale);
                                postHeadScale.addChild(postHeadShape);
                                postHeadScale.addChild(postBulbCoverTransform);
                                    postBulbCoverTransform.addChild(postBulbCover);
    // Update scene graph
    lightPostRoot.update();
    lightPostRoot.print(0, false);  // Print
    
    
    
    // =================================================================
    // SNOWMAN CREATION AND SCENE GRAPH
    // =================================================================
   
    // Models
    Model sphere = Model(defaultShader, mat, glm::mat4(1.0f), s, snowDiffTex);
    Model button = Model(defaultShader, mat, glm::mat4(1.0f), s, buttonTex);
    // Two Triangles Mesh
    Mesh c = Mesh(cubeData.GetVertices(), cubeData.GetIndices(), 0, cubeData.GetIndicesCount(), cubeData.GetVertexSize(), cubeData.GetIndicesSize());
    Material cubeMat = Material(glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.5f), 16.0f);
    Model cube = Model(defaultShader, cubeMat, mm, c, woolTex);
    
    // Params
    float bodyHeight = 3.0f;
    float headHeight = 2.0f;
    float buttonSize = 0.5f;
    float noseSize = 0.15f;
    float hatHeight = 0.4f;
    float hatWidth = 1.0f;
    float hatSideDepth = 0.2f;
    glm::vec3 headPos = glm::vec3(0, bodyHeight/2+headHeight/2, 0);
    glm::vec3 headScale = glm::vec3(headHeight);
    glm::vec3 bodyPos = glm::vec3(xPosition, 0, 0);
    glm::vec3 eyePos = glm::vec3(headHeight/4-buttonSize/2, buttonSize/4, headHeight/4-buttonSize/4);
    glm::vec3 hatSidePos = glm::vec3(headHeight/4, hatHeight/2, 0);
    
    //=================================================
    //  SNOWMAN NODES
    //=================================================
    NameNode snowmanRoot = NameNode("root");
    TransformNode snowmanMoveTranslate = TransformNode("snowman transform", glm::translate(glm::mat4(1.0f), bodyPos));
    
    TransformNode snowmanTranslate = TransformNode("snowman transform2", glm::translate(glm::mat4(1.0f), glm::vec3(0, bodyHeight/2, 0)));
    
    NameNode body = NameNode("body");
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(bodyHeight));
        TransformNode bodyTransform = TransformNode("body transform", mm);
        ModelNode bodyShape = ModelNode("Sphere(body)", sphere);
    
    // THREE BUTTONS
    NameNode buttons = NameNode("buttons");
        mm = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, bodyHeight/2));
        mm = glm::scale(mm, glm::vec3(buttonSize));
        TransformNode Button1Transform = TransformNode("bottom button transform", mm);
        ModelNode button1Shape = ModelNode("Sphere(button)", button);
    
        mm = glm::translate(mm, glm::vec3(0.0f,bodyHeight/3, -buttonSize/2));
        TransformNode Button2Transform = TransformNode("middle button transform", mm);
        ModelNode button2Shape = ModelNode("Sphere(button)", button);
    
        mm = glm::translate(mm, glm::vec3(0.0f, bodyHeight/3, 2*-buttonSize/3));
        TransformNode Button3Transform = TransformNode("top button transform", mm);
        ModelNode button3Shape = ModelNode("Sphere(button)", button);
    
    //HEAD
    NameNode head = NameNode("head");
        mm = glm::mat4(1.0f);

        mm = glm::translate(mm, headPos);
        mm = glm::scale(mm, headScale);
        TransformNode headTransform = TransformNode("head transform", mm);
        ModelNode headShape = ModelNode("Sphere(head)", sphere);
    
   
    //FACE
    NameNode face = NameNode("face");
        TransformNode faceTransform = TransformNode("face Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0)));
    
        NameNode eyes = NameNode("eyes");
            mm = glm::translate(glm::mat4(1.0f), eyePos);
            mm = glm::scale(mm, glm::vec3(buttonSize/2));
            TransformNode leftEyeTransform = TransformNode("left eye transform", mm);
            ModelNode leftEyeShape = ModelNode("Sphere(left eye)", button);
        
    
            mm = glm::translate(glm::mat4(1.0f), eyePos * glm::vec3(-1,1,1));
            mm = glm::scale(mm, glm::vec3(buttonSize/2));
            TransformNode rightEyeTransform = TransformNode("right eye transfrom", mm);
            ModelNode rightEyeShape = ModelNode("SPhere(right eye)", button);

        NameNode nose = NameNode("Nose");
            mm = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, headHeight/4));
            mm = glm::scale(mm, glm::vec3(noseSize, noseSize, buttonSize));
            TransformNode noseTransform = TransformNode("nose transform", mm);
            ModelNode noseShape = ModelNode("Sphere(nose shape)", button);

        NameNode mouth = NameNode("mouth");
            mm = glm::translate(glm::mat4(1.0f), glm::vec3(0, -headHeight/4+buttonSize/2, headHeight/4-buttonSize/4));
            mm = glm::scale(mm, glm::vec3(buttonSize, buttonSize/2, buttonSize/2));
            TransformNode mouthTransform = TransformNode("Mouth Trasnform", mm);
            ModelNode mouthShape = ModelNode("Sphere(mouth)", button);
                 
    //====================================================================================
    // SNOWMAN HAT
    //====================================================================================
    NameNode hat = NameNode("Hat");
        mm = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0 , 0));
        TransformNode hatTransform = TransformNode("Hat transform", mm);
            
        // Top of hat
        mm = glm::translate(glm::mat4(1.0f), glm::vec3(0, headHeight/4, 0));
        mm = glm::scale(mm, glm::vec3(hatWidth, hatHeight, hatWidth));
        TransformNode hatTopTransform = TransformNode("hat top transform", mm);
        ModelNode hatTopShape = ModelNode("Cube(hat main)", cube);
    
        // Right Side
        glm::vec3 sideScale = glm::vec3(hatSideDepth, hatWidth - 0.001, hatWidth - 0.001);
        mm = glm::translate(glm::mat4(1.0f), hatSidePos);
        mm = glm::scale(mm, sideScale);
        TransformNode hatRightTransform = TransformNode("Right hat transform", mm);
        ModelNode rightHatShape = ModelNode("Cube(Right hat)", cube);
        
        //Left Side
        mm = glm::translate(glm::mat4(1.0f), hatSidePos * glm::vec3(-1,1,1));
        mm = glm::scale(mm, sideScale);
        TransformNode hatLeftTransform = TransformNode("Left hat transform", mm);
        ModelNode leftHatShape = ModelNode("Cube(Left hat)", cube);
    
        // Back
        mm = glm::translate(glm::mat4(1.0f), glm::vec3(hatSidePos.z, hatSidePos.y, -hatSidePos.x + hatSideDepth/2 - 0.002));
        mm = glm::scale(mm,glm::vec3(hatWidth, sideScale.y, sideScale.x));
        mm = glm::rotate(mm, glm::radians(90.0f), glm::vec3(0,1,0));
        TransformNode hatBackTransform = TransformNode("back hat transform", mm);
        ModelNode backHatShape = ModelNode ("Cube(back hat)", cube);

    //================================================================================
    // CREATE SNOWMAN SCENE GRAPH
    //================================================================================
    snowmanRoot.addChild(snowmanMoveTranslate);
        snowmanMoveTranslate.addChild(snowmanTranslate);
            snowmanTranslate.addChild(body);
                bodyTransform.addChild(bodyShape);
                    body.addChild(bodyTransform);
                    body.addChild(Button1Transform);
                        Button1Transform.addChild(button1Shape);
                    body.addChild(Button2Transform);
                        Button2Transform.addChild(button2Shape);
                    body.addChild(Button3Transform);
                        Button3Transform.addChild(button3Shape);
                    body.addChild(head);
                        head.addChild(headTransform);
                            headTransform.addChild(headShape);
                            headTransform.addChild(face);
                                face.addChild(faceTransform);
                                    faceTransform.addChild(eyes);
                                        eyes.addChild(leftEyeTransform);
                                            leftEyeTransform.addChild(leftEyeShape);
                                        eyes.addChild(rightEyeTransform);
                                            rightEyeTransform.addChild(rightEyeShape);
                                    faceTransform.addChild(nose);
                                        nose.addChild(noseTransform);
                                            noseTransform.addChild(noseShape);
                                    faceTransform.addChild(mouth);
                                        mouth.addChild(mouthTransform);
                                        mouthTransform.addChild(mouthShape);
                            headTransform.addChild(hat);
                                hat.addChild(hatTransform);
                                    hatTransform.addChild(hatTopTransform);
                                        hatTopTransform.addChild(hatTopShape);
                                    hatTransform.addChild(hatLeftTransform);
                                        hatLeftTransform.addChild(leftHatShape);
                                    hatTransform.addChild(hatRightTransform);
                                        hatRightTransform.addChild(rightHatShape);
                                    hatTransform.addChild(hatBackTransform);
                                        hatBackTransform.addChild(backHatShape);
    
    
    snowmanRoot.update();
    snowmanRoot.print(0, false);
                                
   

    // =============
    // SPECULAR BOX NEXT TO SNOWMAN
    // ==============
    cubeMat.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    cubeMat.setShininess(128.0f);
    
    mm = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f - headHeight, 0.5 * (bodyHeight + headHeight), 0.0f));
    mm = glm::scale(mm, glm::vec3(bodyHeight, bodyHeight+headHeight, bodyHeight));
    Model box = Model(defaultShader, cubeMat, mm, c, containerTex, containerSpecTex);
    
    //=====================================
    //  Set shader values which do NOT change
    //  Materials and other values never change during runtime
    //=====================================
    
    // Spotlight values
    defaultShader.use();
    defaultShader.setVec3("spotLight.ambient", light.getMaterial().getAmbient());
    defaultShader.setVec3("spotLight.diffuse", light.getMaterial().getDiffuse());
    defaultShader.setVec3("spotLight.specular", light.getMaterial().getSpecular());
    defaultShader.setFloat("spotLight.constant", 1.0f);
    defaultShader.setFloat("spotLight.linear", 0.045);
    defaultShader.setFloat("spotLight.quadratic", 0.0075);
    defaultShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(45.0f)));
    defaultShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(60.0f)));
     
    //Directional Light
    defaultShader.setVec3("dirLight.position", globalLightPos);
    defaultShader.setVec3("dirLight.ambient", light.getMaterial().getAmbient());
    defaultShader.setVec3("dirLight.diffuse", light.getMaterial().getDiffuse());
    defaultShader.setVec3("dirLight.specular", light.getMaterial().getSpecular());
    
   
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
    
        // clear buffer bits
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set Projection and View Matrices in Shaders
        //-------------------------------------------
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        // Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
        
        
        // Set view, projection, and view position for default shader
        defaultShader.use();
        defaultShader.setMat4("projection", projection);
        defaultShader.setMat4("view", view);
        defaultShader.setVec3("viewPos", camera.Position);
        
        
        defaultShader.setBool("generalLightOn", (generalLightOn) ? true : false);   // set general light bool on or off in shader
        defaultShader.setBool("spotlightOn", (spotlightOn) ? true : false); //set spotlight bool on or off in shader
        if (spotlightOn)// if spotlight on, update position and direction in shader
        {
            defaultShader.setVec3("spotLight.position", light.getPosition() * 0.3f);
            defaultShader.setVec3("spotLight.direction", light.Front);
        }
        
       
        // Set lighting shader projection and view
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        
        //=========
        // RENDER
        //=========
        
        //render floor and background
        floor.render();
        
        // Calculate Time offset for background texture
        float t = (glfwGetTime())*0.1;
        background.render(glm::vec2(t-glm::floor(t), 0.0f));
        
        // Render light post + rotation animation
        lightPostRoot.draw();
        float lightDistanceFromPole = lightPostHeadLength + lightPostWidth + 1.0f;
        if (lightAnimate)
            rotateLight(light, lightDistanceFromPole);
        light.render();
    
        // render box next to snowman
        box.render();
    
        // Render snowman + any animations
        if (resetSnowman)               // RESET POSITION
            resetPosition(&snowmanMoveTranslate, &xPosition, &headTransform, &headPos, &headScale);
        else if (slideRockRoll)// ROCK ROLL AND SLIDE
            rockRollSlide(&snowmanMoveTranslate, &xPosition, &headTransform, &headPos, &headScale);
        else if (slideFbSnowman)             // SLIDE FORWARDS AND BACKWARD
            slideSnowman(&snowmanMoveTranslate, true, &xPosition);
        else if (slideSsSnowman)        // SLIDE SIDE TO SIDE
            slideSnowman(&snowmanMoveTranslate, false, &xPosition);
        else if (rockFbSnowman)         // ROCK FORWARDS AND BACKWARDS
            rockSnowman(&snowmanMoveTranslate, true, &bodyPos, &headScale);
        else if (rockSsSnowman)         // ROCK SIDE TO SIDE
            rockSnowman(&snowmanMoveTranslate, false, &bodyPos, &headScale);
        else if (rollSnowmanHead)       // ROLL HEAD AROUND THE BODY
            rollSnowman(&headTransform, false, &headPos, &headScale);
        
        
        // RENDER UPDATED SNOWMAN
        snowmanRoot.draw();
        
        
        
        
        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();   // all callbacks
        processInput(window); // process continuous input
    }

    // Dipose of resources
    sphere.dispose();
    light.dispose();
    button.dispose();
    cube.dispose();
    box.dispose();
    
    // Terminate GLFW, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


/*
 * Process the user input. Query GLFW whether relevant keys are pressed/released during frame. React accordingly. Causes issues with keys being registered multiple times, hence additional function `key_callback` to handle keys which should only be registered once.
 *
 * @param window: pointer to the window object.
 *
 */
void processInput(GLFWwindow *window)
{
    // IF user in control of camera, process relevant key
    if (userCam) {
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.ProcessKeyboard(DOWN, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            camera.ProcessKeyboard(UP, deltaTime);
    }
}

/*
 * Keyboard callback. Whenever key is pressed, call function
 *
 * @param window: pointer to window object
 * @param key: integer stating which key token was changed
 * @param scancode: unique field for every key on keyboard (platform specific)
 * @param action: integer stating which action was taken (pressed, released, etc.)
 * @param mods: any special key modifiers
 *
 */
// glfw: key callback function, causes event once per press of a key
// -----------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Change to wireframe view
    if (key == GLFW_KEY_F && action == GLFW_PRESS) // render wireframe with F
        glPolygonMode(GL_FRONT_AND_BACK, (wireframe = 1 - wireframe) ? GL_LINE : GL_FILL);
    //
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) // Set user cam and capture mouse
        glfwSetInputMode(window, GLFW_CURSOR,(userCam = !userCam) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Exit program with escape
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_E && action == GLFW_PRESS) // Turn off spotlight animation with R
        lightAnimate = 1 - lightAnimate;
    if (key == GLFW_KEY_L && action == GLFW_PRESS) // Turn off spotlight light with L
        spotlightOn = 1 - spotlightOn;
    if (key == GLFW_KEY_K && action == GLFW_PRESS) // Turn off general light with K
        generalLightOn = 1 - generalLightOn;
    if (key == GLFW_KEY_R && action == GLFW_PRESS) // Reset snowman with R
        resetSnowman = true;
    if (!animationPlaying)
    {
        std::cout << "No animation playing" << std::endl;
        if (key == GLFW_KEY_G && action == GLFW_PRESS)  // Slide forward and backwards using G
        {
            slideFbSnowman = true;
            animationPlaying = true;
            slideReturn = false;
            startTime = glfwGetTime();
            std::cout << "sliding forward" << std::endl;
        }
        if (key == GLFW_KEY_T && action == GLFW_PRESS)  // Slide left and right using T
        {
            slideSsSnowman = true;
            animationPlaying = true;
            slideReturn = false;
            startTime = glfwGetTime();
            std::cout << "sliding sideway" << std::endl;
        }
        if (key == GLFW_KEY_H && action == GLFW_PRESS)  // Rock forward and backwards using G
        {
            rockFbSnowman = true;
            animationPlaying = true;
            rockReturn = false;
            startTime = glfwGetTime();
            std::cout << "Rock forward" << std::endl;
        }
        if (key == GLFW_KEY_Y && action == GLFW_PRESS)  // Rocl left and right using T
        {
            rockSsSnowman = true;
            animationPlaying = true;
            rockReturn = false;
            startTime = glfwGetTime();
            std::cout << "Rock sideway" << std::endl;
        }
        if (key == GLFW_KEY_J && action == GLFW_PRESS)  // Roll head around body with J
        {
            rollSnowmanHead = true;
            animationPlaying = true;
            rollStart= true;
            rollEnding = false;
            startTime = glfwGetTime();
            std::cout << "Roll" << std::endl;
        }
        if (key == GLFW_KEY_U && action == GLFW_PRESS)  // Roll head around body with J
               {
                   slideRockRoll = true;
                   animationPlaying = true;
                   slideReturn = false;
                   rockReturn = false;
                   rollStart = true;
                   rollEnding = false;
                   startTime = glfwGetTime();
                   std::cout << "CHAOS!!!!!" << std::endl;
               }
    }
}


/*
 * Mouse callback. Activated whenever mouse moves. Allows user to look around.
 *
 * @param window: pointer to the window object
 * @param xpos: new x position of the mouse
 * @param: ypos: new y position of the mouse
 *
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // if user is in control of camera, process movement
    if (userCam)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

/*
 * Callback for when user scrolls mousewheel. Allows user to zoom using scroll
 *
 * @param window: pointer to the window object
 * @param xoffset: offset of new x position
 * @param yoffset: offset of new y position
 *
 */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (userCam)
        camera.ProcessMouseScroll(yoffset);
}


/*
 * Callback for changing viewport size when window resized
 *
 * @param window: pointer to the window object
 * @param width: new width of window
 * @param height: new height of window
 *
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make viewport dimensions the new window dimensions
    // NOTE: width height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/*
 * utility function for loading a 2D texture from file
 *
 * @param path: the filepath for the image being loaded
 *
 * @return unsigned int: the ID of the texture which was loaded.
 */
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format ==  GL_REPEAT); // for this
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format ==  GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

/*
 *  Rotate the lamp post and bulb around the post
 *
 * @param &bulb: refernce to the bulb object, allows function to edit bulb parameters
 * @param: bulbDistanceFromPole: The radius at which the bulb should rotate around the pole
 *
 */
void rotateLight(Light &bulb, float bulbDistanceFromPole){
    float elapsedTime = glfwGetTime();
    
    // Rotate the lamp post
    float rotateAngle = -elapsedTime* 50; // rotate anti-clockwise
    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(1, 0, 0));     // Rotate continuouslt
    transform = glm::rotate(transform, glm::radians(rotateAngle), glm::vec3(0, 0, 1));              // Rotate to lie flat
    postHeadRotate.setTransform(transform);
    postHeadRotate.ModelNode::update();     //Update children
    
    // Rotate the actual bulb
    float bulbX = bulbDistanceFromPole * glm::sin(glm::radians(elapsedTime*50));
    float bulbZ = bulbDistanceFromPole * + glm::cos(glm::radians(elapsedTime*50));
    bulb.setPosition(postBulbPosition + glm::vec3(bulbX, 0.0, bulbZ));
    //Calculate front direction of bulb and set its rotation;
    bulb.rotateAngle = -rotateAngle; // rotate bulb clockwise to stay in rotation relative to post
    bulb.setFront(glm::normalize(glm::vec3(bulbX, 0, bulbZ)));
   
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
void slideSnowman(TransformNode *snowmanBaseTransform, bool dir, float *xPosition){
    float elapsedTime = glfwGetTime()-startTime;
    float distance = -glm::sin(glm::radians(elapsedTime*50));
    
    // Exit function if animation has been played
    if (slideReturn && abs(distance) <= 0.02f){ // When animation is on final slide, and distance less than 0.02; stop the animation and exit function
        animationPlaying = false;
        slideFbSnowman = false;
        slideSsSnowman = false;
        return;
    }
    else if (animationPlaying)
    {
        // Move the snowman
        glm::mat4 mm = glm::translate(glm::mat4(1.0f), glm::vec3(*xPosition, 0, 0));
        if (dir)
            mm = glm::translate(mm, glm::vec3(0, 0, distance));
        else
            mm = glm::translate(mm, glm::vec3(distance, 0, 0));
        snowmanBaseTransform->setTransform(mm);
        snowmanBaseTransform->ModelNode::update();
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
void rockSnowman(TransformNode *snowmanBaseTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale){
    float elapsedTime = glfwGetTime() - startTime;
    float distance = - glm::sin(glm::radians(elapsedTime*50)) /2;
    
    std::cout << distance << std::endl;
    // Exit function if animation has been played
    if (rockReturn && abs(distance) <= 0.01f){ // When animation is on final rock, and distance less than 0.02; stop the animation and exit function
        animationPlaying = false;
        rockFbSnowman = false;
        rockSsSnowman = false;
        return;
    }
    else if (animationPlaying)
    {
        glm::mat4 mm = glm::mat4(1.0f); // Init model matrix
    
        // Rotate in appropriate direction
        if (dir)
            mm = glm::rotate(mm, distance, glm::vec3(0, 0, 1));
            //mm = glm::translate(mm, glm::vec3(0, 0, distance));
        else
            mm = glm::rotate(mm, distance, glm::vec3(1, 0, 0));
        
        // Translate and scale to appropriate location.
        mm = glm::translate(mm, *originalPos);              //*originalPos points to contents of originalPos variable
       // mm = glm::scale(mm, glm::vec3(1,1,1));
        //Apply transform and update children
        snowmanBaseTransform->setTransform(mm);
        snowmanBaseTransform->ModelNode::update();
    }
    
    if (distance >= 0.49f) rockReturn = true;  //return true if snowman is on return to original position
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
void rollSnowman(TransformNode *snowmanHeadTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale){
    float elapsedTime = glfwGetTime() - startTime;
    
    


    if (animationPlaying)
    {
        glm::mat4 mm = glm::mat4(1.0f); // Init model matrix
        float distance = glm::sin(glm::radians(elapsedTime*50)) /2; // calcualte distance from original position to rotate
        
        // If is starting, rotate down the body to chosen level (rotate by 0.45 radians).
        if (rollStart){
            mm = glm::rotate(mm, distance, glm::vec3(1, 0, 0));
            // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
            if (abs(distance) >= 0.45f)
            {    rollStart = false;
                startTime = glfwGetTime();
            }
        }
        // else if roll is ending, rotate head up the body back to original position
        else if (rollEnding){
            mm = glm::rotate(mm, 0.45f-distance, glm::vec3(1, 0, 0));
            // if distance is equal to or greater than 0.45 then head has been returned, make bools false and exit function
            if (abs(distance) >= 0.45f)
            {
                animationPlaying = false;
                rollSnowmanHead = false;
                return;
            }
        }
        // else if roll is not starting or ending, it is in motion, so calculate the angle and apply it
        else {
            
            // calculate angle to rotate around the body
            float rotateAngle = glm::radians(elapsedTime*50);
            
            // Rotate around the head around the y axis and down by 0.45 radians in x axis.
            mm = glm::rotate(mm, -rotateAngle, glm::vec3(0,1,0));
            mm = glm::rotate(mm, 0.45f, glm::vec3(1,0,0));
            
            
            // Once a full loop is complete, activate ending sequence (full loop is 2*pi, or approximately 6.3
            if (rotateAngle >= 6.3f) rollEnding = true;  //return true if head is approximately return to original rotation
        }
        
        // do translation and scale
        mm = glm::translate(mm, *originalPos);              //*originalPos points to contents of originalPos variable
        mm = glm::scale(mm, *scale);
        //Apply transform and update children
        snowmanHeadTransform->setTransform(mm);
        snowmanHeadTransform->ModelNode::update();
    }
}

void resetPosition(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale){
    glm::mat4 mm = glm::translate(glm::mat4(1.0f), glm::vec3(*xPosition, 0, 0));
    baseTransform->setTransform(mm);
    baseTransform->ModelNode::update();
    
    mm = glm::translate(glm::mat4(1.0f), *hPos);
    mm = glm::scale(mm, *hScale);
    headTransform->setTransform(mm);
    headTransform->ModelNode::update();
    
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
    resetSnowman = false;
}


void rockRollSlide(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale){
    
    // Elapsed time since animation began
    float elapsedTime = glfwGetTime()-startTime;
    
    // Model matrices for body and head
    glm::mat4 mm = glm::mat4(1.0f);
    glm::mat4 mmHead = glm::mat4(1.0f);
    
    
    // If animation is starting, rotate head down the body to chosen level (rotate by 0.45 radians).
    float rollDistance = glm::sin(glm::radians(elapsedTime*50)) /2; // calculte distance from original position to rotate
    if (rollStart){
        // Roll down the head
        mmHead = glm::rotate(mmHead, rollDistance, glm::vec3(1, 0, 0));
        // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
        if (abs(rollDistance) >= 0.45f)
        {
            rollStart = false;
            startTime = glfwGetTime();
        }
    }
    

    // Else if animation is not just starting, run rest of animations
    else {
       
        // Distances, and angles
        float slideDistance = -glm::sin(glm::radians(elapsedTime*50));
        float rockDistance = -glm::sin(glm::radians(elapsedTime*50)) /2;
        float rotateAngle = glm::radians(elapsedTime*50); // calculate angle to rotate around the body
        
        //Ending criteria
        std::cout << rockDistance << std::endl;
        if (slideReturn && (abs(slideDistance) <= 0.02f))
            AnimationEnded[0] = true;
        if (rockReturn && (abs(rockDistance) <= 0.01f))
            AnimationEnded[1] = true;
        if(rollEnding && (abs(rollDistance) >= 0.45f))
            AnimationEnded[2] = true;
        
        if (AnimationEnded[0] && AnimationEnded[1] && AnimationEnded[2]){
            animationPlaying = false;
            slideRockRoll = false;
            slideReturn = false;
            rockReturn = false;
            AnimationEnded = {false, false, false};
            return;
        }
        
        // SLIDE SIDEWAYS
        // if slide not complete
        if (!AnimationEnded[0])
        {
            mm = glm::translate(glm::mat4(1.0f), glm::vec3(*xPosition, 0, 0));
            mm = glm::translate(mm, glm::vec3(slideDistance, 0, 0));
        }
        

        // ROCK BACK TO FRONT
        // If rock not compelte
        if (!AnimationEnded[1])
        {
            mm = glm::rotate(mm, rockDistance, glm::vec3(1, 0, 0)); // Rotate in appropriate direction
            mm = glm::translate(mm, glm::vec3(*xPosition, 0, 0)); // Translate and scale to appropriate location.
        }
       

        // ROLL HEAD
        
        // If roll is not complete
        if (!AnimationEnded[2])
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
    mmHead = glm::translate(mmHead, *hPos);              //*hPos points to contents of head position variable
    mmHead = glm::scale(mmHead, *hScale);
    
    baseTransform->setTransform(mm);
    baseTransform->ModelNode::update();
    headTransform->setTransform(mmHead);
    headTransform->ModelNode::update();
}
