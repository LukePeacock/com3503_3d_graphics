//
//  main.cpp
//  COM3503
//
//  Created by Luke on 24/10/2019.
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

//Function protos
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 100.0f;

static unsigned char wireframe;         // Allows scene to be rendered in wireframe

// Self-explanatoiy
int main()
{
    // initialize and configure GLFW
    // -----------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
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
    
    // Bind the key listener for input
    // Prevents multiple actions from one key press
    glfwSetKeyCallback(window, key_callback);
   // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//    float vertices[] = {
//        // positions          // texture coords
//         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
//    };
//    unsigned int indices[] = {
//        0, 1, 3, // first triangle
//        1, 2, 3  // second triangle
//    };
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
    float vertices[] = {
        //Coords                Normals     Tex
        -0.5f, -0.5f, -0.5f,  -1, 0, 0,  0.0f, 0.0f,  // 0      //left bottom back
        -0.5f, -0.5f,  0.5f,  -1, 0, 0,  1.0f, 0.0f,  // 1      //left bottom front
        -0.5f,  0.5f, -0.5f,  -1, 0, 0,  0.0f, 1.0f,  // 2      //left top back
        -0.5f,  0.5f,  0.5f,  -1, 0, 0,  1.0f, 1.0f,  // 3      //left top front
         0.5f, -0.5f, -0.5f,   1, 0, 0,  1.0f, 0.0f,  // 4      //right bottom back
         0.5f, -0.5f,  0.5f,   1, 0, 0,  0.0f, 0.0f,  // 5      //right bottom front
         0.5f,  0.5f, -0.5f,   1, 0, 0,  1.0f, 1.0f,  // 6      //right top back
         0.5f,  0.5f,  0.5f,   1, 0, 0,  0.0f, 1.0f,  // 7      //right top front

        -0.5f, -0.5f, -0.5f,  0,0,-1,  1.0f, 0.0f,  // 8        //left bottom back
        -0.5f, -0.5f,  0.5f,  0,0,1,   0.0f, 0.0f,  // 9        //left bottom front
        -0.5f,  0.5f, -0.5f,  0,0,-1,  1.0f, 1.0f,  // 10       //left top back
        -0.5f,  0.5f,  0.5f,  0,0,1,   0.0f, 1.0f,  // 11       //left top front
         0.5f, -0.5f, -0.5f,  0,0,-1,  0.0f, 0.0f,  // 12       //right bottom back
         0.5f, -0.5f,  0.5f,  0,0,1,   1.0f, 0.0f,  // 13       //right bottom front
         0.5f,  0.5f, -0.5f,  0,0,-1,  0.0f, 1.0f,  // 14       //right top back
         0.5f,  0.5f,  0.5f,  0,0,1,   1.0f, 1.0f,  // 15       //right top front

        -0.5f, -0.5f, -0.5f,  0,-1,0,  0.0f, 0.0f,  // 16       //left bottom back
        -0.5f, -0.5f,  0.5f,  0,-1,0,  0.0f, 1.0f,  // 17       //left bottom front
        -0.5f,  0.5f, -0.5f,  0,1,0,   0.0f, 1.0f,  // 18       //left top back
        -0.5f,  0.5f,  0.5f,  0,1,0,   0.0f, 0.0f,  // 19       //left top front
         0.5f, -0.5f, -0.5f,  0,-1,0,  1.0f, 0.0f,  // 20       //right bottom back
         0.5f, -0.5f,  0.5f,  0,-1,0,  1.0f, 1.0f,  // 21       //right bottom front
         0.5f,  0.5f, -0.5f,  0,1,0,   1.0f, 1.0f,  // 22       //right top back
         0.5f,  0.5f,  0.5f,  0,1,0,   1.0f, 0.0f   // 23       //right top front
    };
    unsigned int indices[] = {  // note that we start from 0!
        0,1,3, // x -ve
        3,2,0, // x -ve
        4,6,7, // x +ve
        7,5,4, // x +ve
        9,13,15, // z +ve
        15,11,9, // z +ve
        8,10,14, // z -ve
        14,12,8, // z -ve
        16,20,21, // y -ve
        21,17,16, // y -ve
        23,22,18, // y +ve
        18,19,23  // y +ve
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //Coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   // Normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Tex attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture
    // -------------------------
    unsigned int containerTex = loadTexture("assets/container.png");
    defaultShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    defaultShader.setInt("diffuse", 0);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear colour and depth buffer bits

        
       
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTex);
        // draw our first triangle
        defaultShader.use();
        
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);
        defaultShader.setMat4("model", model);
        defaultShader.setMat4("view", view);
        defaultShader.setMat4("projection", projection);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources now they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
   // glDeleteBuffers(1, &EBO);

    // Terminate GLFW, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: key callback function, causes event once per press.
// ---------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F && action == GLFW_PRESS) // render wireframe with F
        glPolygonMode(GL_FRONT_AND_BACK, (wireframe = 1 - wireframe) ? GL_LINE : GL_FILL);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // Exit program with escape
        glfwSetWindowShouldClose(window, true);
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
