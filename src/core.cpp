#include <GLFW/linmath.h>

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "core.h"

static const char* vertShader =
    "#version 110\n"
    "uniform mat4 mvp;\n"
    "attribute vec3 vCol;\n"
    "attribute vec2 vPos;\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mvp * vec4(vPos, 0.0, 1.0);\n"
    "    color = vCol;\n"
    "}\n";

static const char* fragShader =
    "#version 110\n"
    "varying vec3 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(color, 1.0);\n"
    "}\n";

void Core::initialize()
{
    this->time = 0;

    this->vertices[0] = { -0.6f, -0.4f, 1.0f, 0.0f, 0.0f };
    this->vertices[1] = { 0.6f, -0.4f, 0.0f, 1.0f, 0.0f };
    this->vertices[2] = { 0.0f,  0.6f, 0.0f, 0.0f, 1.0f };

    GLint success;
    GLchar infoLog[512];

    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
 
    this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vertexShader, 1, &vertShader, NULL);
    glCompileShader(this->vertexShader);

    glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->vertexShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader failed to compile: \n" << infoLog << std::endl;
    }
 
    this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->fragmentShader, 1, &fragShader, NULL);
    glCompileShader(this->fragmentShader);

    glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(this->fragmentShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader failed to compile: \n" << infoLog << std::endl;
    }
 
    this->program = glCreateProgram();
    glAttachShader(this->program, this->vertexShader);
    glAttachShader(this->program, this->fragmentShader);
    glLinkProgram(this->program);

    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        std::cout << "ERROR: Failed to link shader program: \n" << infoLog << std::endl;
    }
 
    this->mvpLocation = glGetUniformLocation(this->program, "mvp");
    this->vPosLocation = glGetAttribLocation(this->program, "vPos");
    this->vColorLocation = glGetAttribLocation(this->program, "vCol");
 
    glEnableVertexAttribArray(this->vPosLocation);
    glVertexAttribPointer(this->vPosLocation, 2, GL_FLOAT, GL_FALSE,
                          sizeof(this->vertices[0]), (void*) 0);
    glEnableVertexAttribArray(this->vColorLocation);
    glVertexAttribPointer(this->vColorLocation, 3, GL_FLOAT, GL_FALSE,
                          sizeof(this->vertices[0]), (void*) (sizeof(float) * 2));
}

void Core::update(State state)
{
    mat4x4 m, p, mvp;

    this->time += (float) state.elapsedSeconds;

    glViewport(0, 0, state.viewPort.width, state.viewPort.height);

    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, this->time);
    mat4x4_ortho(
        p,
        -state.viewPort.aspectRatio,
        state.viewPort.aspectRatio,
        -1.0f, 1.0f, 1.0f, -1.0f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(this->program);
    glUniformMatrix4fv(this->mvpLocation, 1, GL_FALSE, (const GLfloat*) mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}