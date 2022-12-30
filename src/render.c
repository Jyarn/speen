#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "render.h"

#define LOGSIZE 512

char* readFile (char* path) {
    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "ERROR: Unable to open file\n");
        return NULL;
    }

    struct stat i;
    stat(path, &i);

    char* ret = malloc((i.st_size+1)*sizeof(char));

    read(fd, ret, i.st_size);
    ret[i.st_size] = '\0';
    return ret;
}

unsigned int compileShader (char* in, char log[LOGSIZE], GLuint type, bool compileAsFile) {
    const char* src = compileAsFile ? readFile(in) : in;

    unsigned int ret = glCreateShader(type);
    glShaderSource(ret, 1, &src, NULL);
    glCompileShader(ret);

    int succ;
    log[0] = 0;
    glGetShaderiv(ret, GL_COMPILE_STATUS, &succ);

    if (!succ) {
        glGetShaderInfoLog(ret, LOGSIZE, NULL, log);
        return 0;
    }

    if (compileAsFile) {
        free((void *)src);
    }

    return ret;
}

unsigned int linkShaders (char vertexShader[], char fragShader[], char compileAsFile) {
    char* log = malloc(512*sizeof(LOGSIZE));

    // compile vertex shader
    unsigned int v = compileShader(vertexShader, log, GL_VERTEX_SHADER, (bool)(compileAsFile & VERTSHADER_EXTERN));
    if (log[0]) {
        fprintf(stderr, "ERROR: Vertex Shader Compilation failed\n%s\n", log);
        return 0;
    }

    // compile fragment shader
    unsigned int f = compileShader(fragShader, log, GL_FRAGMENT_SHADER, (bool)(compileAsFile & FRAGSHADER_EXTERN));
    if (log[0]) {
        fprintf(stderr, "ERROR: Fragment Shader Compilation failed\n%s\n", log);
        return 0;
    }

    // create program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, v);
    glAttachShader(shaderProgram, f);
    glLinkProgram(shaderProgram);

    int succ;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succ);
    if (!succ) {
        glGetProgramInfoLog(shaderProgram, LOGSIZE, NULL, log);
        fprintf(stderr, "ERROR: glProgram Linking failed\n%s\n", log);
        return 0;
    }

    glDeleteShader(v);
    glDeleteShader(f);
    free(log);

    return shaderProgram;
}

void bindVAO (unsigned int* VAO) {
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}

void bindVBO (unsigned int* VBO) {
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
}

void bindEBO (unsigned int* EBO) {
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
}

void buffWrite (unsigned int VBO, int sz, void* w, GLenum type, GLenum hint) {
    glBufferData(type, sz, w, hint); // oh boy do I love 1 line abstractions
}

void genVAttrib (int loc, int vectorSz, GLenum type, int strideLen, int elementSize, int offset) {
    glVertexAttribPointer(loc, vectorSz, type, GL_FALSE, strideLen*elementSize, (void *)((long unsigned int)offset*elementSize));
    glEnableVertexAttribArray(loc);
}

void unbindBuffers () {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*
void bindBuffers (float vertices[], unsigned int* VBO, int sz, int strdLen, unsigned int* VAO, int loc, GLenum hint,
unsigned int elm[], unsigned int eSz, unsigned int* EBO) {
    // initialize VAO
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);

    // initialize VBO
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sz, vertices, hint);

    // initialize EBO
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eSz, elm, hint);

    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, strdLen*sizeof(float), NULL);
    glEnableVertexAttribArray(loc);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}*/

void deleteBuff (unsigned int* VBO, unsigned int *VAO, unsigned int* EBO) {
    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, EBO);
}