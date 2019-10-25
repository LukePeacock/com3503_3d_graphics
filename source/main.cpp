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
#include <camera.hpp>
#include <mesh.hpp>
#include <material.hpp>
#include <model.hpp>
#include <glm/gtx/string_cast.hpp>

//Function protos
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);


// global settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 100.0f;

static unsigned char wireframe;         // Allows scene to be rendered in wireframe
static bool userCam = false;            // Gives user control of camera

// camera settings
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;    // Timing ensures consistent framerate independent of hardware


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
    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    
    Shader defaultShader("shaders/default_shader.vs", "shaders/default_shader.frag");
    
    Cube cubeData;
    // load and create a texture
    // -------------------------
    unsigned int containerTex = loadTexture("assets/container.png");
    
    defaultShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    defaultShader.setInt("diffuse", 0);
    std::cout << "VC: " << cubeData.GetVerticesCount();
    std::cout << " VS: " << cubeData.GetVertexSize();
    std::cout << " IC: " << cubeData.GetIndicesCount();
    std::cout << " IS: " << cubeData.GetIndicesSize() << std::endl;
    std::cout << "V: " << cubeData.GetVertices() << std::endl;
    
    unsigned int containerTex2 = loadTexture("assets/container_specular.png");
    Mesh m = Mesh(cubeData.GetVertices(), cubeData.GetIndices(), cubeData.GetVerticesCount(), cubeData.GetIndicesCount(), cubeData.GetVertexSize(), cubeData.GetIndicesSize());
    Model test2 = Model(defaultShader, glm::vec3(0.2f), glm::vec3(0.8f), glm::vec3(0.5f),32.0f,  glm::mat4(1.0f), m, containerTex2);

    
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear colour and depth buffer bits

        // Set Projection and View Matrices in Shader
        //-------------------------------------------
        defaultShader.use();
        // Projection
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
        defaultShader.setMat4("projection", projection);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        defaultShader.setMat4("view", view);
        
 
        // Render Objects
        // ---------------
        test2.render();
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Dipose of resources now they're no longer needed:
    // -------------------------------------------------------------
    test2.dispose();
    
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
        userCam = !userCam;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Exit program with escape
        glfwSetWindowShouldClose(window, true);
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
        GLenum format = GL_RED;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
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
