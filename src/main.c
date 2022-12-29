#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <pthread.h>

#include "wnd.h"
#include "const.h"
#include "evt.h"
#include "render.h"

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "out vec4 vColor;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "   vColor = vec4(aPos, aPos.x*aPos.y, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColour;\n"
    "in vec4 vColor;\n"
    "void main () {\n"
    "FragColour = vColor;\n"
    "}\0";

void framebuffer_size_callback (GLFWwindow* wnd, int w, int h) {
    glViewport(0, 0, w, h);

    wndWidth = w;
    wndHeight = h;

    fprintf(stdout, "Resized view port: %dx%d\n", w, h);
}

int main () {
    initGL(1920, 1080, "bum bumn", 4, 6, framebuffer_size_callback);

    // start event handler
    pthread_t thr;
    pthread_create(&thr, NULL, evtStart, window);


    float vertices[] = {
         0.5,  0.5,
         0.5, -0.5,
        -0.5, -0.5,
        -0.5,  0.5,
    };

    unsigned int index[] = {
        0, 1, 2,
        3, 2, 0
    };

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    bindBuffers(vertices, &VBO,
                sizeof(vertices), 2, &VAO,
                0, GL_STATIC_DRAW,
                index, sizeof(index), &EBO
    );

    unsigned int shaderProgram = linkShaders(vertexShaderSource, fragmentShaderSource);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}