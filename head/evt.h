#ifndef __EVT__
#define __EVT__

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef void (*eventHandle)(GLFWwindow*);

typedef struct {
    int         key;
    eventHandle hnd;
} Event;

void* evtStart (void* wnd);

#endif