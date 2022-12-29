#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <glad/glad.h>

#define LOGSIZE 512

unsigned int compileShader (const char* in, char log[LOGSIZE], GLuint type) {
    unsigned int ret = glCreateShader(type);
    glShaderSource(ret, 1, &in, NULL);
    glCompileShader(ret);

    int succ;
    log[0] = 0;
    glGetShaderiv(ret, GL_COMPILE_STATUS, &succ);

    if (!succ) {
        glGetShaderInfoLog(ret, LOGSIZE, NULL, log);
        return 0;
    }

    return ret;
}

unsigned int linkShaders (const char vertexShader[], const char fragShader[]) {
    char* log = malloc(512*sizeof(LOGSIZE));

    // compile vertex shader
    unsigned int v = compileShader(vertexShader, log, GL_VERTEX_SHADER);
    if (log[0]) {
        fprintf(stderr, "ERROR: Vertex Shader Compilation failed\n%s\n", log);
        return 0;
    }

    // compile fragment shader
    unsigned int f = compileShader(fragShader, log, GL_FRAGMENT_SHADER);
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
}