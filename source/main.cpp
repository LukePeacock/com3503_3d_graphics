//
//  main.cpp
//  COM3503
//
//  Created by Luke Peacock on 24/10/2019.
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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
float getElapsedTime();
void rotateLight(Light &bulb, float distanceFromPole);


TransformNode postHeadRotate = TransformNode("Post Head Rotate", glm::mat4(1.0f));
glm::vec3 postBulbPosition;
NameNode lightPostRoot = NameNode("Light Post Root");


// global settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 100.0f;

bool animate = false;
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
float xPosition = 0;
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
    Shader planeShader("shaders/plane_shader.vs", "shaders/plane_shader.frag");
    
    Cube cubeData;
    Sphere sphereData;
    TwoTriangles planeData;
    // load and create a texture
    // -------------------------
    unsigned int snowDiffTex = loadTexture("assets/snow.png");
    unsigned int snow2DiffTex = loadTexture("assets/snow2.png");
    unsigned int metalTex = loadTexture("assets/metal.jpg");
    unsigned int treesTex = loadTexture("assets/trees.png");
    unsigned int buttonTex = loadTexture("assets/stone.jpg");
    unsigned int containerTex = loadTexture("assets/container.png");
    unsigned int containerSpecTex = loadTexture("assets/container_specular.png");
   
    defaultShader.use();
    defaultShader.setInt("material.diffusemap", 0);
    defaultShader.setInt("material.specularmap", 1);
    
    
    // Default material
    Material mat = Material(glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f),32.0f);

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
    Model background = Model(planeShader, mat, mm, t, treesTex);
    
   
    
    // =======================================================
    // Create Light Post
     Mesh s = Mesh(sphereData.GetVertices(), sphereData.GetIndices(), 0, sphereData.getIndicesCount(), sphereData.getVertexSize(), sphereData.getIndicesSize());
    Model lightPost = Model(defaultShader, mat, glm::mat4(1.0f), s, metalTex);      // basic model
    Light light = Light(lightShader);                                               // Light object
   
    // Params
    float lightPostHeight = 5.0f;
    float lightPostWidth = 0.5f;
    float lightPostHeadLength = 2.0f;
    
    // Generate the nodes
    lightPostRoot = NameNode("root");
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
    
    
    
    // =======================================================
    // Create Snowman
   
       Model sphere = Model(defaultShader, mat, glm::mat4(1.0f), s, snowDiffTex);
        Model button = Model(defaultShader, mat, glm::mat4(1.0f), s, buttonTex);
    // Params
    float bodyHeight = 3.0f;
    float headHeight = 2.0f;
    float buttonSize = 0.5f;
    
    NameNode snowmanRoot = NameNode("root");
    TransformNode snowmanMoveTranslate = TransformNode("snowman transform", glm::translate(glm::mat4(1.0f), glm::vec3(xPosition,0,0)));
    
    TransformNode snowmanTranslate = TransformNode("snowman transform2", glm::translate(glm::mat4(1.0f), glm::vec3(0, bodyHeight/2, 0)));
    
    NameNode body = NameNode("body");
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(bodyHeight));
        TransformNode bodyTransform = TransformNode("body transform", mm);
        ModelNode bodyShape = ModelNode("Sphere(body)", sphere);
    
    NameNode buttons = NameNode("buttons");
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(buttonSize));
    
        mm = glm::translate(mm, glm::vec3(0.0f, 0.0f, bodyHeight));
        TransformNode Button1Transform = TransformNode("bottom button transform", mm);
        ModelNode button1Shape = ModelNode("Sphere(button)", button);
    
        mm = glm::translate(mm, glm::vec3(0.0f,bodyHeight/3, -buttonSize/2));
        TransformNode Button2Transform = TransformNode("middle button transform", mm);
        ModelNode button2Shape = ModelNode("Sphere(button)", button);
    
        mm = glm::translate(mm, glm::vec3(0.0f, bodyHeight/3, 2*-buttonSize/3));
        TransformNode Button3Transform = TransformNode("top button transform", mm);
        ModelNode button3Shape = ModelNode("Sphere(button)", button);
    
    
    NameNode head = NameNode("head");
        mm = glm::mat4(1.0f);
        mm = glm::translate(mm, glm::vec3(0, bodyHeight/2+headHeight/2, 0));
        mm = glm::scale(mm, glm::vec3(headHeight));
        TransformNode headTransform = TransformNode("head transform", mm);
        ModelNode headShape = ModelNode("Sphere(head)", sphere);
    
    NameNode face = NameNode("face");
        NameNode eyes = NameNode("eyes");
            mm = glm::scale(glm::mat4(1.0f), glm::vec3(buttonSize/2));
            mm = glm::translate(mm, glm::vec3(headHeight/2, headHeight/4, headHeight));
            TransformNode leftEyeTransform = TransformNode("left eye transform", mm);
            ModelNode leftEyeShape = ModelNode("Sphere(left eye)", button);
        
            mm = glm::scale(glm::mat4(1.0f), glm::vec3(buttonSize/2));
            mm = glm::translate(mm, glm::vec3(-headHeight/2, headHeight/4, headHeight));
            TransformNode rightEyeTransform = TransformNode("right eye transfrom", mm);
            ModelNode rightEyeShape = ModelNode("SPhere(right eye)", button);

    NameNode nose = NameNode("Nose");
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(buttonSize/4, buttonSize/4, buttonSize/2));
        mm = glm::translate(mm, glm::vec3(0, 0, headHeight));
        TransformNode noseTransform = TransformNode("nose transform", mm);
        ModelNode noseShape = ModelNode("Sphere(nose shape)", button);

    NameNode mouth = NameNode("mouth");
    mm = glm::scale(glm::mat4(1.0f), glm::vec3(buttonSize, buttonSize/2, buttonSize/2));
    mm = glm::translate(mm, glm::vec3(0, -headHeight/2, headHeight));
                        TransformNode mouthTransform = TransformNode("Mouth Trasnform", mm);
                        ModelNode mouthShape = ModelNode("Sphere(mouth)", button);
                 
    NameNode hat = NameNode("Hat");
        // Two Triangles Mesh
        Mesh c = Mesh(cubeData.GetVertices(), cubeData.GetIndices(), 0, cubeData.GetIndicesCount(), cubeData.GetVertexSize(), cubeData.GetIndicesSize());
        Material cubeMat = Material(glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.5f), 32.0f);
        Model cube = Model(defaultShader, cubeMat, mm, c, buttonTex);
    
        mm = glm::scale(glm::mat4(1.0f), glm::vec3(headHeight/2, headHeight/4, headHeight/2));
        mm = glm::translate(mm, glm::vec3(0, headHeight/2, 0));
        TransformNode hatTransform = TransformNode("Hat transform", mm);
        
        ModelNode hatShape = ModelNode("Cube(hat main)", cube);
    
        glm::mat4 sideScale = glm::scale(glm::mat4(1.0f), glm::vec3(headHeight/10, headHeight/2, headHeight/2));
        mm = glm::translate(sideScale, glm::vec3(headHeight*1.2, headHeight/8, 0));
        TransformNode hatLeftTransform = TransformNode("Left hat transform", mm);
        ModelNode leftHatShape = ModelNode("Cube(Left hat)", cube);
        
        mm = glm::translate(sideScale, glm::vec3(-headHeight*1.2, headHeight/8,0));
        TransformNode hatRightTransform = TransformNode("right hat transform", mm);
        ModelNode rightHatShape = ModelNode("Cube(right hat)", cube);
    
    

        
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
                                face.addChild(eyes);
                                    eyes.addChild(leftEyeTransform);
                                        leftEyeTransform.addChild(leftEyeShape);
                                    eyes.addChild(rightEyeTransform);
                                        rightEyeTransform.addChild(rightEyeShape);

                                face.addChild(nose);
                                    nose.addChild(noseTransform);
                                        noseTransform.addChild(noseShape);
                                face.addChild(mouth);
                                    mouth.addChild(mouthTransform);
                                        mouthTransform.addChild(mouthShape);
                            headTransform.addChild(hat);
                                hat.addChild(hatTransform);
                                    hatTransform.addChild(hatShape);
                                hat.addChild(hatLeftTransform);
                                    hatLeftTransform.addChild(leftHatShape);
                                hat.addChild(hatRightTransform);
                                    hatRightTransform.addChild(rightHatShape);
    
    
    snowmanRoot.update();
    snowmanRoot.print(0, false);
                                
      

        
    // Box
    mm = glm::scale(glm::mat4(1.0f), glm::vec3(bodyHeight+headHeight));
    mm = glm::translate(mm, glm::vec3(-1.0f, 0.5f, 0.0f));
    Model box = Model(defaultShader, cubeMat, mm, c, containerTex, containerSpecTex);
       
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear colour and depth buffer bits

        // Set Projection and View Matrices in Shaders
        //-------------------------------------------
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        // Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
        
        defaultShader.use();
        defaultShader.setMat4("projection", projection);
        defaultShader.setMat4("view", view);
        defaultShader.setVec3("viewPos", camera.Position);
        defaultShader.setVec3("light.position", light.getPosition());
        //defaultShader.setVec3("light.position", camera.Position);
        // light properties
        defaultShader.setVec3("spotLight.ambient", glm::vec3(1.0f));
        defaultShader.setVec3("spotLight.diffuse", glm::vec3(1.0f));
        defaultShader.setVec3("spotLight.specular", glm::vec3(1.0f));
       // spotLight
        defaultShader.setVec3("spotLight.position", light.getPosition());
        defaultShader.setVec3("spotLight.direction", glm::vec3(0,0,0));
        defaultShader.setFloat("spotLight.constant", 1.0f);
        defaultShader.setFloat("spotLight.linear", 0.045);
        defaultShader.setFloat("spotLight.quadratic", 0.0075);
        defaultShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(25.0f)));
        defaultShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(30.0f)));
        
         defaultShader.setVec3("dirLight.position", globalLightPos);
        defaultShader.setVec3("dirLight.ambient", light.getMaterial().getAmbient());
        defaultShader.setVec3("dirLight.diffuse", light.getMaterial().getDiffuse());
        defaultShader.setVec3("dirLight.specular", light.getMaterial().getSpecular());
        
        
        planeShader.use();
        planeShader.setMat4("projection", projection);
        planeShader.setMat4("view", view);
        planeShader.setVec3("viewPos", camera.Position);
        planeShader.setVec3("light.position", globalLightPos);
        // light properties
        planeShader.setVec3("light.ambient", light.getMaterial().getAmbient());
        planeShader.setVec3("light.diffuse", light.getMaterial().getDiffuse());
        planeShader.setVec3("light.specular", light.getMaterial().getSpecular());
        float t = (getElapsedTime() - startTime)*0.1;
        planeShader.setVec2("offset", glm::vec2(t- glm::floor(t), 0.0f));
    
        
        
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        
        
        
        floor.render();
        background.render();
        
        
        lightPostRoot.draw();
        float lightDistanceFromPole = lightPostHeadLength + lightPostWidth + 1.0f;
        if (animate)
            rotateLight(light, lightDistanceFromPole);
        defaultShader.setVec3("spotLight.direction", light.Front);
        light.render();
        
    
        box.render();
        
        snowmanRoot.draw();
        
        
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Dipose of resources now they're no longer needed:
    // -------------------------------------------------------------
    //testCube.dispose();
   // testCube2.dispose();
    sphere.dispose();
    light.dispose();
    // Terminate GLFW, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// Can Cause issues with keys begin registered multiple times, hence the additional `key_callback` function
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
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

