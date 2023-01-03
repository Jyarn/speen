#ifndef __CONSTH__
#define __CONSTH__

#include <GLFW/glfw3.h>

#define ANGCHNG 1
#define MOVEX 0.01f
#define MOVEY 0.01f

#define MAX(a, b) a < b ? b : a

extern int ang;
extern float objX;
extern float objY;

extern GLFWwindow* window;
extern int wndWidth, wndHeight;
extern char* wndTTL;

#endif