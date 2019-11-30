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
#include <lightpost.hpp>
#include <snowman.hpp>

//Function protos
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);

void slideSnowman(TransformNode *snowmanBaseTranslate, bool dir, float *xPosition);
void rockSnowman(TransformNode *snowmanBaseTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale);
void rollSnowman(TransformNode *snowmanHeadTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale);
void resetPosition(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale);
void rockRollSlide(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale);


// Global Variables
float xPosition = 0;
// global settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 50.0f;


bool lightAnimate = true;
bool spotlightOn = true;
bool generalLightOn = true;
bool animationPlaying = false;
bool snowmanSlide = false;
bool snowmanRock = false;
bool snowmanRoll = false;
bool snowmanChaos = false;
bool snowmanMoveDir = false;    //false = left/right, true = front/back
bool snowmanReset = false;


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
    // Cube Mesh
    Mesh c = Mesh(cubeData.GetVertices(), cubeData.GetIndices(), 0, cubeData.GetIndicesCount(), cubeData.GetVertexSize(), cubeData.GetIndicesSize());
    // Sphere Mesh
     Mesh s = Mesh(sphereData.GetVertices(), sphereData.GetIndices(), 0, sphereData.getIndicesCount(), sphereData.getVertexSize(), sphereData.getIndicesSize());
    
    
    // Floor object
    glm::mat4 mm = glm::mat4(1.0f);
    mm = glm::translate(mm, glm::vec3(0.0f, 0.0f, 0.0f));
    mm = glm::scale(mm, glm::vec3(20.0f, 1.0f, 20.0f));
    Model floor = Model(defaultShader, mat, mm, t, snow2DiffTex);
    
    // background object
    mm = glm::mat4(1.0f);
    mm = glm::rotate(mm, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mm = glm::rotate(mm, glm::radians(180.0f), glm::vec3(0, 0, 1));
    mm = glm::scale(mm, glm::vec3(20.0f, 1.0f, 20.0f));
    mm = glm::translate(mm, glm::vec3(0.0f, -10.0f, 0.5f));
    Model background = Model(defaultShader, mat, mm, t, treesTex);
    
   
    // Create Materials and Meshes for Models
    // =======================================================
    // Create Light Post
    
    Model lightPost = Model(defaultShader, mat, glm::mat4(1.0f), s, metalTex);
    Lightpost lamppost(&lightPost, lightShader);
    
    // Models
    Model sphere = Model(defaultShader, mat, glm::mat4(1.0f), s, snowDiffTex);
    Model button = Model(defaultShader, mat, glm::mat4(1.0f), s, buttonTex);
    
    
    // Create Snowman
    Model cube = Model(defaultShader, mat, mm, c, woolTex);
    Model hatBobble = Model(defaultShader, mat, mm, s, woolTex);
    Snowman snowman = Snowman(&button, &sphere, &cube, &hatBobble);

    // =============
    // SPECULAR BOX NEXT TO SNOWMAN
    // ==============
    
    Material cubeMat = Material(glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(1.0f), 128.0f);

    
    glm::vec3 boxPos = glm::vec3(- snowman.getTotalHeight(), 0.5*(snowman.getTotalHeight()), 0.0f);
    glm::vec3 boxScale = glm::vec3(snowman.getBodyHeight(), snowman.getTotalHeight(), snowman.getBodyHeight());
    mm = glm::translate(glm::mat4(1.0f), boxPos);
    mm = glm::scale(mm, boxScale);
    Model box = Model(defaultShader, cubeMat, mm, c, containerTex, containerSpecTex);
    
    //=====================================
    //  Set shader values which do NOT change
    //  Materials and other values never change during runtime
    //=====================================
    
    // Spotlight values
    defaultShader.use();
    defaultShader.setVec3("spotLight.ambient", lamppost.light.getMaterial().getAmbient());
    defaultShader.setVec3("spotLight.diffuse", lamppost.light.getMaterial().getDiffuse());
    defaultShader.setVec3("spotLight.specular", lamppost.light.getMaterial().getSpecular());
    defaultShader.setFloat("spotLight.constant", 1.0f);
    defaultShader.setFloat("spotLight.linear", 0.045);
    defaultShader.setFloat("spotLight.quadratic", 0.0075);
    defaultShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(45.0f)));
    defaultShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(60.0f)));
     
    //Directional Light
    defaultShader.setVec3("dirLight.position", globalLightPos);
    defaultShader.setVec3("dirLight.ambient", lamppost.light.getMaterial().getAmbient());
    defaultShader.setVec3("dirLight.diffuse", lamppost.light.getMaterial().getDiffuse());
    defaultShader.setVec3("dirLight.specular", lamppost.light.getMaterial().getSpecular());
    
   
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
            defaultShader.setVec3("spotLight.position", lamppost.light.getPosition() * 0.3f);
            defaultShader.setVec3("spotLight.direction", lamppost.light.Front);
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
        
        if (lightAnimate)
            lamppost.rotateLight();
        lamppost.draw();
    
        // render box next to snowman
        box.render();
    
        // Render snowman + any animations
        if (snowman.singleAnimEnded) // If animation has ended, change animation bool to false
        {
            animationPlaying = false;
            snowmanSlide = false;
            snowmanRock = false;
            snowman.singleAnimEnded = false;
        }
        if (animationPlaying)   // If an animation is playing, set snowman animation bool and start time
        {
            snowman.animationPlaying = true;
            snowman.startTime = startTime;
        }
        if (snowmanReset)               // RESET POSITION
        {
            snowman.resetPosition();
            snowmanReset = false;
        }
