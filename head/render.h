#ifndef __RENDER__
#define __RENDER__

#include <stdbool.h>
#include <glad/glad.h>

// math
//float* transform (float vertices[]);

// openGL
//void bindBuffers (float vertices[], unsigned int* VBO, int sz, int strdLen, unsigned int* VAO, int loc, GLenum hint, unsigned int elm[], unsigned int eSz, unsigned int* EBO);
void bindVAO (unsigned int* VAO);
void bindVBO (unsigned int* VBO);
void bindEBO (unsigned int* EBO);
void buffWrite (unsigned int VBO, int sz, void* w, GLenum type, GLenum hint);
void genVAttrib (int loc, int vectorSz, GLenum type, int strideLen, int elementSize, int offset);
void unbindBuffers (unsigned int* VAO, unsigned int* VBO, unsigned int* EBO);

unsigned int linkShaders (const char vertexShader[], const char fragShader[]);
void deleteBuff (unsigned int* VBO, unsigned int *VAO, unsigned int* EBO);

#endif