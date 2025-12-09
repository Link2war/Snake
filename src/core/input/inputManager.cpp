#include "../../../include/core/input/inputManager.h"

InputManager::InputManager() :
    input(Vector2i(0, 0))
{
    std::cout << "InputManager initialisé" << std::endl;
}

InputManager::~InputManager()
{
    std::cout << "InputManager supprimé" << std::endl;
}

void InputManager::update(GLFWwindow * window)
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

Vector2i InputManager::getInput()
{
    return input;
}