//        else if (slideRockRoll)// ROCK ROLL AND SLIDE
//            rockRollSlide(&snowmanMoveTranslate, &xPosition, &headTransform, &headPos, &headScale);
        else if (snowmanSlide && snowmanMoveDir)
        {            // SLIDE FORWARDS AND BACKWARD
            snowman.startTime = startTime;
            snowman.slideMove(true);
        }
        else if (snowmanSlide)
        {// SLIDE SIDE TO SIDE
            snowman.slideMove(false);
            snowman.startTime = startTime;
        }
        else if (snowmanRock && snowmanMoveDir)         // ROCK FORWARDS AND BACKWARDS
            snowman.rockMove(true);
        else if (snowmanRock)         // ROCK SIDE TO SIDE
            snowman.rockMove(false);
//        else if (rollSnowmanHead)       // ROLL HEAD AROUND THE BODY
//            rollSnowman(&headTransform, false, &headPos, &headScale);
//
        
        // RENDER UPDATED SNOWMAN
        snowman.draw();
        
        
        
        
        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();   // all callbacks
        processInput(window); // process continuous input
    }

    // Dipose of resources
    sphere.dispose();
    lamppost.light.dispose();
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
        snowmanReset = true;
    if (!animationPlaying)
    {
        std::cout << "No animation playing" << std::endl;
        if (key == GLFW_KEY_G && action == GLFW_PRESS)  // Slide forward and backwards using G
        {
            snowmanSlide = true;
            animationPlaying = true;
            snowmanMoveDir = true;
            startTime = glfwGetTime();
            std::cout << "sliding forward" << std::endl;
        }
        if (key == GLFW_KEY_T && action == GLFW_PRESS)  // Slide left and right using T
        {
            snowmanSlide = true;
            animationPlaying = true;
            snowmanMoveDir = false;
            startTime = glfwGetTime();
            std::cout << "sliding sideway" << std::endl;
        }
        if (key == GLFW_KEY_H && action == GLFW_PRESS)  // Rock forward and backwards using G
        {
            snowmanRock = true;
            animationPlaying = true;
            snowmanMoveDir = true;
            startTime = glfwGetTime();
            std::cout << "Rock forward" << std::endl;
        }
        if (key == GLFW_KEY_Y && action == GLFW_PRESS)  // Rocl left and right using T
        {
            snowmanRock = true;
            animationPlaying = true;
            snowmanMoveDir = false;
            startTime = glfwGetTime();
            std::cout << "Rock sideway" << std::endl;
        }
//        if (key == GLFW_KEY_J && action == GLFW_PRESS)  // Roll head around body with J
//        {
//            snowman.rollSnowmanHead = true;
//            snowman.animationPlaying = true;
//            snowman.rollStart= true;
//            snowman.rollEnding = false;
//            startTime = glfwGetTime();
//            std::cout << "Roll" << std::endl;
//        }
//        if (key == GLFW_KEY_U && action == GLFW_PRESS)  // Roll head around body with J
//               {
//                   slideRockRoll = true;
//                   animationPlaying = true;
//                   slideReturn = false;
//                   rockReturn = false;
//                   rollStart = true;
//                   rollEnding = false;
//                   startTime = glfwGetTime();
//                   std::cout << "CHAOS!!!!!" << std::endl;
//               }
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




//
///*
// * Rock the snowman in chosen direction twice. Complete one full movement on each side of original position
// * Mid -> Left -> Mid -> Right -> Mid -> Stop;
// *
// * @param snowmanBaseTransform: a pointer to the base transform' transform node
// * @param dir : boolean for direction; true is forward and backwards, fasle is sidways
// * @param originalPos : a pointer to the original position of the snowman
// * @param scale: pointer to the scale of the head -> stored in variable
// *
// */
//void rollSnowman(TransformNode *snowmanHeadTransform, bool dir, glm::vec3 *originalPos, glm::vec3 *scale){
//    float elapsedTime = glfwGetTime() - startTime;
//    
//    
//
//
//    if (animationPlaying)
//    {
//        glm::mat4 mm = glm::mat4(1.0f); // Init model matrix
//        float distance = glm::sin(glm::radians(elapsedTime*50)) /2; // calcualte distance from original position to rotate
//        
//        // If is starting, rotate down the body to chosen level (rotate by 0.45 radians).
//        if (rollStart){
//            mm = glm::rotate(mm, distance, glm::vec3(1, 0, 0));
//            // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
//            if (abs(distance) >= 0.45f)
//            {    rollStart = false;
//                startTime = glfwGetTime();
//            }
//        }
//        // else if roll is ending, rotate head up the body back to original position
//        else if (rollEnding){
//            mm = glm::rotate(mm, 0.45f-distance, glm::vec3(1, 0, 0));
//            // if distance is equal to or greater than 0.45 then head has been returned, make bools false and exit function
//            if (abs(distance) >= 0.45f)
//            {
//                animationPlaying = false;
//                rollSnowmanHead = false;
//                return;
//            }
//        }
//        // else if roll is not starting or ending, it is in motion, so calculate the angle and apply it
//        else {
//            
//            // calculate angle to rotate around the body
//            float rotateAngle = glm::radians(elapsedTime*50);
//            
//            // Rotate around the head around the y axis and down by 0.45 radians in x axis.
//            mm = glm::rotate(mm, -rotateAngle, glm::vec3(0,1,0));
//            mm = glm::rotate(mm, 0.45f, glm::vec3(1,0,0));
//            
//            
//            // Once a full loop is complete, activate ending sequence (full loop is 2*pi, or approximately 6.3
//            if (rotateAngle >= 6.3f) rollEnding = true;  //return true if head is approximately return to original rotation
//        }
//        
//        // do translation and scale
//        mm = glm::translate(mm, *originalPos);              //*originalPos points to contents of originalPos variable
//        mm = glm::scale(mm, *scale);
//        //Apply transform and update children
//        snowmanHeadTransform->setTransform(mm);
//        snowmanHeadTransform->ModelNode::update();
//    }
//}
//
//
//
//
//void rockRollSlide(TransformNode *baseTransform, float *xPosition, TransformNode *headTransform, glm::vec3 *hPos, glm::vec3 *hScale){
//    
//    // Elapsed time since animation began
//    float elapsedTime = glfwGetTime()-startTime;
//    
//    // Model matrices for body and head
//    glm::mat4 mm = glm::mat4(1.0f);
//    glm::mat4 mmHead = glm::mat4(1.0f);
//    
//    
//    // If animation is starting, rotate head down the body to chosen level (rotate by 0.45 radians).
//    float rollDistance = glm::sin(glm::radians(elapsedTime*50)) /2; // calculte distance from original position to rotate
//    if (rollStart){
//        // Roll down the head
//        mmHead = glm::rotate(mmHead, rollDistance, glm::vec3(1, 0, 0));
//        // if distance is equal or greater than 0.45, stop rocking and start the calculation for the actual roll
//        if (abs(rollDistance) >= 0.45f)
//        {
//            rollStart = false;
//            startTime = glfwGetTime();
//        }
//    }
//    
//
//    // Else if animation is not just starting, run rest of animations
//    else {
//       
//        // Distances, and angles
//        float slideDistance = -glm::sin(glm::radians(elapsedTime*50));
//        float rockDistance = -glm::sin(glm::radians(elapsedTime*50)) /2;
//        float rotateAngle = glm::radians(elapsedTime*50); // calculate angle to rotate around the body
//        
//        //Ending criteria
//        std::cout << rockDistance << std::endl;
//        if (slideReturn && (abs(slideDistance) <= 0.02f))
//            AnimationEnded[0] = true;
//        if (rockReturn && (abs(rockDistance) <= 0.01f))
//            AnimationEnded[1] = true;
//        if(rollEnding && (abs(rollDistance) >= 0.45f))
//            AnimationEnded[2] = true;
//        
//        if (AnimationEnded[0] && AnimationEnded[1] && AnimationEnded[2]){
//            animationPlaying = false;
//            slideRockRoll = false;
//            slideReturn = false;
//            rockReturn = false;
//            AnimationEnded = {false, false, false};
//            return;
//        }
//        
//        // SLIDE SIDEWAYS
//        // if slide not complete
//        if (!AnimationEnded[0])
//        {
//            mm = glm::translate(glm::mat4(1.0f), glm::vec3(*xPosition, 0, 0));
//            mm = glm::translate(mm, glm::vec3(slideDistance, 0, 0));
//        }
//        
//
//        // ROCK BACK TO FRONT
//        // If rock not compelte
//        if (!AnimationEnded[1])
//        {
//            mm = glm::rotate(mm, rockDistance, glm::vec3(1, 0, 0)); // Rotate in appropriate direction
//            mm = glm::translate(mm, glm::vec3(*xPosition, 0, 0)); // Translate and scale to appropriate location.
//        }
//       
//
//        // ROLL HEAD
//        
//        // If roll is not complete
//        if (!AnimationEnded[2])
//        {
//            // if roll is ending, rotate head up the body back to original position
//            if (rollEnding){
//                mmHead = glm::rotate(mmHead, 0.45f-rollDistance, glm::vec3(1, 0, 0));
//            }
//            // else roll around body
//            else {
//                // Rotate around the head around the y axis and down by 0.45 radians in x axis.
//                mmHead = glm::rotate(mmHead, -rotateAngle, glm::vec3(0,1,0));
//                mmHead = glm::rotate(mmHead, 0.45f, glm::vec3(1,0,0));
//            }
//        }
//        
////        // Ending booleans
//        if (rockDistance >= 0.49f) rockReturn = true;  //return true if snowman is on return to original position
//        if (slideDistance >= 0.99f) slideReturn = true;  //return true if snowman is on return to original position
//        // Once a full loop is complete, activate ending sequence (full loop is 2*pi, or approximately 6.3
//        if (rotateAngle >= 6.3f) rollEnding = true;  //return true if head is approximately return to original rotation
//    }
//    
//    
//    // do translation and scale
//    mmHead = glm::translate(mmHead, *hPos);              //*hPos points to contents of head position variable
//    mmHead = glm::scale(mmHead, *hScale);
//    
//    baseTransform->setTransform(mm);
//    baseTransform->ModelNode::update();
//    headTransform->setTransform(mmHead);
//    headTransform->ModelNode::update();
//}
