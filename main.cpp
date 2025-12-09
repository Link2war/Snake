#include <BBOP/Graphics.h>

#include "include/core/gameLoop.h"


int main()
{
    std::cout << "-- Initialisation de la Partie" << std::endl;
    
    //creation de la fenêtre glfw
    GLFWwindow * window;

    //initialisation de la lib
    bbopInit(1280,720,"Snake",window);
    glfwMaximizeWindow(window);
    
    GameLoop gameLoop(window);

    //main while loop
    gameLoop.run();

    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << std::endl;
    std::cout << "-- Partie terminée" << std::endl;

    return 0;
}