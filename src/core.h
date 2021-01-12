#include <glad/glad.h>

#include "state.h"

#ifndef _CORE_
#define _CORE_

struct Vertex
{
    float x, y;
    float r, g, b;
};

class Core {
    public:
        void initialize();
        void update(State state);
    private:
        Vertex vertices[3];

        GLuint program;
        GLuint vertexShader;
        GLuint fragmentShader;

        GLuint vertexBuffer;
        GLint mvpLocation;
        GLint vPosLocation;
        GLint vColorLocation;

        float time;
};

#endif /* _CORE_ */