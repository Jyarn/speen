#ifndef __RENDER__
#define __RENDER__

#include <stdbool.h>
#include <glad/glad.h>

#define VERTSHADER_EXTERN (char)0x01
#define FRAGSHADER_EXTERN (char)0x02

// math
//float* transform (float vertices[]);

// openGL
//void bindBuffers (float vertices[], unsigned int* VBO, int sz, int strdLen, unsigned int* VAO, int loc, GLenum hint, unsigned int elm[], unsigned int eSz, unsigned int* EBO);
void bindVAO (unsigned int* VAO);
void bindVBO (unsigned int* VBO);
void bindEBO (unsigned int* EBO);
void buffWrite (unsigned int VBO, int sz, void* w, GLenum type, GLenum hint);
void genVAttrib (int loc, int vectorSz, GLenum type, int strideLen, int elementSize, int offset);
void unbindBuffers ();

unsigned int linkShaders (char vertexShader[], char fragShader[], char compileAsFile);
void deleteBuff (unsigned int* VBO, unsigned int *VAO, unsigned int* EBO);

#endif