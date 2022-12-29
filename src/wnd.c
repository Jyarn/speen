#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#include "wnd.h"

GLFWwindow* window;
int wndWidth, wndHeight;
char* wndTTL;


/*
    * initialize GLFW and GLAD
*/

bool initGL (int w, int h, char* ttl, int verMajor, int verMinor, GLFWframebuffersizefun CB) {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: GLFW init failed\n");
        return false;
    }


    window = glfwCreateWindow(w, h, ttl, NULL, NULL);

    if (window == NULL) {
        fprintf(stderr, "ERROR: Window Creation failed\n");
        return false;
    }

    wndHeight = h;
    wndWidth = w;
    wndTTL = ttl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, verMajor);
    glfwWindowHint(GLFW_VERSION_MINOR, verMinor);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "ERROR: Failed to openGL core\n");
        return false;
    }

    glViewport(0, 0, wndWidth, wndHeight);
    glfwSetFramebufferSizeCallback(window, CB);

    glfwMaximizeWindow(window);

    return true;
}