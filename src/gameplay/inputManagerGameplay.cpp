#include "../../include/gameplay/inputManagerGameplay.h"

InputManagerGameplay::InputManagerGameplay() :
    input(Vector2i(0, 0))
{
    std::cout << "InputManagerGameplay initialisé" << std::endl;
}

InputManagerGameplay::~InputManagerGameplay()
{
    std::cout << "InputManagerGameplay supprimé" << std::endl;
}

void InputManagerGameplay::update(GLFWwindow * window)
{
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
    {
        input.x = 0;
        input.y = -1;
    }
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
    {
        input.x = 0;
        input.y = 1;
    }
    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
    {
        input.x = -1;
        input.y = 0;
    }
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
    {
        input.x = 1;
        input.y = 0;
    }
}

Vector2i InputManagerGameplay::getInput()
{
    return input;
}