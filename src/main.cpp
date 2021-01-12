#include <iostream>

#define GLFW_DLL
#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core.h"
#include "state.h"

State state;

void initState()
{
    Keys keys;
    keys.code = GLFW_KEY_UNKNOWN;
    keys.action = GLFW_RELEASE;
    state.keys = keys;

    state.elapsedSeconds = 0;

    ViewPort view;
    view.width = 0;
    view.height = 0;
    view.aspectRatio = 0;

    state.viewPort = view;
}

void glfwErrorCallback(int error, const char* description)
{
    std::cout << "glfwError:" << error << std::endl << description << std::endl;
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Make escape key close the window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    Keys keys;
    keys.code = key;
    keys.action = action;

    state.keys = keys;
}

int main(int argc, char **argv)
{
    std::cout << "Starting up..." << std::endl;

    if (!glfwInit())
    {
        std::cout << "Cannot find GLFW to make a window, bailing out" << std::endl;
        return 1;
    }

    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Render Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Unable to create GLFW window, bailing out" << std::endl;
        return 1;
    }

    glfwSetKeyCallback(window, glfwKeyCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    Core core;
    core.initialize();

    initState();
    double lastTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = width / (float) height;

        state.viewPort.width = width;
        state.viewPort.height = height;
        state.viewPort.aspectRatio = aspectRatio;

        double currentTime = glfwGetTime();
        state.elapsedSeconds = currentTime - lastTime;
        lastTime = currentTime;

        core.update(state);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // We're done, clean up the window manager and exit.
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}