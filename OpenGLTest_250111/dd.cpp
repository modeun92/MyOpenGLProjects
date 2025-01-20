#pragma once
#include "GlewfwConfig.cpp"
#include "GlmConfig.cpp"
#include "GlmMvpShader.h"

#include "CubeDataConfig.cpp"
#include "StbImageConfig.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    std::cout << "Failed to initialize GLAD" << std::endl;
    //    return -1;
    //}

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    GlmMvpShader l_OurShader("resources/shaders/my3d.vs", "resources/shaders/tex2d.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    unsigned int VBO, VAO, EBO;
    cube::BindObjects(VBO, VAO, EBO);

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2;
    cube::GenerateTexture("resources/images/container1.jpg", texture1);
    cube::GenerateTexture("resources/images/container2.jpg", texture2);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    l_OurShader.Use(); // don't forget to activate/use the shader before setting uniforms!

    // either set it manually like so:
    //glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), texture1);
    // or set it via the texture class
    // 
    l_OurShader.SetInt("texture1", 0);
    l_OurShader.SetInt("texture2", 1);
    // bind textures on corresponding texture units

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1); // texture1 = 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2); // texture2 = 2

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, 
        glm::radians(-55.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));
    
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view,
        glm::vec3(0.0f, 0.0f, -3.0f));
    
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f);

    l_OurShader.SetMvp(model, view, projection);

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
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render container
        l_OurShader.Use();
        cube::RotateModelByTime(model);
        l_OurShader.SetModel(model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cube::DeleteObjects(VBO, VAO, EBO);

    l_OurShader.Dispose();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
static void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}