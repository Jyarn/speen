#ifndef __RENDER__
#define __RENDER__

#include <stdbool.h>
#include <glad/glad.h>

// math
//float* transform (float vertices[]);

// openGL
void bindBuffers (float vertices[], unsigned int* VBO, int sz, int strdLen, unsigned int* VAO, int loc, GLenum hint, unsigned int elm[], unsigned int eSz, unsigned int* EBO);
unsigned int linkShaders (const char vertexShader[], const char fragShader[]);

#endif