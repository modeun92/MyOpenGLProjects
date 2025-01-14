//#include <iostream>
////#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "texture.cpp"
//#include "Shader.h"
//int main1(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//    //Shader ourShader("resources/tex2d.vs", "resources/tex2d.fs");
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        //ourShader.use();
//        //ourShader.setFloat("someUniform", 1.0f);
//
//        //glBindTexture(GL_TEXTURE_2D, texture);
//        //glBindVertexArray(VAO);
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    //glDeleteVertexArrays(1, &VAO);
//    //glDeleteBuffers(1, &VBO);
//    //glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//    return 0;
//}