// glfw: key callback function, causes event once per press of a key
// -----------------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F && action == GLFW_PRESS) // render wireframe with F
        glPolygonMode(GL_FRONT_AND_BACK, (wireframe = 1 - wireframe) ? GL_LINE : GL_FILL);
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) // render wireframe with F
        
        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR,(userCam = !userCam) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Exit program with escape
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_R && action == GLFW_PRESS) // render wireframe with F
        animate = 1 - animate;
}

// glfw: whenever the mouse moves, this callback is called
// If user is in control of camera, allows camera direction change
// ---------------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// If user is in control of camera, allows user to zoom view using scroll
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (userCam)
        camera.ProcessMouseScroll(yoffset);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// utility function for loading a 2D texture from file

// ---------------------------------------------------
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


float getElapsedTime(){
    return glfwGetTime();
}

void rotateLight(Light &bulb, float bulbDistanceFromPole){
    float elapsedTime = getElapsedTime()-startTime;
    
    float rotateAngle = -elapsedTime* 50; // rotate anti-clockwise
    glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(1, 0, 0));     // Rotate continuouslt
    transform = glm::rotate(transform, glm::radians(rotateAngle), glm::vec3(0, 0, 1));              // Rotate to lie flat
    postHeadRotate.setTransform(transform);
    postHeadRotate.ModelNode::update();     //Update children
    
    float bulbX = bulbDistanceFromPole * glm::sin(glm::radians(elapsedTime*50));
    float bulbZ = bulbDistanceFromPole * + glm::cos(glm::radians(elapsedTime*50));
    bulb.setPosition(postBulbPosition + glm::vec3(bulbX, 0.0, bulbZ));
    std::cout << "bulbPos: " << glm::to_string(glm::normalize(glm::vec3(bulbX, 0, bulbZ))) << std::endl;
    //bulb.setFront(glm::normalize(glm::vec3(bulbX, 0, bulbZ)));
    bulb.setFront(glm::vec3(0.0, 0.0, -1.0f));
   
   // bulb.setFront(camera.Front);
    //std::cout << "front: " << glm::to_string(glm::normalize(front)) << std::endl;
}
