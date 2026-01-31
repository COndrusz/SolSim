#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"
#include "Window.h"
#include "Planet.h"


int main()
{
    window current_window;
    current_window.initialise();
    current_window.generateShaders();
    current_window.render();

    Planet earth;
    Planet Mars(1e7, 1e7, 1e3, 1e3, 400, 2e9);

    std::cout << Mars.get_position().first << " " << Mars.get_position().second << std::endl;
    std::cout << Mars.get_mass() << std::endl;
    std::cout << earth.get_position().first << earth.get_position().second << std::endl;
    earth.update_position(10, new std::pair<double, double>[1] { Mars.get_position() }, new float[1] {Mars.get_mass()});
    std::cout << earth.get_position().first << earth.get_position().second << std::endl;

    return 0;
}
