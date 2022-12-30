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
         200,  200,
         200,    0,
           0,    0,
           0,  200,
    };

    unsigned int index[] = {
        0, 1, 2,
        3, 2, 0
    };

    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    bindVAO(&VAO);
    bindVBO(&VBO);
    bindEBO(&EBO);

    buffWrite(VBO, sizeof(vertices), vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    buffWrite(EBO, sizeof(index), index, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    genVAttrib(0, 2, GL_FLOAT, 2, sizeof(float), 0);
    unbindBuffers();

    unsigned int shaderProgram = linkShaders("./shaders/Vertex.vert", "./shaders/Frag1.frag", VERTSHADER_EXTERN | FRAGSHADER_EXTERN);
    int scPtr = glGetUniformLocation(shaderProgram, "screenCoord");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform2f(scPtr, wndWidth, wndHeight);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    deleteBuff(&VBO, &VAO, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    pthread_join(thr, NULL);
}