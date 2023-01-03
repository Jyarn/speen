#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "evt.h"
#include "const.h"

int ang = 0;
float objX = 0;
float objY = 0;

void moveRight (GLFWwindow* wnd) {
    objX += 0.0001f;
}

void moveLeft (GLFWwindow* wnd) {
    objX -= 0.0001f;
}

void moveUp (GLFWwindow* wnd) {
    objY += 0.0001f;
}

void moveDown (GLFWwindow* wnd) {
    objY -= 0.0001f;
}

void clockRight (GLFWwindow* wnd) {
    ang += ANGCHNG;
    ang = ang % 360;
}

void clockLeft (GLFWwindow* wnd) {
    ang -= ANGCHNG;
    ang = ang % 360;
}

void handleGLError () {
    switch (glGetError()) {
        case GL_INVALID_ENUM:
            fprintf(stderr, "ERROR (GL): Invalid Enum\n");
            break;
        case GL_INVALID_VALUE:
            fprintf(stderr, "ERROR (GL): Invalid Value\n");
            break;
        case GL_INVALID_OPERATION:
            fprintf(stderr, "ERROR (GL): Invalid Operation\n");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            fprintf(stderr, "ERROR (GL): Invalid Framebuffer Operation\n");
            break;
        case GL_OUT_OF_MEMORY:
            fprintf(stderr, "ERROR (GL): Out of memory\n");
            break;
        case GL_STACK_UNDERFLOW:
            fprintf(stderr, "ERROR (GL): Stack underflow\n");
            break;
        case GL_STACK_OVERFLOW:
            fprintf(stderr, "ERROR (GL): Stack underflow\n");
            break;
        }
}

void closeWindow (GLFWwindow* wnd) {
    glfwSetWindowShouldClose((GLFWwindow* )wnd, true);
}

void* evtStart (void* wnd) {
    // start event handler
    Event events[] = {
        {
            GLFW_KEY_ESCAPE,
            closeWindow
        },
        {
            GLFW_KEY_LEFT,
            clockLeft
        },
        {
            GLFW_KEY_RIGHT,
            clockRight
        },
        {
            GLFW_KEY_W,
            moveUp
        },
        {
            GLFW_KEY_A,
            moveLeft
        },
        {
            GLFW_KEY_D,
            moveRight
        },
        {
            GLFW_KEY_S,
            moveDown
        },
        {0, NULL}
    };

    while (!glfwWindowShouldClose(wnd)) {
        glfwPollEvents();

        for (int i = 0; events[i].key != 0 ; i++) {
            if  (glfwGetKey(wnd, events[i].key) == GLFW_PRESS) { events[i].hnd(wnd); }
            handleGLError();
        }
    }

    return NULL;
}