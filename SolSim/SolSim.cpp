#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "window.h"


int main()
{
    window current_window;
    current_window.initialise();
    current_window.generateShaders();
    current_window.render();

    return 0;
}
