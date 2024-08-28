#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Graphics", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "glew didn't init";
        return 1;
    }
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(ErrorMessage, 0);
    {
        float positions[] = {
            -0.5, -0.5, // 0
             0.5, -0.5, // 1
             0.5,  0.5, // 2
            -0.5,  0.5, // 3 
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        
        VertexArray va;
        VertexBuffer vb(positions, sizeof(positions));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        IndexBuffer ib(indices, 6);


        Shader shader("res/shaders/Basic.shader");
        shader.Bind();


        float rgb[] = { 0.0, 0.0, 0.1 }, increments[] = { 0.05, 0.02, 0.05 };

        //uniform input
        shader.SetUniform4f("u_Color", rgb[0], rgb[1], rgb[2], 1.0);

        va.Unbind();
        ib.Unbind();
        vb.Unbind();
        shader.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            shader.SetUniform4f("u_Color", rgb[0], rgb[1], rgb[2], 1.0);
            va.Bind();
            //glBindVertexArray(vao); // bind vertex array
            shader.Bind();

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            for (int i = 0; i < 3; i++) {
                if (rgb[i] > 1.0) increments[i] *= -1;
                else if (rgb[i] <= 0.0) increments[i] = (i == 0) ? 0.02 : (i == 2) ? 0.05 : 0.02;
                rgb[i] += increments[i];
            }

            //glDrawArrays(GL_TRIANGLES, 0, 3); // draws whatever buffer was bound last

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}